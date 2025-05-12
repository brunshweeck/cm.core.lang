//
// Created by brunshweeck on 10/05/25.
//

#ifndef CORE_LANG_CACHE_H
#define CORE_LANG_CACHE_H

#include <core/lang/Class.h>


namespace core::lang
{
    class Cache $final : public Object
    {
    public:
        enum EntryType
        {
            DEFAULT, SHARED, EXCLUSIVE, PRIVATE
        };

    private:
        struct Entry;
        $alias(CacheEntry, Class<Entry>::Pointer);

        struct Entry
        {
            CacheEntry next;
            EntryType type;
            glong metadata;
        };

        CacheEntry firstEntry = {};
        volatile gint state = 12345;
        volatile glong count = {};
        volatile glong minValidMetadata = {};
        volatile glong maxValidMetadata = {};

    public:
        Cache() = default;

        ~Cache() override;

        gboolean isEmpty();

        glong size();

        void clear();

        void store(EntryType type, glong metadata);

        gboolean exists(glong metadata);

        static EntryType getType(glong metadata);

        static glong getMetadata(const Object &object);

        static Object &getObject(glong metadata);

        Object &clone() const override;

    private:
        static CacheEntry newEntryFor(glong metadata);

        static Object &getEntry(CacheEntry entry);

        CacheEntry findEntryFor(const Object &object);

        void ensureValidMetadata(glong metadata);

        void lock();

        void unlock();
    };
} // lang
// core

#endif // CORE_LANG_CACHE_H
