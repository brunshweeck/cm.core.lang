//
// Created by brunshweeck on 4/26/25.
//

#include "TraceInfo.h"

#include "CloneNotSupportedException.h"
#include "IllegalArgumentException.h"

namespace core { namespace lang
    {
        TraceInfo::TraceInfo(const String& moduleName, const String& moduleVersion,
                             const String& declaringClass, const String& functionName,
                             const String& fileName, gint lineNumber) {
            TraceInfo::moduleName = moduleName;
            TraceInfo::moduleVersion = moduleVersion;
            TraceInfo::declaringClass = declaringClass;
            TraceInfo::functionName = functionName;
            TraceInfo::fileName = fileName;
            TraceInfo::lineNumber = lineNumber;
        }

        TraceInfo::TraceInfo(const String& declaringClass, const String& functionName,
                             const String& fileName, gint lineNumber) {
            TraceInfo::declaringClass = declaringClass;
            TraceInfo::functionName = functionName;
            TraceInfo::fileName = fileName;
            TraceInfo::lineNumber = lineNumber;
        }

        String TraceInfo::getModuleName() const { return moduleName; }

        String TraceInfo::getModuleVersion() const { return moduleVersion; }

        String TraceInfo::getDeclaringClass() const { return declaringClass; }

        String TraceInfo::getFunctionName() const { return functionName; }

        String TraceInfo::getFileName() const { return fileName; }

        gint TraceInfo::getLineNumber() const { return lineNumber; }

        gboolean TraceInfo::isNativeFunction() const { return lineNumber == -2; }

        gboolean TraceInfo::equals(const Object& other) const {
            // todo:
            return Object::equals(other);
        }

        gint TraceInfo::hash() const {
            return moduleName.hash() * 31 +
                moduleVersion.hash() * 31 +
                declaringClass.hash() * 31 +
                functionName.hash() * 31 +
                fileName.hash() * 31 +
                lineNumber;
        }

        String TraceInfo::toString() const {
            // todo: Implementer cette methode en utilisant des chaine de caractere extensible (XString)
            return Object::toString();
        }

        TraceInfo const& TraceInfo::getInstance(const String& moduleName, const String& moduleVersion,
                                                const String& declaringClass, const String& functionName,
                                                const String& fileName, gint lineNumber) {
            checkModuleName(moduleName);
            checkModuleVersion(moduleVersion);
            resolveName(declaringClass);
            checkFunctionName(functionName);
            checkLineNumber(lineNumber);

            String module, version, clazz, function, file;
            gint line = lineNumber;
            file = fileName;
            module = moduleName;
            version = moduleVersion;
            if (!declaringClass.isEmpty()) {
            }

            return *new TraceInfo(module, version, clazz, function, file, line);
        }

        TraceInfo& TraceInfo::clone() const {
            CloneNotSupportedException($toString()).throws($ftrace());
        }

        void TraceInfo::checkModuleName(const String& moduleName) {
        }

        void TraceInfo::checkModuleVersion(const String& moduleVersion) {
        }

        void TraceInfo::checkName(const String& className) {
            gint index = 0;
            gint n = className.length();
            gchar ch = -1;
            gint S = 0; // Separator :
            gint L = 0; // Letter a-z or A-Z or $ or _
            gint P = 0; // Parenthesis (or)
            gint SS = 0; // Subscript symbols [or]
            for (; index < n; ++index) {
                if ((ch = className.charAt(index)) > 0x7f)
                    IllegalArgumentException($toString(Invalid name)).throws($ftrace());
                if (ch == '(') ++P;
                else if (ch == ')') {
                    --P;
                    if (P < 0)
                        IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                }
                else if (ch == ':') {
                    ++S;
                    if (S > 2)
                        IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                    if (S == 2) {
                        S = 0;
                        L = 0;
                    }
                }
                else if (ch == '[') {
                    ++SS;
                    if (L == 0 || S > 0)
                        IllegalArgumentException($toString(Invalid name)).throws($ftrace());
                }
                else if (ch == ']') {
                    --SS;
                    if (SS < 0)
                        IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                }
                else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && ch != '$' && ch != '_') {
                    L = 1;
                    if (S < 2)
                        IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                }
                else if (ch >= 48 && ch <= 57) {
                    if (L == 0)
                        IllegalArgumentException($toString(Invalid name)).throws($ftrace());
                }
                else {
                    switch (ch) {
                        case '+': // For operators +, ++, +=
                        case '-': // For operators -, --, -=, ->
                        case '*': // For operators *, *=, .*
                        case '/': // For operators /, /=
                        case '%': // For operators %, %=
                        case '>': // For operators >, >>, >=, >>=, <=>, and <lambda#...>
                        case '=': // For operators =, ==, +=, -=, *=, /=, %=, &=, |=, <<=, >>=, <=>, !=
                        case '.': // For operators .*
                        case '&': // For operators &, &&, &=
                        case '|': // For operators |, ||, |=
                        case '^': // For operators ^, ^=
                        case '!': // For operators !, !=
                        case '#': // For operators <lambda#...>
                            if (L != 0)
                                IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                        case '<': // For operators <, <<, <=, <<=, <=>, and <lambda#...>
                        case '~': // For operators ~ and Dtor
                            if (S < 2)
                                IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                            break;
                        default:
                            IllegalArgumentException($toString(Invalid name)).throws($ftrace());
                    }
                }
            }
            if (S != 0 || P != 0 || SS != 0)
                IllegalArgumentException($toString(Malformed name)).throws($ftrace());
        }

        String TraceInfo::resolveName(const String& className) {
            checkName(className);
            gint index = 0;
            gboolean isOperator = false;
            String output;
            // 1- Remove all template arguments specifications
            for (gint n = className.length(), k = 0, last = 0; index < n; last = ++index) {
                gint start = className.indexOf('<', last);
                if (start < last) {
                    if (output.isEmpty() && index > 0)
                        output += $toString(::);
                    output += className.substring(last);
                    break;
                }
                gint nextChar = (start + 1 < n) ? className.charAt(start + 1) : 0;
                gint nextChar2 = (start + 2 < n) ? className.charAt(start + 2) : 0;
                gint nextChar3 = (start + 3 < n) ? className.charAt(start + 2) : 0;
                // try Resolve operator < or << or <<=, <=, <=>
                // Pattern: ^operator\<(=(\>?)|\<(=?)\)$
                if (!isOperator && (
                    // operator<, operator<(...), operator<::...
                    nextChar == '(' || nextChar == 0 || nextChar == ':' ||
                    // operator<<, operator<<(...), operator<<::...
                    nextChar == '<' && (nextChar2 == 0 || nextChar2 == '(' || nextChar2 == ':') ||
                    // operator<=, operator<=(...), operator<=::...
                    nextChar == '=' && (nextChar2 == 0 || nextChar2 == '(' || nextChar2 == ':') ||
                    // operator<<=, operator<<=(...), operator<<=::...
                    nextChar == '<' && nextChar2 == '=' && (nextChar3 == 0 || nextChar3 == '(' || nextChar3 == ':') ||
                    // operator<=>, operator<=>(...), operator<=>::...
                    nextChar == '=' && nextChar2 == '>' && (nextChar3 == 0 || nextChar3 == '(' || nextChar3 == ':')
                )) {
                    k = className.lastIndexOf($toString(operator), start);
                    if (start - k == 8) {
                        isOperator = true;
                        if (nextChar == '<' && nextChar2 == '=' || nextChar == '=' && nextChar2 == '>') {
                            output += className.substring(k, start + 2);
                            index = start + 2;
                        }
                        else if (nextChar == '<' || nextChar == '=') {
                            output += className.substring(k, start + 1);
                            index = start + 1;
                        }
                        else {
                            output += className.substring(k, start);
                            index = start;
                        }
                        continue;
                    }
                }

                // Find closing template argument specifier or closing lambda signature
                isOperator = false;
                gint cnt = 1;
                gint k2 = 0;
                for (k2 = start + 1; k2 < n; ++k2) {
                    nextChar = className.charAt(k2);
                    if (nextChar == '<') ++cnt;
                    else if (nextChar == '>') {
                        --cnt;
                        if (cnt == 0) break;
                    }
                }
                if (cnt > 0 || k2 == n)
                    IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                if (n - start > 6) {
                    // try Resolve lambda signature <lambda(...)>, or ...::<lambda(...)> or ...::<lambda#?(...)>
                    // Pattern: ^\<lambda(#\d+)?\(.*\)(.*)\>$
                    k = className.indexOf($toString(lambda), start);
                    gchar prevChar = (start > 0) ? className.charAt(start - 1) : 0;
                    gchar prevChar2 = (start > 1) ? className.charAt(start - 2) : 0;
                    nextChar = (start + 7 < n) ? className.charAt(start + 7) : 0;
                    if (k - start == 1 &&
                        prevChar == prevChar2 && (prevChar == 0 || prevChar == ':') &&
                        (nextChar == '(' || nextChar == '#')) {
                        if (!output.isEmpty())
                            output += $toString(::<lambda(...)>);
                        else
                            output += $toString(<lambda(...)>);
                        index = 2;
                        continue;
                    }
                }
                if (output.isEmpty())
                    output += $toString(::);
                output += className.substring(last, start);
                index = k2;
            }

            String input = $cast(String&&, output);
            isOperator = false;
            index = 0;
            // 2- Remove all function arguments specifications
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                gint start = input.indexOf('(', last);
                if (start < last) {
                    if (output.isEmpty() && index > 0)
                        output += $toString(::);
                    output += className.substring(last);
                    break;
                }
                gint nextChar = (start + 1 < n) ? input.charAt(start + 1) : 0;
                gint nextChar2 = (start + 2 < n) ? input.charAt(start + 2) : 0;
                // try Resolve operator ()
                // Pattern: ^operator\(\)$
                if (!isOperator &&
                    // operator(), operator()(...), operator()::...
                    nextChar == ')' && (nextChar2 == 0 || nextChar2 == '(' || nextChar2 == ':')) {
                    k = input.lastIndexOf($toString(operator), start);
                    if (start - k == 8) {
                        isOperator = true;
                        output += input.substring(k, start + 1);
                        index = start + 1;
                        continue;
                    }
                }

                // Find closing function argument specifier
                isOperator = false;
                gint cnt = 1;
                gint k2 = 0;
                for (k2 = start + 1; k2 < n; ++k2) {
                    nextChar = input.charAt(k2);
                    if (nextChar == '(') ++cnt;
                    else if (nextChar == ')') {
                        --cnt;
                        if (cnt == 0) break;
                    }
                }
                if (cnt > 0 || k2 == n)
                    IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                if (output.isEmpty())
                    output += $toString(::);
                output += input.substring(last, start);
                index = k2;
            }

            input = $cast(String&&, output);
            isOperator = false;
            index = 0;
            // 3- Remove Cxx-ABI deduction template arguments type
            // Pattern [with ...]
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                gint start = input.indexOf('[', last);
                if (start < last) {
                    if (output.isEmpty() && index > 0)
                        output += $toString(::);
                    output += className.substring(last);
                    break;
                }
                gint nextChar = (start + 1 < n) ? input.charAt(start + 1) : 0;
                gint nextChar2 = (start + 2 < n) ? input.charAt(start + 2) : 0;
                // try Resolve operator[]
                // Pattern: ^operator\[\]$
                if (!isOperator &&
                    // operator[], operator[](...), operator[]::...
                    nextChar == ']' && (nextChar2 == 0 || nextChar2 == '(' || nextChar2 == ':')) {
                    k = input.lastIndexOf($toString(operator), start);
                    if (start - k == 8) {
                        isOperator = true;
                        output += input.substring(k, start + 1);
                        index = start + 1;
                        continue;
                    }
                }

                // Find closing function argument specifier
                isOperator = false;
                gint cnt = 1;
                gint k2 = 0;
                for (k2 = start + 1; k2 < n; ++k2) {
                    nextChar = input.charAt(k2);
                    if (nextChar == '[') ++cnt;
                    else if (nextChar == ']') {
                        --cnt;
                        if (cnt == 0) break;
                    }
                }
                if (cnt > 0 || k2 == n)
                    IllegalArgumentException($toString(Malformed name)).throws($ftrace());
                if (k2 == n - 1 && input.startsWith($toString(with), start + 1))
                    output += className.substring(last, start);
            }
        }

        void TraceInfo::checkFunctionName(const String& functionName) {
        }

        void TraceInfo::checkLineNumber(gint lineNumber) {
            if (lineNumber != -2 && lineNumber < 1)
                IllegalArgumentException($toString(Invalid line number)).throws($ftrace());
        }
    } // lang
} // core
