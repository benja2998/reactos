/*
 * PROJECT:     ReactOS SDK
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Intrinsics for the SSE2 instruction set
 * COPYRIGHT:   Copyright 2024 Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#pragma once

#define _INCLUDED_IMM

//#include <wmmintrin.h>
#include <emmintrin.h>

#if defined(_MSC_VER) && !defined(__clang__)

typedef union _DECLSPEC_INTRIN_TYPE  _CRT_ALIGN(32) __m256i
{
    __int8              m256i_i8[32];
    __int16             m256i_i16[16];
    __int32             m256i_i32[8];
    __int64             m256i_i64[4];
    unsigned __int8     m256i_u8[32];
    unsigned __int16    m256i_u16[16];
    unsigned __int32    m256i_u32[8];
    unsigned __int64    m256i_u64[4];
} __m256i;

#else /* _MSC_VER */

typedef char __v32qi __attribute__ ((__vector_size__ (32)));
typedef short __v16hi __attribute__ ((__vector_size__ (32)));
typedef long long __v4di __attribute__ ((__vector_size__ (32)));

typedef long long __m256i __attribute__((__vector_size__(32), __may_alias__));

#endif /* _MSC_VER */

#ifdef __cplusplus
extern "C" {
#endif

extern __m256i __cdecl _mm256_cmpeq_epi8(__m256i, __m256i);
extern __m256i __cdecl _mm256_cmpeq_epi16(__m256i, __m256i);
extern int __cdecl _mm256_movemask_epi8(__m256i);
extern __m256i __cdecl _mm256_setzero_si256(void);
extern void __cdecl _mm256_zeroupper(void);

extern int __cdecl _rdrand16_step(unsigned short *random_val);
extern int __cdecl _rdrand32_step(unsigned int *random_val);
#if defined(_M_X64)
extern int __cdecl _rdrand64_step(unsigned __int64 *random_val);
#endif

extern int __cdecl _rdseed16_step(unsigned short *random_val);
extern int __cdecl _rdseed32_step(unsigned int *random_val);
#if defined(_M_X64)
extern int __cdecl _rdseed64_step(unsigned __int64 *random_val);
#endif

void __cdecl _fxsave(void *);
void __cdecl _fxrstor(void const *);
void __cdecl _xsave(void *, unsigned __int64);
void __cdecl _xsavec(void *, unsigned __int64);
void __cdecl _xsaveopt(void *, unsigned __int64);
void __cdecl _xsaves(void *, unsigned __int64);
void __cdecl _xrstor(void const *, unsigned __int64);
void __cdecl _xrstors(void const *, unsigned __int64);
#if defined (_M_X64)
void __cdecl _fxsave64(void *);
void __cdecl _fxrstor64(void const *);
void __cdecl _xsave64(void *, unsigned __int64);
void __cdecl _xsavec64(void *, unsigned __int64);
void __cdecl _xsaveopt64(void *, unsigned __int64);
void __cdecl _xsaves64(void *, unsigned __int64);
void __cdecl _xrstor64(void const *, unsigned __int64);
void __cdecl _xrstors64(void const *, unsigned __int64);
#endif

unsigned __int64 __cdecl _xgetbv(unsigned int);
void __cdecl _xsetbv(unsigned int, unsigned __int64);


#if defined(_MSC_VER) && !defined(__clang__)

#pragma intrinsic(_mm256_cmpeq_epi8)
#pragma intrinsic(_mm256_cmpeq_epi16)
#pragma intrinsic(_mm256_movemask_epi8)
#pragma intrinsic(_mm256_setzero_si256)
#pragma intrinsic(_mm256_zeroupper)

#pragma intrinsic(_rdrand16_step)
#pragma intrinsic(_rdrand32_step)
#if defined(_M_X64)
#pragma intrinsic(_rdrand64_step)
#endif
#pragma intrinsic(_rdseed16_step)
#pragma intrinsic(_rdseed32_step)
#if defined(_M_X64)
#pragma intrinsic(_rdseed64_step)
#endif

#pragma intrinsic(_fxsave)
#pragma intrinsic(_fxrstor)
#pragma intrinsic(_xsave)
#pragma intrinsic(_xsaveopt)
#pragma intrinsic(_xsavec)
#pragma intrinsic(_xsaves)
#pragma intrinsic(_xrstor)
#pragma intrinsic(_xrstors)
#if defined (_M_X64)
#pragma intrinsic(_fxsave64)
#pragma intrinsic(_fxrstor64)
#pragma intrinsic(_xsave64)
#pragma intrinsic(_xsaveopt64)
#pragma intrinsic(_xsavec64)
#pragma intrinsic(_xsaves64)
#pragma intrinsic(_xrstor64)
#pragma intrinsic(_xrstors64)
#endif

#pragma intrinsic(_xgetbv)
#pragma intrinsic(_xsetbv)

#else /* _MSC_VER */

#ifdef __clang__
#define __ATTRIBUTE_SSE2__ __attribute__((__target__("sse2"),__min_vector_width__(128)))
#define __ATTRIBUTE_AVX__ __attribute__((__target__("avx"),__min_vector_width__(256)))
#define __ATTRIBUTE_AVX2__ __attribute__((__target__("avx2"),__min_vector_width__(256)))
#else
#define __ATTRIBUTE_SSE2__ __attribute__((__target__("sse2")))
#define __ATTRIBUTE_AVX__ __attribute__((__target__("avx")))
#define __ATTRIBUTE_AVX2__ __attribute__((__target__("avx2")))
#endif
#define __INTRIN_INLINE_SSE2 __INTRIN_INLINE __ATTRIBUTE_SSE2__
#define __INTRIN_INLINE_AVX __INTRIN_INLINE __ATTRIBUTE_AVX__
#define __INTRIN_INLINE_AVX2 __INTRIN_INLINE __ATTRIBUTE_AVX2__

__INTRIN_INLINE_AVX __m256i __cdecl _mm256_cmpeq_epi8(__m256i __A, __m256i __B)
{
    return (__m256i)((__v32qi)__A == (__v32qi)__B);
}

__INTRIN_INLINE_AVX __m256i __cdecl _mm256_cmpeq_epi16(__m256i __A, __m256i __B)
{
    return (__m256i)((__v16hi)__A == (__v16hi)__B);
}

__INTRIN_INLINE_AVX2 int __cdecl _mm256_movemask_epi8(__m256i __A)
{
    return __builtin_ia32_pmovmskb256((__v32qi)__A);
}

__INTRIN_INLINE_AVX __m256i __cdecl _mm256_setzero_si256(void)
{
    return __extension__ (__m256i)(__v4di){ 0, 0, 0, 0 };
}

__INTRIN_INLINE void __cdecl _mm256_zeroupper(void)
{
    __asm__ __volatile__("vzeroupper");
}

__INTRIN_INLINE int _rdrand16_step(unsigned short* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdrand %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}

__INTRIN_INLINE int _rdrand32_step(unsigned int* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdrand %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}

#if defined(__x86_64__)
__INTRIN_INLINE int _rdrand64_step(unsigned __int64* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdrand %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}
#endif // __x86_64__

__INTRIN_INLINE int _rdseed16_step(unsigned short* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdseed %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}

__INTRIN_INLINE int _rdseed32_step(unsigned int* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdseed %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}

#if defined(__x86_64__)
__INTRIN_INLINE int _rdseed64_step(unsigned __int64* random_val)
{
    unsigned char ok;
    __asm__ __volatile__("rdseed %0; setc %1" : "=r"(*random_val), "=qm"(ok));
    return (int)ok;
}
#endif // __x86_64__

__INTRIN_INLINE void _fxsave(void *__P)
{
#if 0 // Needs newer GCC
    __builtin_ia32_fxsave(__P);
#else
    __asm__ __volatile__("fxsave (%0)" : : "r"(__P));
#endif
}

__INTRIN_INLINE void _fxrstor(void const *__P)
{
#if 0 // Needs newer GCC
    __builtin_ia32_fxrstor((void*)__P);
#else
    __asm__ __volatile__("fxrstor (%0)" : : "r"(__P));
#endif
}

#if defined(__x86_64__)
__INTRIN_INLINE void _fxsave64(void *__P)
{
    __builtin_ia32_fxsave64(__P);
}

__INTRIN_INLINE void _fxrstor64(void const *__P)
{
    __builtin_ia32_fxrstor64((void*)__P);
}
#endif // __x86_64__

#ifdef __clang__
#define __ATTRIBUTE_XSAVE__ __attribute__((__target__("xsave")))
#else
#define __ATTRIBUTE_XSAVE__
#endif
#define __INTRIN_INLINE_XSAVE __INTRIN_INLINE __ATTRIBUTE_XSAVE__

__INTRIN_INLINE_XSAVE void _xsave(void *__P, unsigned __int64 __M)
{
    __builtin_ia32_xsave(__P, __M);
}

__INTRIN_INLINE_XSAVE void _xsavec(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsavec(__P, __M);
#else
    __asm__ __volatile__("xsavec %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) :"memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xsaveopt(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsaveopt(__P, __M);
#else
    __asm__ __volatile__("xsaveopt %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) :"memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xsaves(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsaves(__P, __M);
#else
    __asm__ __volatile__("xsaves %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) :"memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xrstor(void const *__P, unsigned __int64 __M)
{
    __builtin_ia32_xrstor((void*)__P, __M);
}

__INTRIN_INLINE_XSAVE void _xrstors(void const *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xrstors((void*)__P, __M);
#else
    __asm__ __volatile__("xrstors %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) :"memory");
#endif
}

#if defined(__x86_64__)
__INTRIN_INLINE_XSAVE void _xsave64(void *__P, unsigned __int64 __M)
{
    __builtin_ia32_xsave64(__P, __M);
}

__INTRIN_INLINE_XSAVE void _xsavec64(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsavec64(__P, __M);
#else
    __asm__ __volatile__("xsavec %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) : "memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xsaveopt64(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsaveopt64(__P, __M);
#else
    __asm__ __volatile__("xsaveopt %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) : "memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xsaves64(void *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xsaves64(__P, __M);
#else
    __asm__ __volatile__("xsaves %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) : "memory");
#endif
}

__INTRIN_INLINE_XSAVE void _xrstor64(void const *__P, unsigned __int64 __M)
{
    __builtin_ia32_xrstor64((void*)__P, __M);
}

__INTRIN_INLINE_XSAVE void _xrstors64(void const *__P, unsigned __int64 __M)
{
#if 0 // Needs newer GCC
    __builtin_ia32_xrstors64((void*)__P, __M);
#else
    __asm__ __volatile__("xrstors %0" : "=m" (*(char*)__P) : "a" ((unsigned int)__M), "d" ((unsigned int)(__M >> 32)) : "memory");
#endif
}
#endif // __x86_64__

#ifndef __clang__
__INTRIN_INLINE unsigned __int64 _xgetbv(unsigned int __A)
{
    return __builtin_ia32_xgetbv(__A);
}

__INTRIN_INLINE void _xsetbv(unsigned int __A, unsigned __int64 __V)
{
    __builtin_ia32_xsetbv(__A, __V);
}
#endif // !__clang__

#endif /* _MSC_VER */

#ifdef __cplusplus
} // extern "C"
#endif
