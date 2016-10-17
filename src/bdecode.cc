#include "bdecode.h"

#include <libtorrent/bdecode.hpp>

using lt::BDecode;
using lt::BDecodeNode;

Nan::Persistent<v8::Function> BDecodeNode::constructor;

struct BDecodeNode::State
{
    std::unique_ptr<libtorrent::bdecode_node> node;
    std::unique_ptr<std::string> buffer;
};

BDecodeNode::BDecodeNode(std::unique_ptr<State> state)
    : state_(std::move(state))
{
}

BDecodeNode::~BDecodeNode()
{
}

libtorrent::bdecode_node& BDecodeNode::GetWrapped()
{
    return *state_->node;
}

NAN_METHOD(DoBDecode)
{
    std::string buf;

    if (info[0]->IsString())
    {
        buf = *Nan::Utf8String(info[0]);
    }
    else
    {
        buf = std::string(
            node::Buffer::Data(info[0]),
            node::Buffer::Length(info[0]));
    }

    std::unique_ptr<BDecodeNode::State> state = std::make_unique<BDecodeNode::State>();
    state->buffer = std::make_unique<std::string>(buf);
    state->node = std::make_unique<libtorrent::bdecode_node>();

    libtorrent::error_code ec;
    libtorrent::bdecode(
        &(*state->buffer)[0],
        &(*state->buffer)[0] + state->buffer->size(),
        *state->node,
        ec);

    if (ec)
    {
        Nan::ThrowError(ec.message().c_str());
        return;
    }

    v8::Local<v8::External> ext = v8::External::New(info.GetIsolate(), static_cast<void*>(&state));
    info.GetReturnValue().Set(BDecodeNode::NewInstance(ext));
}

NAN_MODULE_INIT(BDecode::Init)
{
    Nan::Set(target, Nan::New("bdecode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DoBDecode)->GetFunction());
}

NAN_MODULE_INIT(BDecodeNode::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("bdecode_node").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "dict_find_int_value", DictFindIntValue);
    Nan::SetPrototypeMethod(tpl, "dict_find_string_value", DictFindStringValue);
    Nan::SetPrototypeMethod(tpl, "type", GetType);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(BDecodeNode::DictFindIntValue)
{
    BDecodeNode* obj = Nan::ObjectWrap::Unwrap<BDecodeNode>(info.This());

    std::string key = *Nan::Utf8String(info[0]->ToString());
    int64_t val = obj->state_->node->dict_find_int_value(key);

    info.GetReturnValue().Set(Nan::New<v8::Number>(static_cast<double>(val)));
}

NAN_METHOD(BDecodeNode::DictFindStringValue)
{
    BDecodeNode* obj = Nan::ObjectWrap::Unwrap<BDecodeNode>(info.This());

    std::string key = *Nan::Utf8String(info[0]->ToString());
    std::string val = obj->state_->node->dict_find_string_value(key).to_string();

    info.GetReturnValue().Set(Nan::New(val).ToLocalChecked());
}

NAN_METHOD(BDecodeNode::GetType)
{
    BDecodeNode* obj = Nan::ObjectWrap::Unwrap<BDecodeNode>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->state_->node->type()));
}

NAN_METHOD(BDecodeNode::New)
{
    std::unique_ptr<State>* s = static_cast<std::unique_ptr<State>*>(info[0].As<v8::External>()->Value());

    BDecodeNode* node = new BDecodeNode(std::move(*s));
    node->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> BDecodeNode::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}
