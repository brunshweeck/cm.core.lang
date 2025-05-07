//
// Created by brunshweeck on 4/26/25.
//

#include "TraceInfo.h"

<<<<<<< HEAD
<<<<<<< HEAD
#include <meta/lang/spi/TraceInfoProvider.h>

#include "CloneNotSupportedException.h"
#include "IllegalArgumentException.h"

namespace core::lang { namespace
    {
        class Context $final : public TraceInfoProvider::Context
        {
            const String& moduleName;
            const String& moduleVersion;
            const String& declaringClass;
            const String& functionName;
            const String& fileName;
            gint lineNumber;

        public:
            Context(const String& moduleName, const String& moduleVersion,
                    const String& className, const String& functionName,
                    const String& fileName, gint lineNumber)
                : TraceInfoProvider::Context(!moduleName.isEmpty(), !moduleVersion.isEmpty(),
                                             !className.isEmpty(), !functionName.isEmpty(),
                                             !fileName.isEmpty(), lineNumber < -2),
                  moduleName(moduleName), moduleVersion(moduleVersion),
                  declaringClass(className), functionName(functionName),
                  fileName(fileName), lineNumber(lineNumber) {
            }

            const String& getModuleName() const override { return moduleName; }

            const String& getModuleVersion() const override { return moduleVersion; }

            const String& getClassName() const override { return declaringClass; }

            const String& getFunctionName() const override { return functionName; }

            const String& getFileName() const override { return fileName; }

            gint getLineNumber() const override { return lineNumber; }
        };
    }

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
        if (this == &other) return true;
        if (!Class<TraceInfo>::hasInstance(other)) return false;
        const TraceInfo& otherInfo = $cast(const TraceInfo&, other);
        return lineNumber == otherInfo.lineNumber &&
            moduleName.equals(moduleName) &&
            moduleVersion.equals(moduleVersion) &&
            declaringClass.equals(declaringClass) &&
            functionName.equals(functionName) &&
            fileName.equals(fileName);
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
        String output;
        if (!moduleName.isEmpty()) {
            output += moduleName;
            if (!moduleVersion.isEmpty())
                output += $toString(@ ) + moduleVersion;
        }
        if (!output.isEmpty())
            output += $toString(/);
        if (!declaringClass.isEmpty())
            output += declaringClass + $toString(::);
        output += functionName + u'(';
        if (isNativeFunction())
            output += u'#';
        else {
            if (!fileName.isEmpty())
                output += fileName;
            else
                output += u'#';
            if (lineNumber > 0) {
                output += u':';
                output += lineNumber;
            }
        }
        output += u')';
        return output;
    }

    TraceInfo const& TraceInfo::getInstance(const String& moduleName, const String& moduleVersion,
                                            const String& declaringClass, const String& functionName,
                                            const String& fileName, gint lineNumber) {
        if (functionName.isEmpty())
            IllegalArgumentException($toString(Empty function signature)).throws($ftrace());
        String declaringStruct = resolveName(declaringClass);
        if (declaringStruct.isEmpty() && !functionName.isEmpty())
            declaringStruct = resolveClassName(functionName);
        String function = resolveName(functionName);
        if (!declaringStruct.isEmpty())
            function = resolveFunctionName(declaringStruct, function);
        String library = moduleName;
        String version = moduleVersion;
        String location = fileName;
        gint position = checkLineNumber(lineNumber);


        static TraceInfoProvider provider;
        Context context = Context(library, version, declaringStruct, function, fileName, position);

        return provider.findOrCreateByContext(
            context,
            [](const TraceInfo& info, const TraceInfoProvider::Context& context) -> gboolean {
                return (!info.moduleName.isEmpty() || context.getModuleName().isEmpty()) &&
                    (!info.moduleVersion.isEmpty() || context.getModuleVersion().isEmpty()) &&
                    (!info.declaringClass.isEmpty() || context.getClassName().isEmpty()) &&
                    !info.functionName.isEmpty() &&
                    (!info.fileName.isEmpty() || context.getFileName().isEmpty()) &&
                    info.lineNumber >= -2;
            },
            [](const TraceInfoProvider::Context& context) -> TraceInfo& {
                return *new TraceInfo(
                    context.getModuleName(), context.getModuleVersion(),
                    context.getClassName(), context.getFunctionName(),
                    context.getFileName(), context.getLineNumber()
                );
            }
        );
    }

    TraceInfo& TraceInfo::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
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

    String TraceInfo::resolveName(const String& inputName) {
        checkName(inputName);
        gint index = 0;
        gboolean isOperator = false;
        String output;
        // 1- Remove all template arguments specifications
        for (gint n = inputName.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = inputName.indexOf('<', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += inputName.substring(last);
                break;
            }
            gint nextChar = (start + 1 < n) ? inputName.charAt(start + 1) : 0;
            gint nextChar2 = (start + 2 < n) ? inputName.charAt(start + 2) : 0;
            gint nextChar3 = (start + 3 < n) ? inputName.charAt(start + 2) : 0;
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
                k = inputName.lastIndexOf($toString(operator), start);
                if (start - k == 8) {
                    isOperator = true;
                    if (nextChar == '<' && nextChar2 == '=' || nextChar == '=' && nextChar2 == '>') {
                        output += inputName.substring(k, start + 2);
                        index = start + 2;
                    }
                    else if (nextChar == '<' || nextChar == '=') {
                        output += inputName.substring(k, start + 1);
                        index = start + 1;
                    }
                    else {
                        output += inputName.substring(k, start);
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
                nextChar = inputName.charAt(k2);
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
                k = inputName.indexOf($toString(lambda), start);
                gchar prevChar = (start > 0) ? inputName.charAt(start - 1) : 0;
                gchar prevChar2 = (start > 1) ? inputName.charAt(start - 2) : 0;
                nextChar = (start + 7 < n) ? inputName.charAt(start + 7) : 0;
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
            output += inputName.substring(last, start);
            index = k2;
        }

        String input = $cast(String&&, output);
        isOperator = false;
        index = 0;
        // 2- Remove all function arguments specifications
        for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = input.indexOf('(', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                output += input.substring(last, start);
        }

        // 4 - Normalize output name
        return normalizeName(output);
    }

    String TraceInfo::resolveClassName(const String& inputFunction) {
        checkName(inputFunction);
        gint index = 0;
        gboolean isOperator = false;
        String output;
        // 1- Remove all template arguments specifications
        for (gint n = inputFunction.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = inputFunction.indexOf('<', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += inputFunction.substring(last);
                break;
            }
            gint nextChar = (start + 1 < n) ? inputFunction.charAt(start + 1) : 0;
            gint nextChar2 = (start + 2 < n) ? inputFunction.charAt(start + 2) : 0;
            gint nextChar3 = (start + 3 < n) ? inputFunction.charAt(start + 2) : 0;
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
                k = inputFunction.lastIndexOf($toString(operator), start);
                if (start - k == 8) {
                    isOperator = true;
                    if (nextChar == '<' && nextChar2 == '=' || nextChar == '=' && nextChar2 == '>') {
                        output += inputFunction.substring(k, start + 2);
                        index = start + 2;
                    }
                    else if (nextChar == '<' || nextChar == '=') {
                        output += inputFunction.substring(k, start + 1);
                        index = start + 1;
                    }
                    else {
                        output += inputFunction.substring(k, start);
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
                nextChar = inputFunction.charAt(k2);
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
                k = inputFunction.indexOf($toString(lambda), start);
                gchar prevChar = (start > 0) ? inputFunction.charAt(start - 1) : 0;
                gchar prevChar2 = (start > 1) ? inputFunction.charAt(start - 2) : 0;
                nextChar = (start + 7 < n) ? inputFunction.charAt(start + 7) : 0;
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
            output += inputFunction.substring(last, start);
            index = k2;
        }

        gint indexes[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        gint next = -1;

        String input = $cast(String&&, output);
        isOperator = false;
        index = 0;
        // 2- Remove all function arguments specifications
        for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = input.indexOf('(', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                    indexes[++next % 8] = output.length() - 1;
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
            indexes[++next % 8] = output.length() - 1;
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
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                output += input.substring(last, start);
        }

        // 4 - Delete Function name and Preserve Class name only
        // myNameSpace::MyClass::myFunction(...)::<lambda(...)> -> myNameSpace::MyClass
        if (next >= 0) {
            gint index0 = indexes[next];
            gint index1 = indexes[(next + 7) % 8] + 1;
            gint index2 = indexes[(next + 6) % 8] + 1;
            if (index0 > 0 && index1 > 0 && index2 > 0 &&
                output.charAt(index0) == u'>' && output.charAt(index1) == u'<')
                output = output.substring(0, index2);
        }

        // 5 - Normalize output name
        return normalizeName(output);
    }

    String TraceInfo::resolveFunctionName(const String& inputClass, const String& inputFunction) {
        if (inputClass.isEmpty() || !inputFunction.startsWith(inputClass)) return inputFunction;
        return inputFunction.substring(inputClass.length());
    }

    String TraceInfo::normalizeName(const String& inputName) {
        String outputName;
        // Remove function decorators (attributes, return type, qualifiers, etc.)
        for (gint index0 = 0, n0 = inputName.length(), last0 = 0; index0 < n0; last0 = ++index0) {
            gint k0 = inputName.indexOf(u':', last0);
            if (k0 < last0) {
                if (!outputName.isEmpty())
                    outputName += $toString(::);
                outputName += inputName.substring(last0, k0);
                break;
            }
            index0 = k0 + 1;

            String input = inputName.substring(last0, k0);
            String output;
            if (input.isEmpty()) continue;

            gint index = 0;
            // 1 - Remove Qualifiers and Attributes
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                k = input.indexOf(' ', last);
                String part = (k < last) ? input.substring(last) : input.substring(last, k);
                gint m = part.length();
                index += m;
                gchar nextChar = (m < 1) ? 0 : part.charAt(0);
                gchar nextChar2 = (m < 2) ? 0 : part.charAt(1);
                switch (nextChar) {
                    case '&':
                        if (nextChar2 == '&' || nextChar2 == 0) continue;
                        break;
                    case 'c':
                        if (m == 5 && (part.equals($toString(const)) || part.equals($toString(class)))) continue;
                        if (m == 8 && part.equals($toString(constval))) continue;
                        if (m == 9 && part.equals($toString(constexpr))) continue;
                        break;
                    case 'e':
                        if (m == 4 && part.equals($toString(enum))) continue;
                    case 'n':
                        if (m == 7 && part.equals($toString(nothrow))) continue;
                        break;
                    case 's':
                        if (m == 6 && (part.equals($toString(static)) || part.equals($toString(struct)))) continue;
                        break;
                    case 't':
                        if (m == 5 && part.equals($toString(throw))) continue;
                        break;
                    case 'u':
                        if (m == 5 && part.equals($toString(union))) continue;
                        break;
                    case 'v':
                        if (m == 7 && part.equals($toString(virtual))) continue;
                        if (m == 8 && part.equals($toString(volatile))) continue;
                        break;
                    case '_':
                        if (m == 7 && part.equals($toString(__cdecl))) continue;
                        if (m == 9 && part.equals($toString(__stdcall))) continue;
                        if (m == 10 && part.equals($toString(__fastcall))) continue;
                        break;
                    default: break;
                }
                output += part + u' ';
            }

            // 2 - Remove Return Type
            // All full function signature start with return type: T myFunction -> myFunction
            index = output.indexOf(u' ');
            if (index > 0) {
                String tmp = output.substring(++index);
                output = $cast(String&&, (!tmp.isEmpty()) ? tmp: output);
            }
            input = $cast(String&&, output);
            index = 0;

            // 3 - Remove persistent Qualifiers (& and &&)
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                k = input.indexOf(u'&', last);
                if (k < last) k = n;
                output += input.substring(last, k);
                gchar nextChar = (n - k > 1) ? input.charAt(k + 1) : 0;
                index = (nextChar == '&') ? k + 1 : k;
            }

            if (output.isEmpty()) continue;
            if (!outputName.isEmpty())
                outputName += $toString(::);
            outputName += output;
        }

        return outputName;
    }

    gint TraceInfo::checkLineNumber(gint inputLine) {
        if (inputLine != -2 && inputLine < 1)
            IllegalArgumentException($toString(Invalid line number)).throws($ftrace());
        return inputLine;
    }
} // core::lang
=======
=======
#include <meta/lang/spi/TraceInfoProvider.h>

>>>>>>> 1dd40da (refactor(core-lang-19): unix adjustement)
#include "CloneNotSupportedException.h"
#include "IllegalArgumentException.h"

namespace core::lang { namespace
    {
        class Context $final : public TraceInfoProvider::Context
        {
            const String& moduleName;
            const String& moduleVersion;
            const String& declaringClass;
            const String& functionName;
            const String& fileName;
            gint lineNumber;

        public:
            Context(const String& moduleName, const String& moduleVersion,
                    const String& className, const String& functionName,
                    const String& fileName, gint lineNumber)
                : TraceInfoProvider::Context(!moduleName.isEmpty(), !moduleVersion.isEmpty(),
                                             !className.isEmpty(), !functionName.isEmpty(),
                                             !fileName.isEmpty(), lineNumber < -2),
                  moduleName(moduleName), moduleVersion(moduleVersion),
                  declaringClass(className), functionName(functionName),
                  fileName(fileName), lineNumber(lineNumber) {
            }

            const String& getModuleName() const override { return moduleName; }

            const String& getModuleVersion() const override { return moduleVersion; }

            const String& getClassName() const override { return declaringClass; }

            const String& getFunctionName() const override { return functionName; }

            const String& getFileName() const override { return fileName; }

            gint getLineNumber() const override { return lineNumber; }
        };
    }

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
        if (this == &other) return true;
        if (!Class<TraceInfo>::hasInstance(other)) return false;
        const TraceInfo& otherInfo = $cast(const TraceInfo&, other);
        return lineNumber == otherInfo.lineNumber &&
            moduleName.equals(moduleName) &&
            moduleVersion.equals(moduleVersion) &&
            declaringClass.equals(declaringClass) &&
            functionName.equals(functionName) &&
            fileName.equals(fileName);
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
        String output;
        if (!moduleName.isEmpty()) {
            output += moduleName;
            if (!moduleVersion.isEmpty())
                output += $toString(@ ) + moduleVersion;
        }
        if (!output.isEmpty())
            output += $toString(/);
        if (!declaringClass.isEmpty())
            output += declaringClass + $toString(::);
        output += functionName + u'(';
        if (isNativeFunction())
            output += u'#';
        else {
            if (!fileName.isEmpty())
                output += fileName;
            else
                output += u'#';
            if (lineNumber > 0) {
                output += u':';
                output += lineNumber;
            }
        }
        output += u')';
        return output;
    }

    TraceInfo const& TraceInfo::getInstance(const String& moduleName, const String& moduleVersion,
                                            const String& declaringClass, const String& functionName,
                                            const String& fileName, gint lineNumber) {
        if (functionName.isEmpty())
            IllegalArgumentException($toString(Empty function signature)).throws($ftrace());
        String declaringStruct = resolveName(declaringClass);
        if (declaringStruct.isEmpty() && !functionName.isEmpty())
            declaringStruct = resolveClassName(functionName);
        String function = resolveName(functionName);
        if (!declaringStruct.isEmpty())
            function = resolveFunctionName(declaringStruct, function);
        String library = moduleName;
        String version = moduleVersion;
        String location = fileName;
        gint position = checkLineNumber(lineNumber);


        static TraceInfoProvider provider;
        Context context = Context(library, version, declaringStruct, function, fileName, position);

        return provider.findOrCreateByContext(
            context,
            [](const TraceInfo& info, const TraceInfoProvider::Context& context) -> gboolean {
                return (!info.moduleName.isEmpty() || context.getModuleName().isEmpty()) &&
                    (!info.moduleVersion.isEmpty() || context.getModuleVersion().isEmpty()) &&
                    (!info.declaringClass.isEmpty() || context.getClassName().isEmpty()) &&
                    !info.functionName.isEmpty() &&
                    (!info.fileName.isEmpty() || context.getFileName().isEmpty()) &&
                    info.lineNumber >= -2;
            },
            [](const TraceInfoProvider::Context& context) -> TraceInfo& {
                return *new TraceInfo(
                    context.getModuleName(), context.getModuleVersion(),
                    context.getClassName(), context.getFunctionName(),
                    context.getFileName(), context.getLineNumber()
                );
            }
        );
    }

    TraceInfo& TraceInfo::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
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

    String TraceInfo::resolveName(const String& inputName) {
        checkName(inputName);
        gint index = 0;
        gboolean isOperator = false;
        String output;
        // 1- Remove all template arguments specifications
        for (gint n = inputName.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = inputName.indexOf('<', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += inputName.substring(last);
                break;
            }
            gint nextChar = (start + 1 < n) ? inputName.charAt(start + 1) : 0;
            gint nextChar2 = (start + 2 < n) ? inputName.charAt(start + 2) : 0;
            gint nextChar3 = (start + 3 < n) ? inputName.charAt(start + 2) : 0;
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
                k = inputName.lastIndexOf($toString(operator), start);
                if (start - k == 8) {
                    isOperator = true;
                    if (nextChar == '<' && nextChar2 == '=' || nextChar == '=' && nextChar2 == '>') {
                        output += inputName.substring(k, start + 2);
                        index = start + 2;
                    }
                    else if (nextChar == '<' || nextChar == '=') {
                        output += inputName.substring(k, start + 1);
                        index = start + 1;
                    }
                    else {
                        output += inputName.substring(k, start);
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
                nextChar = inputName.charAt(k2);
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
                k = inputName.indexOf($toString(lambda), start);
                gchar prevChar = (start > 0) ? inputName.charAt(start - 1) : 0;
                gchar prevChar2 = (start > 1) ? inputName.charAt(start - 2) : 0;
                nextChar = (start + 7 < n) ? inputName.charAt(start + 7) : 0;
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
            output += inputName.substring(last, start);
            index = k2;
        }

        String input = $cast(String&&, output);
        isOperator = false;
        index = 0;
        // 2- Remove all function arguments specifications
        for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = input.indexOf('(', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                output += input.substring(last, start);
        }

        // 4 - Normalize output name
        return normalizeName(output);
    }

    String TraceInfo::resolveClassName(const String& inputFunction) {
        checkName(inputFunction);
        gint index = 0;
        gboolean isOperator = false;
        String output;
        // 1- Remove all template arguments specifications
        for (gint n = inputFunction.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = inputFunction.indexOf('<', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += inputFunction.substring(last);
                break;
            }
            gint nextChar = (start + 1 < n) ? inputFunction.charAt(start + 1) : 0;
            gint nextChar2 = (start + 2 < n) ? inputFunction.charAt(start + 2) : 0;
            gint nextChar3 = (start + 3 < n) ? inputFunction.charAt(start + 2) : 0;
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
                k = inputFunction.lastIndexOf($toString(operator), start);
                if (start - k == 8) {
                    isOperator = true;
                    if (nextChar == '<' && nextChar2 == '=' || nextChar == '=' && nextChar2 == '>') {
                        output += inputFunction.substring(k, start + 2);
                        index = start + 2;
                    }
                    else if (nextChar == '<' || nextChar == '=') {
                        output += inputFunction.substring(k, start + 1);
                        index = start + 1;
                    }
                    else {
                        output += inputFunction.substring(k, start);
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
                nextChar = inputFunction.charAt(k2);
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
                k = inputFunction.indexOf($toString(lambda), start);
                gchar prevChar = (start > 0) ? inputFunction.charAt(start - 1) : 0;
                gchar prevChar2 = (start > 1) ? inputFunction.charAt(start - 2) : 0;
                nextChar = (start + 7 < n) ? inputFunction.charAt(start + 7) : 0;
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
            output += inputFunction.substring(last, start);
            index = k2;
        }

        gint indexes[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
        gint next = -1;

        String input = $cast(String&&, output);
        isOperator = false;
        index = 0;
        // 2- Remove all function arguments specifications
        for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
            gint start = input.indexOf('(', last);
            if (start < last) {
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                    indexes[++next % 8] = output.length() - 1;
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
            indexes[++next % 8] = output.length() - 1;
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
                if (!output.isEmpty())
                    output += $toString(::);
                output += input.substring(last);
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
                output += input.substring(last, start);
        }
<<<<<<< HEAD
    } // lang
} // core
>>>>>>> 3aa0f8c (???)
=======

        // 4 - Delete Function name and Preserve Class name only
        // myNameSpace::MyClass::myFunction(...)::<lambda(...)> -> myNameSpace::MyClass
        if (next >= 0) {
            gint index0 = indexes[next];
            gint index1 = indexes[(next + 7) % 8] + 1;
            gint index2 = indexes[(next + 6) % 8] + 1;
            if (index0 > 0 && index1 > 0 && index2 > 0 &&
                output.charAt(index0) == u'>' && output.charAt(index1) == u'<')
                output = output.substring(0, index2);
        }

        // 5 - Normalize output name
        return normalizeName(output);
    }

    String TraceInfo::resolveFunctionName(const String& inputClass, const String& inputFunction) {
        if (inputClass.isEmpty() || !inputFunction.startsWith(inputClass)) return inputFunction;
        return inputFunction.substring(inputClass.length());
    }

    String TraceInfo::normalizeName(const String& inputName) {
        String outputName;
        // Remove function decorators (attributes, return type, qualifiers, etc.)
        for (gint index0 = 0, n0 = inputName.length(), last0 = 0; index0 < n0; last0 = ++index0) {
            gint k0 = inputName.indexOf(u':', last0);
            if (k0 < last0) {
                if (!outputName.isEmpty())
                    outputName += $toString(::);
                outputName += inputName.substring(last0, k0);
                break;
            }
            index0 = k0 + 1;

            String input = inputName.substring(last0, k0);
            String output;
            if (input.isEmpty()) continue;

            gint index = 0;
            // 1 - Remove Qualifiers and Attributes
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                k = input.indexOf(' ', last);
                String part = (k < last) ? input.substring(last) : input.substring(last, k);
                gint m = part.length();
                index += m;
                gchar nextChar = (m < 1) ? 0 : part.charAt(0);
                gchar nextChar2 = (m < 2) ? 0 : part.charAt(1);
                switch (nextChar) {
                    case '&':
                        if (nextChar2 == '&' || nextChar2 == 0) continue;
                        break;
                    case 'c':
                        if (m == 5 && (part.equals($toString(const)) || part.equals($toString(class)))) continue;
                        if (m == 8 && part.equals($toString(constval))) continue;
                        if (m == 9 && part.equals($toString(constexpr))) continue;
                        break;
                    case 'e':
                        if (m == 4 && part.equals($toString(enum))) continue;
                    case 'n':
                        if (m == 7 && part.equals($toString(nothrow))) continue;
                        break;
                    case 's':
                        if (m == 6 && (part.equals($toString(static)) || part.equals($toString(struct)))) continue;
                        break;
                    case 't':
                        if (m == 5 && part.equals($toString(throw))) continue;
                        break;
                    case 'u':
                        if (m == 5 && part.equals($toString(union))) continue;
                        break;
                    case 'v':
                        if (m == 7 && part.equals($toString(virtual))) continue;
                        if (m == 8 && part.equals($toString(volatile))) continue;
                        break;
                    case '_':
                        if (m == 7 && part.equals($toString(__cdecl))) continue;
                        if (m == 9 && part.equals($toString(__stdcall))) continue;
                        if (m == 10 && part.equals($toString(__fastcall))) continue;
                        break;
                    default: break;
                }
                output += part + u' ';
            }

            // 2 - Remove Return Type
            // All full function signature start with return type: T myFunction -> myFunction
            index = output.indexOf(u' ');
            if (index > 0) {
                String tmp = output.substring(++index);
                output = $cast(String&&, (!tmp.isEmpty()) ? tmp: output);
            }
            input = $cast(String&&, output);
            index = 0;

            // 3 - Remove persistent Qualifiers (& and &&)
            for (gint n = input.length(), k = 0, last = 0; index < n; last = ++index) {
                k = input.indexOf(u'&', last);
                if (k < last) k = n;
                output += input.substring(last, k);
                gchar nextChar = (n - k > 1) ? input.charAt(k + 1) : 0;
                index = (nextChar == '&') ? k + 1 : k;
            }

            if (output.isEmpty()) continue;
            if (!outputName.isEmpty())
                outputName += $toString(::);
            outputName += output;
        }

        return outputName;
    }

    gint TraceInfo::checkLineNumber(gint inputLine) {
        if (inputLine != -2 && inputLine < 1)
            IllegalArgumentException($toString(Invalid line number)).throws($ftrace());
        return inputLine;
    }
} // core::lang
>>>>>>> 1dd40da (refactor(core-lang-19): unix adjustement)
