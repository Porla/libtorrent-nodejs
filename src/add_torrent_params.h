#ifndef ADDTORRENTPARAMS_H
#define ADDTORRENTPARAMS_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct add_torrent_params;
}

namespace lt
{
    class AddTorrentParams : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

    private:
        explicit AddTorrentParams();
        explicit AddTorrentParams(std::unique_ptr<libtorrent::add_torrent_params> params);
        ~AddTorrentParams();

        static NAN_METHOD(New);
        static NAN_PROPERTY_GETTER(PropertyGetter);
        static NAN_PROPERTY_SETTER(PropertySetter);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<libtorrent::add_torrent_params> p_;
    };
}

#endif
