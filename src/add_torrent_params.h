#ifndef ADDTORRENTPARAMS_H
#define ADDTORRENTPARAMS_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct add_torrent_params;
}

namespace plt
{
    class AddTorrentParams
    {
    public:
        static libtorrent::add_torrent_params FromObject(v8::Local<v8::Object> object);
        static v8::Local<v8::Object> ToObject(libtorrent::add_torrent_params const& params);
    };
}

#endif
