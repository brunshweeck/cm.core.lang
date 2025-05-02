//
// Created by brunshweeck on 03/04/25.
//


#ifndef CORE_LANG_TYPES_H
#define CORE_LANG_TYPES_H

#include <exception>

#ifndef CORE_ALIAS
#define CORE_ALIAS(A, ...) using A = __VA_ARGS__
#endif

#ifndef CORE_FAST_ASSERT
#define CORE_FAST_ASSERT(x) static_assert(x, CORE_STRINGIFY(x))
#define CORE_FAST_ASSERT2(x, text) static_assert(x, text)
#endif

#ifndef CORE_FAST
#define CORE_FAST CORE_CONSTEXPR
#endif

#ifndef CORE_CONCAT
#define CORE_CONCAT(A, B) A##B
#endif

#ifndef CORE_REVERSE
#define CORE_REVERSE(A, B) B A
#endif

#ifndef CORE_STRINGIFY
#define CORE_STRINGIFY(A) #A
#endif


#define $(...) __VA_ARGS__
#define $reverse(a, ...) CORE_REVERSE(a, __VA_ARGS__)
#define $concat(a, ...) CORE_CONCAT(a, __VA_ARGS__)
#define $decimal(a,...) $concat(a,$concat(., __VA_ARGS__))
#define $stringify(a, ...) CORE_STRINGIFY(a __VA_ARGS__)
#define $text(a) $concat(u, $stringify(a))
#define $toString(a) $concat($text(a), _Su)
#define $cast(T, ...) ($reverse((__VA_ARGS__), dynamic_cast<T>))
#define $alias(A, ...) CORE_ALIAS(A, __VA_ARGS__)

#ifndef CORE_FILE
#define CORE_FILE __FILE__
#endif // CORE_FILE
#define $file CORE_FILE

#ifndef CORE_FILENAME
#define CORE_FILENAME __FILE_NAME__
#endif // CORE_FILENAME
#define $filename CORE_FILENAME

#ifndef CORE_LINE
#define CORE_LINE __LINE__
#endif // CORE_LINE
#define $line CORE_LINE

#ifdef $func
#undef $func
#endif // $func
#define $func CORE_FUNCTION

#ifdef $function
#undef $function
#endif // $function
#define $function CORE_FUNCTION_SIGNATURE

#ifndef CORE_MODULE_NAME
#define CORE_MODULE_NAME $toString()
#endif // CORE_MODULE_NAME

#ifndef CORE_MODULE_VERSION
#define CORE_MODULE_VERSION $toString()
#endif // CORE_MODULE_VERSION

#ifdef $trace
#undef $trace
#endif // $trace
#define $trace(...) ::core::lang::Trace::getInstance(CORE_MODULE_NAME, CORE_MODULE_VERSION, $toString(), $func, $file, $line)

#ifdef $ftrace
#undef $ftrace
#endif // $ftrace
#define $ftrace(...) ::core::lang::TraceInfo::getInstance(CORE_MODULE_NAME, CORE_MODULE_VERSION, $toString(), $function, $file, $line)

#ifdef $final
#undef $final
#endif // $final
#define $final CORE_FINAL

#if __has_builtin(__builtin_nanf)
#define __builtin_nan(...) (gdouble) (__builtin_nanf($stringify()))
#else
#define __builtin_nan(...) (gdouble) ($reverse(1.0E300, (gfloat)) * 0.0f)
#endif

#if __has_builtin(__builtin_inff)
#define __builtin_infinity(...) (gdouble) (__builtin_inff())
#else
#define __builtin_infinity(...) (gdouble) ($reverse(1.0E300, (gfloat)) * 1.0f)
#endif

#ifdef BIG_ENDIAN
#undef BIG_ENDIAN // for Unsafe::BIG_ENDIAN
#endif

#ifndef _Complex
#define _Complex _Complex
#endif // _Complex

namespace core
{
    namespace lang
    {
        namespace spi
        {
            extern "C" {
            typedef signed char __int8;
            typedef unsigned char __uint8;
            typedef short int __int16;
            typedef unsigned short int __uint16;
            typedef int __int32;
            typedef unsigned int __uint32;
#if __WORDSIZE == 64
            typedef long __int64;
            typedef unsigned long __uint64;
            typedef long long __varint;
            typedef unsigned long long __uvarint;
#else
            typedef long long __int64;
            typedef unsigned long long __uint64;
            typedef long __varint;
            typedef unsigned long __uvarint;
#endif
            typedef unsigned long long __literal_int64;
            typedef float __float32;
            typedef double __float64;
            typedef long double __literal_float64;
            typedef char __literal_char8;
            typedef char16_t __literal_char16;
            typedef char32_t __literal_char32;
            typedef wchar_t __literal_varchar;
            typedef bool __literal_boolean;
#ifdef CORE_COMPILER_MSVC
#ifndef CORE_LANG_COMPILER_H
#error "For support of complex numbers the file Compiler.h is required!"
#else
            typedef _C_double_complex  _Dcomplex;
            typedef _C_float_complex   _Fcomplex;
            typedef _C_ldouble_complex _Lcomplex;
#endif
#else
            typedef _Complex double _Dcomplex;
            typedef _Complex float _Fcomplex;
            typedef _Complex long double _Lcomplex;
            typedef _Complex signed char __complex_int8;
            typedef _Complex unsigned char __complex_uint8;
            typedef _Complex short __complex_int16;
            typedef _Complex unsigned short __complex_uint16;
            typedef _Complex int __complex_int32;
            typedef _Complex unsigned int __complex_uint32;
#if __WORDSIZE == 64
            typedef _Complex long __complex_int64;
            typedef _Complex unsigned long __complex_uint64;
            typedef _Complex long long __complex_varint;
            typedef _Complex unsigned long long __complex_uvarint;
#else
            typedef _Complex long __complex_varint;
            typedef _Complex unsigned long __complex_uvarint;
            typedef _Complex long long __complex_int64;
            typedef _Complex unsigned long long __complex_uint64;
#endif

#endif // CORE_COMPILER_MSVC
            //
            }
        } // namespace spi

        class Null;
        class Appendable;
        template <class T>
        class Comparable;
        class CharSequence;
        class Number;
        template <class T>
        class Iterable;

        using namespace ::core;
        class Throwable;
        class Exception;
        class Error;
    } // namespace lang

    class Object;
    class Boolean;
    class Byte;
    class Short;
    class Integer;
    class Long;
    class Float;
    class Double;
    class String;
    class Character;
    class Complex;
    class Void;

    class Math;

    class BooleanArray;
    class ByteArray;
    class ShortArray;
    class IntArray;
    class LongArray;
    class FloatArray;
    class DoubleArray;
    class StringArray;
    class CharArray;

    template <class T>
    class Enum;
    template <class T>
    class Array;
    template <class T>
    class Class;
} // namespace core

// Generic Byte Primitive Type (1 byte)
$alias(gbyte, core::lang::spi::__int8);
// Generic Short Integer Primitive Type (2 bytes)
$alias(gshort, core::lang::spi::__int16);
// Generic Integer Primitive Type (4 bytes)
$alias(gint, core::lang::spi::__int32);
// Generic Long Integer Primitive Type (8 bytes)
$alias(glong, core::lang::spi::__int64);
// Generic Float Primitive Type (4 bytes)
$alias(gfloat, core::lang::spi::__float32);
// Generic Double Float Primitive Type (8 bytes)
$alias(gdouble, core::lang::spi::__float64);
// Generic Character Primitive Type (2 bytes)
$alias(gchar, core::lang::spi::__literal_char16);
// Generic Boolean Primitive Type (1 byte)
$alias(gboolean, core::lang::spi::__literal_boolean);

/*
        Compiler type support checking
 */
CORE_FAST_ASSERT(sizeof (gboolean) == 1);
CORE_FAST_ASSERT(sizeof (gbyte) == 1);
CORE_FAST_ASSERT(sizeof (gshort) == 2);
CORE_FAST_ASSERT(sizeof (gint) == 4);
CORE_FAST_ASSERT(sizeof (glong) == 8);
CORE_FAST_ASSERT(sizeof (gfloat) == 4);
CORE_FAST_ASSERT(sizeof (gdouble) == 8);
CORE_FAST_ASSERT(sizeof (gchar) == 2);

#endif // CORE_LANG_TYPES_H
