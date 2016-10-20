#include "file_storage.h"

#include <libtorrent/file_storage.hpp>

using lt::FileStorage;

Nan::Persistent<v8::Function> FileStorage::constructor;


FileStorage::FileStorage(std::reference_wrapper<const libtorrent::file_storage> fs)
    : fs_(fs)
{
}

NAN_MODULE_INIT(FileStorage::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("file_storage").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "is_valid", IsValid);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(FileStorage::New)
{
    std::reference_wrapper<const libtorrent::file_storage>* fs = static_cast<std::reference_wrapper<const libtorrent::file_storage>*>(info[0].As<v8::External>()->Value());

    FileStorage* node = new FileStorage(*fs);
    node->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> FileStorage::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(FileStorage::IsValid)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().is_valid()));
}
