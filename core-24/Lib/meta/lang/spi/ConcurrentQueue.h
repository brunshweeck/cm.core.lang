//
// Created by brunshweeck on 06/05/25.
//

#ifndef CORE_LANG_CONCURRENTQUEUE_H
#define CORE_LANG_CONCURRENTQUEUE_H

#include <core/lang/Object.h>

#include "core/lang/Class.h"

namespace core::lang
{
    class ConcurrentQueue
    {
        struct ConcurrentNode;
        $alias(Node, Class<ConcurrentNode>::Pointer);
        $alias(Item, Class<Object>::Pointer);
        $alias(Comparator, gint(*)(const Object& a, const Object& b));

        struct ConcurrentNode
        {
            Node next, prev;
            Item item;
        };

        Node root = {};
        gboolean volatile isLocked = false;
        gint volatile count = 0;
        Comparator comparator = {};

    public:

    private:
        void lock();
        void unlock();
    };
}

#endif // CORE_LANG_CONCURRENTQUEUE_H
