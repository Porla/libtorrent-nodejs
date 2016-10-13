#ifndef BDECODE_H
#define BDECODE_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct bdecode_node;
}

namespace lt
{
    class BDecode
    {
    public:
        static NAN_MODULE_INIT(Init);
    };

    class BDecodeNode : public Nan::ObjectWrap
    {
    public:
        struct State;

        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        libtorrent::bdecode_node& GetWrapped();

    private:
        explicit BDecodeNode(std::unique_ptr<State> state);
        ~BDecodeNode();

        static NAN_METHOD(DictFindIntValue);
        static NAN_METHOD(DictFindStringValue);
        static NAN_METHOD(New);
        static NAN_METHOD(GetType);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<State> state_;
    };
}

#endif
