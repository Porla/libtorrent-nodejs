#include "bdecode.h"

#include <libtorrent/bdecode.hpp>
#include <libtorrent/entry.hpp>

#include "entry.h"

#if !defined(WIN32) && __cplusplus <= 201103
    #include "_aux/std_make_unique.h"
#endif

using plt::BDecode;

static NAN_METHOD(DoBDecode)
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

    libtorrent::bdecode_node node;
    libtorrent::error_code ec;

    libtorrent::bdecode(
        &buf[0],
        &buf[0] + buf.size(),
        node,
        ec);

    if (ec)
    {
        Nan::ThrowError(ec.message().c_str());
        return;
    }

    libtorrent::entry e;
    e = node;

    info.GetReturnValue().Set(plt::Entry::ToJson(e));
}

NAN_MODULE_INIT(BDecode::Init)
{
    Nan::Set(target, Nan::New("bdecode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DoBDecode)->GetFunction());
}
