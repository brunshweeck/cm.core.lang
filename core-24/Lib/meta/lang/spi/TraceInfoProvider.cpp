//
// Created by brunshweeck on 06/05/25.
//

#include "TraceInfoProvider.h"

#include "core/lang/Null.h"

namespace core::lang
{
    TraceInfoProvider::Context::Context(gboolean moduleName, gboolean moduleVersion,
                                        gboolean className, gboolean functionName,
                                        gboolean fileName, gboolean lineNumber):
        MODULE_NAME(moduleName),
        MODULE_VERSION(moduleVersion),
        CLASS_NAME(className),
        FUNCTION_NAME(functionName),
        FILE_NAME(fileName),
        LINE_NUMBER(lineNumber) {
    }

    gboolean TraceInfoProvider::Context::useModuleName() const { return MODULE_NAME; }

    gboolean TraceInfoProvider::Context::useModuleVersion() const { return MODULE_VERSION; }

    gboolean TraceInfoProvider::Context::useClassName() const { return CLASS_NAME; }

    gboolean TraceInfoProvider::Context::useFunctionName() const { return FUNCTION_NAME; }

    gboolean TraceInfoProvider::Context::useFileName() const { return FILE_NAME; }

    gboolean TraceInfoProvider::Context::useLineNumber() const { return LINE_NUMBER; }

    const Object& TraceInfoProvider::findByContext(const Context& context, Selector selector) {
        lock();
        // 1 - Find First Node
        Node node = root;
        while (node && node->left) node = node->left;
        // 2 - Run on Each Entry to verify context
        while (node) {
            Info info = node->info;
            node = successor(node);
            if (!info) continue;
            if (context.useModuleName() && !context.getModuleName().equals(info->getModuleName())) continue;
            if (context.useModuleVersion() && !context.getModuleVersion().equals(info->getModuleVersion())) continue;
            if (context.useClassName() && !context.getClassName().equals(info->getDeclaringClass())) continue;
            if (context.useFunctionName() && !context.getFunctionName().equals(info->getFunctionName())) continue;
            if (context.useFileName() && !context.getFileName().equals(info->getFileName())) continue;
            if (context.useLineNumber() && context.getLineNumber() != info->getLineNumber()) continue;
            if (selector(*info)) break;
        }
        unlock();
        return node && node->info ? *node->info : null;
    }

    const TraceInfo& TraceInfoProvider::findOrCreateByContext(const Context& context, Selector selector,
                                                              Creator creator) {
        const Object& trace = findByContext(context, selector);
        if (trace != null) return $cast(const TraceInfo&, trace);
        // Create new Instance
        lock();
        Node node = root;
        Node newNode = new Entry();
        TraceInfo& newInfo = creator(context);
        {
            newNode->left = newNode->right = null;
            newNode->info = &newInfo;
        }
        if (!node)
            root = newNode;
        else
            while (node) {
                if (node->info) {
                    gint cmp = newInfo.getModuleName().compareTo(node->info->getModuleName());
                    if (cmp == 0)
                        cmp = newInfo.getModuleVersion().compareTo(node->info->getModuleVersion());
                    if (cmp == 0)
                        cmp = newInfo.getDeclaringClass().compareTo(node->info->getDeclaringClass());
                    if (cmp == 0)
                        cmp = newInfo.getFunctionName().compareTo(node->info->getFunctionName());
                    if (cmp == 0)
                        cmp = newInfo.getFileName().compareTo(node->info->getFileName());
                    if (cmp == 0)
                        cmp = newInfo.getLineNumber() - node->info->getLineNumber();
                    if (cmp == 0) {
                        delete newNode;
                        delete &newInfo;
                        return *node->info;
                    }
                    if (cmp < 0) {
                        if (node->left)
                            node = node->left;
                        else {
                            node->left = newNode;
                            break;
                        }
                    }
                    else {
                        if (node->right)
                            node = node->right;
                        else {
                            node->right = newNode;
                            break;
                        }
                    }
                }
                else {
                    if (node->left)
                        node = node->left;
                    else {
                        delete newNode;
                        node->info = &newInfo;
                        break;
                    }
                }
            }
        unlock();
        return newInfo;
    }

    void TraceInfoProvider::lock() {
        gboolean LOCKED = true;
        gboolean UNLOCKED = false;
        // todo: Using specific system api wrapper corresponding to this calling
        while (!__atomic_compare_exchange_n(&isLocked, &UNLOCKED, LOCKED, true, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE))
            CORE_UNLIKELY(LOCKED);
    }

    void TraceInfoProvider::unlock() {
        gboolean LOCKED = true;
        gboolean UNLOCKED = false;
        // todo: Using specific system api wrapper corresponding to this calling
        while (!__atomic_compare_exchange_n(&isLocked, &LOCKED, UNLOCKED, true, __ATOMIC_RELEASE, __ATOMIC_RELAXED))
            CORE_UNLIKELY(UNLOCKED);
    }

    TraceInfoProvider::Node TraceInfoProvider::successor(Node node) {
        if (!node) return node;
    }
} // core
