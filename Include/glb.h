// Function declaration and implementing for GLBASIC



#ifndef _GLBASIC_MAIN_H
#define _GLBASIC_MAIN_H

// maximum array size
#ifndef _GLB_MAX_ARAY
	#define _GLB_MAX_ARAY 4
#endif

/*
#ifndef WIN32
	#undef DECLARE_HANDLE
	#define DECLARE_HANDLE(a)	typedef unsigned long a;
	#ifndef LINUX_LIB
		#define WIN32_LEAN_AND_MEAN
		#ifndef APIENTRY
			#define APIENTRY
		#endif
		typedef const char* LPCTSTR;
		typedef char* LPSTR;
		#define NULL (0L)
		#define DWORD	unsigned long
		#define LPWSTR	short*
		#define LPCWSTR	const short*
		typedef unsigned char   BYTE;
		typedef unsigned short  WORD;
		typedef long		LONG;
		DECLARE_HANDLE(HANDLE);
		DECLARE_HANDLE(HWND);
		typedef HANDLE HINSTANCE;
		extern "C" { int APIENTRY WinMain(HINSTANCE,HINSTANCE,LPSTR,int);}
		#define __stdcall
		#define TRUE	1
		#define	FALSE	0
		typedef DWORD   COLORREF;
		#ifndef MAX_PATH
			#define MAX_PATH 260
		#endif

	// #include "../../gpc_temp.cpp"
	#endif
#endif
*/


#define _NO_OLDNAMES // Allow _yn() but not yn() in Math.h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ifndef windows.h
#ifndef DECLARE_HANDLE
	#define WIN32_LEAN_AND_MEAN

	#ifndef _MSC_VER
		#ifndef __stdcall
			#define __stdcall __attribute__ ((stdcall))
		#endif
	#endif
	#define APIENTRY	__stdcall
	#ifdef UNICODE
	typedef short TCHAR;
	#else
	typedef char TCHAR;
	#endif
	typedef const TCHAR* LPCTSTR;
	typedef TCHAR* LPSTR;
	#ifndef NULL
		#define NULL (0L)
	#endif
	#define DWORD	unsigned long
	#define LPWSTR	short*
	#define LPCWSTR	const short*
	typedef unsigned char   BYTE;
	typedef unsigned short  WORD;

	typedef void* HANDLE;
	#define DECLARE_HANDLE(name) typedef struct name##__{int i;}*name
	DECLARE_HANDLE(HINSTANCE);
	DECLARE_HANDLE(HWND);


	#define TRUE	1
	#define	FALSE	0
	typedef DWORD   COLORREF;
#endif

// DGInt / DGNat
typedef			int				DGNat;

#if defined(__arm__) || defined(TARGET_OS_IPHONE)
	typedef		float			DGInt;
#else
	typedef		double			DGInt;
#endif

#ifdef RGB
	#undef RGB
#endif

// why was that a function?
#define RGB(r, g, b) ((DGNat)((unsigned long)(((unsigned char)(DGNat)(r)|((unsigned short)((unsigned char)(DGNat)(g))<<8))|(((unsigned long)(unsigned char)(DGNat)(b))<<16))))


#define	CMP_OK					(0x00000)
#define	CMP_FOR_WITHOUT_NEXT	(0x00001)
#define	CMP_SYNTAX_ERROR		(0x00002)
#define CMP_NO_FILE				(0x00003)
#define CMP_WRONG_ARGUMENT		(0x00004)
#define CMP_STRING_TOO_LONG		(0x00005)
#define CMP_DIVISION_BY_ZERO	(0x00006)
#define CMP_OUT_OF_MEMORY		(0x00007)
#define CMP_WRONG_DIMENSION		(0x00008)
#define CMP_OUT_OF_DIMENSION	(0x00009)
#define CMP_OUT_OF_DATA			(0x00014)
#define CMP_ASSERTION_FAILED	(0x00015)


// LIMITATIONS
#define MAX_WAV_SAMPLES	0x1000
#ifdef POCKETPC
#define GLB_MAX_BITMAPS 4096
#endif


// not in namespace (linker errors on iPhone)
extern "C" void __EndProgram(void);


namespace __GLBASIC__
{
class CGStr
{
public:
	CGStr(const char* c) {m_dat = c;}
	inline const char* c_str()const {return m_dat;}
	DGInt number()const;
	DGNat natural()const;
	unsigned int len()const;

	inline operator DGInt()const {return number();}
	inline operator DGNat()const {return natural();}

	inline operator const char*() const {return m_dat;}
	inline operator char*() const {return (char*)m_dat;}
	const char* m_dat;
};


class DGStr
{
public:
	DGStr();
	DGStr(CGStr a);
	DGStr(const DGStr& a);
	DGStr(const char* c);
	DGStr(const wchar_t* c);
	DGStr(int a);
	DGStr(float a);
	DGStr(double a);
	inline ~DGStr() {clear();}

	void alloc(unsigned int n, bool keep_content);
	void clear();

	template<typename T> static void dgstr_myswap(T& a, T& b) {T t(a); a=b; b=t;}
	inline void swap(DGStr& s)
	{
		dgstr_myswap(s.m_dat,    m_dat);
		dgstr_myswap(s.m_length, m_length);
		dgstr_myswap(s.m_buflen, m_buflen);
	}

	inline const char* c_str()const {return m_dat;}
	const wchar_t*     w_str()const; // returns a static temp buffer -> don't use twice in one call!
	char*		getbuffer(unsigned int size);
	void		releasebuffer();

	#ifdef _DEBUG
		char  operator[](unsigned int n)const;
		char& operator[](unsigned int n);
		char  operator[](int n)const;
		char& operator[](int n);
		char  operator[](long n)const;
		char& operator[](long n);
	#else
		char  operator[](unsigned int n)const		{return m_dat[n];}
		char& operator[](unsigned int n)			{return m_dat[n];}
		char  operator[](int n)const				{return m_dat[n];}
		char& operator[](int n)						{return m_dat[n];}
		char  operator[](long n)const				{return m_dat[n];}
		char& operator[](long n)					{return m_dat[n];}
	#endif
	void		addchar(char c);
	void		left(long i);
	int			compare(const char* s);
	int			compare(const DGInt& i);
	int			compare(const DGNat& i);
	void		trimright(void);
	DGInt		number() const;
	DGNat		natural() const;
	inline unsigned int len() const	{return m_length;}
	void assign(const char* c);
	void assign(const wchar_t* c);
	void assignlowmem(const char* c);


	void upper();
	void lower();
	inline void setlength(unsigned int len)
	{
		#ifdef _DEBUG
		if(len && len>=m_buflen)
			*(int*)0 = 42;
		#endif
		m_length = len;
	}
	DGStr replace(const DGStr& sOld, const DGStr& sNew)const;


//	DGStr& operator=(const DGStr& a);

	// ++str
	inline DGStr& operator++()				{*this = (DGInt(*this)) + 1.0; return *this;}
	inline DGStr& operator--()				{*this = (DGInt(*this)) - 1.0; return *this;}

	DGStr& operator=(const DGStr& a);
//	inline DGStr& operator=(DGStr a)		{swap(a); return *this;} // slow due to realloc
	inline DGStr& operator=(CGStr a)		{DGStr tmp(a); swap(tmp); return *this;}
	inline DGStr& operator=(const char* a)	{DGStr tmp(a); swap(tmp); return *this;}
	inline DGStr& operator=(int a)			{DGStr tmp(a); swap(tmp); return *this;}
	inline DGStr& operator=(float a)		{DGStr tmp(a); swap(tmp); return *this;}
	inline DGStr& operator=(double a)		{DGStr tmp(a); swap(tmp); return *this;}

	inline operator DGInt()const {return number();}
	inline operator DGNat()const {return natural();}
	inline operator bool() const {return natural() ? true:false;} // if(a$)
	inline operator const char*() const {return c_str();}
	inline operator char*() {alloc(1024, true); return m_dat;}

	// DGStr  operator +-*/ (const DGStr& a);
	#define MK_OPERATOR_CL(zz) \
		DGStr& operator zz(const char* a); \
		DGStr& operator zz(CGStr a); \
		DGStr& operator zz(const DGStr& a); \
		DGStr& operator zz(int a); \
		DGStr& operator zz(float a); \
		DGStr& operator zz(double a);
	MK_OPERATOR_CL(+=)
	MK_OPERATOR_CL(-=)
	MK_OPERATOR_CL(*=)
	MK_OPERATOR_CL(/=)
	MK_OPERATOR_CL(^=)

	#undef MK_OPERATOR_CL

private:
	char* m_dat;
	unsigned int m_buflen;
	unsigned int m_length;
};

#define MK_OPERATOR(zz) \
DGStr operator zz (int a, CGStr b); \
DGStr operator zz (int a, const DGStr& b); \
DGStr operator zz (float a, CGStr b); \
DGStr operator zz (float a, const DGStr& b); \
DGStr operator zz (double a, CGStr b); \
DGStr operator zz (double a, const DGStr& b); \
DGStr operator zz (CGStr a, CGStr b); \
DGStr operator zz (CGStr a, const DGStr& b); \
DGStr operator zz (CGStr a, int b); \
DGStr operator zz (CGStr a, float b); \
DGStr operator zz (CGStr a, double b); \
DGStr operator zz (const DGStr& a, CGStr b); \
DGStr operator zz (const DGStr& a, const DGStr& b); \
DGStr operator zz (const DGStr& a, int b); \
DGStr operator zz (const DGStr& a, float b); \
DGStr operator zz (const DGStr& a, double b);
MK_OPERATOR(+)
MK_OPERATOR(-)
MK_OPERATOR(*)
MK_OPERATOR(/)
MK_OPERATOR(^)
#undef MK_OPERATOR

#define MK_OPERATOR(zz) \
bool operator zz (int a, CGStr b)		; \
bool operator zz (int a, const DGStr& b)		; \
bool operator zz (float a, CGStr b)	; \
bool operator zz (float a, const DGStr& b)	; \
bool operator zz (double a, CGStr b)	; \
bool operator zz (double a, const DGStr& b)	; \
bool operator zz (CGStr a, CGStr b)	; \
bool operator zz (CGStr a, const DGStr& b)	; \
bool operator zz (CGStr a, int b)		; \
bool operator zz (CGStr a, float b)	; \
bool operator zz (CGStr a, double b)	; \
bool operator zz (const DGStr& a, CGStr b)	; \
bool operator zz (const DGStr& a, const DGStr& b)	; \
bool operator zz (const DGStr& a, int b)		; \
bool operator zz (const DGStr& a, float b)	; \
bool operator zz (const DGStr& a, double b)	;

MK_OPERATOR(==)
MK_OPERATOR(<=)
MK_OPERATOR(>=)
MK_OPERATOR(!=)
MK_OPERATOR(<)
MK_OPERATOR(>)
#undef MK_OPERATOR
inline bool operator == (const DGStr& a, const char* b) {return a==CGStr(b);}
inline bool operator == (const char* b, const DGStr& a) {return a==CGStr(b);}


DGNat __Error(DGNat code);
void __dLn	(int nfile, int num);
extern "C" int  __GlobalInit(HINSTANCE hInst, int nCmdShow, const char* Caption);

template<class A, class B> A MIN(A a, B b) {return a<(A)b ? a : (A)b;}
template<class A, class B> A MAX(A a, B b) {return a>(A)b ? a : (A)b;}

template<class A, class B> void SWAP(A& a, B& b) {A c= (A)b; b=(B)a; a=c;}

// DEBUGGIN Fkts
void	DEBUG(const DGStr& s);
DGStr	FORMAT_Str(DGInt minchars, DGInt numaftercomma, DGInt i);

// CONSOLE
void	STDOUT(const DGStr& str);
void	STDERR(const DGStr& str);
DGStr	STDIN_Str();
void	STDCOLOR(DGNat iForeground=15, DGNat iBackground=0);


// debug array access out of bounds
template<class A> void glb_err_array_range(const A& arr, int a, int b=0, int c=0, int d=0)
{
	DGStr s1, s2;
	s1=CGStr("[")+FORMAT_Str(4,0,arr.max1)+CGStr("]");
	s2=CGStr("[")+FORMAT_Str(4,0,a       )+CGStr("]");
	#if _GLB_MAX_ARAY>1
		if(arr.max2>0)
		{
			s1+=CGStr("[")+FORMAT_Str(4,0,arr.max2)+CGStr("]");
			s2+=CGStr("[")+FORMAT_Str(4,0,b       )+CGStr("]");
			#if _GLB_MAX_ARAY>2
			if(arr.max3>0)
			{
				s1+=CGStr("[")+FORMAT_Str(4,0,arr.max3)+CGStr("]");
				s2+=CGStr("[")+FORMAT_Str(4,0,c       )+CGStr("]");
				#if _GLB_MAX_ARAY>3
				if(arr.max4>0)
				{
					s1+=CGStr("[")+FORMAT_Str(4,0,arr.max4)+CGStr("]");
					s2+=CGStr("[")+FORMAT_Str(4,0,d       )+CGStr("]");
				}
				#endif
			}
			#endif
		}
	#endif

	DEBUG(CGStr("bounds: ")+s1+CGStr("\n"));
	DEBUG(CGStr("access: ")+s2+CGStr("\n"));

	STDERR(CGStr("bounds: ")+s1+CGStr("\n"));
	STDERR(CGStr("access: ")+s2+CGStr("\n"));
}

#define DGARRAY_STATIC_SIZE 0 // crashes on large projects ;_;
// ------------------------------------------------------------- //
class DGIntArray
// ------------------------------------------------------------- //
{
public:
	DGInt*	pData;
	#if DGARRAY_STATIC_SIZE>0
	DGInt	pDataStatic[DGARRAY_STATIC_SIZE];
	#endif
	int	fac2;
	int	fac3;
	int	fac4;

	int	max1;
	int	max2;
	int	max3;
	int	max4;
	int count; // number of DIMed items [2][3] = 2*3=6
	int	dim;
	int mem;

	DGIntArray(const DGIntArray& i):pData(NULL),mem(0) {*this = i;}
	DGIntArray() : pData(NULL), count(0), dim(0), mem(0) {max1=max2=max3=max4=fac2=fac3=fac4=0;}
	~DGIntArray() {if (pData!=NULL
				#if DGARRAY_STATIC_SIZE>0
						 && pData!=&pDataStatic[0]
				#endif
					) delete[] pData; pData=NULL;}
	DGIntArray& operator=(const DGIntArray& a);
	operator DGInt ()	{return pData ? pData[0] : 0;}
	operator DGNat ()	{return (DGNat)(pData ? pData[0] : 0);}
	operator DGStr ()	{return pData ? (DGStr)pData[0] : DGStr();}
	//DGInt& operator ()(DGInt xt1, DGInt xt2=0, DGInt xt3=0, DGInt xt4=0);
	inline DGInt& operator ()
							(int xt1
							#if _GLB_MAX_ARAY>1
								, int xt2=0
								#if _GLB_MAX_ARAY>2
									, int xt3=0
									#if _GLB_MAX_ARAY>3
										, int xt4=0
									#endif
								#endif
							#endif
							)
	{
		if(xt1<0) xt1+=max1; // a[-1] -> last element
		if (pData==NULL || xt1>=this->max1 || xt1 < 0
			#if _GLB_MAX_ARAY>1
			|| xt2<0 || (this->max2 && xt2>=this->max2)
			#if _GLB_MAX_ARAY>2
			|| xt3<0 || (this->max3 && xt3>=this->max3)
			#if _GLB_MAX_ARAY>3
			|| xt4<0 || (this->max4 && xt4>=this->max4)
			#endif
			#endif
			#endif
		)
		{
			#if _GLB_MAX_ARAY>1
				glb_err_array_range(*this, xt1, xt2);
			#if _GLB_MAX_ARAY>2
				glb_err_array_range(*this, xt1, xt2, xt3);
			#if _GLB_MAX_ARAY>3
				glb_err_array_range(*this, xt1, xt2, xt3, xt4);
			#endif
			#endif
			#else
				glb_err_array_range(*this, xt1);
			#endif
			__Error(CMP_OUT_OF_DIMENSION); __EndProgram();
		}

		return this->pData[xt1
				#if _GLB_MAX_ARAY>1
							 + fac2*xt2
				#if _GLB_MAX_ARAY>2
							 + fac3*xt3
				#if _GLB_MAX_ARAY>3
							 + fac4*xt4
				#endif
				#endif
				#endif
			 ];
	}
	DGIntArray& operator ()(void) {return *this;}
	bool operator<(const DGIntArray& a)const {return this->max1<a.max1 ? true:false;}
	bool operator>(const DGIntArray& a)const {return this->max1<a.max1 ? false:true;}
	bool operator==(const DGIntArray& a) const
	{
		if(a.max1!=max1 || a.max2!=max2 || a.max3!=max3 || a.max4!=max4) return false;
		for(int i=0; i<a.count; ++i) {if (!(pData[i] == a.pData[i])) return false;}
		return true;
	}
};


// ------------------------------------------------------------- //
class DGNatArray
// ------------------------------------------------------------- //
{
public:
	DGNat*	pData;
	#if DGARRAY_STATIC_SIZE>0
	DGNat	pDataStatic[DGARRAY_STATIC_SIZE];
	#endif
	int	fac2;
	int	fac3;
	int	fac4;

	int	max1;
	int	max2;
	int	max3;
	int	max4;
	int count; // number of DIMed items [2][3] = 2*3=6
	int	dim;
	int mem;
	DGNatArray(const DGNatArray& i) : pData(NULL), mem(0) {*this = i;}
	DGNatArray() :pData(NULL),  count(0), dim(0), mem(0) {max1=max2=max3=max4=fac2=fac3=fac4=0;}
	~DGNatArray() {if (pData!=NULL
	#if DGARRAY_STATIC_SIZE>0
	 && pData!=&pDataStatic[0]
	#endif
	 ) delete[] pData; pData=NULL;}
	DGNatArray& operator=(const DGNatArray& a);
	operator DGInt ()	{return (DGInt)(pData ? pData[0] : 0);}
	operator DGNat ()	{return pData ? pData[0] : 0;}
	operator DGStr ()	{return pData ? (DGStr)pData[0] : DGStr();}
	//DGInt& operator ()(DGInt xt1, DGInt xt2=0, DGInt xt3=0, DGInt xt4=0);
	inline DGNat& operator ()
							(int xt1
							#if _GLB_MAX_ARAY>1
								, int xt2=0
								#if _GLB_MAX_ARAY>2
									, int xt3=0
									#if _GLB_MAX_ARAY>3
										, int xt4=0
									#endif
								#endif
							#endif
							)
	{
		if(xt1<0) xt1+=max1; // a[-1] -> last element
		if (pData==NULL || xt1>=this->max1 || xt1 < 0
			#if _GLB_MAX_ARAY>1
			|| xt2<0 || (this->max2 && xt2>=this->max2)
			#if _GLB_MAX_ARAY>2
			|| xt3<0 || (this->max3 && xt3>=this->max3)
			#if _GLB_MAX_ARAY>3
			|| xt4<0 || (this->max4 && xt4>=this->max4)
			#endif
			#endif
			#endif
		)
		{
			#if _GLB_MAX_ARAY>1
				glb_err_array_range(*this, xt1, xt2);
			#if _GLB_MAX_ARAY>2
				glb_err_array_range(*this, xt1, xt2, xt3);
			#if _GLB_MAX_ARAY>3
				glb_err_array_range(*this, xt1, xt2, xt3, xt4);
			#endif
			#endif
			#else
				glb_err_array_range(*this, xt1);
			#endif
			__Error(CMP_OUT_OF_DIMENSION); __EndProgram();
		}
		return this->pData[xt1
				#if _GLB_MAX_ARAY>1
							 + fac2*xt2
				#if _GLB_MAX_ARAY>2
							 + fac3*xt3
				#if _GLB_MAX_ARAY>3
							 + fac4*xt4
				#endif
				#endif
				#endif
			 ];
	}
	DGNatArray& operator ()(void) {return *this;}
	bool operator<(const DGNatArray& a)const {return this->max1<a.max1 ? true:false;}
	bool operator>(const DGNatArray& a)const {return this->max1<a.max1 ? false:true;}
	bool operator==(const DGNatArray& a) const
	{
		if(a.max1!=max1 || a.max2!=max2 || a.max3!=max3 || a.max4!=max4) return false;
		for(int i=0; i<a.count; ++i){if (!(pData[i] == a.pData[i])) return false;}
		return true;
	}
};

// ------------------------------------------------------------- //
template<class T> class DGArray
// ------------------------------------------------------------- //
{
public:
	T*	pData;
	int	fac2;
	int	fac3;
	int	fac4;

	int	max1;
	int	max2;
	int	max3;
	int	max4;
	int count; // number of DIMed items [2][3] = 2*3=6
	int	dim;// 0:1D, 1:2D..
	int mem;
	DGArray(const DGArray& i):pData(NULL),mem(0) {*this = i;}
	DGArray()  {pData=NULL; dim=0; mem=0; count=0; max1=max2=max3=max4=fac2=fac3=fac4=0;}
	~DGArray() {if (pData) delete[] pData; pData=(T*)NULL;
				#ifdef _DEBUG
				dim= -787878; mem= -787878; count=-787878; max1=max2=max3=max4=fac2=fac3=fac4= -787878;
				#endif
				}

	DGArray& operator=(const DGArray& a)
	{
		DIM(*this, a.max1, a.max2, a.max3, a.max4);
		int	siz=a.count;
		const T* pR=a.pData; T* pW=this->pData;
		while(siz){*pW++ = *pR++; --siz;}
	return *this;
	}
	inline T& operator ()
							(int xt1
							#if _GLB_MAX_ARAY>1
								, int xt2=0
								#if _GLB_MAX_ARAY>2
									, int xt3=0
									#if _GLB_MAX_ARAY>3
										, int xt4=0
									#endif
								#endif
							#endif
							)
	{
		if(xt1<0) xt1+=max1; // a[-1] -> last element


#ifdef _DEBUG
	if(count != max1*MAX(1,max2)*MAX(1,max3)*MAX(1,max4))
	{
		__Error(CMP_OUT_OF_DIMENSION); __EndProgram();
	}
#endif










		if (pData==NULL || xt1>=this->max1 || xt1 < 0
			#if _GLB_MAX_ARAY>1
			|| xt2<0 || (this->max2 && xt2>=this->max2)
			#if _GLB_MAX_ARAY>2
			|| xt3<0 || (this->max3 && xt3>=this->max3)
			#if _GLB_MAX_ARAY>3
			|| xt4<0 || (this->max4 && xt4>=this->max4)
			#endif
			#endif
			#endif
		)
		{
			#if _GLB_MAX_ARAY>1
				glb_err_array_range(*this, xt1, xt2);
			#if _GLB_MAX_ARAY>2
				glb_err_array_range(*this, xt1, xt2, xt3);
			#if _GLB_MAX_ARAY>3
				glb_err_array_range(*this, xt1, xt2, xt3, xt4);
			#endif
			#endif
			#else
				glb_err_array_range(*this, xt1);
			#endif
			__Error(CMP_OUT_OF_DIMENSION); __EndProgram();
		}

		return this->pData[xt1
				#if _GLB_MAX_ARAY>1
							 + fac2*xt2
				#if _GLB_MAX_ARAY>2
							 + fac3*xt3
				#if _GLB_MAX_ARAY>3
							 + fac4*xt4
				#endif
				#endif
				#endif
			 ];
	}

	operator DGInt ()
	{return 0;}
	operator DGStr ()
	{return DGStr();}
	DGArray& operator ()(void) {return *this;}
	bool operator<(const DGArray<T>& a)const {return this->max1<a.max1 ? true:false;}
	bool operator>(const DGArray<T>& a)const {return this->max1<a.max1 ? false:true;}
	bool operator==(const DGArray& a) const
	{
		if(a.max1!=max1 || a.max2!=max2 || a.max3!=max3 || a.max4!=max4) return false;
		for(int i=0; i<a.count; ++i){if (!(pData[i] == a.pData[i])) return false;}
		return true;
	}
};
typedef DGArray<DGStr> DGStrArray;


#define ADDRESSOF(a) ((DGNat)((void*)&(a)))

template <class T> int compare_by_foo(T& a, T& b, int foo)
{
	typedef DGInt(*pcmp)(T&a, T&b);
	pcmp cmp;
	#pragma warning(disable:4312)
	cmp = (pcmp)(void*)foo;
	return (int)cmp(a,b);
}


template <class T, const unsigned int size> void glb_swap_item(T*& a, T*& b)
{
	struct arr_s {
	    char element[size];
	} t;

	                  t = *(struct arr_s *) a;
	*(struct arr_s *) a = *(struct arr_s *) b;
	*(struct arr_s *) b = t;
}


// Sorting
template <class T> void sortarray(T* low, T* high, int foo)
{
	T* lo, *hi;
	lo = low;
	hi = high;
	T t;
	T* piv = high;
	for(;;)
	{
		if(foo)
		{
			while(compare_by_foo(*lo, *piv, foo)<0) {++lo;}
			while(compare_by_foo(*hi, *piv, foo)>0) {++hi;}
		}
		else
		{
			while(*lo < *piv) {++lo;}
			while(*hi > *piv) {++hi;}
		}
		if(lo <= hi) // pointer positions ~= index
		{
			glb_swap_item<T, sizeof(T) >(lo, hi);
			++lo;
			--hi;
		}
		if(lo > hi) break;
	}
	if(hi > low)  sortarray(low, hi, foo);
	if(lo < high) sortarray(lo, high, foo);
}

template <class T> void SORTARRAY(T& arry, DGNat foo)
{
	int len = LEN(arry);
	if(len>1)
		sortarray(&arry(0), &arry(len-1), foo);
}

// no preallocation (for fixed size types)
template <class T> void FIXDIM(DGArray<T>& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0)
{
int clr=0;
	if (xt1<1) {xt1=0;/* xt2=0; xt3=0; xt4=0;*/ clr=1;}
	int	siz=(int)(xt1*MAX(1,xt2)*MAX(1,xt3)*MAX(1,xt4));
	if (siz>arr.mem || clr)
	{
		arr.mem = siz;if (arr.pData)delete[] arr.pData;arr.pData=new T[siz];
	}
	else
	{for(int i=0; i<siz; ++i){arr.pData[i] = T();}}
	if (arr.pData==NULL) {__Error(CMP_OUT_OF_MEMORY); __EndProgram();}
	if (xt4) arr.dim=4; else if (xt3) arr.dim=3; else if (xt2) arr.dim=2; else if(xt1) arr.dim=1; else arr.dim=0;
	arr.fac2=(int)xt1; arr.fac3=arr.fac2*(int)xt2; arr.fac4=arr.fac3*(int)xt3;
	arr.max1=(int)xt1; arr.max2=(int)xt2; arr.max3=(int)xt3; arr.max4=(int)xt4;
	arr.count = arr.max1*MAX(1,arr.max2)*MAX(1,arr.max3)*MAX(1,arr.max4);
}


template <class T> void DIM(DGArray<T>& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0)
{
int clr=0;
	if (xt1<1) {xt1=0;/* xt2=0; xt3=0; xt4=0;*/ clr=1;}
	int	siz=(int)(xt1*MAX(1,xt2)*MAX(1,xt3)*MAX(1,xt4));
	if (siz>arr.mem || clr)
	{
		if(siz)
		{
			if(sizeof(T) <128)
			{
				siz=((int)(siz/64)+1 )*64;
			}
			else
			{
				siz=((int)(siz/8)+1 )*8;
			}
		}
		arr.mem = siz;
		if (arr.pData)delete[] arr.pData;
		if(siz>0)
		{
			arr.pData=new T[siz];
			if (arr.pData==NULL) {__Error(CMP_OUT_OF_MEMORY); __EndProgram();}
		}
		else
			arr.pData=NULL;
	}
	else
		{T* pT = arr.pData; for(int i=0; i<siz; ++i){*pT++ = T();}}
	if (xt4) arr.dim=4; else if (xt3) arr.dim=3; else if (xt2) arr.dim=2; else if(xt1) arr.dim=1; else arr.dim=0;
	arr.fac2=(int)xt1; arr.fac3=arr.fac2*(int)xt2; arr.fac4=arr.fac3*(int)xt3;
	arr.max1=(int)xt1; arr.max2=(int)xt2; arr.max3=(int)xt3; arr.max4=(int)xt4;
	arr.count = arr.max1*MAX(1,arr.max2)*MAX(1,arr.max3)*MAX(1,arr.max4);
}

template <class T> void REDIM(DGArray<T>& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0)
{
	// just reset dimensions
	if(xt1<=0)
	{
		arr.max1=0; arr.max2=0; arr.max3=0; arr.max4=0; arr.fac2=0; arr.fac3=0; arr.fac4=0; arr.dim=0; arr.count=0;
		return;
	}

#define min_(a,b) (a)<(b)?(int)(a):(int)(b)
	DGArray<T> tmp;
	DIM(tmp, xt1, xt2, xt3, xt4);
	int ma, mb, mc, md;
	ma = min_(arr.max1, xt1); mb = min_(arr.max2, xt2); mc = min_(arr.max3, xt3); md = min_(arr.max4, xt4);

	for(int a=0; a<ma; ++a)
	{
		#if _GLB_MAX_ARAY>1
		if(mb)for(int b=0; b<mb; ++b)
		{
			#if GLB_MAX_ARAY>2
			if(mc)for(int c=0; c<mc; ++c)
			{
				#if _GLB_MAX_ARAY>3
				if(md)for(int d=0; d<md; ++d)
				{
					tmp(a,b,c,d) = arr(a,b,c,d);
				}
				else
				#endif
					tmp(a,b,c) = arr(a,b,c);
			}
			else
			#endif
				tmp(a,b) = arr(a,b);
		}
		else
		#endif
			tmp(a) = arr(a);
	}

	// now copy tmp to arr data
	arr.fac2 = tmp.fac2; arr.fac3 = tmp.fac3; arr.fac4 = tmp.fac4;
	arr.max1 = tmp.max1; arr.max2 = tmp.max2; arr.max3 = tmp.max3; arr.max4 = tmp.max4;
	arr.count= tmp.count;

	// Now swap the data storage - not the data itself!
	arr.dim  = tmp.dim;
	arr.mem  = tmp.mem;
	T* ptr = arr.pData; arr.pData=tmp.pData; tmp.pData=ptr;
#undef min_
}


// *** DATA ***
template <class T> void DIMDATA(DGArray<T>& arr, int count, T* pData)
	{DIM(arr, count); for(int i=0; i<count; ++i) arr(i) = pData[i];}

struct GFDataStorageEntry
{
	DGInt n;
	const char* pC;
};
struct GFDataStoreageContainer
{
	GFDataStorageEntry* data;
	int count;
	int index;
	GFDataStoreageContainer(int c, GFDataStorageEntry* d) : data(d), count(c), index(0) {}
};
extern GFDataStoreageContainer* __gpDataContainer;
void RESTORE(GFDataStoreageContainer& container);
void READ(DGInt& i);
void READ(DGNat& i);
void READ(DGStr& str);




template <class T> DGNat	BOUNDS(const DGArray<T>& arr, DGNat nDim)
{
	switch(nDim)
	{
		case 0: return arr.max1; break;
		case 1: return arr.max2; break;
		case 2: return arr.max3; break;
		case 3: return arr.max4; break;
	}
return 0;
}

void	FIXDIM(DGIntArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	FIXDIM(DGNatArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	DIM(DGIntArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	DIM(DGNatArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	REDIM(DGIntArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	REDIM(DGNatArray& arr, DGNat xt1, DGNat xt2=0, DGNat xt3=0, DGNat xt4=0);
void	DIMDATA(DGIntArray& arr, int count, DGInt* pData);
DGNat	BOUNDS(const DGIntArray& arr, DGNat nDim);
void	DIMDATA(DGNatArray& arr, int count, DGNat* pData);
DGNat	BOUNDS(const DGNatArray& arr, DGNat nDim);


DGNat	LEN(DGInt s);
DGNat	LEN(DGNat s);
inline DGNat	LEN(const DGStr& s)							{return (DGNat)s.len();}
inline DGNat	LEN(const CGStr& s)							{return (DGNat)s.len();}
inline DGNat	LEN(const DGIntArray& arr)					{return BOUNDS(arr, 0);}
inline DGNat	LEN(const DGNatArray& arr)					{return BOUNDS(arr, 0);}
template <class T>inline DGNat	LEN(const DGArray<T>& arr)	{return BOUNDS(arr, 0);}

// Drawing text width
DGNat	LEN(const DGStr& s, DGNat kerning);
DGNat	LEN(const CGStr& s, DGNat kerning);


template <class T>          void action_copy_B2A(T& a, const T& b) {a=b;}
template <class T, class U> void ForEachRowElement(T& arr, int row1, int row2, void(action)(U&, const U&))
{
	int mb, mc, md;
	mb = arr.max2;
	mc = arr.max3;
	md = arr.max4;
	#if _GLB_MAX_ARAY>1
	if(mb)for(int b=0; b<mb; ++b)
	{
		#if _GLB_MAX_ARAY>2
		if(mc)for(int c=0; c<mc; ++c)
		{
			#if _GLB_MAX_ARAY>3
			if(md)for(int d=0; d<md; ++d)
			{
				action(arr(row1,b,c,d), arr(row2,b,c,d));
			}
			else
			#endif
				action(arr(row1,b,c), arr(row2,b,c));
		}
		else
		#endif
			action(arr(row1,b), arr(row2,b));
	}
	else
	#endif

	action(arr(row1), arr(row2));
}

template <class T> void	DIMDEL(DGArray<T>& arr, int index)
{
	if(index<0) index += arr.max1; // DIMDEL a[], -1 -> remove last

	if(arr.max1<=0 || index>=arr.max1) {arr(index);} // out of bounds

	if(index < arr.max1) // must move
	{
		if(arr.max2) // Mutli-array
		{
			for(int i=index; i<arr.max1-1; ++i)
			{
				ForEachRowElement<DGArray<T>, T>(arr, i, i+1, action_copy_B2A);
			}
		}
		else // 1D array
		{
			T* pA = &arr(index);
			T* pB = pA+1;
			for(int i=index+1; i<arr.max1; ++i)
			{
				*pA++ = *pB++;
			}
		}
	}
	--arr.max1;
	--arr.count;
}

inline void DIMDEL(DGIntArray& arr, int index)
{
	if(index<0) index += arr.max1; // DIMDEL a[], -1 -> remove last
	if(arr.max1<=0 || index>=arr.max1) {arr(index);} // out of bounds
	if(index < arr.max1) // must move
	{
		if(arr.max2) // Mutli-array
		{
			for(int i=index; i<arr.max1-1; ++i)
			{
				ForEachRowElement<DGIntArray, DGInt>(arr, i, i+1, action_copy_B2A);
			}
		}
		else // 1D array
		{
			DGInt* pA = &arr(index);
			const DGInt* pB = pA+1;
			for(int i=index+1; i<arr.max1; ++i)
			{
				*pA++ = *pB++;
			}
		}
	}
	--arr.max1;
	--arr.count;
}

inline void DIMDEL(DGNatArray& arr, int index)
{
	if(index<0) index += arr.max1;
	if(arr.max1<=0 || index>=arr.max1) {arr(index);} // out of bounds
	if(index < arr.max1) // must move
	{
		if(arr.max2) // Mutli-array
		{
			for(int i=index; i<arr.max1-1; ++i)
			{
				ForEachRowElement<DGNatArray, DGNat>(arr, i, i+1, action_copy_B2A);
			}
		}
		else // 1D array
		{
			DGNat* pA = &arr(index);
			const DGNat* pB = pA+1;
			for(int i=index+1; i<arr.max1; ++i)
			{
				*pA++ = *pB++;
			}
		}
	}
	--arr.max1;
	--arr.count;
}


template <class T> void DIMPUSH(DGArray<T>& arr, const T t)
{
	if(arr.max2) {__Error(CMP_WRONG_DIMENSION); __EndProgram();}
	if(arr.mem>arr.max1+1)
	{
		++arr.max1;
		++arr.count;
		arr(arr.max1-1) = t;
	}
	else
	{
		REDIM(arr, arr.max1+1, 0,0,0);
		arr(arr.max1-1) = t;
	}
}

inline void DIMPUSH(DGIntArray& arr, DGInt t)
{
	if(arr.max2) {__Error(CMP_WRONG_DIMENSION); __EndProgram();}
	if(arr.mem>arr.max1+1)
	{
		++arr.max1;
		++arr.count;
		arr(arr.max1-1) = t;
	}
	else
	{
		REDIM(arr, arr.max1+1, 0,0,0);
		arr(arr.max1-1) = t;
	}
}
inline void DIMPUSH(DGNatArray& arr, DGNat t)
{
	if(arr.max2) {__Error(CMP_WRONG_DIMENSION); __EndProgram();}
	if(arr.mem>arr.max1+1)
	{
		++arr.max1;
		++arr.count;
		arr(arr.max1-1) = t;
	}
	else
	{
		REDIM(arr, arr.max1+1, 0,0,0);
		arr(arr.max1-1) = t;
	}
}
inline void DIMPUSH(DGStrArray& arr, CGStr t) {DIMPUSH(arr, (DGStr)t);}
inline void DIMPUSH(DGStrArray& arr, DGInt t) {DIMPUSH(arr, (DGStr)t);}


// FUNCTIONS
// ------------------------------------------------------------- //

DGNat INSTR(CGStr s1, CGStr s2, DGNat start=0);
DGNat INSTR(CGStr s1, const DGStr& s2, DGNat start=0);
DGNat INSTR(const DGStr& s1, CGStr s2, DGNat start=0);
DGNat INSTR(const DGStr& s1, const DGStr& s2, DGNat start=0);
// DGNat INSTR(const char* s1, const char* s2, DGNat start=0);

DGNat REVINSTR(CGStr s1, CGStr s2, DGNat start=-1);
DGNat REVINSTR(CGStr s1, const DGStr& s2, DGNat start=-1);
DGNat REVINSTR(const DGStr& s1, CGStr s2, DGNat start=-1);
DGNat REVINSTR(const DGStr& s1, const DGStr& s2, DGNat start=-1);
// DGNat REVINSTR(const char* s1, const char* s2, DGNat start=-1);



DGNat SPLITSTR(const DGStr& instr, DGStrArray& arr, const DGStr& splitter, DGNat bSkipEmtpy=TRUE);
DGStr REPLACE_Str(DGStr str, const DGStr& oldstr, const DGStr& newstr);

DGStr UCASE_Str(const DGStr& org);
DGStr LCASE_Str(const DGStr& org);

DGStr __CompileTime();
DGStr __BuildSerial();
DGStr __GetPrpjectVersionGLB();
DGStr PLATFORMINFO_Str(DGStr WhatInfo);
#define CODELINE()	((DGNat)__GLBNO__)

DGStr   GETENV_Str(DGStr name);
void	PUTENV(DGStr name, DGStr value);

// FILE IO
void	CLEARERROR();
DGStr	GETLASTERROR_Str();

void	SETSHOEBOX(const DGStr& data, const DGStr& media);
DGInt	PutFile(LPCTSTR filename, short line, const DGStr& data);
DGInt	GetFile(LPCTSTR filename, short line,       DGStr& data);
void	GETFILE(const DGStr& file, DGInt line, DGInt& num);
void	GETFILE(const DGStr& file, DGInt line, DGNat& num);
void	GETFILE(const DGStr& file, DGInt line, DGStr& str);
void	PUTFILE(const DGStr& file, DGInt line, DGInt num);
void	PUTFILE(const DGStr& file, DGInt line, DGStr str);
DGStr	FILEREQUEST_Str(DGNat open, const DGStr& filter);

DGNat	GETFILESIZE(const DGStr& file);
DGNat	ENDOFFILE(DGNat channel);
DGNat	OPENFILE(DGNat channel, const DGStr& file, DGNat mode);
// DGNat	OPENPROCESS(DGNat channel, const DGStr& process);
void	CLOSEFILE(DGNat channel);
void	READBYTE(DGNat channel, DGNat& v);
void	READWORD(DGNat channel, DGNat& v);
void	READLONG(DGNat channel, DGNat& v);
void	READUBYTE(DGNat channel, DGNat& v);
void	READUWORD(DGNat channel, DGNat& v);
void	READULONG(DGNat channel, DGNat& v);
void	READIEEE(DGNat channel, DGInt& v);
void	READSHORTIEEE(DGNat channel, DGInt& v);
void	READSTR(DGNat channel, DGStr& v, DGNat nchar);
void	READLINE(DGNat channel, DGStr& v);
void	READLINE(DGNat channel, DGInt& v);
void	READLINE(DGNat channel, DGNat& v);
void	WRITEBYTE(DGNat channel, DGNat v);
void	WRITEWORD(DGNat channel, DGNat v);
void	WRITELONG(DGNat channel, DGNat v);
void	WRITEUBYTE(DGNat channel, DGNat v);
void	WRITEUWORD(DGNat channel, DGNat v);
void	WRITEULONG(DGNat channel, DGNat v);
void	WRITEIEEE(DGNat channel, DGInt v);
void	WRITESHORTIEEE(DGNat channel, DGInt v);
void	WRITESTR(DGNat channel, const DGStr& str);
void	WRITELINE(DGNat channel, const DGStr& str);
DGNat	FILEPOSITION(DGNat channel);
void	FILESEEK(DGNat channel, DGNat bytes, DGNat direction);


DGInt	SHELLCMD(DGStr cmd, DGInt wait, DGInt show, DGInt& retval);
void	SHELLEND(DGStr cmd);
DGNat	CREATEDIR(const DGStr& dir);
void	KILLFILE(const DGStr& file);
void	COPYFILE(const DGStr& src, const DGStr& dst);
DGNat	DOESFILEEXIST(const DGStr& file);
DGNat	DOESDIREXIST(const DGStr& dir);
DGStr	GETCURRENTDIR_Str(void);
DGInt	SETCURRENTDIR(const DGStr& dir);
DGInt	GETFILELIST(const DGStr& wildcard, DGStrArray& files);
// INI-Files
void	INIOPEN(const DGStr& filename);
DGStr	INIGET_Str(const DGStr& section, const DGStr& key, DGStr nodata=DGStr("NO_DATA"));
void	INIPUT(const DGStr& section, const DGStr& key, const DGStr& value);

DGInt	SIN(DGInt angle);
DGInt	COS(DGInt angle);
DGInt	TAN(DGInt angle);
DGNat	KEY(DGNat key);
void	SEEDRND(DGNat seed);
DGNat	RND(DGNat max);

DGInt	POW(DGInt n, DGInt e);
DGNat	MOD(DGNat n, DGNat m);
DGInt	FMOD(DGInt n, DGInt m);
DGInt	ATAN(DGInt dx, DGInt dy);
DGInt	ASIN(DGInt n);
DGInt	ACOS(DGInt n);
DGInt	SQR(DGInt n);
DGInt	LOGN(DGInt n);

inline DGInt	ABS(DGInt n){return n<0 ? -n:n;}
inline DGNat	ABS(DGNat n){return n<0 ? -n:n;}
inline DGInt	SGN(DGInt n) {return n<0 ? -1 : (n > 0 ? 1:0);}
inline DGNat	SGN(DGNat n) {return n<0 ? -1 : (n > 0 ? 1:0);}
inline DGNat	ASL(DGNat n, DGNat shift) {return n << shift;}
inline DGNat	ASR(DGNat n, DGNat shift) {return n >> shift;}

#define AND	&&
#define OR	||
#define GLOBAL __GLBASIC__::
#define LOCAL
#define LET
#define NOT !

template <typename T, typename U> inline void INC(T& t, U u) {t+=(T)u;}
template <typename T, typename U> inline void DEC(T& t, U u) {t-=(T)u;}
template <typename T> inline void INC(T& t) {++t;}
template <typename T> inline void DEC(T& t) {--t;}

inline DGNat bAND(DGNat a, DGNat b)
{
	unsigned int	la = (unsigned int)(a),
					lb = (unsigned int)(b);
	return (unsigned int)(la & lb);
}
inline DGNat bOR(DGNat a, DGNat b)
{
	unsigned int	la = (unsigned int)(a),
					lb = (unsigned int)(b);
	return (unsigned int)(la | lb);
}
inline DGNat bXOR(DGNat a, DGNat b)
{
	unsigned int	la = (unsigned int)(a),
					lb = (unsigned int)(b);
	return (unsigned int)(la ^ lb);
}

inline DGNat bNOT(DGNat a)
{
	unsigned int	la = (unsigned int)(a);
	return (unsigned int)( ~la );
}

template <class T> inline DGNat INTEGER(T t) {return (DGNat) t;}
template <>        inline DGNat INTEGER<const DGStr&>(const DGStr& n) {return n.natural();}


void	END();
DGInt	CALLBYNAME(const DGStr& sub_name);
void*	GETSUBADDRESS(const DGStr& sub_name);
DGStr	MID_Str(const DGStr& s, DGNat start, DGNat len=-1);
inline DGStr	LEFT_Str(const DGStr& s, DGNat count) {return MID_Str(s,0,count);}
inline DGStr	RIGHT_Str(const DGStr& s, DGNat count){return MID_Str(s, MAX(0, LEN(s)-count), -1);}
DGStr	LTRIM_Str(const DGStr& str, const DGStr& trim=DGStr(" \t\r\n\f\v"));
DGStr	RTRIM_Str(const DGStr& str, const DGStr& trim=DGStr(" \t\r\n\f\v"));
inline DGStr	TRIM_Str(const DGStr& str, const DGStr& trim=DGStr(" \t\r\n\f\v")){return LTRIM_Str(RTRIM_Str(str, trim), trim);}


DGNat	ASC(const DGStr& s);
DGNat	ASC(const DGStr& s, DGNat index);
DGStr	CHR_Str(DGNat i);
void	CLEARSCREEN(DGNat col = 0);
inline void	BLACKSCREEN(void) {CLEARSCREEN(0);}
void	BLENDSCREEN(const DGStr& s, DGNat msecs=1000);
void	PLAYMOVIE(const DGStr& s);
void	LOOPMOVIE(const DGStr& s);
void	PLAYMUSIC(const DGStr& s, DGNat bLoop);
DGNat	ISMUSICPLAYING();
void	PAUSEMUSIC(DGNat bPause);
void	MUSICVOLUME(DGInt volume);
void	STOPMUSIC();
void	PRINT(const DGStr& s, DGInt x, DGInt y, DGNat kerning=FALSE);
DGStr	ENCRYPT_Str(DGStr code, DGStr text);
DGStr	DECRYPT_Str(DGStr code, DGStr text);
DGStr	URLENCODE_Str(const DGStr& SrcString);
DGStr	URLDECODE_Str(const DGStr& SrcString);

void	ASSERT(DGNat eq);

void	DRAWANIM(DGNat num, DGNat iTile, DGNat x, DGNat y);
void	ROTOZOOMANIM(DGNat num, DGNat itile, DGNat x, DGNat y, DGInt phi, DGInt scale);
void	STRETCHANIM(DGNat num, DGNat itile, DGNat x, DGNat y, DGNat w, DGNat h);
DGNat	ANIMCOLL(DGNat ani1, DGNat tile1, DGNat x1, DGNat y1,  DGNat ani2, DGNat tile2, DGNat x2, DGNat y2);

void	SMOOTHSHADING(DGNat smooth);
void	ALPHAMODE(DGInt alpha);
void	ALPHATESTING(DGInt alpha);
void	ROTOSPRITE(DGNat num, DGNat x, DGNat y, DGInt angle);
void	ROTOZOOMSPRITE(DGNat num, DGNat x, DGNat y, DGInt angle, DGInt size);
void	DRAWSPRITE(DGNat num, DGNat x, DGNat y);
void	STRETCHSPRITE(DGNat nr, DGNat xa, DGNat ya, DGNat wx, DGNat wy);
void	ZOOMSPRITE(DGNat num, DGNat x, DGNat y, DGInt xsize, DGInt ysize);
void	GRABSPRITE(DGNat num, DGNat x, DGNat y, DGNat wx, DGNat wy);
void	USEASBMP();
void	AUTOPAUSE(DGNat mode);
void	SHOWSCREEN(void);
void	HIBERNATE(void);
void	SLEEP(DGNat ns);
void	ALLOWESCAPE(DGInt i);
void	LIMITFPS(DGInt n);
void	SETSCREEN(DGNat w, DGNat h, DGNat fs);
DGNat	ISFULLSCREEN();
DGInt	GETTIMER(void);
DGInt	GETTIMERALL(void);
void	INPUT(DGStr& s, DGNat x, DGNat y, DGNat bKerning=FALSE);
void	INPUT(DGInt& s, DGNat x, DGNat y, DGNat bKerning=FALSE);
void	INPUT(DGNat& s, DGNat x, DGNat y, DGNat bKerning=FALSE);
DGStr	INKEY_Str(void);
void	JOYSTATE(DGNat& jx, DGNat& jy, DGNat& b1, DGNat& b2);
void	JOYSTATE(DGInt& jx, DGInt& jy, DGInt& b1, DGInt& b2);
void	KEYWAIT(void);
DGNat	GETMOUSECOUNT();
void	SETACTIVEMOUSE(DGNat i);
DGNat	MOUSEAXIS(DGNat nAxis);
void	MOUSESTATE(DGInt& jx, DGInt& jy, DGInt& b1, DGInt& b2);
void	MOUSESTATE(DGNat& jx, DGNat& jy, DGNat& b1, DGNat& b2);
void	SYSTEMPOINTER(DGInt onoff);
void	SETMOUSE(DGNat mx, DGNat my);
void	MOUSEWAIT(void);
void	LOADBMP(const DGStr& s);
DGStr	GETCOMMANDLINE_Str(void);
void	LOADFONT(const DGStr& s, DGNat i);
void	SETFONT(DGNat i);
void	SETTRANSPARENCY(DGNat col);
void	GETSPRITESIZE(DGInt id, DGInt& wx, DGInt& wy);
void	GETSPRITESIZE(DGNat id, DGNat& wx, DGNat& wy);
void	GETFONTSIZE(DGInt& wx, DGInt& wy);
void	GETFONTSIZE(DGNat& wx, DGNat& wy);
void	GETSCREENSIZE(DGInt& wx, DGInt& wy);
void	GETSCREENSIZE(DGNat& wx, DGNat& wy);
void	GETDESKTOPSIZE(DGInt& wx, DGInt& wy);
void	GETDESKTOPSIZE(DGNat& wx, DGNat& wy);

void	SETORIENTATION(DGNat imode);
DGNat	GETORIENTATION();

void	VIEWPORT(DGNat x, DGNat y, DGNat w, DGNat h);
void	GETVIEWPORT(DGNat& x, DGNat& y, DGNat& w, DGNat& h);
void	GETVIEWPORT(DGInt& x, DGInt& y, DGInt& w, DGInt& h);
void	CREATESCREEN(DGNat iScreen, DGNat iSprite, DGNat width, DGNat height);
void	USESCREEN(DGNat iScreen);
void	LOADSPRITE(const DGStr& s, DGNat n);
DGNat	MEM2SPRITE(DGNatArray& pixRGBA, DGNat num, DGNat w, DGNat h);
DGNat	SPRITE2MEM(DGNatArray& pixRGBA, DGNat num);
DGNat	LOADSPRITEMEM(const DGStr& s, DGNat& w, DGNat& h, DGNatArray& pixRGBA);
void	LOADANIM(DGStr s, DGNat n, DGNat width, DGNat height);
void	SETSPRITEANIM(DGNat n, DGNat width, DGNat height);

unsigned int get_sprite_texture(int id);
void	LOADBUMPTEXTURE(const DGStr& s, DGNat n);
void	LOADSOUND(const DGStr& s, DGNat num, DGNat buffers);
DGNat	PLAYSOUND(DGNat num, DGInt fade, DGInt volume);
DGNat	SOUNDPLAYING(DGNat channel);
void	STOPSOUND(DGNat channel);
void	HUSH(void);
void	SAVEBMP(const DGStr& s);
void	SAVESPRITE(const DGStr& s, DGNat n);
DGNat	BOXCOLL(DGNat x1, DGNat y1, DGNat w1, DGNat h1, DGNat x2, DGNat y2, DGNat w2, DGNat h2);
DGNat	SPRCOLL(DGNat n1, DGNat x1, DGNat y1, DGNat n2, DGNat x2, DGNat y2);
void	DRAWLINE(DGNat sx, DGNat sy, DGNat ex, DGNat ey, DGNat col);
void	SETPIXEL(DGNat x,  DGNat y,  DGNat col);
void	DRAWRECT(DGNat sx, DGNat sy, DGNat ex, DGNat ey, DGNat col);
DGNat	GETPIXEL(DGNat x, DGNat y);
void	STARTPOLY(DGNat nTexture=-1, DGNat bMode=0);
void	POLYVECTOR(DGInt x, DGInt y, DGInt tx=0, DGInt ty=0, DGNat col=0xffffff);
void	POLYNEWSTRIP(void);
void	ENDPOLY(void);

// Get an empty slot for objects
DGNat	GENSPRITE();
DGNat	GENSOUND();
DGNat	GENX_OBJ();
DGNat	GENFILE();
DGNat	GENFONT();


// GLBASIC NX
DGNat	NETHOSTGAME(DGNat port_tcp);
DGNat	NETJOINGAME(const DGStr& address, DGNat port_tcp);
void	NETSHUTDOWN();
DGNat	NETCREATEPLAYER(const DGStr& Name);
DGStr	NETPLAYERNAME_Str(DGNat Player);
DGNat	NETNUMPLAYERS();
DGNat	NETGETQUITPLAYER();
DGNat	NETGETPLAYERID(DGNat num);
DGStr	NETGETIP_Str();
DGStr	NETGETLASTERROR_Str();
DGNat	NETWEBGET(const DGStr& server, const DGStr& path, DGNat port, const DGStr& local, DGNat timeout_ms=5000);
DGStr	NETWEBGET_Str(const DGStr& server, const DGStr& path, DGNat port, DGNat max_length, DGNat timeout_ms=5000);
void	NETWEBEND(DGStr url);
DGNat   NETISACTIVE();
void	NETALLOWJOINING(DGNat allow);

// SOCKETS
DGNat SOCK_INIT();
void  SOCK_SHUTDOWN();
DGNat SOCK_TCPLISTEN(DGNat port);
DGNat SOCK_TCPCONNECT(const DGStr& server, DGNat port, DGNat timeout=5000);
DGNat SOCK_TCPACCEPT(DGNat socket, DGNat& ip);
DGNat SOCK_TCPSEND(DGNat sock_to, const DGStr& msg);
DGNat SOCK_UDPOPEN(DGNat port);
DGNat SOCK_GETIP(const DGStr& server);
DGStr SOCK_GETIP_Str(DGNat ip);

DGNat SOCK_GETREMOTEIP(DGNat sock);
DGNat SOCK_GETREMOTEPORT(DGNat sock);

DGNat SOCK_UDPSEND(DGNat sock, const DGStr& msg, DGNat ip, DGNat port);
DGNat SOCK_RECV(DGNat sock_from, DGStr& msg, DGNat length);
void  SOCK_SETBLOCKING(DGNat socket, DGNat block);
DGNat SOCK_CLOSE(DGNat socket);

// DGStr Player = DPID of player
void	NETDESTROYPLAYER(DGNat Player);
DGNat	NETSENDMSG(DGNat Player, DGNat Recipent, const DGStr& Messy);
DGStr	NETGETMSG_Str(DGNat Player);
DGNat	NETGETSENDER();

// New Joystick Commands
DGInt	GETJOYX(DGNat nJoy);
DGInt	GETJOYY(DGNat nJoy);
DGInt	GETJOYZ(DGNat nJoy);
DGInt	GETJOYRX(DGNat nJoy);
DGInt	GETJOYRY(DGNat nJoy);
DGInt	GETJOYRZ(DGNat nJoy);
DGInt	GETDIGIX(DGNat nJoy);
DGInt	GETDIGIY(DGNat nJoy);
DGNat	GETJOYBUTTON(DGNat nJoy, DGNat Button);
DGInt	GETNUMJOYSTICKS(void);
DGStr	GETJOYNAME_Str(DGNat nJoy);
void	FORCEFEEDBACK(DGNat nJoy, DGInt duration, DGInt x_motor, DGInt y_motor);

DGNat FINDPATH(DGIntArray& map, DGNatArray& solutions, DGInt heuristic, DGNat xstart, DGNat ystart, DGNat xend, DGNat yend);
DGNat FINDPATH(DGNatArray& map, DGNatArray& solutions, DGInt heuristic, DGNat xstart, DGNat ystart, DGNat xend, DGNat yend);
DGNat FINDPATH(DGIntArray& map, DGIntArray& solutions, DGInt heuristic, DGNat xstart, DGNat ystart, DGNat xend, DGNat yend);


#ifdef __EXCEPTIONS
# define glbtry      try
# define glbcatch(X) catch(X)
	inline void	THROW(DGStr err) {throw err;}
#else
# define glbtry      if (1)
# define glbcatch(X) for (X; 0; )
	inline void	THROW(DGStr err) {DEBUG(err); STDERR(err); ASSERT(0); END();}
#endif

// Extern Symbols

extern "C"
{
	extern int				__DG_RESX; // window screen res
	extern int				__DG_RESY;
	extern int				__DG_DESKTOPX;
	extern int				__DG_DESKTOPY;
	extern int				__DG_MULTISAMPLE;
	extern int				__DG_DEBUG;
	extern int				__DG_FRAMERATE;
	extern int				__DG_WANTMOUSE;
	extern int				__DG_FULLSCREEN;
	extern void				__GLB_Defaults();
}


extern DGNat			__g_debugline;
extern DGNat			__g_error;
extern DGNat			__g_errorline;
void					__SetDemoVersion();
extern int				__DG_SCHOOLVER;
extern DGInt			__HR;


DGStr&			__glb_cmdline();
DGStr&			__glb_AppName();

#ifdef POCKETPC
extern int				__g_mx, __g_my;
#endif

	// INLINE gags
	void* GLBASIC_HWND();
	void DLLCALL(const char* dll, const char* func, void** pPointer);
	void DLL_DELAY_LOAD_NOW();

	struct c_dll_fkt_loadr {c_dll_fkt_loadr(const char* dllname, const char* realname, void** pFoo) {DLLCALL(dllname, realname, pFoo);}};

	#define         DECLARE(declname, dll          , paras, ret) ret (__stdcall* declname) paras=0; c_dll_fkt_loadr g_fl ##declname(dll, #declname, (void**)& declname);
	#define       DECLARE_C(declname, dll          , paras, ret) ret (         * declname) paras=0; c_dll_fkt_loadr g_fl ##declname(dll, #declname, (void**)& declname);
	#define   DECLARE_ALIAS(declname, dll, realname, paras, ret) ret (__stdcall* declname) paras=0; c_dll_fkt_loadr g_fl ##declname(dll,  realname, (void**)& declname);
	#define DECLARE_C_ALIAS(declname, dll, realname, paras, ret) ret (         * declname) paras=0; c_dll_fkt_loadr g_fl ##declname(dll,  realname, (void**)& declname);

	// wrap pointer-to-function objects
	template<class prototype> struct GLB_PROTO
	{
		prototype ptr;
		GLB_PROTO() : ptr(NULL){}
		inline prototype operator=( prototype p) {ptr = p; return ptr;}
		inline operator prototype()
		{
			if(!ptr) {__Error(CMP_WRONG_ARGUMENT); __EndProgram();}
			return ptr;
		}
		inline operator DGNat() {return ptr ? TRUE:FALSE;}
		bool operator< (const GLB_PROTO& p)const {return ptr > p.ptr;}
		bool operator> (const GLB_PROTO& p)const {return ptr < p.ptr;}
		bool operator==(const GLB_PROTO& p)const {return ptr ==p.ptr;}
	};
	#define PROTODECL(proto, retval, args) typedef retval(* __glb_ ##proto) args; typedef GLB_PROTO< __glb_ ##proto> proto;

#ifndef POCKETPC
	#ifndef WIN32
		#undef WANT_GLB_DEBUGGER
	#endif

	#ifdef WANT_GLB_DEBUGGER
		// debugable variables
		#define MAX_DBG_VARS	1024
		#define MAX_BREAKPOINTS	1024

		// Container for registered variables
		extern int __g_FunctionStackDepth;
		extern int __g_FunctionStackDepth_StepOver;
		class __VAR_CONTAINER
		{
		public:
			struct A_VAR
			{
				const char* pName;
				int			type;
				const void*	pVar;
			};
			__VAR_CONTAINER()	{num=0; ++__g_FunctionStackDepth;}
			~__VAR_CONTAINER()	{--__g_FunctionStackDepth;}
			void push(const char* pName, int type, const void* p){A_VAR var; var.pName=pName; var.type=type; var.pVar=p; data[num++] = var;}
			void pop(const void* p)							{
																for(int i=0; i<num; ++i)
																{
																	if (data[i].pVar == p)
																		{data[i] = data[--num]; break;}
																}
															}
			int num;
			A_VAR data[MAX_DBG_VARS];
		};

		// variable creation object
	/*
			case 0: // DGInt
			case 1: // DGStr
			case 2: // DGIntArray
			case 3: // DGStrArray
			case 4: // UserType
			case 5: // DGNat
			case 6: // DGNatArray
	*/
		class __VAR_OBJECT
		{
		public:
			template<class T> __VAR_OBJECT(const char* pName, const T& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 4, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGInt& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 0, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGNat& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 5, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGStr& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 1, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGIntArray& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 2, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGStrArray& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 3, (void*)&t); FixName(pParent);}
			__VAR_OBJECT(const char* pName, const DGNatArray& t, __VAR_CONTAINER& cnt, const void* pParent=NULL) {pCont = &cnt; pVar=(const void*)&t; cnt.push(pName, 6, (void*)&t); FixName(pParent);}
			~__VAR_OBJECT() {pCont->pop(pVar);}
			void FixName(const void* pParent) {} //#NEED
			__VAR_CONTAINER* pCont;
			const void* pVar;
		};

		// Breakpoints
		struct __BREAKPOINTS
		{
			long fileid[MAX_BREAKPOINTS];
			long lineid[MAX_BREAKPOINTS];
		};

		// interaction structure
		struct __DEBUGGER
		{
			__DEBUGGER(){num_bp=0; num_glob=0; num_loc=0; pGlobals=NULL; pLocals=NULL; firsttime=1000; suicide=0; stepover=0;}
			int    num_bp, num_glob, num_loc, firsttime, curfile, curline, suicide, stepover;
			long* fileid;
			long* lineid;
			__VAR_CONTAINER::A_VAR *pGlobals, *pLocals;
		};


		void __PauseAndDebug(void*);

		#define H_REGISTER_VAR(typ, var)			extern typ var; extern __VAR_OBJECT reg ##var;
		#define H_REGISTER_VAR_DEF(typ, var, def)	extern typ var; extern __VAR_OBJECT reg ##var;
		#define REGISTER_VAR(typ, var)			typ var    ; __VAR_OBJECT reg ##var(#var, var, __FKT);
		#define REGISTER_VAR_DEF(typ, var, def) typ var=def; __VAR_OBJECT reg ##var(#var, var, __FKT);
		#define REGISTER_MEMBER(var)				var(#var, var, __FKT, this)
		#define ARGS_VAR(typ, var)			__VAR_OBJECT reg ##var(#var, var, __FKT);
		#define ON_DEBUG(nfile, nline)	__on_debug(nfile, nline, __FKT);

		// Global variables - only in _g.cpp file
		#define __FKT __g_dbg_cont
		#ifdef DD_GLOBALS_FILE
			int __g_FunctionStackDepth = 0;
			int __g_FunctionStackDepth_StepOver = 0;

			__VAR_CONTAINER __FKT;
			__DEBUGGER __g_dbg;
			__BREAKPOINTS __g_breakpoints;


			// ------------------------------------------------------------- //
			// At each line, check if the debugger wants something
			// ------------------------------------------------------------- //
			void __on_debug(int nfile, int nline, __VAR_CONTAINER& __l_dbg_cont)
			{
				__dLn(nfile, nline);

				if(__g_dbg.stepover)
				{
					if (__g_FunctionStackDepth <= __g_FunctionStackDepth_StepOver)
						goto ok_debug;
					// else
					//	__g_FunctionStackDepth_StepOver = MIN(__g_FunctionStackDepth, __g_FunctionStackDepth_StepOver);
				}
				if(__g_dbg.firsttime)
					goto ok_debug;
				for(int n=0; n<__g_dbg.num_bp; ++n)
				{
					if(__g_breakpoints.fileid[n]==nfile && __g_breakpoints.lineid[n]==nline)
						goto ok_debug;
				}
				return;
				ok_debug:
					if(__g_dbg.suicide) END();
					__g_dbg.curfile=nfile; __g_dbg.curline=nline;
					__g_dbg.pGlobals = & __g_dbg_cont.data[0];
					__g_dbg.pLocals  = & __l_dbg_cont.data[0];
					__g_dbg.fileid = __g_breakpoints.fileid;
					__g_dbg.lineid = __g_breakpoints.lineid;
					__g_dbg.num_glob = __g_dbg_cont.num;
					__g_dbg.num_loc  = __l_dbg_cont.num;

					__PauseAndDebug((void*)&__g_dbg);

					__g_dbg.firsttime = 0;
					switch(__g_dbg.stepover)
					{
					case -1:
						__g_dbg.stepover=1;
						__g_FunctionStackDepth_StepOver = __g_FunctionStackDepth-1; break;
					case 1:
						__g_dbg.stepover=1;
						__g_FunctionStackDepth_StepOver = __g_FunctionStackDepth+1; break;
					case 0:
						__g_dbg.stepover=1;
						__g_FunctionStackDepth_StepOver = __g_FunctionStackDepth;
						//__g_dbg.firsttime = 1;
						break;
					case 100:// continue
						__g_dbg.stepover=0;
						__g_FunctionStackDepth_StepOver = 0;
						__g_dbg.firsttime = 0;
						break;
					}

			}
		#else
			void __on_debug(int nfile, int nline, __VAR_CONTAINER& __l_dbg_cont);
		#endif


	// No debugger
	#else
		// debugger interface for release version
		#define H_REGISTER_VAR(typ, var)			extern typ var;
		#define H_REGISTER_VAR_DEF(typ, var, def)	extern typ var;
		#define REGISTER_VAR(typ, var)				typ var;
		#define REGISTER_VAR_DEF(typ, var, def)		typ var=def; // can also be static!!
		#define ON_DEBUG(nfile, nline) __dLn(nfile, nline)
		#define REGISTER_MEMBER(parent, var)		var(#var, var, var)
		class __VAR_OBJECT
		{
			public:
				template<class T, class U> __VAR_OBJECT(const char* c, const T& t, U& v) {}
		};
	#endif

#endif // not POCKETPC

}; // namespace __GLBASIC__
using namespace __GLBASIC__;


// #define INPUT __GLBASIC__::INPUT

#ifdef POCKETPC
	// For WinCE WinMain...
	#ifdef _WIN32_WCE
	#undef LPSTR
	#define LPSTR LPWSTR
	#endif

	#define INPUT	__GLBASIC__::INPUT

	// debugger interface for release version
	#define ARGS_VAR(typ, var)
	#define H_REGISTER_VAR(typ, var)			extern typ var;
	#define H_REGISTER_VAR_DEF(typ, var, def)	extern typ var;
	#define REGISTER_VAR(typ, var)				typ var;
	#define REGISTER_VAR_DEF(typ, var, def)		typ var=def;
	#define ON_DEBUG(nfile, nline) __dLn(nfile, nline);
	#define __VAR_CONTAINER int
#endif


// GLBasic Profiling Instruments
#ifdef FUNCTION_PROFILE
	#define __PPRegisterFunction GFProfilerClass profiler(__FUNCTION__);
	#define __PPExportProf(a,b,c) {GFProfilerClass::ExportProf(a,b,c);}

	// the main class
	class GFProfilerClass
	{
	public:
		// the constructor and the destructor each registers a ProfRecord
		// at the entry and the exit points of the functions
		GFProfilerClass(const char* lpszFuncName);
		~GFProfilerClass();
		static void ExportProf(const char* cstrFileName, const char* date, const char* time); // exports results to a CSV file
		const char*	m_pszFuncName;
	};
#else
	#define __PPRegisterFunction
	#define __PPExportProf(a,b,c) {}
#endif

void SetupAccurateTimer();
DGInt AccurateTime();



#endif // DEFINE





