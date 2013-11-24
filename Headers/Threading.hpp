//-----------------------------
// James Payor - Evolution RTS
// Created 10/05/13
//-----------------------------
//
//----------------
// Threading.hpp |
//-------------------------------------------
// Declares interface functions for the
// support of cross-platform multithreading
// of game functions.
//-------------------------------------------

#ifndef THREADING_H
#define THREADING_H

// Required declarations for Hawkthreads (cross-platform multithreading library):
#include <../Headers/Hawkthreads.hpp>

// Useful for marking void return values:
typedef int threadvoid;

// Virtual class that allows objects to easily inherit basic threading support:
class Thread {
public:
	HThreadID threadID;
	int priority;
	inline HThreadID self() {
		return threadID;
	}
	inline void sleep(int milliseconds) {
		HT::Thread::Sleep(milliseconds);
	}
	inline void yield() {
		HT::Thread::Yield();
	}
	inline int getPriority() {
		return priority;
	}
	inline void setPriority(int priority) {
		this->priority = priority;
		HT::Thread::SetPriority(priority);
	}
};

namespace Threading {

	// Declare the existence of the "Threaded" class:
	template<class FunctorT> class Threaded;


	// Define the worker class, "ThreadRunner", responsible for coordinating the results of threads:
	template <class FunctorT>
	class ThreadRunner : virtual Thread, FunctorT {
		friend class Thread;

	private:
		// Record the result type:
		typedef typeof((*((FunctorT*)0))()) ResultT;

		// Whether the thread is currently running or not:
		bool running;
		// The result of the threaded functor:
		ResultT result;

		friend class Threaded<FunctorT>;
		// Whether the result is still required or not:
		bool required;

	public:
		// Initialise the thread:
		ThreadRunner(const FunctorT &functor, int priority = HT::Thread::Priority::Normal) : FunctorT(functor), required(true) {
			running = true;
			threadID = HT::Thread::Create(run, this);
			setPriority(priority);
		}

		// A simple helper definition:
		inline bool finished() {
			return !running;
		}

		// To return the result, join with the thread, then grab the result:
		ResultT operator()() {
			HT::Thread::Join(threadID);
			return result;
		}

	private:
		// Given a void* to a ThreadRunner object, runs a thread:
		static void *run(void *object) {
			// Convert the void*:
			ThreadRunner<FunctorT> *obj = static_cast<ThreadRunner<FunctorT>*>(object);

			// Run the thread:
			obj->running = true;
			obj->result = obj->FunctorT::operator()();
			obj->running = false;

			// Delete the object if the result isn't required:
			if(!obj->required) delete obj;

			return NULL;
		}
	};

	// Declares the threaded class, which stores a reference to the working ThreadRunner, so that the thread can continue should this
	// object be destroyed:
	template<class FunctorT>
	class Threaded {
		friend class ThreadRunner<FunctorT>;

	private:
		// The actual ThreadRunner object handling the thread:
		ThreadRunner<FunctorT> *thread;

	public:
		// Initialise the thread runner on instantiation:
		Threaded(FunctorT functor, int priority = HT::Thread::Priority::Normal) : thread(new ThreadRunner<FunctorT>(functor,priority)) {}

		// Get the functor's return type:
		typedef typeof((*((FunctorT*)0))()) ResultT;

		// Methods for getting the result, as if this were a functor:
		inline ResultT operator()() {
			return thread->operator()();
		}
		inline ResultT join() {
			return thread->operator()();
		}

		// On destruction:
		~Threaded() {
			// If the thread is finished, we can destroy it, otherwise we mark it as not required:
			if(thread->finished()) {
				delete thread;
			} else {
				thread->required = false;
			}
		}

		// Helper function:
		inline bool finished() {
			return thread->finished();
		}
	};

	// A simple functor that wraps void functions to be able to be run as threads:
	class FunctionWrapper {
	private:
		typedef void FuncT(void);
		// Pointer to the wrapped function:
		FuncT *func;
	public:
		FunctionWrapper(FuncT *func) : func(func) {}
		// Calling the functor simply calls the wrapped function:
		inline int operator()() {
			(*func)();
			return 0;
		}
	};


	// A helper function that simply creates a threaded version of the given functor:
	template<typename FunctorT>
	static inline Threaded<FunctorT> Create(FunctorT functor, int priority = HT::Thread::Priority::Normal) {
		return Threaded<FunctorT>(functor, priority);
	}

	// A specialisation of the helper function that builds a thread from a void function:
	static inline Threaded<FunctionWrapper> Create(void (*func)(void), int priority = HT::Thread::Priority::Normal) {
		return Threaded<FunctionWrapper>(FunctionWrapper(func), priority);
	}

	// Helpful type definition:
	typedef Threaded<FunctionWrapper> ThreadedFunc;



	// A wrapper around Hawkthreads' mutex interface:
	class Mutex {
	private:
		HTmutex mutex;
	public:
		// Initialise mutex on creation, destroy on deletion:
		Mutex() {
			HT::Mutex::Init(mutex);
		}
		~Mutex() {
			HT::Mutex::Destroy(mutex);
		}
		// Allow locking and unlocking of the mutex:
		inline bool Lock() const {
			return HT::Mutex::Lock(mutex);
		}
		inline bool Unlock() const {
			return HT::Mutex::Unlock(mutex);
		}
	};


	// A wrapper around Hawkthreads' condition interface:
	class Cond {
	private:
		HTcond cond;
	public:
		// Initialise condition on creation, destroy on deletion:
		Cond() {
			HT::Cond::Init(cond);
		}
		~Cond() {
			HT::Cond::Destroy(cond);
		}
		// Allow waiting for signals and sending signals:
		inline bool Wait(int timeout=0) {
			return HT::Cond::Wait(cond, timeout);
		}
		inline bool Signal() {
			return HT::Cond::Signal(cond);
		}
		inline bool Broadcast() {
			return HT::Cond::Broadcast(cond);
		}
	};

}


#endif
