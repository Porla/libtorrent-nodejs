#ifndef ENTRY_H
#define ENTRY_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class entry;
}

namespace lt
{
    class Entry : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        libtorrent::entry& GetWrapped();

    private:
        explicit Entry(std::shared_ptr<libtorrent::entry> e);
        ~Entry();

        static NAN_METHOD(Dict);
        static NAN_METHOD(Integer);
        static NAN_METHOD(List);
        static NAN_METHOD(New);
        static NAN_METHOD(String);
        static NAN_METHOD(Type);

        static Nan::Persistent<v8::Function> constructor;

        std::shared_ptr<libtorrent::entry> e_;
    };
}

#endif
