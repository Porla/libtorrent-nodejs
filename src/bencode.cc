#include "bencode.h"

#include "entry.h"

#include <libtorrent/bencode.hpp>

using lt::BEncode;

NAN_METHOD(DoBEncode)
{
    lt::Entry* e = Nan::ObjectWrap::Unwrap<lt::Entry>(info[0]->ToObject());

    std::vector<char> buf;
    libtorrent::bencode(std::back_inserter(buf), e->GetWrapped());

    char* copy = static_cast<char*>(malloc(sizeof(char) * (buf.size() + 1)));
    std::strncpy(copy, &buf[0], buf.size());

    v8::Local<v8::Object> nodeBuffer = Nan::NewBuffer(copy, static_cast<uint32_t>(buf.size())).ToLocalChecked();
    info.GetReturnValue().Set(nodeBuffer);
}

NAN_MODULE_INIT(BEncode::Init)
{
    Nan::Set(target, Nan::New("bencode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DoBEncode)->GetFunction());
}
