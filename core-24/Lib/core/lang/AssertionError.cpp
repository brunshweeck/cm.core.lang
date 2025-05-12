//
// Created by brunshweeck on 4/27/25.
//

#include "AssertionError.h"

#include <core/misc/VarHandle.h>
#include "Character.h"
#include "Double.h"
#include "Long.h"

namespace core
{
    AssertionError::AssertionError(const String &message): Error(message) {
    }

    AssertionError::AssertionError(const Object &message): Error(message.toString()) {
        if (Class<Throwable>::hasInstance(message))
            initCause($cast(const Throwable&, message));
    }

    AssertionError::AssertionError(gboolean message): Error(message ? $toString(true) : $toString(false)) {
    }

    AssertionError::AssertionError(gchar message): Error(Character::toString(message)) {
    }

    AssertionError::AssertionError(glong message): Error(Long::toString(message)) {
    }

    AssertionError::AssertionError(gdouble message): Error(Double::toString(message)) {
    }

    AssertionError::AssertionError(const String& message, const Throwable &throwable): Error(message, throwable) {
    }

    lang::Error & AssertionError::clone() const {
        return misc::VarHandle::newObject<AssertionError>(*this);
    }

    void AssertionError::selfThrow() const { throw *this; }
} // core
