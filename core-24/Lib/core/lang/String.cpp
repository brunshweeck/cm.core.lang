//
// Created by brunshweeck on 4/17/25.
//

#include "String.h"

#include "Error.h"
#include "Exception.h"
#include "Null.h"

namespace core { namespace lang
    {
        static CORE_FAST spi::__int32 _val = 0x07FF;
        static CORE_FAST spi::__int8 _val1 = (gbyte)(0xc0 | _val >> 6);
        static CORE_FAST spi::__int8 _val2 = (gbyte)(0x80 | _val & 0x3f);
        static CORE_FAST const spi::__literal_char8* _8 = "\u0080";
        static CORE_FAST const spi::__literal_char16* _16 = u"\u07FF";
        static CORE_FAST const spi::__literal_char32* _32 = U"\u07FF";
        static CORE_FAST const spi::__literal_varchar* _var = L"\u07FF";
    }

    inline namespace literals
    {
        String operator ""_S(lang::spi::__literal_char8 const input[], lang::spi::__uint64 count) {
            try {
                static CORE_FAST gboolean UsingUtf8Decoder = lang::_8[0] != lang::_val1 || lang::_8[1] != lang::_val2;
                if (UsingUtf8Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception& ex) {
                ex.throws($ftrace());
            } catch (const lang::Error& err) {
                err.throws($ftrace());
            }
        }

        String operator ""_S(lang::spi::__literal_char16 const input[], lang::spi::__uint64 count) {
            try {
                static CORE_FAST gboolean UsingUtf16Decoder = lang::_16[0] == lang::_val;
                if (UsingUtf16Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception& ex) {
                ex.throws($ftrace());
            } catch (const lang::Error& err) {
                err.throws($ftrace());
            }
        }

        String operator ""_S(lang::spi::__literal_char32 const input[], lang::spi::__uint64 count) {
            try {
                static CORE_FAST gboolean UsingUtf32Decoder = lang::_32[0] == lang::_val;
                if (UsingUtf32Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception& ex) {
                ex.throws($ftrace());
            } catch (const lang::Error& err) {
                err.throws($ftrace());
            }
        }

        String operator ""_S(lang::spi::__literal_varchar const input[], lang::spi::__uint64 count) {
            try {
                static CORE_FAST gboolean UsingUnicodeDecoder = lang::_var[0] == lang::_val;
                if (UsingUnicodeDecoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception& ex) {
                ex.throws($ftrace());
            } catch (const lang::Error& err) {
                err.throws($ftrace());
            }
        }

        String operator ""_Sl(lang::spi::__literal_char8 const input[], lang::spi::__uint64 count) {
            if (input == null || count == 0L) return String();
            // TODO: Implements this method
        }

        String operator ""_Sl(lang::spi::__literal_char16 const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Sl(lang::spi::__literal_char32 const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Sl(lang::spi::__literal_varchar const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Su(lang::spi::__literal_char8 const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Su(lang::spi::__literal_char16 const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Su(lang::spi::__literal_char32 const input[], lang::spi::__uint64 count) {
        }

        String operator ""_Su(lang::spi::__literal_varchar const input[], lang::spi::__uint64 count) {
        }
    }} // core
