#include "torrent_handle.h"

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "torrent_info.h"
#include "torrent_status.h"

using lt::TorrentHandle;

Nan::Persistent<v8::Function> TorrentHandle::constructor;

TorrentHandle::TorrentHandle(std::unique_ptr<libtorrent::torrent_handle> th)
    : th_(std::move(th))
{
}

TorrentHandle::~TorrentHandle()
{
}

NAN_MODULE_INIT(TorrentHandle::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("torrent_handle").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Methods
    Nan::SetPrototypeMethod(tpl, "status", GetStatus);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("torrent_handle").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(TorrentHandle::New)
{
    if (info.IsConstructCall())
    {
        libtorrent::torrent_handle* th = static_cast<libtorrent::torrent_handle*>(info[0].As<v8::External>()->Value());
        
        TorrentHandle* obj = new TorrentHandle(std::make_unique<libtorrent::torrent_handle>(*th));
        obj->Wrap(info.This());

        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}

v8::Local<v8::Object> TorrentHandle::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(TorrentHandle::GetStatus)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    libtorrent::torrent_status st = obj->th_->status();

    info.GetReturnValue().Set(TorrentStatus::CreateObject(info.GetIsolate(), st));
}
