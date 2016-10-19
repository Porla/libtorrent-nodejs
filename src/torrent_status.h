#ifndef TORRENTSTATUS_H
#define TORRENTSTATUS_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct torrent_status;
}

namespace lt
{
    class TorrentStatus
    {
    public:
        static v8::Local<v8::Object> CreateObject(libtorrent::torrent_status& ts);
    };
}

#endif
