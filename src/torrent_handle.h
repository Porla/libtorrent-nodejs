#ifndef TORRENTHANDLE_H
#define TORRENTHANDLE_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct torrent_handle;
}

namespace lt
{
    class TorrentHandle : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

    private:
        explicit TorrentHandle(std::unique_ptr<libtorrent::torrent_handle> params);
        ~TorrentHandle();

        static NAN_METHOD(New);
        static NAN_METHOD(GetStatus);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<libtorrent::torrent_handle> th_;
    };
}

#endif
