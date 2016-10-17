#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/time.hpp>

#include "torrent_info.h"

using lt::AddTorrentParams;

Nan::Persistent<v8::Function> AddTorrentParams::constructor;

AddTorrentParams::AddTorrentParams()
    : p_(std::make_unique<libtorrent::add_torrent_params>())
{
}

AddTorrentParams::AddTorrentParams(std::unique_ptr<libtorrent::add_torrent_params> params)
    : p_(std::move(params))
{
}

AddTorrentParams::~AddTorrentParams()
{
}

NAN_MODULE_INIT(AddTorrentParams::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("add_torrent_params").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Properties
    Nan::SetNamedPropertyHandler(tpl->PrototypeTemplate(), PropertyGetter, PropertySetter);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("add_torrent_params").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(AddTorrentParams::New)
{
    if (info.IsConstructCall())
    {
        AddTorrentParams* obj;

        if (info.Length() > 0 && info[0]->IsExternal())
        {
            libtorrent::add_torrent_params* p = static_cast<libtorrent::add_torrent_params*>(info[0].As<v8::External>()->Value());
            obj = new AddTorrentParams(std::make_unique<libtorrent::add_torrent_params>(*p));
        }
        else
        {
            obj = new AddTorrentParams();
        }

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}

v8::Local<v8::Object> AddTorrentParams::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_PROPERTY_GETTER(AddTorrentParams::PropertyGetter)
{
    AddTorrentParams* obj = Nan::ObjectWrap::Unwrap<AddTorrentParams>(info.This());

    if (property->Equals(Nan::New("active_time").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(obj->p_->active_time));
    }
    else if (property->Equals(Nan::New("added_time").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->p_->added_time)));
    }
    else if (property->Equals(Nan::New("completed_time").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->p_->completed_time)));
    }
    else if (property->Equals(Nan::New("download_limit").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(obj->p_->download_limit));
    }
    else if (property->Equals(Nan::New("file_priorities").ToLocalChecked()))
    {
        v8::Local<v8::Array> arr = Nan::New<v8::Array>(obj->p_->file_priorities.size());

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            arr->Set(i, Nan::New(obj->p_->file_priorities[i]));
        }

        info.GetReturnValue().Set(arr);
    }
    else if (property->Equals(Nan::New("finished_time").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->p_->finished_time)));
    }
    else if (property->Equals(Nan::New("save_path").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(obj->p_->save_path).ToLocalChecked());
    }
    else if (property->Equals(Nan::New("ti").ToLocalChecked()))
    {
        if (!obj->p_->ti)
        {
            info.GetReturnValue().SetNull();
            return;
        }

        v8::Local<v8::External> ext = v8::External::New(info.GetIsolate(), static_cast<void*>(&obj->p_->ti));
        info.GetReturnValue().Set(TorrentInfo::NewInstance(ext));
    }
    else if (property->Equals(Nan::New("url").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(obj->p_->url).ToLocalChecked());
    }
}

NAN_PROPERTY_SETTER(AddTorrentParams::PropertySetter)
{
    AddTorrentParams* obj = Nan::ObjectWrap::Unwrap<AddTorrentParams>(info.This());

    if (property->Equals(Nan::New("active_time").ToLocalChecked()))
    {
        obj->p_->active_time = value->Int32Value();
    }
    else if (property->Equals(Nan::New("added_time").ToLocalChecked()))
    {
        obj->p_->added_time = value->IntegerValue();
    }
    else if (property->Equals(Nan::New("completed_time").ToLocalChecked()))
    {
        obj->p_->completed_time = value->IntegerValue();
    }
    else if (property->Equals(Nan::New("download_limit").ToLocalChecked()))
    {
        obj->p_->download_limit = value->Int32Value();
    }
    else if (property->Equals(Nan::New("file_priorities").ToLocalChecked()))
    {
        v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(value);
        
        obj->p_->file_priorities.clear();
        obj->p_->file_priorities.resize(arr->Length());

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            obj->p_->file_priorities[i] = static_cast<uint8_t>(arr->Get(i)->Int32Value());
        }
    }
    else if (property->Equals(Nan::New("finished_time").ToLocalChecked()))
    {
        obj->p_->finished_time = value->IntegerValue();
    }
    else if (property->Equals(Nan::New("save_path").ToLocalChecked()))
    {
        obj->p_->save_path = *Nan::Utf8String(value);
    }
    else if (property->Equals(Nan::New("ti").ToLocalChecked()))
    {
        TorrentInfo* ti = Nan::ObjectWrap::Unwrap<TorrentInfo>(value->ToObject());
        obj->p_->ti = ti->GetWrapped();
    }
    else if (property->Equals(Nan::New("url").ToLocalChecked()))
    {
        obj->p_->url = *Nan::Utf8String(value);
    }
}
