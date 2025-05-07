//
// Created by brunshweeck on 06/04/25.
//

#ifndef CORE_LANG_LITERALS_H
#define CORE_LANG_LITERALS_H

#include "Traits.h"

#ifndef __UNARY_OPERATOR_DECL
#define __UNARY_OPERATOR_DECL(Operator, Type, Return) \
    extern $reverse($reverse(Operator, operator) (Type), Return);
#endif // __UNARY_OPERATOR_DECL

#ifndef __BINARY_OPERATOR_DECL
#define __BINARY_OPERATOR_DECL(Operator, LhsType, RhsType, Return) \
    extern $reverse($reverse(Operator, operator) (LhsType, RhsType), Return);

#define __BINARY_OPERATOR_DECL2(Operator, LhsType, RhsType, Return) \
    extern $reverse($reverse(Operator, operator) (LhsType, RhsType), Return); \
    extern $reverse($reverse(Operator, operator) (RhsType, LhsType), Return);
#endif // __BINARY_OPERATOR_DECL

/*
        Strings operations
 */

#define __STRING_OPERATION_DECL(String)  \
    __BINARY_OPERATOR_DECL(+, String const&, String const&, String)     \
    __BINARY_OPERATOR_DECL(+, String const&, Object const&, String)     \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_boolean_t, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int8_t, String)     \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint8_t, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int16_t, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint16_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int32_t, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint32_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int64_t, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint64_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__varint_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uvarint_t, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__float32_t, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__float64_t, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_float64_t, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char8_t, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char16_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char32_t, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_varchar_t, String)      \
    \
    __BINARY_OPERATOR_DECL(+=, String&, Object const&, String&)     \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_boolean_t, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int8_t, String&)     \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint8_t, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int16_t, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint16_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int32_t, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint32_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int64_t, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint64_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__varint_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uvarint_t, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__float32_t, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__float64_t, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_float64_t, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char8_t, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char16_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char32_t, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_varchar_t, String&)      \
    \
    __BINARY_OPERATOR_DECL(==, String const&, String const&, gboolean)      \
    __BINARY_OPERATOR_DECL2(==, String const&, Object const&, gboolean)      \
    __BINARY_OPERATOR_DECL2(==, String const&, lang::Null const&, gboolean)      \
    \
    __BINARY_OPERATOR_DECL(!=, String const&, String const&, gboolean)      \
    __BINARY_OPERATOR_DECL2(!=, String const&, Object const&, gboolean) \
    __BINARY_OPERATOR_DECL2(!=, String const&, lang::Null const&, gboolean)

#define __STRING_LITERAL_OPERATORS_DECL(String, Suffix) \
    __BINARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char8_t const[], lang::spi::__uint64_t, String) \
    __BINARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char16_t const[], lang::spi::__uint64_t, String) \
    __BINARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char32_t const[], lang::spi::__uint64_t, String) \
    __BINARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_varchar_t const[], lang::spi::__uint64_t, String)

/*
        Objects operations
 */

#define __OBJECT_OPERATION_DECL(Object) \
    __BINARY_OPERATOR_DECL(==, Object const&, Object const&, gboolean) \
    __BINARY_OPERATOR_DECL(!=, Object const&, Object const&, gboolean)

/*
        Numbers operations
 */

#define __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, Operator) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, Number const&, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int8_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint8_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int16_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint16_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int32_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint32_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int64_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint64_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__varint_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uvarint_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__float32_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__float64_t, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__literal_float64_t, Number) \
    \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, Number const&, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int8_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint8_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int16_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint16_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int32_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint32_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int64_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint64_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__varint_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uvarint_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__float32_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__float64_t, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__literal_float64_t, Number&)

#define __NUMBER_OPERATION_DECL(Number) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, +) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, -) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, *) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, /)

#define __INTEGER_LITERAL_OPERATORS_DECL(Number, Suffix) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_int64, Number)

#define __FLOATING_LITERAL_OPERATORS_DECL(Number, Suffix) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_float64_t, Number)

#define __NULL_OPERATION_DECL(Null) \
    __OBJECT_OPERATION_DECL(Null)\
    __BINARY_OPERATOR_DECL2(==, Null const&, void*, gboolean) \
    __BINARY_OPERATOR_DECL2(!=, Null const&, void*, gboolean)

#define CORE_INTRINSIC_ACCESS_DECL(ValueType) \
        operator ValueType const () const CORE_NOTHROW; \
        operator ValueType () volatile CORE_NOTHROW; \
        operator ValueType const () const volatile CORE_NOTHROW; \
        operator ValueType& () & CORE_NOTHROW; \
        operator ValueType const& () const& CORE_NOTHROW; \
        operator ValueType volatile& () volatile& CORE_NOTHROW; \
        operator ValueType const volatile& () const volatile& CORE_NOTHROW; \
        operator ValueType&& () && CORE_NOTHROW; \
        operator ValueType const&& () const&& CORE_NOTHROW; \
        operator ValueType volatile&& () volatile&& CORE_NOTHROW; \
        operator ValueType const volatile&& () const volatile&& CORE_NOTHROW;

#define CORE_INTRINSIC_ACCESS_IMPL(ValueType, ClassType, FieldName) \
        ClassType::operator ValueType const () const CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType () volatile CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType const () const volatile CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType& () & CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType const& () const& CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType volatile& () volatile& CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType const volatile& () const volatile& CORE_NOTHROW { return FieldName; } \
        ClassType::operator ValueType&& () && CORE_NOTHROW { return (ValueType&&) FieldName; } \
        ClassType::operator ValueType const&& () const&& CORE_NOTHROW { return (ValueType const&&) FieldName; } \
        ClassType::operator ValueType volatile&& () volatile&& CORE_NOTHROW { return (ValueType volatile&&) FieldName; } \
        ClassType::operator ValueType const volatile&& () const volatile&& CORE_NOTHROW { return (ValueType const volatile &&) FieldName; }

#define CORE_SET_AS_NON_COPYABLE_CLASS(ClassType) \
       ClassType (const ClassType&  ) = delete;  \
       ClassType (const ClassType&&) = delete; \
       ClassType& operator=(const ClassType&  ) = delete; \
       ClassType& operator=(const ClassType&&) CORE_NOTHROW = delete;
#define CORE_INTRINSIC_INDEXED_ITEM_ACCESS_DECL(ValueType, IndexType, ...) \
    virtual ValueType& operator[](IndexType) CORE_NOTHROW; \
    virtual const ValueType& operator[](IndexType) const CORE_NOTHROW;

#define CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(ValueType, IndexType, ClassType, GetterName, TemplateDeclaration) \
    TemplateDeclaration ValueType& ClassType::operator[](IndexType index) CORE_NOTHROW { return GetterName(index); } \
    TemplateDeclaration const ValueType& ClassType::operator[](IndexType index) const CORE_NOTHROW { return GetterName(index); }

#define CORE_INTRINSIC_FOR_EACH_DECL(ForEachClassType, ForEachRefClassType) \
    ForEachClassType begin() const CORE_NOTHROW; \
    ForEachClassType end() const CORE_NOTHROW; \
    ForEachRefClassType begin() CORE_NOTHROW;\
    ForEachRefClassType end() CORE_NOTHROW;

#define CORE_INTRINSIC_FOR_EACH_IMPL(ForEachClassType, ForEachRefClassType, ClassType, startCtorArgs, endCtorArgs, TemplateDeclaration) \
    TemplateDeclaration ForEachClassType ClassType::begin() const CORE_NOTHROW { return ForEachClassType startCtorArgs; } \
    TemplateDeclaration ForEachClassType ClassType::end() const CORE_NOTHROW { return ForEachClassType endCtorArgs; }  \
    TemplateDeclaration ForEachRefClassType ClassType::begin() CORE_NOTHROW { return ForEachRefClassType startCtorArgs; } \
    TemplateDeclaration ForEachRefClassType ClassType::end() CORE_NOTHROW { return ForEachRefClassType endCtorArgs; } \


namespace core
{
    inline namespace literals
    {
        __STRING_OPERATION_DECL(String)
        __STRING_LITERAL_OPERATORS_DECL(String, _S)
        __STRING_LITERAL_OPERATORS_DECL(String, _Su)
        __STRING_LITERAL_OPERATORS_DECL(String, _Sl)
        __OBJECT_OPERATION_DECL(Object)
        __NUMBER_OPERATION_DECL(Complex)
        CORE_WARNING_PUSH
        CORE_WARNING_DISABLE_UDL
        __INTEGER_LITERAL_OPERATORS_DECL(Complex, i)
//        __INTEGER_LITERAL_OPERATORS_DECL(Complex, j)
        CORE_WARNING_POP
        __INTEGER_LITERAL_OPERATORS_DECL(Complex, _i)
//        __INTEGER_LITERAL_OPERATORS_DECL(Complex, _j)
        __NULL_OPERATION_DECL(lang::Null)
    } // literals
} // core

#undef __BINARY_OPERATOR_DECL
#undef __BINARY_OPERATOR_DECL2
#undef __UNARY_OPERATOR_DECL
#undef __NUMBER_OPERATION_FOR_OPERATOR_DECL
#endif // CORE_LANG_LITERALS_H
