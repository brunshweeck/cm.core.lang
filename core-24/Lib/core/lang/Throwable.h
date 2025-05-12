//
// Created by brunshweeck on 4/26/25.
//

#ifndef CORE_LANG_THROWABLE_H
#define CORE_LANG_THROWABLE_H

#include "TraceInfo.h"


namespace core::lang
{
    /// The @c Throwable class is the superclass of all errors and exceptions supported by Core24 platform.
    /// Only objects that are instances of this class (or one of its subclasses) can be thrown by the @c throws and @c rethrow method.
    /// Similarly, only this class or one of its subclasses can be the argument type in a @c catch clause after operation defined in this platform.
    /// For compile-time checking of exceptions, @c Throwable and any subclass of @c Throwable that is not also a subclass of either @b RuntimeException or @b Error are regarded as checked exceptions.
    /// Instances of two subclasses, @b core::Error and @b core::Exception, are conventionally used to indicate that exceptional situations have occurred.
    /// Typically, these instances are freshly created in the context of the exceptional situation to include relevant information (such as stack trace data).
    /// A throwable contains a snapshot of the execution stack of its thread at the time it was created. It can also contain a message string that gives more information about the error.
    /// Finally, the throwable can also contain a <i>cause</i>: another throwable that caused this throwable to be constructed.
    /// The recording of this causal information is referred to as the <i>chained exception</i> facility, as the cause can, itself, have a cause, and so on, leading to a "chain" of exceptions, each caused by another.
    /// One reason that a throwable may have a cause is that the class that throws it is built atop a lower layered abstraction, and an operation on the upper layer fails due to a failure in the lower layer.
    /// It would be bad design to let the throwable thrown by the lower layer propagate outward, as it is generally unrelated to the abstraction provided by the upper layer.
    /// Further, doing so would tie the API of the upper layer to the details of its implementation, assuming the lower layer's exception was a checked exception.
    /// Throwing a "wrapped exception" (i.e., an exception containing a cause) allows the upper layer to communicate the details of the failure to its caller without incurring either of these shortcomings.
    /// It preserves the flexibility to change the implementation of the upper layer without changing its API (in particular, the set of exceptions thrown by its methods).
    /// A second reason that a throwable may have a cause is that the method that throws it must conform to a general-purpose interface that does not permit the method to throw the cause directly.
    /// For example, suppose a persistent collection conforms to the @b Collection interface, and that its persistence is implemented atop @c core::io.
    /// Suppose the internals of the @c add method can throw an @b IOException.
    /// The implementation can communicate the details of the @c IOException to its caller while conforming to the @c Collection interface by wrapping the @c IOException in an appropriate unchecked exception.
    /// (The specification for the persistent collection should indicate that it is capable of throwing such exceptions.)
    /// A cause can be associated with a throwable in two ways: via a constructor that takes the cause as an argument, or via the @b setCause(Throwable) method.
    /// New throwable classes that wish to allow causes to be associated with them should provide constructors that take a cause and delegate (perhaps indirectly) to one of the @c Throwable constructors that takes a cause.
    /// Because the @c setCause method is public, it allows a cause to be associated with any throwable, even a "legacy throwable" whose implementation predates the addition of the exception chaining mechanism to @c Throwable.
    /// By convention, class @c Throwable and its subclasses have two constructors, one that takes no arguments and one that takes a @c String argument that can be used to produce a detail message.
    /// Further, those subclasses that might likely have a cause associated with them should have two more constructors, one that takes a @c Throwable (the cause), and one that takes a @c String (the detail message) and a @c Throwable (the cause).
    class Throwable : public Object, public std::exception
    {
        friend Exception;
        friend Error;
        $alias(Cause, Class<Throwable>::Pointer);
        $alias(Sentinel, Class<Object>::Pointer);
        $alias(NativeMessage, ClassOf('\0')::ConstPointer);

        /// Specific details about the Throwable.
        /// For example, for @c FileNotFoundException, this contains the name of the file that could not be found.
        String detailMessage;

        /// The throwable that caused this throwable to get thrown, or null if this throwable was not caused by another throwable, or if the causative throwable is unknown.
        /// If this field is equal to this throwable itself, it indicates that the cause of this throwable has not yet been initialized.
        Cause cause = this;

        /// This class saves some sign of the stack backtrace in this slot.
        Sentinel backtrace = {};

        enum class Status: gbyte
        {
            NORMAL,
            COPY,
            READY
        } status = Status::NORMAL;


        Throwable(const Throwable &original);

        Throwable(Throwable &&original) CORE_NOTHROW;

    public:
        /// Constructs a new throwable with the specified detail message.
        /// The cause is not initialized, and may subsequently be initialized by a call to @b initCause.
        /// The @b fillInStackTrace() method is called to initialize the stack trace data in the newly created throwable.
        /// @param message The detail message. The detail message is saved for later retrieval by the @b getMessage() method.
        CORE_EXPLICIT Throwable(const String &message);

        /// Constructs a new throwable with the specified detail message and cause.
        /// Note that the detail message associated with @c cause is <i>not</i> automatically incorporated in this throwable's detail message.
        /// @param message the detail message (which is saved for later retrieval by the @b getMessage() method).
        /// @param cause the cause (which is saved for later retrieval by the @b getCause() method).
        CORE_EXPLICIT Throwable(const String &message, const Throwable &cause);

        ~Throwable() override = default;

        /// Returns the detail message string of this throwable.
        /// @return the detail message string of this @c Throwable instance.
        virtual String getMessage() const;

        /// Creates a localized description of this throwable.
        /// Subclasses may override this method to produce a local-specific message.
        /// For subclasses that do not override this method, the default implementation returns the same result as @c getMessage().
        /// @return The localized description of this throwable.
        virtual String getLocalizedMessage() const;

        /// Returns the cause of this throwable or itself if the cause is nonexistent or unknown.
        /// (The cause is the throwable that caused this throwable to get thrown.)
        /// This implementation returns the cause that was supplied via one of the constructors requiring a @c Throwable, or that was set after creation with the @b initCause(Throwable) method.
        /// While it is typically unnecessary to override this method, a subclass can override it to return a cause set by some other means.
        /// This is appropriate for a "legacy chained throwable" that predates the addition of chained exceptions to @c Throwable.
        /// Note that it is <i>not</i> necessary to override any of the @c dumpStackTrace methods, all of which invoke the @c getCause method to determine the cause of a throwable.
        /// @return the cause of this throwable or itself if the cause is nonexistent or unknown.
        virtual const Throwable &getCause() const;

        /// Initializes the <i>cause</i> of this throwable to the specified value.
        /// (The cause is the throwable that caused this throwable to get thrown).
        /// This method can be called at most once.  It is generally called from within the constructor, or immediately after creating the throwable.
        /// If this throwable was created with @b Throwable(Throwable) or <b>Throwable(String, Throwable)</b>, this method cannot be called even once.
        /// An example of using this method on a legacy throwable type without other support for setting the cause is:
        /// @code
        ///     try {
        ///         lowLevelOperation();
        ///     } catch (const LowLevelException& lle) {
        ///         HighLevelException("??").initCause(lle).throw($ftrace()); // Legacy constructor
        ///     }
        /// @endcode
        /// @param cause the cause (which is saved for later retrieval by the @b getCause() method).
        /// @return a reference to this @c Throwable instance.
        /// @throws IllegalArgumentException if @c cause is this throwable.  (A throwable cannot be its own cause.)
        /// @throws IllegalStateException if this throwable was created with @b Throwable(Throwable) or <b>Throwable(String, Throwable)</b>, or this method has already been called on this throwable.
        Throwable &initCause(const Throwable &cause);

        /// Prints this throwable and its backtrace to the standard error stream.
        /// This method prints a stack trace for this @c Throwable object on the error output stream that is the value of the field @c Console::err.
        /// The first line of output contains the result of the @b toString() method for this object.
        /// The Remaining lines represent data previously recorded by the method @b fillInStackTrace().
        /// The format of this information depends on the implementation, but the following example may be regarded as typical:
        /// @code
        ///     core::io::FileNotFoundException: Sample.txt
        ///             at MyClass::recycleFile(MyClass.h:9)
        ///             at MyClass::checkExistence(MyClass.h:6)
        ///             at main(Main.cpp:3)
        /// @endcode
        /// This example was produced by running the program:
        /// @code
        ///     // MyClass.h
        ///     class MyClass {
        ///     public:
        ///         static void recycleFile(const File& f) {
        ///             checkExistence(a)
        ///             // ...
        ///         }
        ///         static void checkExistence(const File& f) {
        ///             if (!f.exists())
        ///                 FileNotFoundException(f.getName()).throws($ftrace());
        ///         }
        ///     };
        ///
        ///     // Main.cpp
        ///     int main() {
        ///         File f = File("Sample.txt");
        ///         MyClass::recycleFile(File("Sample.txt"))
        ///         return 0;
        ///     }
        /// @endcode
        /// The backtrace for a throwable with an initialized, non-null cause should generally include the backtrace for the cause.
        /// The format of this information depends on the implementation, but the following example may be regarded as typical:
        /// @code
        ///     HighLevelException: high level exception message
        ///             at MyClass::method1(MyClass.h:13)
        ///             at main(Main.cpp:13)
        ///     Caused by: MiddleLevelException: middle level exception message
        ///             at MyClass::method3(MyClass.h:13)
        ///             at MyClass::method2(MyClass.h:17)
        ///             at MyClass::method1(MyClass.h:23)
        ///             ... 1 more
        ///     Caused by: LowLevelException: low level exception message
        ///             at MyClass::method3(MyClass.h:21)
        ///             at MyClass::method4(MyClass.h:27)
        ///             at MyClass::method5(MyClass.h:30)
        ///             ... 3 more
        /// @endcode
        /// Note the presence of lines containing the characters @c "...".
        /// These lines indicate that the remainder of the stack trace for this exception matches the indicated number of frames from the bottom of the stack trace of the exception that was caused by this exception (the "enclosing" exception).
        /// This shorthand can greatly reduce the length of the output in the common case where a wrapped exception is thrown from the same method as the "causative exception" is caught.
        /// The above example was produced by running the program:
        /// @code
        ///     // MyClass.h
        ///     class MyClass {
        ///     public:
        ///         static void method1() {
        ///             try {
        ///                 method2();
        ///             } catch (const MiddleLevelException& mle) {
        ///                 HighLevelException("high level message"_S, mle).throws($ftrace());
        ///             }
        ///         }
        ///         static void method2() {
        ///             method3();
        ///         }
        ///         static void method3() {
        ///             try {
        ///                 method2();
        ///             } catch (const LowLevelException& lle) {
        ///                 MidLevelException("middle level message"_S, mle).throws($ftrace());
        ///             }
        ///         }
        ///         static void method4() {
        ///             method5();
        ///         }
        ///         static void method5() {
        ///             LowLevelException("low level message"_S).throws($ftrace());
        ///         }
        ///     };
        ///     // HighLevelException.h
        ///     class HighLevelException: public Exception {
        ///     public:
        ///         HighLevelException(const String& message): Exception(message) {}
        ///         HighLevelException(const String& message, const Throwable& cause): Exception(message, cause) {}
        ///     private:
        ///         void selfThrow() const override { throw *this; }
        ///     };
        ///     // MidLevelException.h
        ///     class MidLevelException: public Exception {
        ///     public:
        ///         MidLevelException(const String& message): Exception(message) {}
        ///         MidLevelException(const String& message, const Throwable& cause): Exception(message, cause) {}
        ///     private:
        ///         void selfThrow() const override { throw *this; }
        ///     };
        ///     // LowLevelException.h
        ///     class LowLevelException: public Exception {
        ///     public:
        ///         LowLevelException(const String& message): Exception(message) {}
        ///         LowLevelException(const String& message, const Throwable& cause): Exception(message, cause) {}
        ///     private:
        ///         void selfThrow() const override { throw *this; }
        ///     };
        ///     // Main.cpp
        ///     int main() {
        ///         try {
        ///             MyClass::method1();
        ///         } catch (const HighLevelException& hle) {
        ///             hle.dumpStackTrace();
        ///         }
        ///         return 0;
        ///     }
        /// @endcode
        virtual void dumpStackTrace() const;

        /// Provides programmatic access to the stack trace information printed by @b dumpStackTrace().
        /// Returns an array of stack trace elements, each representing one stack frame.
        /// The zeroth element of the array (assuming the array's length is non-zero) represents the top of the stack, which is the last method invocation in the sequence.
        /// Typically, this is the point at which this throwable was created and thrown.
        /// The last element of the array (assuming the array's length is non-zero) represents the bottom of the stack, which is the first method invocation in the sequence.
        ///
        /// @return an array of stack trace elements representing the stack trace pertaining to this throwable.
        Array<TraceInfo> getStackTrace() const;

        gboolean equals(const Object &other) const override;

        /// Return the hash code of this object.
        /// @return the hash code of this throwable instance
        gint hash() const override;

        /// Returns a short description of this throwable.
        /// The result is the concatenation of:
        /// - the @em name of the class of this object
        /// - ": " (a colon and a space)
        /// - the result of invoking this object's @b getLocalizedMessage method
        /// If @c getLocalizedMessage returns empty string, then just the class name is returned.
        /// @return a string representation of this throwable.
        String toString() const override;

        /// Thrown or rethrow this throwable at the specified execution point (if backtrace access failed).
        /// @param currentExecutionPoint the current execution point
        CORE_NORETURN void throws(const TraceInfo &currentExecutionPoint) const CORE_THROW;

        /// Thrown this throwable again with ignoring the current execution point.
        /// @throws IllegalStateException if this method is not called after one first call of @c throws method
        CORE_NORETURN void throws() const CORE_THROW;

        Throwable &clone() const override;

    protected:
        $alias(VH, misc::VarHandle);

    private:
        /// Thrown the perfect and temporary copy of this throwable.
        /// This method is important to preserve the chaining and safe naming of a throwable object.
        /// @note It recommended that all instance derived from throwable class implement this method because
        /// by default, C++ language does not guarantee that it can preserve instance.
        /// Example: (C++ method)
        /// @code
        ///     // MyClass.h
        ///     class MyClass {
        ///     public:
        ///         static void method1() {
        ///             throw LowLevelException("Low Level Message");
        ///         }
        ///         static void method2() {
        ///             try {
        ///                 method1();
        ///             } catch (const Exception& exception) {
        ///                 throw exception; // rethrowing
        ///             }
        ///         }
        ///     };
        ///     // Main.cpp
        ///     int main() {
        ///         try {
        ///             MyClass::method2();
        ///         } catch (const Throwable& th) {
        ///             CORE_ASSERT(Class<LowLevelException>::hasInstance(th));
        ///         }
        ///         return 0;
        ///     }
        ///     // Output
        ///     AssertionError: ...
        /// @endcode
        /// Example: (Solution)
        /// @code
        ///     // MyClass.h
        ///     class MyClass {
        ///     public:
        ///         static void method1() {
        ///             LowLevelException("Low Level Message").throws($ftrace());
        ///         }
        ///         static void method2() {
        ///             try {
        ///                 method1();
        ///             } catch (const Exception& exception) {
        ///                 exception.throws($ftrace()); // rethrowing
        ///             }
        ///         }
        ///     };
        ///     // Main.cpp
        ///     int main() {
        ///         try {
        ///             MyClass::method2();
        ///         } catch (const Throwable& th) {
        ///             CORE_ASSERT(Class<LowLevelException>::hasInstance(th));
        ///         }
        ///         return 0;
        ///     }
        ///     // Output
        ///     ...
        /// @endcode
        virtual void selfThrow() const;

        /// Return the stacktrace of this throwable on C-String.
        /// @note On certain compiler, this method is called by C++ standard exception class after throwing to dump stacktrace into standard error printstream.
        /// @return The stack trace of this throwable as C-String
        NativeMessage what() const CORE_NOTHROW $final;
    };
} // lang
// core

#endif // CORE_LANG_THROWABLE_H
