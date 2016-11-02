#ifndef CREATETORRENT_H
#define CREATETORRENT_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct create_torrent;
}

namespace lt
{
    class CreateTorrent : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

    private:
        explicit CreateTorrent(std::unique_ptr<libtorrent::create_torrent> ct);
        ~CreateTorrent();

        static NAN_METHOD(Generate);
        static NAN_METHOD(New);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<libtorrent::create_torrent> ct_;
    };
}

#endif
