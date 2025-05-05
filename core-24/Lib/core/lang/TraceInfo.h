//
// Created by brunshweeck on 4/26/25.
//

#ifndef CORE_LANG_TRACE_H
#define CORE_LANG_TRACE_H

#include "String.h"

namespace core { namespace lang
    {
        /// The class @c TraceInfo represent the execution of the current program.
        /// Is used by class @c Throwable to view stack trace of program execution.
        /// @see core.lang::Throwable
        class TraceInfo $final : public Object
        {
            String moduleName;
            String moduleVersion;
            String declaringClass;
            String functionName;
            String fileName;
            gint lineNumber;

            /// Creates a new trace info representing the specified execution point.
            /// @param moduleName the module name if the class containing the execution point represented by the trace is in a named module, otherwise @c "".
            /// @param moduleVersion the module version if the class containing the execution point represented by the trace is in a named module that has a version; otherwise @c "".
            /// @param declaringClass the fully qualified name of the class containing the execution point represented by the trace (namespace and classname).
            /// @param functionName the name of the function containing the execution point represented by the trace.
            /// @param fileName the name of the file containing the execution point represented by the trace, or @c "" if this information is unavailable.
            /// @param lineNumber The line number of the source line containing the execution point represented by this trace, or a negative number if this information is unavailable.
            ///                                     A value of -2 indicates that the method containing the execution point is a C++ builtin or native function.
            CORE_EXPLICIT TraceInfo(const String& moduleName, const String& moduleVersion,
                                    const String& declaringClass, const String& functionName,
                                    const String& fileName, gint lineNumber);

            /// Creates a new trace info representing the specified execution point.
            /// @param declaringClass the fully qualified name of the class containing the execution point represented by the trace (namespace and classname).
            /// @param functionName the name of the function containing the execution point represented by the trace.
            /// @param fileName the name of the file containing the execution point represented by the trace, or @c "" if this information is unavailable.
            /// @param lineNumber The line number of the source line containing the execution point represented by this trace, or a negative number if this information is unavailable.
            ///                                     A value of -2 indicates that the method containing the execution point is a C++ builtin or native function.
            /// @note
            ///     - If the @c declaringClass argument is empty string, is will be deducted automatically from @c functionName argument.
            ///     - The @c moduleName argument can be retrieved with @c CORE_MODULE_NAME macro
            ///     - The @c moduleVersion argument can be retrieved with @c CORE_MODULE_VERSION macro
            ///     - The @c fileName argument can be retrieved with @c CORE_FILE, @c CORE_FILENAME, @c $file macro
            ///     - The @c functionName argument can be retrieved with @c CORE_FUNCTION, @c CORE_FUNCTION_SIGNATURE, @c $func, or @c $function macro
            ///     - The @c lineNumber argument can be retrieved with @c CORE_LINE, or @c $line macro
            CORE_EXPLICIT TraceInfo(const String& declaringClass, const String& functionName,
                                    const String& fileName, gint lineNumber);

        public:
            ~TraceInfo() override = default;

            CORE_SET_AS_NON_COPYABLE_CLASS(TraceInfo)

            /// Returns the module name of the module containing the execution point represented by this trace.
            /// @return  the name of the @c module containing the execution point represented by this trace info; empty string if the module name is not available.
            String getModuleName() const;

            /// Returns the module version of the module containing the execution point represented by this trace.
            /// @return  the version of the @c module containing the execution point represented by this trace info; empty string if the module version is not available.
            String getModuleVersion() const;

            /// Returns the fully qualified name of the class containing the execution point represented by this trace.
            /// @return the fully qualified name of the @c class containing the execution point represented by this trace info.
            String getDeclaringClass() const;

            /// Returns the name of the function containing the execution point represented by this trace.
            /// @return the name of the function containing the execution point represented by this trace info.
            String getFunctionName() const;

            /// Returns the name of the source file containing the execution point represented by this trace.
            /// Generally, this corresponds o the @a SourceFile attribute of the relevant @c class file.
            /// In some systems, the name may refer to some source code unit other than a file, such as an entry in source repository.
            /// @return the name of the file containing the execution point represented by this trace info, or @c "" if this information is unavailable.
            String getFileName() const;

            /// Returns the line number of the source line containing the execution point represented by this trace.
            /// Generally, this is derived from the @c LineNumberTable attribute of the relevant @c class file.
            /// @return the line number of the source line containing the execution point represented by this trace info, or a negative number if this information is unavailable.
            gint getLineNumber() const;

            /// Returns true if the method containing the execution point represented by this trace info is a native method.
            /// @return @c true if the method containing the execution point represented by this trace info is a native method.
            gboolean isNativeFunction() const;

            /// Returns true if the specified object is another @c TraceInfo instance representing the same execution point as this instance.
            /// Two trace info @c a and @c b are equal if and only if:
            /// @code
            ///     a.getModuleName().equals(b.getModuleName()) &&
            ///     a.getModuleVersion().equals(b.getModuleVersion()) &&
            ///     a.getDeclaringClass().equals(b.getDeclaringClass()) &&
            ///     a.getFunctionName().equals(b.getFunctionName()) &&
            ///     a.getFileName().equals(b.getFileName()) &&
            ///     a.getLineNumber() == b.getLineNumber()
            /// @endcode
            /// @param other the object to be compared with this trace info.
            /// @return @c true if the specified object is another @c TraceInfo instance representing the same execution point as this instance.
            gboolean equals(const Object& other) const override;

            /// Returns a hash code value for this trace.
            /// @return a hash code value for this object.
            gint hash() const override;

            /// Returns a string representation of this trace info.
            /// @note The format of this string depends on the implementation, but the following examples may be regarded as typical:
            ///     - @c "myLib@2.4/cm::foo::Main.run(Main.cpp:57)": The class of the execution point is defined in @c myLib module;
            ///     - @c "myLib@2.4/cm::foo::Main.run(Main.cpp)": The line number is unavailable;
            ///     - @c "myLib@2.4/cm::foo::Main.run(#:57)": Neither the file name nor the line number is available;
            ///     - @c "myLib@2.4/cm::foo::Main.run(#)": The method containing the execution point is a native method;
            ///     - @c "cm::foo::Main.run(Main.cpp:57)": The class of the execution point is defined in the unnamed module;
            ///
            /// The first example shows a trace info consisting of three elements, each separated by @c "/", followed by the source file name and the line number of the source line containing the execution point.
            /// - The first element @c "myLib@2.4" is the module name and version.
            /// - The second element is the method containing the execution point;
            /// @return the string representation of this trace info.
            String toString() const override;

            /// Get an instance trace info representing the specified execution point.
            /// @param moduleName the module name if the class containing the execution point represented by the trace is in a named module, otherwise @c "".
            /// @param moduleVersion the module version if the class containing the execution point represented by the trace is in a named module that has a version; otherwise @c "".
            /// @param declaringClass the fully qualified name of the class containing the execution point represented by the trace (namespace and classname).
            /// @param functionName the name of the function containing the execution point represented by the trace.
            /// @param fileName the name of the file containing the execution point represented by the trace, or @c "" if this information is unavailable.
            /// @param lineNumber The line number of the source line containing the execution point represented by this trace, or a negative number if this information is unavailable.
            ///                                     A value of -2 indicates that the method containing the execution point is a C++ builtin or native function.
            /// @note
            ///     - If the @c declaringClass argument is empty string, is will be deducted automatically from @c functionName argument.
            ///     - The @c moduleName argument can be retrieved with @c CORE_MODULE_NAME macro
            ///     - The @c moduleVersion argument can be retrieved with @c CORE_MODULE_VERSION macro
            ///     - The @c fileName argument can be retrieved with @c CORE_FILE, @c CORE_FILENAME, @c $file macro
            ///     - The @c functionName argument can be retrieved with @c CORE_FUNCTION, @c CORE_FUNCTION_SIGNATURE, @c $func, or @c $function macro
            ///     - The @c lineNumber argument can be retrieved with @c CORE_LINE, or @c $line macro
            /// @return The instance of trace info corresponding to given execution point.
            static TraceInfo const& getInstance(const String& moduleName, const String& moduleVersion,
                                                const String& declaringClass, const String& functionName,
                                                const String& fileName, gint lineNumber);

            TraceInfo& clone() const override;

        private:
            static void checkModuleName(const String& moduleName);
            static void checkModuleVersion(const String& moduleVersion);
            static void checkName(const String& className);
            static String resolveName(const String& className);
            static void checkFunctionName(const String& functionName);
            static void checkLineNumber(gint lineNumber);
        };
    } // lang
} // core


#endif // CORE_LANG_TRACE_H
