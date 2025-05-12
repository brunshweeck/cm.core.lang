//
// Created by brunshweeck on 4/26/25.
//

#include "Throwable.h"

#include "Array.h"
#include "IllegalArgumentException.h"
#include "Null.h"
#include <core/misc/VarHandle.h>


namespace core::lang
{
    Throwable::Throwable(const Throwable &original)
        : detailMessage(original.detailMessage) {
        if (original.cause != null && original.cause != &original)
            initCause(original.getCause());
    }

    Throwable::Throwable(Throwable &&original) CORE_NOTHROW {
        detailMessage = (String &&) original.detailMessage;
        if (original.cause != null && original.cause != &original) {
            cause = original.cause;
            original.cause = &original;
        }
    }

    Throwable::Throwable(const String &message) {
        detailMessage = message;
        cause = this;
    }

    Throwable::Throwable(const String &message, const Throwable &cause) {
        detailMessage = message;
        initCause(cause);
    }

    String Throwable::getMessage() const {
        return detailMessage;
    }

    String Throwable::getLocalizedMessage() const {
        return getMessage();
    }

    const Throwable &Throwable::getCause() const {
        return cause == null ? *this : *cause;
    }

    Throwable &Throwable::initCause(const Throwable &cause) {
        if (Throwable::cause != null && Throwable::cause != this)
            IllegalArgumentException($toString(Could not override cause)).throws($ftrace());
        if (this == &cause)
            IllegalArgumentException($toString(Self-causation not permitted)).throws($ftrace());
        try {
            Throwable &thr = VH::copyObject(cause, cause.status == Status::COPY);
            Throwable::cause = &thr;
        }
        catch (CloneNotSupportedException &cnse) {
            IllegalArgumentException($toString(Non-cloneable throwable cause), cnse).throws($ftrace());
        }
        return *this;
    }

    void Throwable::dumpStackTrace() const {
    }

    Array<TraceInfo> Throwable::getStackTrace() const {
        return {};
    }

    gboolean Throwable::equals(const Object &other) const {
        return Object::equals(other);
    }

    gint Throwable::hash() const {
        return Object::hash();
    }

    String Throwable::toString() const {
        // todo: complete cet implementation
        // if (detailMessage.isEmpty())
        //     return getTypeName(*this);
        return getLocalizedMessage();
    }

    void Throwable::throws(const TraceInfo &currentExecutionPoint) const CORE_THROW {
        throws();
    }

    void Throwable::throws() const CORE_THROW {
        selfThrow();
        CORE_UNREACHABLE();
    }

    Throwable &Throwable::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
    }

    void Throwable::selfThrow() const {
        UnsupportedOperationException($toString(self-thrown)).throws($ftrace());
    }

    Throwable::NativeMessage Throwable::what() const noexcept {
        return exception::what();
    }
} // lang
// core
