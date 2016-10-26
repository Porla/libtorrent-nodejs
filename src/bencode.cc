#include "bencode.h"

#include "entry.h"

#include <libtorrent/bencode.hpp>

using lt::BEncode;

NAN_METHOD(DoBEncode)
{
    lt::Entry* e = Nan::ObjectWrap::Unwrap<lt::Entry>(info[0]->ToObject());

    std::vector<char> buf;
    libtorrent::bencode(std::back_inserter(buf), e->GetWrapped());

    std::string encoded(buf.begin(), buf.end());

    info.GetReturnValue().Set(Nan::New(encoded).ToLocalChecked());
}

NAN_MODULE_INIT(BEncode::Init)
{
    Nan::Set(target, Nan::New("bencode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DoBEncode)->GetFunction());
}
