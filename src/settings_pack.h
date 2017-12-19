#ifndef SETTINGSPACK_H
#define SETTINGSPACK_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct settings_pack;
}

namespace plt
{
    class SettingsPack : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        libtorrent::settings_pack& GetWrapped();

    private:
        explicit SettingsPack(std::unique_ptr<libtorrent::settings_pack> sp);
        ~SettingsPack();

        static NAN_METHOD(GetBool);
        static NAN_METHOD(GetInt);
        static NAN_METHOD(GetStr);
        static NAN_METHOD(New);
        static NAN_METHOD(SetBool);
        static NAN_METHOD(SetInt);
        static NAN_METHOD(SetStr);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<libtorrent::settings_pack> sp_;
    };
}

#endif
