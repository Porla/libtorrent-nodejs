#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class torrent_info;
}

namespace lt
{
    class TorrentInfo : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        std::shared_ptr<libtorrent::torrent_info> GetWrapped();

    private:
        explicit TorrentInfo(std::shared_ptr<libtorrent::torrent_info> ti);
        ~TorrentInfo();

        static NAN_METHOD(New);
        static NAN_PROPERTY_GETTER(PropertyGetter);
        static NAN_PROPERTY_SETTER(PropertySetter);

        static Nan::Persistent<v8::Function> constructor;

        std::shared_ptr<libtorrent::torrent_info> ti_;
    };
}

#endif
