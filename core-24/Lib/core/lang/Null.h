//
// Created by brunshweeck on 4/15/25.
//

#ifndef CORE_LANG_NULL_H
#define CORE_LANG_NULL_H

#include "Object.h"

namespace core
{
    namespace lang
    {
        /// The class @c Null represent the all objects with null address
        /// @see null
        class Null $final : public Object
        {
            CORE_FAST Null() = default;
            CORE_FAST Null(const Null&) = default;
            CORE_FAST Null(Null&&) = default;
            Null& operator=(const Null&) = default;
            Null& operator=(Null&&) = default;

        public:
            ~Null() override = default;

            /**
             * Return the single instance of this class
             * @return The instance of this class
             */
            static Null& getInstance();

            template <class T>
            CORE_FAST operator T*() const { return {}; }

            Null& clone() const override;
        };
    } // lang

    /// The unique instance of class @c Null
    extern lang::Null& null;
} // core

#endif //CORE_LANG_NULL_H
