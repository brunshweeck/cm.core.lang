//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ERROR_H
#define CORE_LANG_ERROR_H
#include "Throwable.h"

namespace core
{
    namespace lang
    {
        class Error : public Throwable
        {
        public:
            CORE_EXPLICIT Error(const String& message);
            CORE_EXPLICIT Error(const String& message, const Throwable& cause);
            CORE_EXPLICIT Error(const Throwable& cause);
            ~Error() override = default;

            Error& clone() const override;
        private:
            void selfThrow() const override;
        };
    } // lang
} // core

#endif // CORE_LANG_ERROR_H
