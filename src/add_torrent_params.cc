#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>

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
    Nan::SetNamedPropertyHandler(tpl->PrototypeTemplate(), PropertyGetter);

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

    if (property->Equals(Nan::New("save_path").ToLocalChecked()))
    {
        info.GetReturnValue().Set(Nan::New(obj->p_->save_path).ToLocalChecked());
    }
}

NAN_PROPERTY_SETTER(AddTorrentParams::PropertySetter)
{
    AddTorrentParams* obj = Nan::ObjectWrap::Unwrap<AddTorrentParams>(info.This());

    if (property->Equals(Nan::New("save_path").ToLocalChecked()))
    {
        obj->p_->save_path = *Nan::Utf8String(value);
    }
}
