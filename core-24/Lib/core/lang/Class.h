//
// Created by brunshweeck on 06/04/25.
//

#ifndef CORE_LANG_CLASS_H
#define CORE_LANG_CLASS_H

#include "Object.h"

namespace core
{
    template <class T>
    class Class $final: public Object
    {
        CORE_FAST Class() = default;

    public:
        /*
            All Version of T
         */

        /// Version of T with @c const qualifier
        $alias(Constant, typename lang::spi::__TypeTransform<__CONST_QUALIFIER, T>::type);

        /// Version of T without @c const qualifier
        $alias(NoConstant,
               typename lang::spi::__TypeTransform<__CONST_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Version of T with @c volatile qualifier
        $alias(Volatile, typename lang::spi::__TypeTransform<__VOLATILE_QUALIFIER, T>::type);

        /// Version of T without @c volatile qualifier
        $alias(NoVolatile,
               typename lang::spi::__TypeTransform<__VOLATILE_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Version of T with @c & qualifier
        $alias(Reference, typename lang::spi::__TypeTransform<__REFERENCE_QUALIFIER, T>::type);

        /// Version of T without @c & and @c && qualifiers
        $alias(NoReference,
               typename lang::spi::__TypeTransform<__REFERENCE_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Version of T with @c & qualifier
        $alias(LvalueReference,
               typename lang::spi::__TypeTransform<__REFERENCE_QUALIFIER | __LVALUE_QUALIFIER, T>::type);

        /// Version of T without @c & qualifier
        $alias(NoLvalueReference, typename lang::spi::__TypeTransform<
               __REFERENCE_QUALIFIER | __LVALUE_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Version of T with @c && qualifier
        $alias(RvalueReference,
               typename lang::spi::__TypeTransform<__REFERENCE_QUALIFIER | __RVALUE_QUALIFIER, T>::type);

        /// Version of T without @c && qualifier
        $alias(NoRvalueReference, typename lang::spi::__TypeTransform<
               __REFERENCE_QUALIFIER | __RVALUE_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Pointer Version of T
        $alias(Pointer, typename lang::spi::__TypeTransform<__POINTER_QUALIFIER, T>::type);

        /// NonPointer Version of T
        $alias(NoPointer, typename lang::spi::__TypeTransform<__POINTER_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Multi-Dimensional Pointer Version of T
        /// @tparam dimension The number of pointer layers
        template <glong dimension>
        $alias(MultiPointer, typename lang::spi::__TypeTransform<__POINTER_QUALIFIER, T, -1, dimension>::type);

        /// Unbound Array Version of T
        $alias(UnboundArray, typename lang::spi::__TypeTransform<__ARRAY_QUALIFIER, T>::type);

        /// Multi-Dimensional Unbound Array Version of T
        ///  @tparam dimension The number of array layer
        template <glong dimension>
        $alias(MultiUnboundArray, typename lang::spi::__TypeTransform<__ARRAY_QUALIFIER, T, -1, dimension>::type);

        /// Bounded Array Version of T
        /// @tparam numberOfElements The number of array elements
        template <glong numberOfElements>
        $alias(Array, typename lang::spi::__TypeTransform<__ARRAY_QUALIFIER, T, numberOfElements>::type);

        ///  Non Array Version of T
        $alias(NoArray, typename lang::spi::__TypeTransform<__ARRAY_QUALIFIER | __DELETE_QUALIFIER, T>::type);

        /// Multi-Dimensional Bounded Array Version of T
        ///  @tparam numberOfElements The number of elements per layer
        ///  @tparam dimension The number of array layer
        template <glong numberOfElements, glong dimension>
        $alias(MultiArray,
               typename lang::spi::__TypeTransform<__ARRAY_QUALIFIER, T, numberOfElements, dimension>::type);

        /// Constant - Volatile Version of T
        /// @see Class::Constant
        /// @see Class::Volatile
        $alias(ConstVolatile,
               typename lang::spi::__TypeChainedTransform<T, __CONST_QUALIFIER, __VOLATILE_QUALIFIER>::type);

        /// NoConstant - NoVolatile Version of T
        /// @see Class::NoConstant
        /// @see Class::NoVolatile
        $alias(NoConstVolatile, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER | __DELETE_QUALIFIER, __VOLATILE_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Constant - Volatile - Reference Version of T
        /// @see Class::Constant
        /// @see Class::Volatile
        /// @see Class::Reference
        $alias(ConstVolatileRef, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER, __VOLATILE_QUALIFIER, __REFERENCE_QUALIFIER>::type);

        /// NoConstant - NoVolatile - NoReference Version of T
        /// @see Class::NoConstant
        /// @see Class::NoVolatile
        /// @see Class::NoReference
        $alias(NoConstVolatileRef, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER | __DELETE_QUALIFIER, __VOLATILE_QUALIFIER | __DELETE_QUALIFIER,
               __REFERENCE_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Constant - Reference Version of T
        $alias(ConstRef,
               typename lang::spi::__TypeChainedTransform<T, __CONST_QUALIFIER, __REFERENCE_QUALIFIER>::type);

        /// NoConstant - NoReference Version of T
        /// @see Class::NoConstant
        /// @see Class::NoReference
        $alias(NoConstRef, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER | __DELETE_QUALIFIER, __REFERENCE_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Volatile - Reference Version of T
        $alias(VolatileRef,
               typename lang::spi::__TypeChainedTransform<T, __VOLATILE_QUALIFIER, __REFERENCE_QUALIFIER>::type);

        /// NoVolatile - NoReference Version of T
        /// @see Class::NoVolatile
        /// @see Class::NoReference
        $alias(NoVolatileRef, typename lang::spi::__TypeChainedTransform<T,
               __VOLATILE_QUALIFIER | __DELETE_QUALIFIER, __REFERENCE_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Constant - Volatile - Pointer Version of T
        /// @see Class::Constant
        /// @see Class::Volatile
        /// @see Class::Pointer
        $alias(ConstVolatilePointer, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER, __VOLATILE_QUALIFIER, __POINTER_QUALIFIER>::type);

        /// NoConstant - NoVolatile - NoPointer Version of T
        /// @see Class::NoConstant
        /// @see Class::NoVolatile
        /// @see Class::NoPointer
        $alias(NoConstVolatilePointer, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER | __DELETE_QUALIFIER, __VOLATILE_QUALIFIER | __DELETE_QUALIFIER,
               __POINTER_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Constant - Pointer Version of T
        $alias(ConstPointer,
               typename lang::spi::__TypeChainedTransform<T, __CONST_QUALIFIER, __POINTER_QUALIFIER>::type);

        /// NoConstant - NoPointer Version of T
        /// @see Class::NoConstant
        /// @see Class::NoPointer
        $alias(NoConstPointer, typename lang::spi::__TypeChainedTransform<T,
               __CONST_QUALIFIER | __DELETE_QUALIFIER, __POINTER_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Volatile - Pointer Version of T
        $alias(VolatilePointer,
               typename lang::spi::__TypeChainedTransform<T, __VOLATILE_QUALIFIER, __POINTER_QUALIFIER>::type);

        /// NoVolatile - NoPointer Version of T
        /// @see Class::NoVolatile
        /// @see Class::NoPointer
        $alias(NoVolatilePointer, typename lang::spi::__TypeChainedTransform<T,
               __VOLATILE_QUALIFIER | __DELETE_QUALIFIER, __POINTER_QUALIFIER | __DELETE_QUALIFIER>::type);

        /// Slimmed version of T
        /// @see Class::NoConstant
        /// @see Class::NoVolatile
        /// @see Class::NoReference
        /// @see Class::NoConstVolatileRef
        $alias(Slimmed, typename lang::spi::__TypeTransform<__TO_SLIMMED_TYPE, T>::type);

        /// Strict Conditional version of T
        /// @tparam condition The condition of validity of T
        template <gboolean condition>
        $alias(OnlyIf, typename lang::spi::__StrictCondition<condition, T>::type);

        /// Strict Multi-Conditional version of T
        /// @tparam conditions The conditions of validity of T
        template <gboolean ... conditions>
        $alias(OnlyIfAll, typename lang::spi::__StrictCondition<
               lang::spi::__All<lang::spi::__Always<conditions>...>::value, T>::type);

        /// Strict Multi-Conditional version of T
        /// @tparam conditions The conditions of validity of T
        template <gboolean ... conditions>
        $alias(OnlyIfAny, typename lang::spi::__StrictCondition<
               lang::spi::__Any<lang::spi::__Always<conditions>...>::value, T>::type);

        /// Conditional version of T
       /// @tparam condition The condition of validity of T
       /// @tparam FallbackType The type returned if condition is @c false
        template <gboolean condition, class FallbackType>
        $alias(IfOrElse, typename lang::spi::__Condition<condition, T, FallbackType>::type);

        /// This type
        $alias(Identity, T);

        /// Class version of T
        $alias(ClassType, typename lang::spi::__TypeTransform<__TO_CLASS_TYPE, Slimmed>::type);

        /// Primitive version of T
        $alias(Primitive, typename lang::spi::__TypeTransform<__TO_PRIMITIVE_TYPE, Slimmed>::type);

        /// Return type of instance of T called with given arguments types
        template <class... Args>
        $alias(ReturnType, typename lang::spi::__TypeTesting<__IS_CALLABLE_TYPE, T, Args...>::optionalType::type);

        /// Size of T in bytes
        static CORE_FAST glong SIZE = lang::spi::__TypeTesting<__IS_SIZEABLE_TYPE, Slimmed>::size;

        /// Number of Elements in any instance of T
        static CORE_FAST glong COUNT = lang::spi::__TypeTesting<__IS_SIZEABLE_TYPE, Slimmed>::count;

        /*
              The Properties checker of T
         */

        template <class U>
        static CORE_FAST gboolean isSameTo() { return lang::spi::__TypeTesting<__IS_SAME_TYPE, T, U>::value; }

        template <class... U>
        static CORE_FAST gboolean isSameToAny()
        {
            return lang::spi::__Any<lang::spi::__TypeTesting<__IS_SAME_TYPE, T, U>...>::value;
        }

        /// Return @c true if T has @c const qualifier
        static CORE_FAST gboolean isConstant() { return lang::spi::__TypeTesting<__IS_CONSTANT_TYPE, T>::value; }

        /// Return @c true if T has @c volatile qualifier
        static CORE_FAST gboolean isVolatile() { return lang::spi::__TypeTesting<__IS_VOLATILE_TYPE, T>::value; }

        /// Return @c true if T has @c & or @c && qualifier
        static CORE_FAST gboolean isReference() { return lang::spi::__TypeTesting<__IS_REFERENCE_TYPE, T>::value; }

        /// Return @c true if T is pointer type
        static CORE_FAST gboolean isPointer() { return lang::spi::__TypeTesting<__IS_POINTER_TYPE, T>::value; }

        /// Return @c true if T has @c && qualifier
        static CORE_FAST gboolean isRvalue() { return lang::spi::__TypeTesting<__IS_RVALUE_TYPE, T>::value; }

        /// Return @c true if T is an array type
        ///  @note In this case, use @c Class::COUNT constant to find number of element supported by T
        static CORE_FAST gboolean isArray() { return lang::spi::__TypeTesting<__IS_ARRAY_TYPE, T>::value; }

        /// Return @c true if is possible to calculate size of T in current scope
        /// @note In this case use @c Class::SIZE constant to find size in bytes of T
        static CORE_FAST gboolean isSizeable() { return lang::spi::__TypeTesting<__IS_SIZEABLE_TYPE, T>::value; }

        /// Return @c true if T is template type
        static CORE_FAST gboolean isTemplate() { return lang::spi::__TypeTesting<__IS_TEMPLATE_TYPE, T>::value; }

        /// Return @c true if T is function type
        static CORE_FAST gboolean isFunction() { return lang::spi::__TypeTesting<__IS_FUNCTION_TYPE, T>::value; }

        /// Return @c true if T is member type
        static CORE_FAST gboolean isMember() { return lang::spi::__TypeTesting<__IS_MEMBER_TYPE, T>::value; }

        /// Return @c true if T is function member type
        static CORE_FAST gboolean isFunctionMember()
        {
            return lang::spi::__TypeTesting<__IS_FUNCTION_MEMBER_TYPE, T>::value;
        }

        /// Return @c true if T is abstract type
        static CORE_FAST gboolean isAbstract() { return lang::spi::__TypeTesting<__IS_ABSTRACT_TYPE, T>::value; }

        /// Return @c true if T is enumeration type
        static CORE_FAST gboolean isEnum() { return lang::spi::__TypeTesting<__IS_ENUM_TYPE, T>::value; }

        /// Return @c true if T is class or struct type
        static CORE_FAST gboolean isClass() { return lang::spi::__TypeTesting<__IS_CLASS_TYPE, T>::value; }

        /// Return @c true if T is class or struct type
        static CORE_FAST gboolean isPrimitive()
        {
            return isVoid() || isIntegral() || isFunction() || isEnum();
        }

        /// Return @c true if T is union type
        static CORE_FAST gboolean isUnion() { return lang::spi::__TypeTesting<__IS_UNION_TYPE, T>::value; }

        /// Return @c true if T is empty type
        static CORE_FAST gboolean isEmpty() { return lang::spi::__TypeTesting<__IS_EMPTY_TYPE, T>::value; }

        /// Return @c true if T is literal type
        static CORE_FAST gboolean isLiteral() { return lang::spi::__TypeTesting<__IS_LITERAL_TYPE, T>::value; }

        /// Return @c true if T is polymorphic type
        static CORE_FAST gboolean isPolymorphic() { return lang::spi::__TypeTesting<__IS_POLYMORPHIC_TYPE, T>::value; }

        /// Return @c true if T is trivial type
        static CORE_FAST gboolean isTrivial() { return lang::spi::__TypeTesting<__IS_TRIVIAL_TYPE, T>::value; }

        /// Return @c true if T is boolean type
        static CORE_FAST gboolean isBoolean() { return lang::spi::__TypeTesting<__IS_BOOLEAN_TYPE, T>::value; }

        /// Return @c true if T is integer number type
        static CORE_FAST gboolean isInteger() { return lang::spi::__TypeTesting<__IS_INTEGER_TYPE, T>::value; }

        /// Return @c true if T is floating number type
        static CORE_FAST gboolean isFloating() { return lang::spi::__TypeTesting<__IS_FLOAT_TYPE, T>::value; }

        /// Return @c true if T is character type
        static CORE_FAST gboolean isCharacter() { return lang::spi::__TypeTesting<__IS_CHARACTER_TYPE, T>::value; }

        /// Return @c true if T is string type
        static CORE_FAST gboolean isString() { return lang::spi::__TypeTesting<__IS_STRING_TYPE, T>::value; }

        /// Return @c true if T is void type
        static CORE_FAST gboolean isVoid() { return lang::spi::__TypeTesting<__IS_VOID_TYPE, T>::value; }

        /// Return @c true if T is number type
        static CORE_FAST gboolean isNumber() { return isInteger() || isFloating(); }

        /// Return @c true if T is integral type
        static CORE_FAST gboolean isIntegral() { return isInteger() || isCharacter() || isBoolean(); }

        /// Return @c true if T is slimmed type
        static CORE_FAST gboolean isSlimmed() { return lang::spi::__TypeTesting<__IS_SLIMMED_TYPE, T>::value; }

        /// Return @c true if T support or implement @c operator==
        static CORE_FAST gboolean isEqComparable()
        {
            return lang::spi::__TypeTesting<__IS_EQUAL_TO_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support or implement @c operator!=
        static CORE_FAST gboolean isNeComparable()
        {
            return lang::spi::__TypeTesting<__IS_NOT_EQUAL_TO_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support or implement @c operator<
        static CORE_FAST gboolean isLtComparable()
        {
            return lang::spi::__TypeTesting<__IS_LESS_THAN_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support or implement @c operator<=
        static CORE_FAST gboolean isLeComparable()
        {
            return lang::spi::__TypeTesting<__IS_LESS_THAN_OR_EQUAL_TO_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support or implement @c operator>
        static CORE_FAST gboolean isGtComparable()
        {
            return lang::spi::__TypeTesting<__IS_GREATER_THAN_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support or implement @c operator>=
        static CORE_FAST gboolean isGeComparable()
        {
            return lang::spi::__TypeTesting<__IS_GREATER_THAN_OR_EQUAL_TO_COMPARABLE_TYPE, T>::value;
        }

        /// Return @c true if T support natural comparison
        static CORE_FAST gboolean isNaturallyComparable()
        {
            return (
                (isEqComparable() || isNeComparable())
                && (isLtComparable() || isGtComparable() || isLeComparable() || isGeComparable())
            ) || (isLeComparable() && isGeComparable());
        }

        /// Return @c true if instance  of typeT can be constructed with arguments types
        ///  @tparam Args The arguments type
        template <class... Args>
        static CORE_FAST gboolean isConstructible()
        {
            return lang::spi::__TypeTesting<__IS_CONSTRUCTIBLE_TYPE, T, Args...>::value;
        }

        /// Return @c true if instance of type T is assignable to instance of given type
        /// @tparam U The target type for assignment
        template <class U>
        static CORE_FAST gboolean isAssignableTo()
        {
            return lang::spi::__TypeTesting<__IS_ASSIGNABLE_TYPE, U, T>::value;
        }

        /// Return @c true if T is base of given type
        /// @tparam U the given Type
        template <class U>
        static CORE_FAST gboolean isBaseOf() { return lang::spi::__TypeTesting<__IS_SUPER_TYPE, T, U>::value; }

        /// Return @c true if any instance of type T is convertible implicitly to given type
        /// @tparam U The target type
        template <class U>
        static CORE_FAST gboolean isConvertibleTo()
        {
            return lang::spi::__TypeTesting<__IS_CONVERTIBLE_TYPE, T, U>::value;
        }

        /// Return @c true if any instance of type T support or implement @c operator() with
        /// given arguments type
        /// @tparam Args The arguments type
        template <class... Args>
        static CORE_FAST gboolean isCallable()
        {
            return lang::spi::__TypeTesting<__IS_CALLABLE_TYPE, T, Args...>::value;
        }

        /// Return @c true if the given value is instance of type T
        /// @tparam U the type of given value
        /// @param value The value to test
        template <class U>
        static CORE_FAST gboolean hasInstance(U const& value)
        {
            return lang::spi::__TypeTesting<__IS_INSTANCE_OF_TYPE, T, U>::isInstanceOf(value);
        }
    };
} // core

#undef __DELETE_QUALIFIER
#undef __CONST_QUALIFIER
#undef __VOLATILE_QUALIFIER
#undef __REFERENCE_QUALIFIER
#undef __POINTER_QUALIFIER
#undef __ARRAY_QUALIFIER
#undef __IS_FUNCTION_TYPE
#undef __IS_CLASS_TYPE
#undef __IS_ENUM_TYPE
#undef __IS_UNION_TYPE
#undef __IS_PRIMITIVE_TYPE
#undef __TO_CLASS_TYPE
#undef __TO_PRIMITIVE_TYPE
#undef __IS_SAME_TYPE
#undef __IS_TEMPLATE_TYPE
#undef __IS_FUNCTION_MEMBER_TYPE
#undef __IS_ABSTRACT_TYPE
#undef __IS_ARRAY_TYPE
#undef __IS_SUPER_TYPE
#undef __IS_FINAL_TYPE
#undef __IS_SIZEABLE_TYPE
#undef __IS_INTEGER_TYPE
#undef __IS_FLOAT_TYPE
#undef __IS_VOID_TYPE
#undef __IS_BOOLEAN_TYPE
#undef __IS_CHARACTER_TYPE
#undef __IS_STRING_TYPE
#undef __IS_CALLABLE_TYPE
#undef __IS_EMPTY_TYPE
#undef __IS_TRIVIAL_TYPE
#undef __IS_POLYMORPHIC_TYPE
#undef __IS_LITERAL_TYPE
#undef __IS_SLIMMED_TYPE
#undef __IS_CONVERTIBLE_TYPE
#undef __IS_CONSTRUCTIBLE_TYPE
#undef __IS_ASSIGNABLE_TYPE
#undef __IS_DESTRUCTIBLE_TYPE
#undef __IS_COPYABLE_TYPE
#undef __IS_LESS_THAN_COMPARABLE_TYPE
#undef __IS_EQUAL_TO_COMPARABLE_TYPE
#undef __IS_GREATER_THAN_COMPARABLE_TYPE
#undef __IS_GREATER_THAN_OR_EQUAL_TO_COMPARABLE_TYPE
#undef __IS_NOT_EQUAL_TO_COMPARABLE_TYPE
#undef __IS_LESS_THAN_OR_EQUAL_TO_COMPARABLE_TYPE
#undef __IS_CONSTANT_TYPE
#undef __IS_REFERENCE_TYPE
#undef __IS_POINTER_TYPE
#undef __IS_VOLATILE_TYPE
#undef __LVALUE_QUALIFIER
#undef __RVALUE_QUALIFIER
#undef __IS_MEMBER_TYPE
#undef __TO_SLIMMED_TYPE
#undef __IS_INSTANCE_OF_TYPE
#undef __IS_RVALUE_TYPE

#ifdef ClassOf
#undef ClassOf
#endif // ClassOf

#define ClassOf(expr) Class<decltype(expr)>

#endif // CORE_LANG_CLASS_H
