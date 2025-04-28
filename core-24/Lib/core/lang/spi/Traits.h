//
// Created by brunshweeck on 05/04/25.
//

#ifndef CORE_LANG_TRAITS_H
#define CORE_LANG_TRAITS_H

#include "Processor.h"
#include "Compiler.h"
#include "Types.h"

namespace core::lang::spi
{
    template <gint V, class... T>
    class __Always;

    template <>
    class __Always<1>
    {
    public:
        static CORE_FAST gboolean value = true;
    };

    template <class T>
    class __Always<1, T>
    {
    public:
        static CORE_FAST gboolean value = true;
        $alias(type, T);
    };

    template <class... T>
    class __Always<0, T...>
    {
    public:
        static CORE_FAST gboolean value = false;
    };

    $alias(__AlwaysTrue, __Always<1>);
    $alias(__AlwaysFalse, __Always<0>);
    template <class T>
    $alias(__AlwaysTrueType, __Always<1, T>);
    template <class T>
    $alias(__AlwaysFalseType, __Always<0, T>);

    template <glong test, class... T>
    class __TypeTesting : public __AlwaysFalse
    {
    };

    template <glong transform, class T, glong numberOfElements = -1, glong dimension = 1>
    class __TypeTransform : public __AlwaysTrueType<T>
    {
    };

    template <bool condition, class T>
    class __StrictCondition;

    template <class T>
    class __StrictCondition<true, T> : __AlwaysTrueType<T>
    {
    };

    template <class T>
    class __StrictCondition<false, T> : __AlwaysFalseType<T>
    {
    };

    template <bool condition, class T, class U>
    class __Condition;

    template <class T, class U>
    class __Condition<true, T, U> : public __AlwaysTrueType<T>
    {
    };

    template <class T, class U>
    class __Condition<false, T, U> : public __AlwaysTrueType<U>
    {
    };

    template <class... T>
    class __All;

    template <>
    class __All<> : public __AlwaysTrue
    {
    };

    template <class T>
    class __All<T> : public T
    {
    };

    template <class T, class... U>
    class __All<T, U...> : public __StrictCondition<T::value, __All<U...>>
    {
    };

    template <class... T>
    class __Any;

    template <>
    class __Any<> : public __AlwaysTrue
    {
    };

    template <class T>
    class __Any<T> : public T
    {
    };

    template <class T, class... U>
    class __Any<T, U...> : public __Condition<T::value, T, __Any<U...>>
    {
    };

    template <class T>
    class __Not : public __Always<~T::value>
    {
    };

    template <class T, glong ... transforms>
    class __TypeChainedTransform;

    template <class T>
    class __TypeChainedTransform<T> : public __AlwaysTrueType<T>
    {
    };

    template <class T, glong transform>
    class __TypeChainedTransform<T, transform>
        : public __TypeTransform<transform, T>
    {
    };

    template <class T, glong transform, glong ... otherTransforms>
    class __TypeChainedTransform<T, transform, otherTransforms...>
        : public __TypeChainedTransform<typename __TypeTransform<transform, T>::type, otherTransforms...>
    {
    };

    template <class... T>
    $alias(__IgnoredType, void);

    template <class T, class U = T&&>
    static U tryDeclare0(gint) { CORE_UNREACHABLE(); }

    template <class T>
    static T tryDeclare0(...) { CORE_UNREACHABLE(); }

    template <class T>
    static decltype(tryDeclare0<T>(0)) tryDeclare() { CORE_UNREACHABLE(); }

#define __DELETE_QUALIFIER                   1L << 0x00
#define __CONST_QUALIFIER                      1L << 0x01
#define __VOLATILE_QUALIFIER                   1L << 0x02
#define __REFERENCE_QUALIFIER                1L << 0x03
#define __POINTER_QUALIFIER                    1L << 0x04
#define __ARRAY_QUALIFIER                       1L << 0x05
#define __IS_FUNCTION_TYPE                    1L << 0x06
#define __IS_CLASS_TYPE                        1L << 0x07
#define __IS_ENUM_TYPE                          1L << 0x08
#define __IS_UNION_TYPE                          1L << 0x09
#define __IS_PRIMITIVE_TYPE                     1L << 0x0A
#define __TO_CLASS_TYPE                            1L << 0x0B
#define __TO_PRIMITIVE_TYPE                         1L << 0x0C
#define __IS_SAME_TYPE                  1L << 0x0D
#define __IS_TEMPLATE_TYPE         1L << 0x0E
#define __IS_FUNCTION_MEMBER_TYPE   1L << 0x0F
#define __IS_ABSTRACT_TYPE  1L << 0x10
#define __IS_ARRAY_TYPE    1L << 0x11
#define __IS_SUPER_TYPE   1L << 0x12
#define __IS_FINAL_TYPE    1L << 0x13
#define __IS_SIZEABLE_TYPE  1L << 0x14
#define __IS_INTEGER_TYPE  1L << 0x15
#define __IS_FLOAT_TYPE    1L << 0x16
#define __IS_VOID_TYPE     1L << 0x17
#define __IS_BOOLEAN_TYPE  1L << 0x18
#define __IS_CHARACTER_TYPE  1L << 0x19
#define __IS_STRING_TYPE    1L << 0x1A
#define __IS_CALLABLE_TYPE  1L << 0x1B
#define __IS_EMPTY_TYPE    1L << 0x1C
#define __IS_TRIVIAL_TYPE  1L << 0x1D
#define __IS_POLYMORPHIC_TYPE  1L << 0x1E
#define __IS_LITERAL_TYPE    1L << 0x1F
#define __IS_SLIMMED_TYPE    1L << 0x20
#define __IS_CONVERTIBLE_TYPE  1L << 0x21
#define __IS_CONSTRUCTIBLE_TYPE  1L << 0x22
#define __IS_ASSIGNABLE_TYPE    1L << 0x23
#define __IS_DESTRUCTIBLE_TYPE  1L << 0x24
#define __IS_COPYABLE_TYPE       1L << 0x25
#define __IS_LESS_THAN_COMPARABLE_TYPE  1L << 0x26
#define __IS_EQUAL_TO_COMPARABLE_TYPE  1L << 0x27
#define __IS_GREATER_THAN_COMPARABLE_TYPE  1L << 0x28
#define __IS_GREATER_THAN_OR_EQUAL_TO_COMPARABLE_TYPE  1L << 0x29
#define __IS_NOT_EQUAL_TO_COMPARABLE_TYPE  1L << 0x2A
#define __IS_LESS_THAN_OR_EQUAL_TO_COMPARABLE_TYPE  1L << 0x2B
#define __IS_CONSTANT_TYPE  1L << 0x2C
#define __IS_REFERENCE_TYPE  1L << 0x2D
#define __IS_POINTER_TYPE  1L << 0x2E
#define __IS_VOLATILE_TYPE  1L << 0x2F
#define __LVALUE_QUALIFIER   1L << 0x30
#define __RVALUE_QUALIFIER    1L << 0x31
#define __IS_MEMBER_TYPE  1L << 0x32
#define __TO_SLIMMED_TYPE  1L << 0x33
#define __IS_INSTANCE_OF_TYPE  1L << 0x34
#define __IS_RVALUE_TYPE  1L << 0x35

    //  Similarity
    template <class T>
    class __TypeTesting<__IS_SAME_TYPE, T, T> : public __AlwaysTrue
    {
    };

    template <class T, class U>
    class __TypeTesting<__IS_SAME_TYPE, T, U> : public __Always<__is_same(T, U)>
    {
    };

    // Constant types
    template <class T>
    class __TypeTesting<__IS_CONSTANT_TYPE, T const> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTransform<__CONST_QUALIFIER, T> : public __AlwaysTrueType<T const>
    {
    };

    template <class T>
    class __TypeTransform<__CONST_QUALIFIER | __DELETE_QUALIFIER, T const> : public __AlwaysTrueType<T>
    {
    };

    // Volatile types
    template <class T>
    class __TypeTesting<__IS_VOLATILE_TYPE, T volatile> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTransform<__VOLATILE_QUALIFIER, T> : public __AlwaysTrueType<T volatile>
    {
    };

    template <class T>
    class __TypeTransform<__VOLATILE_QUALIFIER | __DELETE_QUALIFIER, T volatile> : public __AlwaysTrueType<T>
    {
    };

    // Reference types
    template <class T>
    class __TypeTesting<__IS_REFERENCE_TYPE, T&> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTesting<__IS_REFERENCE_TYPE, T&&> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTesting<__IS_RVALUE_TYPE, T&&> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTransform<__REFERENCE_QUALIFIER, T> : public __AlwaysTrueType<T&>
    {
    };

    template <class T>
    class __TypeTransform<__REFERENCE_QUALIFIER | __LVALUE_QUALIFIER, T> : public __AlwaysTrueType<T&>
    {
    };

    template <class T>
    class __TypeTransform<__REFERENCE_QUALIFIER | __RVALUE_QUALIFIER, T> : public __AlwaysTrueType<T&&>
    {
    };

    template <class T>
    class __TypeTransform<__REFERENCE_QUALIFIER | __DELETE_QUALIFIER, T&> : public __AlwaysTrueType<T>
    {
    };

    template <class T>
    class __TypeTransform<
            __REFERENCE_QUALIFIER | __LVALUE_QUALIFIER | __DELETE_QUALIFIER, T&> : public __AlwaysTrueType<T>
    {
    };

    template <class T>
    class __TypeTransform<__REFERENCE_QUALIFIER | __DELETE_QUALIFIER, T&&> : public __AlwaysTrueType<T>
    {
    };

    template <class T>
    class __TypeTransform<
            __REFERENCE_QUALIFIER | __RVALUE_QUALIFIER | __DELETE_QUALIFIER, T&&> : public __AlwaysTrueType<T>
    {
    };

    // Pointer types
    template <class T>
    class __TypeTesting<__IS_POINTER_TYPE, T*> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTesting<__IS_POINTER_TYPE, T[]> : public __AlwaysFalse
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTesting<__IS_POINTER_TYPE, T[numberOfElements]> : public __AlwaysFalse
    {
    };

    template <class T>
    class __TypeTransform<__POINTER_QUALIFIER, T> : public __AlwaysTrueType<T*>
    {
    };

    template <class T, glong dimension>
    class __TypeTransform<
            __POINTER_QUALIFIER, T, -1, dimension> : public __TypeTransform<__POINTER_QUALIFIER, T*, -1, dimension - 1>
    {
        CORE_FAST_ASSERT(dimension > 1L);
    };

    template <class T>
    class __TypeTransform<__POINTER_QUALIFIER | __DELETE_QUALIFIER, T*> : public __AlwaysTrueType<T>
    {
    };

    // Array types
    template <class T>
    class __TypeTesting<__IS_ARRAY_TYPE, T[]> : public __AlwaysTrue
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTesting<__IS_ARRAY_TYPE, T[numberOfElements]> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTransform<__ARRAY_QUALIFIER, T> : public __AlwaysTrueType<T[]>
    {
    };

    template <class T, glong dimension>
    class __TypeTransform<
            __ARRAY_QUALIFIER, T, -1, dimension> : public __TypeTransform<__ARRAY_QUALIFIER, T[], -1, dimension - 1>
    {
        CORE_FAST_ASSERT(dimension > 1L);
    };

    template <class T, glong numberOfElements>
    class __TypeTransform<__ARRAY_QUALIFIER, T, numberOfElements> : public __AlwaysTrueType<T[numberOfElements]>
    {
        CORE_FAST_ASSERT(numberOfElements >= 0L);
    };

    template <class T, glong numberOfElements, glong dimension>
    class __TypeTransform<
            __ARRAY_QUALIFIER, T, numberOfElements, dimension> : public __TypeTransform<
            __ARRAY_QUALIFIER, T[numberOfElements], numberOfElements, dimension - 1>
    {
        CORE_FAST_ASSERT(numberOfElements >= 0L);
        CORE_FAST_ASSERT(dimension > 1L);
    };

    template <class T>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[]> : public __AlwaysTrueType<T>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[numberOfElements]> : public __AlwaysTrueType<T>
    {
    };

    template <class T>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[], -1, 0> : public __AlwaysFalseType<T[]>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[numberOfElements], -1, 0>
        : public __AlwaysFalseType<T[numberOfElements]>
    {
        CORE_FAST_ASSERT(numberOfElements >= 0L);
    };

    template <class T, glong dimension>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[], dimension>
        : public __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T, -1, dimension - 1>
    {
        CORE_FAST_ASSERT(dimension > 1L);
    };

    template <class T, glong numberOfElements, glong dimension>
    class __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T[numberOfElements], -1, dimension>
        : public __TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T, -1, dimension - 1>
    {
        CORE_FAST_ASSERT(dimension > 1L);
        CORE_FAST_ASSERT(numberOfElements >= 0L);
    };

    // Function Pointer types
    template <class T, class... U>
    class __TypeTesting<__IS_FUNCTION_TYPE, T(U...)> : public __AlwaysTrue
    {
    };

    template <class T, class... U>
    class __TypeTesting<__IS_FUNCTION_TYPE, T(U..., ...)> : public __AlwaysTrue
    {
    };

    template <class T>
    class __TypeTesting<__IS_FUNCTION_TYPE, T(...)> : public __AlwaysTrue
    {
    };

    // Struct member types
    template <class T, class U>
    class __TypeTesting<__IS_MEMBER_TYPE, T U::*> : public __AlwaysTrue
    {
    };

#ifdef CORE_COMPILER_CLANG
    template <class T>
    class __TypeTesting<__IS_MEMBER_TYPE, T> : public __Always<__is_member_pointer(T)>
    {
    };
#endif // CORE_COMPILER_CLANG

    // Struct function member types
    template <class T, class U, class... V>
    class __TypeTesting<__IS_FUNCTION_MEMBER_TYPE, T (U::*)(V...)> : public __AlwaysTrue
    {
    };

    template <class T, class U, class... V>
    class __TypeTesting<__IS_FUNCTION_MEMBER_TYPE, T (U::*)(V..., ...)> : public __AlwaysTrue
    {
    };

    template <class T, class U>
    class __TypeTesting<__IS_FUNCTION_MEMBER_TYPE, T (U::*)(...)> : public __AlwaysTrue
    {
    };

    // Enumeration types
    template <class T>
    class __TypeTesting<__IS_ENUM_TYPE, T> : public __Always<__is_enum(T)>
    {
    };

    // Struct or Class types
    template <class T>
    class __TypeTesting<__IS_CLASS_TYPE, T> : public __Always<__is_class(T)>
    {
    };

    // Constructible types
    template <class T, class... U>
    class __TypeTesting<__IS_CONSTRUCTIBLE_TYPE, T, U...> : public __AlwaysFalse
    {
        template <class __T, class... __U, glong sizeInBytes = sizeof(__T)>
        static __Always<__is_constructible(__T, __U...)> tryConstruct(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryConstruct(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryConstruct<T>(0))::value;
    };

    // Assignable types
    template <class T, class U>
    class __TypeTesting<__IS_ASSIGNABLE_TYPE, T, U> : public __Always<__is_assignable(U, T)>
    {
    };

    // Super types
    template <class T, class U>
    class __TypeTesting<__IS_SUPER_TYPE, T, U> : public __Always<__is_base_of(T, U)>
    {
    };

    // Implicit Convertible types
#ifdef CORE_COMPILER_MSVC
    template <class T, class U>
    class __TypeTesting<__IS_CONVERTIBLE_TYPE, T, U> : public __Always<__is_convertible_to(T, U)>
    {
    };
#else
    template <class T, class U>
    class __TypeTesting<__IS_CONVERTIBLE_TYPE, T, U> : public __AlwaysFalse
    {
        template <class __T>
        static void tryCall(__T value) { CORE_UNREACHABLE(); }

        template <class __T, class __U, class __V = decltype(tryCall<__U>(tryDeclare<__T>()))>
        static __AlwaysTrue tryConvert(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryConvert(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryConvert<T, U>(0))::value;
    };
#endif // CORE_COMPILER_MSVC

    // Sizable types (Complete types)
    template <class T>
    class __TypeTesting<__IS_SIZEABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T>
        class __TypeSizeable : public __AlwaysTrueType<__T>
        {
        public:
            static CORE_FAST glong size = sizeof(__T);
            static CORE_FAST glong count = -1L;
        };

        template <class __T, glong numberOfElements>
        class __TypeSizeable<__T[numberOfElements]>
        {
        public:
            static CORE_FAST glong size = sizeof(__T) * numberOfElements;
            static CORE_FAST glong count = numberOfElements;
        };

        class __TypeIncomplete : public __AlwaysFalse
        {
        public:
            static CORE_FAST glong size = -1L;
            static CORE_FAST glong count = -1L;
        };

        template <class __T, glong sizeInBytes = sizeof(__T)>
        static __TypeSizeable<__T> tryCalculateSize(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __TypeIncomplete tryCalculateSize(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCalculateSize<T>(0))::value;
        static CORE_FAST glong size = decltype(tryCalculateSize<T>(0))::size;
        static CORE_FAST glong count = decltype(tryCalculateSize<T>(0))::count;
    };

    // Integer types
    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __int8> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __uint8> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __int16> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __uint16> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __int32> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __uint32> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __int64> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __uint64> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __varint> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_INTEGER_TYPE, __uvarint> : public __AlwaysTrue
    {
    };

    // Floating types
    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, __float32> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, __float64> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, __literal_float64> : public __AlwaysTrue
    {
    };

#ifdef __STDCPP_FLOAT16_T__
    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, _Float16> : public __AlwaysTrue
    {
    };
#endif // __STDCPP_FLOAT16_T__

#ifdef __STDCPP_FLOAT32_T__
    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, _Float32> : public __AlwaysTrue
    {
    };
#endif // __STDCPP_FLOAT32_T__

#ifdef __STDCPP_FLOAT64_T__
    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, _Float64> : public __AlwaysTrue
    {
    };
#endif // __STDCPP_FLOAT64_T__

#ifdef __STDCPP_FLOAT128_T__
    template <>
    class __TypeTesting<__IS_FLOAT_TYPE, _Float128> : public __AlwaysTrue
    {
    };
#endif // __STDCPP_FLOAT128_T__


    //  Character types
    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __int8> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __uint8> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __literal_char8> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __literal_char16> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __literal_char32> : public __AlwaysTrue
    {
    };

    template <>
    class __TypeTesting<__IS_CHARACTER_TYPE, __literal_varchar> : public __AlwaysTrue
    {
    };

    // Boolean types
    template <>
    class __TypeTesting<__IS_BOOLEAN_TYPE, __literal_boolean> : public __AlwaysTrue
    {
    };

    // Callable types
    template <class T, class... U>
    class __TypeTesting<__IS_CALLABLE_TYPE, T(U...), U...> : public __AlwaysTrue
    {
    };

    template <class T, class... U>
    class __TypeTesting<__IS_CALLABLE_TYPE, T(U..., ...), U...> : public __AlwaysTrue
    {
    };

    /**
     *
     * @tparam T The function type
     * @tparam U The arguments types
     */
    template <class T, class... U>
    class __TypeTesting<__IS_CALLABLE_TYPE, T, U...> : public __AlwaysFalse
    {
        template <class __T, class... __U, class __V = decltype(tryDeclare<__T>(tryDeclare<__U>()...))>
        static __AlwaysTrueType<__V> tryCall(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCall(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCall<T, U...>(0))::value;
        $alias(optionalType, decltype(tryCall<T, U...>(0)));
    };

    /**
     *
     * @tparam T The class type
     * @tparam U The function member pointer or class member pointer type
     * @tparam V The class instance type
     * @tparam W The arguments type
     */
    template <class T, class U, class V, class... W>
    class __TypeTesting<__IS_CALLABLE_TYPE, T U::*, V, W...> : public __AlwaysFalse
    {
        template <class __T, class __U, class... __V,
                  class __W = decltype((tryDeclare<__U>().*tryDeclare<__T>())(tryDeclare<__V>()...))>
        static __AlwaysTrueType<__W> tryCallFunctionMember(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCallFunctionMember(...) { CORE_UNREACHABLE(); }

        template <class __T, class __U, class... __V,
                  class __W = decltype(((*tryDeclare<__U>()).*tryDeclare<__T>())(tryDeclare<__V>()...))>
        static __AlwaysTrueType<__W> tryCallMember(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCallMember(...) { CORE_UNREACHABLE(); }

        $alias(__V, typename __TypeTransform<__REFERENCE_QUALIFIER | __DELETE_QUALIFIER, V>::type);
        $alias(optionalType1, decltype(tryCallFunctionMember<T U::*, __V, W...>(0)));
        $alias(optionalType2, decltype(tryCallMember<T U::*, __V, W...>(0)));

    public:
        static CORE_FAST gboolean value = __Any<optionalType1, optionalType2>::value;
        $alias(optionalType, __Any<optionalType1, optionalType2>);
    };

    // String types
    template <class T>
    class __TypeTesting<__IS_STRING_TYPE, T*> : public __TypeTesting<__IS_CHARACTER_TYPE, T>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTesting<__IS_STRING_TYPE, T[numberOfElements]> : public __TypeTesting<__IS_CHARACTER_TYPE, T>
    {
    };

    // Comparable types
    template <class T>
    class __TypeTesting<__IS_EQUAL_TO_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() == tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    template <class T>
    class __TypeTesting<__IS_NOT_EQUAL_TO_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() != tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    template <class T>
    class __TypeTesting<__IS_LESS_THAN_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() < tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    template <class T>
    class __TypeTesting<__IS_LESS_THAN_OR_EQUAL_TO_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() <= tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    template <class T>
    class __TypeTesting<__IS_GREATER_THAN_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() > tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    template <class T>
    class __TypeTesting<__IS_GREATER_THAN_OR_EQUAL_TO_COMPARABLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>() >= tryDeclare<__T>())>
        static __TypeTesting<__IS_BOOLEAN_TYPE, __U> tryCompare(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryCompare(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryCompare<T>(0))::value;
    };

    // Destructible types
#ifdef CORE_COMPILER_MSVC
    template <class T>
    class __TypeTesting<__IS_DESTRUCTIBLE_TYPE, T> : public __Always<__is_destructible(T)>
    {
    };
#else
    template <class T>
    class __TypeTesting<__IS_DESTRUCTIBLE_TYPE, T> : public __AlwaysFalse
    {
        template <class __T, class __U = decltype(tryDeclare<__T>().~T())>
        static __AlwaysTrue tryDestroy(gint) { CORE_UNREACHABLE(); }

        template <class...>
        static __AlwaysFalse tryDestroy(...) { CORE_UNREACHABLE(); }

    public:
        static CORE_FAST gboolean value = decltype(tryDestroy<T>(0))::value;
    };
#endif // CORE_COMPILER_MSVC

    // Primitive types
    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Boolean> : public __AlwaysTrueType<gboolean>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Byte> : public __AlwaysTrueType<gbyte>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Short> : public __AlwaysTrueType<gshort>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Integer> : public __AlwaysTrueType<gint>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Long> : public __AlwaysTrueType<glong>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Float> : public __AlwaysTrueType<gfloat>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Double> : public __AlwaysTrueType<gdouble>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Character> : public __AlwaysTrueType<gchar>
    {
    };

    template <>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Void> : public __AlwaysTrueType<void>
    {
    };

    template <class T>
    class __TypeTransform<__TO_PRIMITIVE_TYPE, Enum<T>> : public __AlwaysTrueType<T>
    {
    };

    // Class types
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_boolean> : public __AlwaysTrueType<Boolean>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __int8> : public __AlwaysTrueType<Byte>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __uint8> : public __AlwaysTrueType<Byte>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __int16> : public __AlwaysTrueType<Short>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __uint16> : public __AlwaysTrueType<Short>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __int32> : public __AlwaysTrueType<Integer>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __uint32> : public __AlwaysTrueType<Integer>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __int64> : public __AlwaysTrueType<Long>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __uint64> : public __AlwaysTrueType<Long>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __varint> : public __AlwaysTrueType<Long>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __uvarint> : public __AlwaysTrueType<Long>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __float32> : public __AlwaysTrueType<Float>
    {
    };

#ifdef __STDCPP_FLOAT16_T__
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Float16> : public __AlwaysTrueType<Float>
    {
    };
#endif // __STDCPP_FLOAT16_T__

#ifdef __STDCPP_FLOAT32_T__
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Float32> : public __AlwaysTrueType<Float>
    {
    };
#endif // __STDCPP_FLOAT32_T__

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __float64> : public __AlwaysTrueType<Double>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_float64> : public __AlwaysTrueType<Double>
    {
    };

#ifdef __STDCPP_FLOAT64_T__
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Float64> : public __AlwaysTrueType<Double>
    {
    };
#endif // __STDCPP_FLOAT64_T__

#ifdef __STDCPP_FLOAT128_T__
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Float128> : public __AlwaysTrueType<Double>
    {
    };
#endif // __STDCPP_FLOAT128_T__

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_char8> : public __AlwaysTrueType<Character>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_char16> : public __AlwaysTrueType<Character>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_char32> : public __AlwaysTrueType<Character>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __literal_varchar> : public __AlwaysTrueType<Character>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __IgnoredType<>> : public __AlwaysTrueType<Void>
    {
    };

#ifndef CORE_COMPILER_MSVC
    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_int8> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_uint8> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_int16> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_uint16> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_int32> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_uint32> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_int64> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_uint64> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_varint> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, __complex_uvarint> : public __AlwaysTrueType<Complex>
    {
    };
#endif // CORE_COMPILER_MSVC

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Fcomplex> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Dcomplex> : public __AlwaysTrueType<Complex>
    {
    };

    template <>
    class __TypeTransform<__TO_CLASS_TYPE, _Lcomplex> : public __AlwaysTrueType<Complex>
    {
    };

    template <class T>
    class __TypeTransform<__TO_CLASS_TYPE, T*>
        : public __Condition<__TypeTesting<__IS_CHARACTER_TYPE, T>::value, String, T*>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTransform<__TO_CLASS_TYPE, T[numberOfElements]>
        : public __Condition<__TypeTesting<__IS_CHARACTER_TYPE, T>::value, String, T[numberOfElements]>
    {
    };

    template <class T>
    class __TypeTransform<__TO_CLASS_TYPE, T>
        : public __Condition<__TypeTesting<__IS_ENUM_TYPE, T>::value, Enum<T>, T>
    {
    };

    // Empty types
    template <class T>
    class __TypeTesting<__IS_EMPTY_TYPE, T> : public __Always<__is_empty(T)>
    {
    };

    // Polymorphic types
    template <class T>
    class __TypeTesting<__IS_POLYMORPHIC_TYPE, T> : public __Always<__is_polymorphic(T)>
    {
    };

    // Literal types
    template <class T>
    class __TypeTesting<__IS_LITERAL_TYPE, T> : public __Always<__is_literal_type(T)>
    {
    };

    // Trivial types
    template <class T>
    class __TypeTesting<__IS_TRIVIAL_TYPE, T> : public __Always<__is_trivial(T)>
    {
    };

    // Trivial types
    template <>
    class __TypeTesting<__IS_VOID_TYPE, __IgnoredType<>> : public __AlwaysTrue
    {
    };

    // Slimmed type
    template <class T>
    class __TypeTesting<__IS_SLIMMED_TYPE, T> : public __Not<__Any<
            __TypeTesting<__IS_CONSTANT_TYPE, T>,
            __TypeTesting<__IS_VOLATILE_TYPE, T>,
            __TypeTesting<__IS_REFERENCE_TYPE, T>
        >>
    {
    };

    template <class T>
    class __TypeTesting<__IS_SLIMMED_TYPE, T*> : public __TypeTesting<__IS_SLIMMED_TYPE, T>
    {
    };

    template <class T>
    class __TypeTesting<__IS_SLIMMED_TYPE, T[]> : public __TypeTesting<__IS_SLIMMED_TYPE, T>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTesting<__IS_SLIMMED_TYPE, T[numberOfElements]> : public __TypeTesting<__IS_SLIMMED_TYPE, T>
    {
    };

    template <class T>
    class __TypeTransform<__TO_SLIMMED_TYPE, T> : public __TypeChainedTransform<T,
            __CONST_QUALIFIER | __DELETE_QUALIFIER,
            __VOLATILE_QUALIFIER | __DELETE_QUALIFIER,
            __REFERENCE_QUALIFIER | __DELETE_QUALIFIER
        >
    {
    };

    template <class T>
    class __TypeTransform<__TO_SLIMMED_TYPE, T*> : public __TypeTransform<
            __POINTER_QUALIFIER,
            typename __TypeTransform<__TO_SLIMMED_TYPE, T>::type>
    {
    };

    template <class T>
    class __TypeTransform<__TO_SLIMMED_TYPE, T[]> : public __TypeTransform<
            __ARRAY_QUALIFIER,
            typename __TypeTransform<__TO_SLIMMED_TYPE, T>::type>
    {
    };

    template <class T, glong numberOfElements>
    class __TypeTransform<__TO_SLIMMED_TYPE, T[numberOfElements]> : public __TypeTransform<
            __ARRAY_QUALIFIER,
            typename __TypeTransform<__TO_SLIMMED_TYPE, T>::type,
            numberOfElements>
    {
    };

    // Instance types
    template <class T, class U>
    class __TypeTesting<__IS_INSTANCE_OF_TYPE, T, U> : public __AlwaysFalse
    {
        template <class __T, class __U,
                  gboolean __V = __TypeTesting<__IS_SAME_TYPE, __T>::value,
                  gboolean __W = __TypeTesting<__IS_CLASS_TYPE, __T>::value,
                  gboolean __X = __TypeTesting<__IS_CLASS_TYPE, __U>::value,
                  gboolean __Y = __TypeTesting<__IS_SUPER_TYPE, __T, __U>::value
        >
        class __TypeInstanceCheck;

        template <class __T, class __U, gboolean __V, gboolean __W, gboolean __X>
        class __TypeInstanceCheck<__T, __U, true, __V, __W, __X>
        {
        public:
            static CORE_FAST gboolean isInstanceOf(__U const&) { return true; }
        };

        template <class __T, class __U, gboolean __V, gboolean __W>
        class __TypeInstanceCheck<__T, __U, false, false, __V, __W>
        {
        public:
            static CORE_FAST gboolean isInstanceOf(__U const&) { return false; }
        };

        template <class __T, class __U, gboolean __V, gboolean __W>
        class __TypeInstanceCheck<__T, __U, false, __V, false, __W>
        {
        public:
            static CORE_FAST gboolean isInstanceOf(__U const&) { return false; }
        };

        template <class __T, class __U, gboolean __V, gboolean __W>
        class __TypeInstanceCheck<__T, __U, false, __V, __W, true>
        {
        public:
            static CORE_FAST gboolean isInstanceOf(__U const&) { return true; }
        };

        template <class __T, class __U, gboolean __V, gboolean __W>
        class __TypeInstanceCheck<__T, __U, false, __V, __W, false>
        {
        public:
            static CORE_FAST gboolean isInstanceOf(__U const& __value)
            {
                $alias(__Target, typename __TypeTransform<__TO_SLIMMED_TYPE, __T>::type);
                $alias(__Expected, typename __TypeTransform<__TO_SLIMMED_TYPE, __U>::type);
                return $cast(__Target, (__Expected)__value);
            }
        };

    public:
        static CORE_FAST gboolean checkInstance(U const& value)
        {
            return __TypeInstanceCheck<T, U>::isInstanceOf(value);
        }
    };

    // Template types
    template <template <class...> class T, class... U>
    class __TypeTesting<__IS_TEMPLATE_TYPE, T<U...>> : public __AlwaysTrue
    {
    };
} // core::lang::spi

#endif // CORE_LANG_TRAITS_H
