#include "create_torrent.h"

#include <libtorrent/create_torrent.hpp>

#include "entry.h"
#include "file_storage.h"
#include "torrent_info.h"

using lt::CreateTorrent;

Nan::Persistent<v8::Function> CreateTorrent::constructor;

CreateTorrent::CreateTorrent(std::unique_ptr<libtorrent::create_torrent> ct)
    : ct_(std::move(ct))
{
}

CreateTorrent::~CreateTorrent()
{
}

NAN_MODULE_INIT(CreateTorrent::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("create_torrent").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "generate", Generate);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("create_torrent").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(CreateTorrent::Generate)
{
    CreateTorrent* obj = Nan::ObjectWrap::Unwrap<CreateTorrent>(info.This());
    libtorrent::entry entry = obj->ct_->generate();

    info.GetReturnValue().Set(Entry::NewInstance(Nan::New<v8::External>(static_cast<void*>(&entry))));
}

NAN_METHOD(CreateTorrent::New)
{
    if (info.IsConstructCall())
    {
        CreateTorrent* obj = nullptr;

        if (info.Length() > 0 && info[0]->IsObject())
        {
            auto params = info[0]->ToObject();
            auto fs = Nan::New("fs").ToLocalChecked();
            auto ti = Nan::New("ti").ToLocalChecked();

            if (params->Has(fs) && params->Get(fs)->IsObject())
            {
                v8::Local<v8::Object> fsObject = params->Get(fs)->ToObject();
                FileStorage* fileStorage = Nan::ObjectWrap::Unwrap<FileStorage>(fsObject);

                //auto ct = std::make_unique<libtorrent::create_torrent>(fileStorage->GetWrapped());
                //obj = new CreateTorrent(std::move(ct));
            }
            else if (params->Has(ti) && params->Get(ti)->IsObject())
            {
                v8::Local<v8::Object> tiObject = params->Get(ti)->ToObject();
                TorrentInfo* torrentInfo = Nan::ObjectWrap::Unwrap<TorrentInfo>(tiObject);

                auto ct = std::make_unique<libtorrent::create_torrent>(*torrentInfo->GetWrapped().get());
                obj = new CreateTorrent(std::move(ct));
            }
        }
        else
        {
            Nan::ThrowError("Invalid object constructor");
            return;
        }

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        Nan::ThrowError("Use 'new' to create instances of 'session'.");
    }
}
