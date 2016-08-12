# 1 "test/test_Linklist.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "test/test_Linklist.c"
# 1 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity.h" 1
# 16 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity.h"
# 1 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 1
# 14 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
# 1 "c:\\mingw\\include\\setjmp.h" 1 3
# 16 "c:\\mingw\\include\\setjmp.h" 3
# 1 "c:\\mingw\\include\\_mingw.h" 1 3
# 41 "c:\\mingw\\include\\_mingw.h" 3
       
# 42 "c:\\mingw\\include\\_mingw.h" 3
# 17 "c:\\mingw\\include\\setjmp.h" 2 3
# 33 "c:\\mingw\\include\\setjmp.h" 3
typedef int jmp_buf[16];





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _setjmp (jmp_buf);







 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) longjmp (jmp_buf, int) __attribute__ ((__noreturn__));
# 15 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 2






# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stdint.h" 1 3 4
# 9 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stdint.h" 3 4
# 1 "c:\\mingw\\include\\stdint.h" 1 3 4
# 24 "c:\\mingw\\include\\stdint.h" 3 4
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 1 3 4
# 324 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 3 4
typedef short unsigned int wchar_t;
# 353 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 3 4
typedef short unsigned int wint_t;
# 25 "c:\\mingw\\include\\stdint.h" 2 3 4


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
typedef long long int_least64_t;
typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
typedef long long int_fast64_t;
typedef unsigned long long uint_fast64_t;
# 66 "c:\\mingw\\include\\stdint.h" 3 4
  typedef int intptr_t;
# 75 "c:\\mingw\\include\\stdint.h" 3 4
  typedef unsigned int uintptr_t;




typedef long long intmax_t;
typedef unsigned long long uintmax_t;
# 10 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stdint.h" 2 3 4
# 22 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 2



# 1 "c:\\mingw\\include\\limits.h" 1 3
# 26 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 2
# 41 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
# 1 "c:\\mingw\\include\\math.h" 1 3
# 16 "c:\\mingw\\include\\math.h" 3
       
# 17 "c:\\mingw\\include\\math.h" 3
# 139 "c:\\mingw\\include\\math.h" 3
struct _exception
{
 int type;
 char *name;
 double arg1;
 double arg2;
 double retval;
};

 double __attribute__((__cdecl__)) sin (double);
 double __attribute__((__cdecl__)) cos (double);
 double __attribute__((__cdecl__)) tan (double);
 double __attribute__((__cdecl__)) sinh (double);
 double __attribute__((__cdecl__)) cosh (double);
 double __attribute__((__cdecl__)) tanh (double);
 double __attribute__((__cdecl__)) asin (double);
 double __attribute__((__cdecl__)) acos (double);
 double __attribute__((__cdecl__)) atan (double);
 double __attribute__((__cdecl__)) atan2 (double, double);
 double __attribute__((__cdecl__)) exp (double);
 double __attribute__((__cdecl__)) log (double);
 double __attribute__((__cdecl__)) log10 (double);
 double __attribute__((__cdecl__)) pow (double, double);
 double __attribute__((__cdecl__)) sqrt (double);
 double __attribute__((__cdecl__)) ceil (double);
 double __attribute__((__cdecl__)) floor (double);
 double __attribute__((__cdecl__)) fabs (double);
 double __attribute__((__cdecl__)) ldexp (double, int);
 double __attribute__((__cdecl__)) frexp (double, int*);
 double __attribute__((__cdecl__)) modf (double, double*);
 double __attribute__((__cdecl__)) fmod (double, double);
# 215 "c:\\mingw\\include\\math.h" 3
struct _complex
{
 double x;
 double y;
};

 double __attribute__((__cdecl__)) _cabs (struct _complex);

 double __attribute__((__cdecl__)) _hypot (double, double);
 double __attribute__((__cdecl__)) _j0 (double);
 double __attribute__((__cdecl__)) _j1 (double);
 double __attribute__((__cdecl__)) _jn (int, double);
 double __attribute__((__cdecl__)) _y0 (double);
 double __attribute__((__cdecl__)) _y1 (double);
 double __attribute__((__cdecl__)) _yn (int, double);
 int __attribute__((__cdecl__)) _matherr (struct _exception *);
# 239 "c:\\mingw\\include\\math.h" 3
 double __attribute__((__cdecl__)) _chgsign (double);
 double __attribute__((__cdecl__)) _copysign (double, double);
 double __attribute__((__cdecl__)) _logb (double);
 double __attribute__((__cdecl__)) _nextafter (double, double);
 double __attribute__((__cdecl__)) _scalb (double, long);

 int __attribute__((__cdecl__)) _finite (double);
 int __attribute__((__cdecl__)) _fpclass (double);
 int __attribute__((__cdecl__)) _isnan (double);
# 259 "c:\\mingw\\include\\math.h" 3
 double __attribute__((__cdecl__)) j0 (double);
 double __attribute__((__cdecl__)) j1 (double);
 double __attribute__((__cdecl__)) jn (int, double);
 double __attribute__((__cdecl__)) y0 (double);
 double __attribute__((__cdecl__)) y1 (double);
 double __attribute__((__cdecl__)) yn (int, double);

 double __attribute__((__cdecl__)) chgsign (double);
# 275 "c:\\mingw\\include\\math.h" 3
 int __attribute__((__cdecl__)) finite (double);
 int __attribute__((__cdecl__)) fpclass (double);
# 329 "c:\\mingw\\include\\math.h" 3
typedef long double float_t;
typedef long double double_t;
# 359 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __fpclassifyf (float);
extern int __attribute__((__cdecl__)) __fpclassify (double);
extern int __attribute__((__cdecl__)) __fpclassifyl (long double);
# 384 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __isnan (double);
extern int __attribute__((__cdecl__)) __isnanf (float);
extern int __attribute__((__cdecl__)) __isnanl (long double);
# 424 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __signbit (double);
extern int __attribute__((__cdecl__)) __signbitf (float);
extern int __attribute__((__cdecl__)) __signbitl (long double);
# 452 "c:\\mingw\\include\\math.h" 3
extern float __attribute__((__cdecl__)) sinf (float);
extern long double __attribute__((__cdecl__)) sinl (long double);

extern float __attribute__((__cdecl__)) cosf (float);
extern long double __attribute__((__cdecl__)) cosl (long double);

extern float __attribute__((__cdecl__)) tanf (float);
extern long double __attribute__((__cdecl__)) tanl (long double);

extern float __attribute__((__cdecl__)) asinf (float);
extern long double __attribute__((__cdecl__)) asinl (long double);

extern float __attribute__((__cdecl__)) acosf (float);
extern long double __attribute__((__cdecl__)) acosl (long double);

extern float __attribute__((__cdecl__)) atanf (float);
extern long double __attribute__((__cdecl__)) atanl (long double);

extern float __attribute__((__cdecl__)) atan2f (float, float);
extern long double __attribute__((__cdecl__)) atan2l (long double, long double);


extern float __attribute__((__cdecl__)) sinhf (float);




extern long double __attribute__((__cdecl__)) sinhl (long double);

extern float __attribute__((__cdecl__)) coshf (float);




extern long double __attribute__((__cdecl__)) coshl (long double);

extern float __attribute__((__cdecl__)) tanhf (float);




extern long double __attribute__((__cdecl__)) tanhl (long double);



extern double __attribute__((__cdecl__)) acosh (double);
extern float __attribute__((__cdecl__)) acoshf (float);
extern long double __attribute__((__cdecl__)) acoshl (long double);


extern double __attribute__((__cdecl__)) asinh (double);
extern float __attribute__((__cdecl__)) asinhf (float);
extern long double __attribute__((__cdecl__)) asinhl (long double);


extern double __attribute__((__cdecl__)) atanh (double);
extern float __attribute__((__cdecl__)) atanhf (float);
extern long double __attribute__((__cdecl__)) atanhl (long double);



extern float __attribute__((__cdecl__)) expf (float);




extern long double __attribute__((__cdecl__)) expl (long double);


extern double __attribute__((__cdecl__)) exp2(double);
extern float __attribute__((__cdecl__)) exp2f(float);
extern long double __attribute__((__cdecl__)) exp2l(long double);



extern double __attribute__((__cdecl__)) expm1(double);
extern float __attribute__((__cdecl__)) expm1f(float);
extern long double __attribute__((__cdecl__)) expm1l(long double);


extern float __attribute__((__cdecl__)) frexpf (float, int*);




extern long double __attribute__((__cdecl__)) frexpl (long double, int*);




extern int __attribute__((__cdecl__)) ilogb (double);
extern int __attribute__((__cdecl__)) ilogbf (float);
extern int __attribute__((__cdecl__)) ilogbl (long double);


extern float __attribute__((__cdecl__)) ldexpf (float, int);




extern long double __attribute__((__cdecl__)) ldexpl (long double, int);


extern float __attribute__((__cdecl__)) logf (float);
extern long double __attribute__((__cdecl__)) logl (long double);


extern float __attribute__((__cdecl__)) log10f (float);
extern long double __attribute__((__cdecl__)) log10l (long double);


extern double __attribute__((__cdecl__)) log1p(double);
extern float __attribute__((__cdecl__)) log1pf(float);
extern long double __attribute__((__cdecl__)) log1pl(long double);


extern double __attribute__((__cdecl__)) log2 (double);
extern float __attribute__((__cdecl__)) log2f (float);
extern long double __attribute__((__cdecl__)) log2l (long double);


extern double __attribute__((__cdecl__)) logb (double);
extern float __attribute__((__cdecl__)) logbf (float);
extern long double __attribute__((__cdecl__)) logbl (long double);
# 608 "c:\\mingw\\include\\math.h" 3
extern float __attribute__((__cdecl__)) modff (float, float*);
extern long double __attribute__((__cdecl__)) modfl (long double, long double*);


extern double __attribute__((__cdecl__)) scalbn (double, int);
extern float __attribute__((__cdecl__)) scalbnf (float, int);
extern long double __attribute__((__cdecl__)) scalbnl (long double, int);

extern double __attribute__((__cdecl__)) scalbln (double, long);
extern float __attribute__((__cdecl__)) scalblnf (float, long);
extern long double __attribute__((__cdecl__)) scalblnl (long double, long);



extern double __attribute__((__cdecl__)) cbrt (double);
extern float __attribute__((__cdecl__)) cbrtf (float);
extern long double __attribute__((__cdecl__)) cbrtl (long double);


extern float __attribute__((__cdecl__)) fabsf (float x);
extern long double __attribute__((__cdecl__)) fabsl (long double x);


extern double __attribute__((__cdecl__)) hypot (double, double);
extern float __attribute__((__cdecl__)) hypotf (float, float);




extern long double __attribute__((__cdecl__)) hypotl (long double, long double);


extern float __attribute__((__cdecl__)) powf (float, float);




extern long double __attribute__((__cdecl__)) powl (long double, long double);


extern float __attribute__((__cdecl__)) sqrtf (float);
extern long double __attribute__((__cdecl__)) sqrtl (long double);


extern double __attribute__((__cdecl__)) erf (double);
extern float __attribute__((__cdecl__)) erff (float);
extern long double __attribute__((__cdecl__)) erfl (long double);


extern double __attribute__((__cdecl__)) erfc (double);
extern float __attribute__((__cdecl__)) erfcf (float);
extern long double __attribute__((__cdecl__)) erfcl (long double);


extern double __attribute__((__cdecl__)) lgamma (double);
extern float __attribute__((__cdecl__)) lgammaf (float);
extern long double __attribute__((__cdecl__)) lgammal (long double);


extern double __attribute__((__cdecl__)) tgamma (double);
extern float __attribute__((__cdecl__)) tgammaf (float);
extern long double __attribute__((__cdecl__)) tgammal (long double);


extern float __attribute__((__cdecl__)) ceilf (float);
extern long double __attribute__((__cdecl__)) ceill (long double);


extern float __attribute__((__cdecl__)) floorf (float);
extern long double __attribute__((__cdecl__)) floorl (long double);


extern double __attribute__((__cdecl__)) nearbyint ( double);
extern float __attribute__((__cdecl__)) nearbyintf (float);
extern long double __attribute__((__cdecl__)) nearbyintl (long double);



extern double __attribute__((__cdecl__)) rint (double);
extern float __attribute__((__cdecl__)) rintf (float);
extern long double __attribute__((__cdecl__)) rintl (long double);


extern long __attribute__((__cdecl__)) lrint (double);
extern long __attribute__((__cdecl__)) lrintf (float);
extern long __attribute__((__cdecl__)) lrintl (long double);

extern long long __attribute__((__cdecl__)) llrint (double);
extern long long __attribute__((__cdecl__)) llrintf (float);
extern long long __attribute__((__cdecl__)) llrintl (long double);
# 776 "c:\\mingw\\include\\math.h" 3
extern double __attribute__((__cdecl__)) round (double);
extern float __attribute__((__cdecl__)) roundf (float);
extern long double __attribute__((__cdecl__)) roundl (long double);


extern long __attribute__((__cdecl__)) lround (double);
extern long __attribute__((__cdecl__)) lroundf (float);
extern long __attribute__((__cdecl__)) lroundl (long double);

extern long long __attribute__((__cdecl__)) llround (double);
extern long long __attribute__((__cdecl__)) llroundf (float);
extern long long __attribute__((__cdecl__)) llroundl (long double);



extern double __attribute__((__cdecl__)) trunc (double);
extern float __attribute__((__cdecl__)) truncf (float);
extern long double __attribute__((__cdecl__)) truncl (long double);


extern float __attribute__((__cdecl__)) fmodf (float, float);
extern long double __attribute__((__cdecl__)) fmodl (long double, long double);


extern double __attribute__((__cdecl__)) remainder (double, double);
extern float __attribute__((__cdecl__)) remainderf (float, float);
extern long double __attribute__((__cdecl__)) remainderl (long double, long double);


extern double __attribute__((__cdecl__)) remquo(double, double, int *);
extern float __attribute__((__cdecl__)) remquof(float, float, int *);
extern long double __attribute__((__cdecl__)) remquol(long double, long double, int *);


extern double __attribute__((__cdecl__)) copysign (double, double);
extern float __attribute__((__cdecl__)) copysignf (float, float);
extern long double __attribute__((__cdecl__)) copysignl (long double, long double);


extern double __attribute__((__cdecl__)) nan(const char *tagp);
extern float __attribute__((__cdecl__)) nanf(const char *tagp);
extern long double __attribute__((__cdecl__)) nanl(const char *tagp);
# 826 "c:\\mingw\\include\\math.h" 3
extern double __attribute__((__cdecl__)) nextafter (double, double);
extern float __attribute__((__cdecl__)) nextafterf (float, float);
extern long double __attribute__((__cdecl__)) nextafterl (long double, long double);


extern double __attribute__((__cdecl__)) nexttoward (double, long double);
extern float __attribute__((__cdecl__)) nexttowardf (float, long double);
extern long double __attribute__((__cdecl__)) nexttowardl (long double, long double);



extern double __attribute__((__cdecl__)) fdim (double x, double y);
extern float __attribute__((__cdecl__)) fdimf (float x, float y);
extern long double __attribute__((__cdecl__)) fdiml (long double x, long double y);







extern double __attribute__((__cdecl__)) fmax (double, double);
extern float __attribute__((__cdecl__)) fmaxf (float, float);
extern long double __attribute__((__cdecl__)) fmaxl (long double, long double);


extern double __attribute__((__cdecl__)) fmin (double, double);
extern float __attribute__((__cdecl__)) fminf (float, float);
extern long double __attribute__((__cdecl__)) fminl (long double, long double);



extern double __attribute__((__cdecl__)) fma (double, double, double);
extern float __attribute__((__cdecl__)) fmaf (float, float, float);
extern long double __attribute__((__cdecl__)) fmal (long double, long double, long double);
# 42 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 2
# 119 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
    typedef unsigned char _UU8;
    typedef unsigned short _UU16;
    typedef unsigned int _UU32;
    typedef signed char _US8;
    typedef signed short _US16;
    typedef signed int _US32;
# 154 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
typedef _UU32 _U_UINT;
typedef _US32 _U_SINT;
# 179 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
    typedef _UU32 _UP;
# 225 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
typedef float _UF;
# 292 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
# 1 "c:\\mingw\\include\\stdio.h" 1 3
# 26 "c:\\mingw\\include\\stdio.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 1 3 4
# 212 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 3 4
typedef unsigned int size_t;
# 27 "c:\\mingw\\include\\stdio.h" 2 3

# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stdarg.h" 1 3 4
# 40 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 29 "c:\\mingw\\include\\stdio.h" 2 3
# 130 "c:\\mingw\\include\\stdio.h" 3
typedef struct _iobuf
{
 char* _ptr;
 int _cnt;
 char* _base;
 int _flag;
 int _file;
 int _charbuf;
 int _bufsiz;
 char* _tmpfname;
} FILE;
# 155 "c:\\mingw\\include\\stdio.h" 3
extern __attribute__ ((__dllimport__)) FILE _iob[];












 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fopen (const char*, const char*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) freopen (const char*, const char*, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fflush (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fclose (FILE*);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) remove (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rename (const char*, const char*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tmpfile (void);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tmpnam (char*);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _rmtmp(void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _unlink (const char*);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rmtmp(void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) unlink (const char*);



 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) setvbuf (FILE*, char*, int, size_t);

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) setbuf (FILE*, char*);
# 203 "c:\\mingw\\include\\stdio.h" 3
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_fprintf(FILE*, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_printf(const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_sprintf(char*, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_snprintf(char*, size_t, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vfprintf(FILE*, const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vprintf(const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vsprintf(char*, const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vsnprintf(char*, size_t, const char*, __gnuc_va_list);
# 292 "c:\\mingw\\include\\stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fprintf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) printf (const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) sprintf (char*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfprintf (FILE*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vprintf (const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsprintf (char*, const char*, __gnuc_va_list);
# 307 "c:\\mingw\\include\\stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_fprintf(FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_printf(const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_sprintf(char*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vfprintf(FILE*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vprintf(const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vsprintf(char*, const char*, __gnuc_va_list);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _snprintf (char*, size_t, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vsnprintf (char*, size_t, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vscprintf (const char*, __gnuc_va_list);
# 330 "c:\\mingw\\include\\stdio.h" 3
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) snprintf (char *, size_t, const char *, ...);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsnprintf (char *, size_t, const char *, __gnuc_va_list);

int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vscanf (const char * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfscanf (FILE * __restrict__, const char * __restrict__,
       __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsscanf (const char * __restrict__,
       const char * __restrict__, __gnuc_va_list);







 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fscanf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) scanf (const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) sscanf (const char*, const char*, ...);




 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetc (FILE*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgets (char*, int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputc (int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputs (const char*, FILE*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) gets (char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) puts (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ungetc (int, FILE*);







 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _filbuf (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _flsbuf (int, FILE*);



extern __inline__ int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getc (FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) *__F->_ptr++
    : _filbuf (__F);
}

extern __inline__ int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putc (int __c, FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) (*__F->_ptr++ = (char)__c)
    : _flsbuf (__c, __F);
}

extern __inline__ int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getchar (void)
{
  return (--(&_iob[0])->_cnt >= 0)
    ? (int) (unsigned char) *(&_iob[0])->_ptr++
    : _filbuf ((&_iob[0]));
}

extern __inline__ int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putchar(int __c)
{
  return (--(&_iob[1])->_cnt >= 0)
    ? (int) (unsigned char) (*(&_iob[1])->_ptr++ = (char)__c)
    : _flsbuf (__c, (&_iob[1]));}
# 411 "c:\\mingw\\include\\stdio.h" 3
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fread (void*, size_t, size_t, FILE*);
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwrite (const void*, size_t, size_t, FILE*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fseek (FILE*, long, int);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ftell (FILE*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rewind (FILE*);
# 454 "c:\\mingw\\include\\stdio.h" 3
typedef long long fpos_t;




 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetpos (FILE*, fpos_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fsetpos (FILE*, const fpos_t*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) feof (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ferror (FILE*);
# 479 "c:\\mingw\\include\\stdio.h" 3
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) clearerr (FILE*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) perror (const char*);






 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _popen (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _pclose (FILE*);


 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) popen (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) pclose (FILE*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _flushall (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fgetchar (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fputchar (int);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fdopen (int, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fileno (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fcloseall (void);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fsopen (const char*, const char*, int);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getmaxstdio (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _setmaxstdio (int);
# 526 "c:\\mingw\\include\\stdio.h" 3
unsigned int __attribute__((__cdecl__)) __mingw_get_output_format (void);
unsigned int __attribute__((__cdecl__)) __mingw_set_output_format (unsigned int);







int __attribute__((__cdecl__)) __mingw_get_printf_count_output (void);
int __attribute__((__cdecl__)) __mingw_set_printf_count_output (int);
# 553 "c:\\mingw\\include\\stdio.h" 3
extern __inline__ __attribute__((__always_inline__)) unsigned int __attribute__((__cdecl__)) _get_output_format (void)
{ return __mingw_get_output_format (); }

extern __inline__ __attribute__((__always_inline__)) unsigned int __attribute__((__cdecl__)) _set_output_format (unsigned int __style)
{ return __mingw_set_output_format (__style); }
# 579 "c:\\mingw\\include\\stdio.h" 3
extern __inline__ __attribute__((__always_inline__)) int __attribute__((__cdecl__)) _get_printf_count_output (void)
{ return 0 ? 1 : __mingw_get_printf_count_output (); }

extern __inline__ __attribute__((__always_inline__)) int __attribute__((__cdecl__)) _set_printf_count_output (int __mode)
{ return 0 ? 1 : __mingw_set_printf_count_output (__mode); }



 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetchar (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputchar (int);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fdopen (int, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fileno (FILE*);
# 599 "c:\\mingw\\include\\stdio.h" 3
# 1 "c:\\mingw\\include\\sys\\types.h" 1 3
# 35 "c:\\mingw\\include\\sys\\types.h" 3
       
# 36 "c:\\mingw\\include\\sys\\types.h" 3
# 45 "c:\\mingw\\include\\sys\\types.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 1 3 4
# 147 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 3 4
typedef int ptrdiff_t;
# 46 "c:\\mingw\\include\\sys\\types.h" 2 3



# 1 "c:\\mingw\\include\\parts\\time.h" 1 3
# 64 "c:\\mingw\\include\\parts\\time.h" 3
   typedef long __time32_t;
   typedef long long __time64_t;
# 74 "c:\\mingw\\include\\parts\\time.h" 3
    typedef __time32_t time_t;
# 50 "c:\\mingw\\include\\sys\\types.h" 2 3




typedef long _off_t;


typedef _off_t off_t;







typedef unsigned int _dev_t;





typedef _dev_t dev_t;






typedef short _ino_t;


typedef _ino_t ino_t;






typedef int _pid_t;


typedef _pid_t pid_t;






typedef unsigned short _mode_t;


typedef _mode_t mode_t;






typedef int _sigset_t;


typedef _sigset_t sigset_t;





typedef int _ssize_t;


typedef _ssize_t ssize_t;





typedef long long fpos64_t;




typedef long long off64_t;







typedef unsigned long useconds_t __attribute__ ((__deprecated__));
# 600 "c:\\mingw\\include\\stdio.h" 2 3
extern __inline__
FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fopen64 (const char* filename, const char* mode)
{ return fopen (filename, mode); }

int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fseeko64 (FILE*, off64_t, int);






extern __inline__
off64_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ftello64 (FILE * stream)
{
  fpos_t pos;
  if (fgetpos(stream, &pos))
    return -1LL;
  else
   return ((off64_t) pos);
}
# 628 "c:\\mingw\\include\\stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwprintf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wprintf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _snwprintf (wchar_t*, size_t, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfwprintf (FILE*, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vwprintf (const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vsnwprintf (wchar_t*, size_t, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vscwprintf (const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwscanf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wscanf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) swscanf (const wchar_t*, const wchar_t*, ...);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetwc (FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputwc (wchar_t, FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ungetwc (wchar_t, FILE*);



 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) swprintf (wchar_t*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vswprintf (wchar_t*, const wchar_t*, __gnuc_va_list);



 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetws (wchar_t*, int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputws (const wchar_t*, FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getwc (FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getwchar (void);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getws (wchar_t*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putwc (wint_t, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putws (const wchar_t*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putwchar (wint_t);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfdopen(int, const wchar_t *);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfopen (const wchar_t*, const wchar_t*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfreopen (const wchar_t*, const wchar_t*, FILE*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfsopen (const wchar_t*, const wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtmpnam (wchar_t*);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtempnam (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wrename (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wremove (const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wperror (const wchar_t*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wpopen (const wchar_t*, const wchar_t*);



int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) snwprintf (wchar_t* s, size_t n, const wchar_t* format, ...);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, __gnuc_va_list arg);





int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vwscanf (const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfwscanf (FILE * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vswscanf (const wchar_t * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
# 690 "c:\\mingw\\include\\stdio.h" 3
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wpopen (const wchar_t*, const wchar_t*);






 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fgetwchar (void);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fputwchar (wint_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getw (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putw (int, FILE*);


 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetwchar (void);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputwchar (wint_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getw (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putw (int, FILE*);





# 293 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h" 2
# 347 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
typedef void (*UnityTestFunction)(void);






typedef enum
{



    UNITY_DISPLAY_STYLE_INT = 4 + (0x10) + (0x80),



    UNITY_DISPLAY_STYLE_INT8 = 1 + (0x10),
    UNITY_DISPLAY_STYLE_INT16 = 2 + (0x10),
    UNITY_DISPLAY_STYLE_INT32 = 4 + (0x10),







    UNITY_DISPLAY_STYLE_UINT = 4 + (0x20) + (0x80),



    UNITY_DISPLAY_STYLE_UINT8 = 1 + (0x20),
    UNITY_DISPLAY_STYLE_UINT16 = 2 + (0x20),
    UNITY_DISPLAY_STYLE_UINT32 = 4 + (0x20),



    UNITY_DISPLAY_STYLE_HEX8 = 1 + (0x40),
    UNITY_DISPLAY_STYLE_HEX16 = 2 + (0x40),
    UNITY_DISPLAY_STYLE_HEX32 = 4 + (0x40),



    UNITY_DISPLAY_STYLE_UNKNOWN
} UNITY_DISPLAY_STYLE_T;


typedef enum _UNITY_FLOAT_TRAIT_T
{
    UNITY_FLOAT_IS_NOT_INF = 0,
    UNITY_FLOAT_IS_INF,
    UNITY_FLOAT_IS_NOT_NEG_INF,
    UNITY_FLOAT_IS_NEG_INF,
    UNITY_FLOAT_IS_NOT_NAN,
    UNITY_FLOAT_IS_NAN,
    UNITY_FLOAT_IS_NOT_DET,
    UNITY_FLOAT_IS_DET,
    UNITY_FLOAT_INVALID_TRAIT
} UNITY_FLOAT_TRAIT_T;


struct _Unity
{
    const char* TestFile;
    const char* CurrentTestName;

    const char* CurrentDetail1;
    const char* CurrentDetail2;

    _U_UINT CurrentTestLineNumber;
    _U_UINT NumberOfTests;
    _U_UINT TestFailures;
    _U_UINT TestIgnores;
    _U_UINT CurrentTestFailed;
    _U_UINT CurrentTestIgnored;
    jmp_buf AbortFrame;
};

extern struct _Unity Unity;





void UnityBegin(const char* filename);
int UnityEnd(void);
void UnityConcludeTest(void);
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum);
# 461 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
void UnityPrint(const char* string);
void UnityPrintMask(const _U_UINT mask, const _U_UINT number);
void UnityPrintNumberByStyle(const _U_SINT number, const UNITY_DISPLAY_STYLE_T style);
void UnityPrintNumber(const _U_SINT number);
void UnityPrintNumberUnsigned(const _U_UINT number);
void UnityPrintNumberHex(const _U_UINT number, const char nibbles);
# 480 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
void UnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char* msg,
                            const _U_UINT lineNumber,
                            const UNITY_DISPLAY_STYLE_T style);

void UnityAssertEqualIntArray( const void* expected,
                              const void* actual,
                              const _UU32 num_elements,
                              const char* msg,
                              const _U_UINT lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

void UnityAssertBits(const _U_SINT mask,
                     const _U_SINT expected,
                     const _U_SINT actual,
                     const char* msg,
                     const _U_UINT lineNumber);

void UnityAssertEqualString(const char* expected,
                            const char* actual,
                            const char* msg,
                            const _U_UINT lineNumber);

void UnityAssertEqualStringLen(const char* expected,
                            const char* actual,
                            const _UU32 length,
                            const char* msg,
                            const _U_UINT lineNumber);

void UnityAssertEqualStringArray( const char** expected,
                                  const char** actual,
                                  const _UU32 num_elements,
                                  const char* msg,
                                  const _U_UINT lineNumber);

void UnityAssertEqualMemory( const void* expected,
                             const void* actual,
                             const _UU32 length,
                             const _UU32 num_elements,
                             const char* msg,
                             const _U_UINT lineNumber);

void UnityAssertNumbersWithin(const _U_UINT delta,
                              const _U_SINT expected,
                              const _U_SINT actual,
                              const char* msg,
                              const _U_UINT lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

void UnityFail(const char* message, const _U_UINT line);

void UnityIgnore(const char* message, const _U_UINT line);


void UnityAssertFloatsWithin(const _UF delta,
                             const _UF expected,
                             const _UF actual,
                             const char* msg,
                             const _U_UINT lineNumber);

void UnityAssertEqualFloatArray( const _UF* expected,
                                const _UF* actual,
                                const _UU32 num_elements,
                                const char* msg,
                                const _U_UINT lineNumber);

void UnityAssertFloatSpecial(const _UF actual,
                             const char* msg,
                             const _U_UINT lineNumber,
                             const UNITY_FLOAT_TRAIT_T style);
# 576 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity_internals.h"
extern const char UnityStrErrFloat[];
extern const char UnityStrErrDouble[];
extern const char UnityStrErr64[];
# 17 "c:/Users/Hwa-Neng/CoIDE/workspace/PCB Laser Etcher/vendor/ceedling/vendor/unity/src/unity.h" 2

void setUp(void);
void tearDown(void);
# 2 "test/test_Linklist.c" 2
# 1 "src/Linklist.h" 1




# 1 "src/projectStruct.h" 1



# 1 "src/Linklist.h" 1
# 5 "src/projectStruct.h" 2
# 6 "src/Linklist.h" 2

typedef struct ListElement_t ListElement;
struct ListElement_t{
   ListElement *next;
   ListElement *prev;
   void (*callBack)(void* unknown);
   void *args;
   uint16_t actionTime;
};
typedef struct Linkedlist_t Linkedlist;
struct Linkedlist_t{
   ListElement *head;
   ListElement *tail;
    uint32_t curTime;
    uint32_t baseTime;
    int callBackState;
    int count;
};

void elementDelete(ListElement* Node);
void linkedListRemove(Linkedlist *newList, ListElement *newElement);
Linkedlist *createLinkedList();
ListElement *createLinkedElement(int x);
void addList( Linkedlist *newList, ListElement *newElement);
# 3 "test/test_Linklist.c" 2

# 1 "c:\\mingw\\include\\malloc.h" 1 3
# 20 "c:\\mingw\\include\\malloc.h" 3
# 1 "c:\\mingw\\include\\stdlib.h" 1 3
# 22 "c:\\mingw\\include\\stdlib.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\4.9.3\\include\\stddef.h" 1 3 4
# 23 "c:\\mingw\\include\\stdlib.h" 2 3
# 60 "c:\\mingw\\include\\stdlib.h" 3

# 70 "c:\\mingw\\include\\stdlib.h" 3
extern int _argc;
extern char** _argv;




extern int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___argc(void);
extern char*** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___argv(void);
extern wchar_t*** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___wargv(void);
# 111 "c:\\mingw\\include\\stdlib.h" 3
   extern __attribute__ ((__dllimport__)) int __mb_cur_max;
# 136 "c:\\mingw\\include\\stdlib.h" 3
 int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _errno(void);


 int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __doserrno(void);
# 148 "c:\\mingw\\include\\stdlib.h" 3
  extern char *** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__environ(void);
  extern wchar_t *** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__wenviron(void);
# 171 "c:\\mingw\\include\\stdlib.h" 3
  extern __attribute__ ((__dllimport__)) int _sys_nerr;
# 195 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__ ((__dllimport__)) char* _sys_errlist[];
# 208 "c:\\mingw\\include\\stdlib.h" 3
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__osver(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winver(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winmajor(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winminor(void);







extern __attribute__ ((__dllimport__)) unsigned int _osver;
extern __attribute__ ((__dllimport__)) unsigned int _winver;
extern __attribute__ ((__dllimport__)) unsigned int _winmajor;
extern __attribute__ ((__dllimport__)) unsigned int _winminor;
# 259 "c:\\mingw\\include\\stdlib.h" 3
 char** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__pgmptr(void);

 wchar_t** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__wpgmptr(void);
# 292 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__ ((__dllimport__)) int _fmode;
# 302 "c:\\mingw\\include\\stdlib.h" 3
 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atof (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atoi (const char*);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atol (const char*);

 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtof (const wchar_t *);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtoi (const wchar_t *);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtol (const wchar_t *);


double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __strtod (const char*, char**);
extern double __attribute__((__cdecl__)) __attribute__ ((__nothrow__))
strtod (const char* __restrict__ __nptr, char** __restrict__ __endptr);
float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtof (const char * __restrict__, char ** __restrict__);
long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtold (const char * __restrict__, char ** __restrict__);




 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtol (const char*, char**, int);
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoul (const char*, char**, int);



 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstol (const wchar_t*, wchar_t**, int);
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstoul (const wchar_t*, wchar_t**, int);
 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstod (const wchar_t*, wchar_t**);

float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstof( const wchar_t * __restrict__, wchar_t ** __restrict__);
long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstold (const wchar_t * __restrict__, wchar_t ** __restrict__);


 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wgetenv(const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wputenv(const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsearchenv(const wchar_t*, const wchar_t*, wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsystem(const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wmakepath(wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsplitpath (const wchar_t*, wchar_t*, wchar_t*, wchar_t*, wchar_t*);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfullpath (wchar_t*, const wchar_t*, size_t);




 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstombs (char*, const wchar_t*, size_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wctomb (char*, wchar_t);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mblen (const char*, size_t);
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mbstowcs (wchar_t*, const char*, size_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mbtowc (wchar_t*, const char*, size_t);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rand (void);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) srand (unsigned int);

 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) calloc (size_t, size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) malloc (size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) realloc (void*, size_t);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) free (void*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) abort (void) __attribute__ ((__noreturn__));
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit (int) __attribute__ ((__noreturn__));


int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atexit (void (*)(void));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) system (const char*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getenv (const char*);


 void* __attribute__((__cdecl__)) bsearch (const void*, const void*, size_t, size_t,
          int (*)(const void*, const void*));
 void __attribute__((__cdecl__)) qsort(void*, size_t, size_t,
      int (*)(const void*, const void*));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) abs (int) __attribute__ ((__const__));
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) labs (long) __attribute__ ((__const__));
# 384 "c:\\mingw\\include\\stdlib.h" 3
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

 div_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) div (int, int) __attribute__ ((__const__));
 ldiv_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ldiv (long, long) __attribute__ ((__const__));







 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _beep (unsigned int, unsigned int) __attribute__ ((__deprecated__));

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _seterrormode (int) __attribute__ ((__deprecated__));
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _sleep (unsigned long) __attribute__ ((__deprecated__));

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit (int) __attribute__ ((__noreturn__));



typedef int (* _onexit_t)(void);
_onexit_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _onexit( _onexit_t );

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putenv (const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _searchenv (const char*, const char*, char*);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _gcvt (double, int, char*);

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _makepath (char*, const char*, const char*, const char*, const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _splitpath (const char*, char*, char*, char*, char*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fullpath (char*, const char*, size_t);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _itoa (int, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ltoa (long, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ultoa(unsigned long, char*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _itow (int, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ltow (long, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ultow (unsigned long, wchar_t*, int);


 long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _atoi64(const char *);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _i64toa(long long, char *, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ui64toa(unsigned long long, char *, int);
 long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtoi64(const wchar_t *);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _i64tow(long long, wchar_t *, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ui64tow(unsigned long long, wchar_t *, int);

 unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_rotl)(unsigned int, int) __attribute__ ((__const__));
 unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_rotr)(unsigned int, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_lrotl)(unsigned long, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_lrotr)(unsigned long, int) __attribute__ ((__const__));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _set_error_mode (int);
# 476 "c:\\mingw\\include\\stdlib.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putenv (const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) searchenv (const char*, const char*, char*);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) itoa (int, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ltoa (long, char*, int);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) gcvt (double, int, char*);
# 496 "c:\\mingw\\include\\stdlib.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _Exit(int) __attribute__ ((__noreturn__));





typedef struct { long long quot, rem; } lldiv_t;

lldiv_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lldiv (long long, long long) __attribute__ ((__const__));

long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) llabs(long long);
# 516 "c:\\mingw\\include\\stdlib.h" 3
long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoll (const char* __restrict__, char** __restrict, int);
unsigned long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoull (const char* __restrict__, char** __restrict__, int);


long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atoll (const char *);


long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wtoll (const wchar_t *);
char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lltoa (long long, char *, int);
char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ulltoa (unsigned long long , char *, int);
wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lltow (long long, wchar_t *, int);
wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ulltow (unsigned long long, wchar_t *, int);
# 567 "c:\\mingw\\include\\stdlib.h" 3
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mkstemp( char * );
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_mkstemp( int, char * );
# 609 "c:\\mingw\\include\\stdlib.h" 3
extern __inline__ __attribute__((__always_inline__))
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mkstemp( char *__filename_template )
{ return __mingw_mkstemp( 0, __filename_template ); }
# 620 "c:\\mingw\\include\\stdlib.h" 3
char * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mkdtemp( char * );
char * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_mkdtemp( char * );

extern __inline__ __attribute__((__always_inline__))
char * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mkdtemp( char *__dirname_template )
{ return __mingw_mkdtemp( __dirname_template ); }




# 21 "c:\\mingw\\include\\malloc.h" 2 3






typedef struct _heapinfo
{
 int* _pentry;
 size_t _size;
 int _useflag;
} _HEAPINFO;
# 56 "c:\\mingw\\include\\malloc.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _heapwalk (_HEAPINFO*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) heapwalk (_HEAPINFO*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _heapchk (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _heapmin (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _heapset (unsigned int);

 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _msize (void*);
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _get_sbh_threshold (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _set_sbh_threshold (size_t);
 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _expand (void*, size_t);
# 90 "c:\\mingw\\include\\malloc.h" 3
void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_aligned_offset_malloc (size_t, size_t, size_t);
void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_aligned_offset_realloc (void*, size_t, size_t, size_t);

void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_aligned_malloc (size_t, size_t);
void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_aligned_realloc (void*, size_t, size_t);
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_aligned_free (void*);
# 5 "test/test_Linklist.c" 2

# 1 "src/CustomAssertion.h" 1
# 22 "src/CustomAssertion.h"
void test_assert_link_list(Linkedlist *newList,uint32_t arr[],int arraySize,int lineNo);
# 7 "test/test_Linklist.c" 2
# 1 "src/projectStruct.h" 1
# 8 "test/test_Linklist.c" 2

void setUp(void)
{
}

void tearDown(void)
{
}

 void test_createLinkedList_the_new_list_was_initialized_by_the_function(void)
{
 Linkedlist *newList = createLinkedList();
 if ((((newList)) != ((void *)0))) {} else {UnityFail( (((" Expected Non-NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(20))));};
 if ((((newList->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(21))));};
 if ((((newList->tail)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(22))));};
  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->baseTime)), (((void *)0)), (_U_UINT)(23), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->curTime)), (((void *)0)), (_U_UINT)(24), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((newList->count)), (((void *)0)), (_U_UINT)(25), UNITY_DISPLAY_STYLE_INT);
}


void test_creatlikedelement_the_element_was_initialized_by_the_function(void){
  ListElement *newNode;
  newNode = createLinkedElement(9);
  UnityAssertEqualNumber((_U_SINT)(_UU16)((9)), (_U_SINT)(_UU16)((newNode->actionTime)), (((void *)0)), (_U_UINT)(32), UNITY_DISPLAY_STYLE_UINT16);
   if ((((newNode->next)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(33))));};

}
# 55 "test/test_Linklist.c"
void test_cycle_link_list_Elem9_Elem8_Elem7_and_Elem6_add_to_link_list(void){

   Linkedlist *list = createLinkedList();
   ListElement *Element9 = createLinkedElement(9);
   ListElement *Element8 = createLinkedElement(8);
   ListElement *Element7 = createLinkedElement(7);
   ListElement *Element6 = createLinkedElement(6);
   addList(list,Element9);
   addList(list,Element8);
   addList(list,Element7);
   addList(list,Element6);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element8)), (_U_SINT)(_UP)((Element9->next)), (((void *)0)), (_U_UINT)(67), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element8->next)), (((void *)0)), (_U_UINT)(68), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((Element7->next)), (((void *)0)), (_U_UINT)(69), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element9)), (_U_SINT)(_UP)((Element6->next)), (((void *)0)), (_U_UINT)(70), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((list->head)), (_U_SINT)(_UP)((Element6->next)), (((void *)0)), (_U_UINT)(71), UNITY_DISPLAY_STYLE_HEX32);

   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((list->head->prev)), (((void *)0)), (_U_UINT)(73), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element6)), (_U_SINT)(_UP)((Element9->prev)), (((void *)0)), (_U_UINT)(74), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element9)), (_U_SINT)(_UP)((Element8->prev)), (((void *)0)), (_U_UINT)(75), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element8)), (_U_SINT)(_UP)((Element7->prev)), (((void *)0)), (_U_UINT)(76), UNITY_DISPLAY_STYLE_HEX32);
   UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element6->prev)), (((void *)0)), (_U_UINT)(77), UNITY_DISPLAY_STYLE_HEX32);

  UnityAssertEqualNumber((_U_SINT)(_UP)((Element7)), (_U_SINT)(_UP)((Element6->prev)), (((void *)0)), (_U_UINT)(79), UNITY_DISPLAY_STYLE_HEX32);
  UnityAssertEqualNumber((_U_SINT)(_UP)((4)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(80), UNITY_DISPLAY_STYLE_HEX32);
}

void test_timerListDelete_delete_a_Node(void){
   printf("elementDelete\n");
   Linkedlist *list = createLinkedList();
   uint16_t arr[] = {9,8,6};
   ListElement *Element9 = createLinkedElement(9);
   ListElement *Element8 = createLinkedElement(8);
   ListElement *Element7 = createLinkedElement(7);
   ListElement *Element6 = createLinkedElement(6);

   addList(list,Element9);
   addList(list,Element8);
   addList(list,Element7);
   addList(list,Element6);
   UnityAssertEqualNumber((_U_SINT)(_UP)((4)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(96), UNITY_DISPLAY_STYLE_HEX32);
   linkedListRemove(list,list->head->next->next);
   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),98); };
   UnityAssertEqualNumber((_U_SINT)(_UP)((3)), (_U_SINT)(_UP)((list->count)), (((void *)0)), (_U_UINT)(99), UNITY_DISPLAY_STYLE_HEX32);

}
# 112 "test/test_Linklist.c"
void test_elementDetele_Detele_node_that_is_between_two_node(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {1,3};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);

   linkedListRemove(list,Element2);
   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),123); };
   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);
}
# 138 "test/test_Linklist.c"
void test_elementDetele_Detele_the_node_that_was_pointed_by_head(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {2,3};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);

   linkedListRemove(list,Element1);
   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),149); };
   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);
}
# 161 "test/test_Linklist.c"
void test_elementDetele_Detele_the_node_that_is_last_node_in_linked_list(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);
   uint16_t arr[] = {1,2};
   Linkedlist *list = createLinkedList();
   addList(list,Element1);
   addList(list,Element2);
   addList(list,Element3);
   linkedListRemove(list,Element3);
   { test_assert_cycle_link_list(list,arr,sizeof(arr)/sizeof(uint32_t),171); };
   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);
}
# 184 "test/test_Linklist.c"
void test_elementDetele_Detele_the_node_that_is_the_only_one_elem_in_linked_list(void){
   ListElement *Element1 = createLinkedElement(1);
   ListElement *Element2 = createLinkedElement(2);
   ListElement *Element3 = createLinkedElement(3);

   Linkedlist *list = createLinkedList();
   addList(list,Element1);

   linkedListRemove(list,Element1);
   if ((((list->head)) == ((void *)0))) {} else {UnityFail( (((" Expected NULL"))), (_U_UINT)((_U_UINT)((_U_UINT)(193))));};
   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((list->count)), (((void *)0)), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);
}
