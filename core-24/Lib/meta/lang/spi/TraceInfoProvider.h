//
// Created by brunshweeck on 06/05/25.
//

#ifndef CORE_LANG_TRACEINFOPROVIDER_H
#define CORE_LANG_TRACEINFOPROVIDER_H

#include <core/lang/Class.h>
#include <core/lang/TraceInfo.h>

namespace core::lang
{
    class TraceInfoProvider
    {
        struct Entry;
        struct Context;
        $alias(Node, Class<Entry>::Pointer);
        $alias(Info, Class<TraceInfo>::Pointer);
        $alias(Selector, gboolean(*)(const TraceInfo& trace, const Context& context));
        $alias(Creator, TraceInfo&(*)(const Context& context));

        struct Entry
        {
            Node parent = {};
            Node left = {};
            Node right = {};
            Info info = {};
        };

        Node root = {};
        gint volatile isLocked = false;
        gint volatile count = 0;

    public:
        TraceInfoProvider() = default;

        const Object &findByContext(const Context &context, Selector selector);

        const TraceInfo &findOrCreateByContext(const Context &context, Selector selector, Creator creator);

    private:
        void lock();

        void unlock();

        static Node successor(Node node);

        struct Context
        {
            gboolean MODULE_NAME = false;
            gboolean MODULE_VERSION = false;
            gboolean CLASS_NAME = false;
            gboolean FUNCTION_NAME = false;
            gboolean FILE_NAME = false;
            gboolean LINE_NUMBER = false;

        protected:
            CORE_EXPLICIT Context(gboolean moduleName, gboolean moduleVersion,
                                  gboolean className, gboolean functionName,
                                  gboolean fileName, gboolean lineNumber);

        public:
            virtual ~Context() = default;

            virtual const String &getModuleName() const = 0;

            virtual const String &getModuleVersion() const = 0;

            virtual const String &getClassName() const = 0;

            virtual const String &getFunctionName() const = 0;

            virtual const String &getFileName() const = 0;

            virtual gint getLineNumber() const = 0;

            gboolean useModuleName() const;

            gboolean useModuleVersion() const;

            gboolean useClassName() const;

            gboolean useFunctionName() const;

            gboolean useFileName() const;

            gboolean useLineNumber() const;
        };

        friend TraceInfo;
    };
} // core

#endif // CORE_LANG_TRACEINFOPROVIDER_H
