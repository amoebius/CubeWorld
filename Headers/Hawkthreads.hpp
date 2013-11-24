//-----------------------------
// James Payor - Evolution RTS
// Created 10/05/13
//-----------------------------
//
//----------------
// Hawkthreads.hpp |
//-------------------------------------------
// Declares the interface required to use the
// 'Hawkthreads' library for multithreading.
//-------------------------------------------

#ifndef HAWKTHREADS_HPP
#define HAWKTHREADS_HPP

// Requred headers:
#include <cstddef>
#include <../Include/HT/hawkthreads.h>


// Wrapper functions to provide a nicer interface:
namespace HT {

	// Wrap thread functions:
	namespace Thread {

		// Priority constants:
		namespace Priority {
			const int Lowest = HT_THREAD_PRIORITY_LOWEST,
					  Low = HT_THREAD_PRIORITY_LOW,
					  Normal = HT_THREAD_PRIORITY_NORMAL,
					  High = HT_THREAD_PRIORITY_HIGH,
					  Highest = HT_THREAD_PRIORITY_HIGHEST;
		}

		// Nicer threading interface around the other functions:
		inline HThreadID Create(HThreadFunc func, void *data, int joinable = 1) {
			return htThreadCreate(func, data, joinable);
		}
		inline bool Join(HThreadID threadID, void* &retval) {
			return htThreadJoin(threadID, &retval);
		}
		inline bool Join(HThreadID threadID) {
			return htThreadJoin(threadID, NULL);
		}
		inline HThreadID Self() {
			return htThreadSelf();
		}
		inline void Sleep(int milliseconds) {
			htThreadSleep(milliseconds);
		}
		inline void Yield() {
			htThreadYield();
		}
		inline int GetPriority() {
			return htThreadGetPriority();
		}
		inline bool SetPriority(int priority = Priority::Normal) {
			return htThreadSetPriority(priority) == 0;
		}
	}


	// Wrap mutex functions:
	namespace Mutex {
		inline bool Init(HTmutex &mutex) {
			return htMutexInit(&mutex) == 0;
		}
		inline bool Destroy(HTmutex &mutex) {
			return htMutexDestroy(&mutex) == 0;
		}
		inline bool Lock(const HTmutex &mutex) {
			return htMutexLock(&(HTmutex &)mutex) == 0;
		}
		inline bool Unlock(const HTmutex &mutex) {
			return htMutexUnlock(&(HTmutex &)mutex) == 0;
		}
	}

	// Wrap condition functions:
	namespace Cond {
		inline bool Init(HTcond &cond) {
			return htCondInit(&cond) == 0;
		}
		inline bool Destroy(HTcond &cond) {
			return htCondDestroy(&cond) == 0;
		}
		inline bool Wait(HTcond &cond, int timeout) {
			return htCondWait(&cond, timeout) == 0;
		}
		inline bool Signal(HTcond &cond) {
			return htCondSignal(&cond) == 0;
		}
		inline bool Broadcast(HTcond &cond) {
			return htCondBroadcast(&cond) == 0;
		}
	}

}

#endif
