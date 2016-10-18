#ifndef SESSION_H
#define SESSION_H

#include <nan.h>

namespace libtorrent
{
    struct add_torrent_params;
    class session;
    struct settings_pack;
}

namespace lt
{
    class Session : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);

    private:
        explicit Session();
        explicit Session(libtorrent::settings_pack& settings);
        ~Session();

        static NAN_METHOD(AddDhtRouter);
        static NAN_METHOD(AddTorrent);
        static NAN_METHOD(ApplySettings);
        static NAN_METHOD(AsyncAddTorrent);
        static NAN_METHOD(GetSettings);
        static NAN_METHOD(IsListening);
        static NAN_METHOD(IsPaused);
        static NAN_METHOD(LoadState);
        static NAN_METHOD(New);
        static NAN_METHOD(PopAlerts);
        static NAN_METHOD(RemoveTorrent);
        static NAN_METHOD(WaitForAlert);

        static Nan::Persistent<v8::Function> constructor;

        libtorrent::session* wrap_;
    };
}

#endif
