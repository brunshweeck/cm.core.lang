//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_EXCEPTION_H
#define CORE_LANG_EXCEPTION_H
#include "Throwable.h"

namespace core
{
    namespace lang
    {
        class Exception : public Throwable
        {
        public:
            CORE_EXPLICIT Exception(const String& message);
            CORE_EXPLICIT Exception(const String& message, const Throwable& cause);
            CORE_EXPLICIT Exception(const Throwable& cause);
            ~Exception() override = default;

            Exception& clone() const override;

        private:
            void selfThrow() const override;
        };
    } // lang
} // core

#endif // CORE_LANG_EXCEPTION_H
