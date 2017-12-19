#ifndef ENTRY_H
#define ENTRY_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class entry;
}

namespace plt
{
    class Entry
    {
    public:
        static libtorrent::entry FromJson(v8::Local<v8::Value> val);
        static v8::Local<v8::Value> ToJson(libtorrent::entry const& entry);
    };
}

#endif
