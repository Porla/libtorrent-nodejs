#include "entry.h"

#include <libtorrent/entry.hpp>

using lt::Entry;

libtorrent::entry Entry::FromJson(v8::Local<v8::Value> val)
{
    if (val->IsNumber())
    {
        return libtorrent::entry(static_cast<int64_t>(val->NumberValue()));
    }

    if (val->IsString())
    {
        ssize_t size = Nan::DecodeBytes(val);

        if (size < 0)
        {
            Nan::ThrowError("Could not decode bytes.");
            return libtorrent::entry();
        }

        std::string str(size, '\0');
        Nan::DecodeWrite(&str[0], size, val);

        return libtorrent::entry(str);
    }

    if (val->IsArray())
    {
        v8::Local<v8::Array> arr = val.As<v8::Array>();
        libtorrent::entry::list_type list;

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            list.push_back(FromJson(arr->Get(i)));
        }

        return libtorrent::entry(list);
    }

    if (val->IsObject() && !val->IsExternal())
    {
        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Array> props = obj->GetOwnPropertyNames();

        libtorrent::entry::dictionary_type dict;

        for (uint32_t i = 0; i < props->Length(); i++)
        {
            std::string key = *Nan::Utf8String(props->Get(i));
            v8::Local<v8::Value> val = obj->Get(Nan::New(key).ToLocalChecked());

            dict.insert({ key, FromJson(val) });
        }

        return libtorrent::entry(dict);
    }

    return libtorrent::entry();
}

v8::Local<v8::Value> Entry::ToJson(libtorrent::entry const& entry)
{
    switch (entry.type())
    {
    case libtorrent::entry::data_type::dictionary_t:
    {
        auto dict = entry.dict();
        v8::Local<v8::Object> obj = Nan::New<v8::Object>();

        for (auto& p : dict)
        {
            v8::Local<v8::Value> key = Nan::New(p.first).ToLocalChecked();
            v8::Local<v8::Value> val = ToJson(p.second);

            obj->Set(key, val);
        }

        return obj;
    }
    case libtorrent::entry::data_type::int_t:
    {
        return Nan::New(static_cast<double>(entry.integer()));
    }
    case libtorrent::entry::data_type::list_t:
    {
        auto list = entry.list();
        v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(list.size()));

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            v8::Local<v8::Value> val = ToJson(list.at(i));
            arr->Set(i, val);
        }

        return arr;
    }
    case libtorrent::entry::data_type::string_t:
    {
        std::string s = entry.string();
        return Nan::Encode(s.c_str(), s.size());
    }
    case libtorrent::entry::data_type::preformatted_t:
    {
        auto pre = entry.preformatted();
        return Nan::CopyBuffer(&pre[0], static_cast<uint32_t>(pre.size())).ToLocalChecked();
    }
    }

    return Nan::Undefined();
}
