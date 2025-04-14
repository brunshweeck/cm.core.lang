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
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_boolean, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int8, String)     \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint8, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int16, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint16, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int32, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint32, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__int64, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uint64, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__varint, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__uvarint, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__float32, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__float64, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_float64, String)      \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char8, String)        \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char16, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_char32, String)       \
    __BINARY_OPERATOR_DECL(+, String const&, lang::spi::__literal_varchar, String)      \
    \
    __BINARY_OPERATOR_DECL(+=, String&, Object const&, String&)     \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_boolean, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int8, String&)     \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint8, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int16, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint16, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int32, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint32, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__int64, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uint64, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__varint, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__uvarint, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__float32, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__float64, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_float64, String&)      \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char8, String&)        \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char16, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_char32, String&)       \
    __BINARY_OPERATOR_DECL(+=, String&, lang::spi::__literal_varchar, String&)      \
    \
    __BINARY_OPERATOR_DECL(==, String const&, String const&, gboolean)      \
    __BINARY_OPERATOR_DECL2(==, String const&, Object const&, gboolean)      \
    \
    __BINARY_OPERATOR_DECL(!=, String const&, String const&, gboolean)      \
    __BINARY_OPERATOR_DECL2(!=, String const&, Object const&, gboolean)

#define __STRING_LITERAL_OPERATORS_DECL(String, Suffix) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char8, String) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char16, String) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_char32, String) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_varchar, String)

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
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int8, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint8, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int16, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint16, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int32, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint32, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__int64, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uint64, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__varint, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__uvarint, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__float32, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__float64, Number) \
    __BINARY_OPERATOR_DECL2(Operator, Number const&, lang::spi::__literal_float64, Number) \
    \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, Number const&, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int8, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint8, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int16, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint16, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int32, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint32, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__int64, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uint64, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__varint, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__uvarint, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__float32, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__float64, Number&) \
    __BINARY_OPERATOR_DECL2($concat(Operator, =), Number&, lang::spi::__literal_float64, Number&)

#define __NUMBER_OPERATION_DECL(Number) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, +) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, -) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, *) \
    __NUMBER_OPERATION_FOR_OPERATOR_DECL(Number, /)

#define __INTEGER_LITERAL_OPERATORS_DECL(Number, Suffix) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_int64, Number)

#define __FLOATING_LITERAL_OPERATORS_DECL(Number, Suffix) \
    __UNARY_OPERATOR_DECL($concat("", Suffix), lang::spi::__literal_float64, Number)

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
        __INTEGER_LITERAL_OPERATORS_DECL(Complex, j)
        CORE_WARNING_POP
        __INTEGER_LITERAL_OPERATORS_DECL(Complex, _i)
        __INTEGER_LITERAL_OPERATORS_DECL(Complex, _j)
    } // literals
} // core

#undef __BINARY_OPERATOR_DECL
#undef __UNARY_OPERATOR_DECL
#undef __NUMBER_OPERATION_FOR_OPERATOR_DECL
#endif // CORE_LANG_LITERALS_H
