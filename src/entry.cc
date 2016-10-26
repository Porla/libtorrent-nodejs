#include "entry.h"

#include <libtorrent/entry.hpp>

using lt::Entry;

Nan::Persistent<v8::Function> Entry::constructor;

static libtorrent::entry GetEntry(v8::Local<v8::Value> val)
{
    if (val->IsNumber())
    {
        return libtorrent::entry(static_cast<int64_t>(val->NumberValue()));
    }

    if (val->IsString())
    {
        std::string str = *Nan::Utf8String(val);
        return libtorrent::entry(str);
    }

    if (val->IsArray())
    {
        v8::Local<v8::Array> arr = val.As<v8::Array>();
        libtorrent::entry::list_type list;

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            list.push_back(GetEntry(arr->Get(i)));
        }

        return list;
    }

    if (val->IsObject())
    {
        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Array> props = obj->GetOwnPropertyNames();

        libtorrent::entry::dictionary_type dict;

        for (uint32_t i = 0; i < props->Length(); i++)
        {
            std::string key = *Nan::Utf8String(props->Get(i));
            v8::Local<v8::Value> val = obj->Get(Nan::New(key).ToLocalChecked());

            dict.insert({ key, GetEntry(val) });
        }

        return dict;
    }

    return libtorrent::entry();
}

Entry::Entry(std::shared_ptr<libtorrent::entry> e)
    : e_(e)
{
}

Entry::~Entry()
{
}

libtorrent::entry& Entry::GetWrapped()
{
    return *e_.get();
}

NAN_MODULE_INIT(Entry::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("entry").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "dict", Dict);
    Nan::SetPrototypeMethod(tpl, "integer", Integer);
    Nan::SetPrototypeMethod(tpl, "list", List);
    Nan::SetPrototypeMethod(tpl, "string", String);
    Nan::SetPrototypeMethod(tpl, "type", Type);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("entry").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Entry::New)
{
    if (info.IsConstructCall())
    {
        Entry* obj = nullptr;

        if (info.Length() > 0 && info[0]->IsExternal())
        {
            libtorrent::entry* e = static_cast<libtorrent::entry*>(info[0].As<v8::External>()->Value());
            obj = new Entry(std::make_shared<libtorrent::entry>(*e));
        }
        else if (info.Length() > 0)
        {
            obj = new Entry(std::make_shared<libtorrent::entry>(GetEntry(info[0])));
        }
        else
        {
            obj = new Entry(std::make_shared<libtorrent::entry>());
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

v8::Local<v8::Object> Entry::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(Entry::Dict)
{
    Entry* e = Nan::ObjectWrap::Unwrap<Entry>(info.This());
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    libtorrent::entry::dictionary_type dict = e->e_->dict();

    for (auto& p : dict)
    {
        v8::Local<v8::Value> key = Nan::New(p.first).ToLocalChecked();
        v8::Local<v8::Object> val = NewInstance(Nan::New<v8::External>(static_cast<void*>(&p.second)));

        obj->Set(key, val);
    }

    info.GetReturnValue().Set(obj);
}

NAN_METHOD(Entry::Integer)
{
    Entry* e = Nan::ObjectWrap::Unwrap<Entry>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<double>(e->e_->integer())));
}

NAN_METHOD(Entry::List)
{
    Entry* e = Nan::ObjectWrap::Unwrap<Entry>(info.This());
    libtorrent::entry::list_type list = e->e_->list();
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(list.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        v8::Local<v8::Object> val = NewInstance(Nan::New<v8::External>(static_cast<void*>(&list.at(i))));
        arr->Set(i, val);
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(Entry::String)
{
    Entry* e = Nan::ObjectWrap::Unwrap<Entry>(info.This());
    info.GetReturnValue().Set(Nan::New(e->e_->string()).ToLocalChecked());
}

NAN_METHOD(Entry::Type)
{
    Entry* e = Nan::ObjectWrap::Unwrap<Entry>(info.This());
    info.GetReturnValue().Set(Nan::New(e->e_->type()));
}
