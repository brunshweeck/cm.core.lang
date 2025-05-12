//
// Created by brunshweeck on 10/05/25.
//

#include "Cache.h"

#include "Intrinsic.h"
#include "Memory.h"
#include <core/lang/CloneNotSupportedException.h>
#include <core/lang/Null.h>

namespace core::lang
{
    Cache::~Cache() {
        clear();
    }

    gboolean Cache::isEmpty() {
        return size() == 0;
    }

    glong Cache::size() {
        return Intrinsic::loadLong((glong) &count, Intrinsic::RELAXED);
    }

    void Cache::clear() {
        lock();
        start:
        CacheEntry entry = firstEntry;
        firstEntry = null;
        count = 0;
        maxValidMetadata = 0;
        minValidMetadata = 0;
        unlock();
        while (entry) {
            CacheEntry tmp = entry;
            entry = tmp->next;
            glong metadata = tmp->metadata;
            tmp->metadata = 0;
            tmp->next = null;
            tmp->type = DEFAULT;
            Memory::deallocate((glong) tmp);
            Object &object = getObject(metadata);
            delete &object;
        }
        lock();
        entry = firstEntry;
        if (entry) goto start;
    }

    void Cache::store(EntryType type, glong metadata) {
        CacheEntry entry = newEntryFor(metadata);
        lock();
        entry->next = firstEntry;
        firstEntry = entry;
        Intrinsic::loadAndAddLong((glong) &count, 1, Intrinsic::RELAXED);
        unlock();
    }

    gboolean Cache::exists(glong metadata) {
        return findEntryFor(getObject(metadata)) != null;
    }

    Cache::EntryType Cache::getType(glong metadata) {
        Object &object = getObject(metadata);
        if (Class<Throwable>::hasInstance(object)) return EXCLUSIVE;
        return DEFAULT;
    }

    glong Cache::getMetadata(const Object &object) {
        if (object == null) return 0L;
        return (glong) &object;
    }

    Object &Cache::getObject(glong metadata) {
        if (metadata == 0L) return null;
        return *(Object *) metadata;
    }

    Object & Cache::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
    }

    Cache::CacheEntry Cache::newEntryFor(glong metadata) {
        if (metadata == 0L) return null;
        CacheEntry entry = (CacheEntry) Memory::allocate(Class<Entry>::SIZE);
        if (entry == null) return null;
        entry->type = getType(metadata);
        entry->metadata = metadata;
        entry->next = null;
        return entry;
    }

    Object &Cache::getEntry(CacheEntry entry) {
        if (entry == null) return null;
        return getObject(entry->metadata);
    }

    Cache::CacheEntry Cache::findEntryFor(const Object &object) {
        glong metadata = getMetadata(object);
        lock();
        CacheEntry entry = firstEntry;
        while (entry) {
            if (metadata == entry->metadata) break;
            entry = entry->next;
        }
        unlock();
        return entry;
    }

    void Cache::ensureValidMetadata(glong metadata) {
        lock();
        if (maxValidMetadata >= 0) {
            if (metadata > maxValidMetadata)
                Intrinsic::storeLong((glong) &maxValidMetadata, metadata, Intrinsic::RELAXED);
        }
        else {
            if (metadata < maxValidMetadata)
                Intrinsic::storeLong((glong) &maxValidMetadata, metadata, Intrinsic::RELAXED);
        }
        if (minValidMetadata >= 0) {
            if (metadata < minValidMetadata)
                Intrinsic::storeLong((glong) &minValidMetadata, metadata, Intrinsic::RELAXED);
        }
        else {
            if (metadata > minValidMetadata)
                Intrinsic::storeLong((glong) &minValidMetadata, metadata, Intrinsic::RELAXED);
        }
        unlock();
    }

    void Cache::lock() {
        while (!Intrinsic::compareAndExchangeInt((glong) &state, 12345, 67890, true, Intrinsic::ACQUIRE)) {
            Intrinsic::threadFence(Intrinsic::RELEASE);
        }
        Intrinsic::signalFence(Intrinsic::ACQUIRE);
    }

    void Cache::unlock() {
        while (!Intrinsic::compareAndExchangeInt((glong) &state, 67890, 12345, true, Intrinsic::RELEASE)) {
            Intrinsic::threadFence(Intrinsic::ACQUIRE);
        }
        Intrinsic::signalFence(Intrinsic::RELEASE);
    }
}
