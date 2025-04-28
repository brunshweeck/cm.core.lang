//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_RUNTIMEEXCEPTION_H
#define CORE_LANG_RUNTIMEEXCEPTION_H
#include "Exception.h"

namespace core
{
    namespace lang
    {
        class RuntimeException : public Exception
        {
        public:
            explicit RuntimeException(const String& message);
            explicit RuntimeException(const String& message, const Throwable& cause);
            explicit RuntimeException(const Throwable& cause);
            ~RuntimeException() override = default;
            Exception& clone() const override;

        private:
            void selfThrow() const override;
        };
    } // lang
} // core

#endif // CORE_LANG_RUNTIMEEXCEPTION_H
