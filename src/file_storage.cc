#include "file_storage.h"

#include <sstream>

#include <libtorrent/file_storage.hpp>

using plt::FileStorage;

Nan::Persistent<v8::Function> FileStorage::constructor;

FileStorage::FileStorage(std::reference_wrapper<const libtorrent::file_storage> fs)
    : fs_(fs)
{
}

libtorrent::file_storage const& FileStorage::GetWrapped()
{
    return fs_.get();
}

NAN_MODULE_INIT(FileStorage::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("file_storage").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "is_valid", IsValid);
    Nan::SetPrototypeMethod(tpl, "num_files", NumFiles);
    Nan::SetPrototypeMethod(tpl, "total_size", TotalSize);
    Nan::SetPrototypeMethod(tpl, "num_pieces", NumPieces);
    Nan::SetPrototypeMethod(tpl, "piece_length", PieceSize);
    Nan::SetPrototypeMethod(tpl, "piece_size", PieceSize);
    Nan::SetPrototypeMethod(tpl, "name", Name);
    Nan::SetPrototypeMethod(tpl, "hash", Hash);
    Nan::SetPrototypeMethod(tpl, "symlink", Symlink);
    Nan::SetPrototypeMethod(tpl, "mtime", Mtime);
    Nan::SetPrototypeMethod(tpl, "file_path", FilePath);
    Nan::SetPrototypeMethod(tpl, "file_name", FileName);
    Nan::SetPrototypeMethod(tpl, "file_size", FileSize);
    Nan::SetPrototypeMethod(tpl, "pad_file_at", PadFileAt);
    Nan::SetPrototypeMethod(tpl, "file_offset", FileOffset);
    Nan::SetPrototypeMethod(tpl, "file_path_hash", FilePathHash);
    Nan::SetPrototypeMethod(tpl, "all_path_hashes", AllPathHashes);
    Nan::SetPrototypeMethod(tpl, "paths", Paths);
    Nan::SetPrototypeMethod(tpl, "file_flags", FileFlags);
    Nan::SetPrototypeMethod(tpl, "file_absolute_path", FileAbsolutePath);
    Nan::SetPrototypeMethod(tpl, "file_index_at_offset", FileIndexAtOffset);

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
    v8::Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();

    return scope.Escape(instance);
}

NAN_METHOD(FileStorage::IsValid)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().is_valid()));
}

NAN_METHOD(FileStorage::NumFiles)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().num_files()));
}

NAN_METHOD(FileStorage::TotalSize)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->fs_.get().total_size())));
}

NAN_METHOD(FileStorage::NumPieces)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().num_pieces()));
}

NAN_METHOD(FileStorage::PieceLength)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().piece_length()));
}

NAN_METHOD(FileStorage::PieceSize)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().piece_size(libtorrent::piece_index_t(info[0]->Int32Value()))));
}

NAN_METHOD(FileStorage::Name)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().name()).ToLocalChecked());
}

NAN_METHOD(FileStorage::Hash)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    std::stringstream ss;
    ss << obj->fs_.get().hash(libtorrent::file_index_t(info[0]->Int32Value()));
    info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}

NAN_METHOD(FileStorage::Symlink)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().symlink(libtorrent::file_index_t(info[0]->Int32Value()))).ToLocalChecked());
}

NAN_METHOD(FileStorage::Mtime)
{
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(FileStorage::FilePath)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());

    std::string save_path = "";

    if (info.Length() >= 2)
    {
        save_path = *Nan::Utf8String(info[1]);
    }

    info.GetReturnValue().Set(Nan::New(obj->fs_.get().file_path(libtorrent::file_index_t(info[0]->Int32Value()), save_path)).ToLocalChecked());
}

NAN_METHOD(FileStorage::FileName)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().file_name(libtorrent::file_index_t(info[0]->Int32Value())).to_string()).ToLocalChecked());
}

NAN_METHOD(FileStorage::FileSize)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->fs_.get().file_size(libtorrent::file_index_t(info[0]->Int32Value())))));
}

NAN_METHOD(FileStorage::PadFileAt)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().pad_file_at(libtorrent::file_index_t(info[0]->Int32Value()))));
}

NAN_METHOD(FileStorage::FileOffset)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->fs_.get().file_offset(libtorrent::file_index_t(info[0]->Int32Value())))));
}

NAN_METHOD(FileStorage::FilePathHash)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());

    std::string save_path = "";

    if (info.Length() >= 2)
    {
        save_path = *Nan::Utf8String(info[1]);
    }

    info.GetReturnValue().Set(Nan::New(obj->fs_.get().file_path_hash(libtorrent::file_index_t(info[0]->Int32Value()), save_path)));
}

NAN_METHOD(FileStorage::AllPathHashes)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    
    std::unordered_set<uint32_t> hashes;
    obj->fs_.get().all_path_hashes(hashes);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(hashes.size()));
    uint32_t i = 0;

    for (auto& h : hashes)
    {
        arr->Set(i, Nan::New(h));
        i += 1;
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(FileStorage::Paths)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    std::vector<std::string> const& paths = obj->fs_.get().paths();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(paths.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(paths.at(i)).ToLocalChecked());
    }
    
    info.GetReturnValue().Set(arr);
}

NAN_METHOD(FileStorage::FileFlags)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<uint8_t>(obj->fs_.get().file_flags(libtorrent::file_index_t(info[0]->Int32Value())))));
}

NAN_METHOD(FileStorage::FileAbsolutePath)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->fs_.get().file_absolute_path(libtorrent::file_index_t(info[0]->Int32Value()))));
}

NAN_METHOD(FileStorage::FileIndexAtOffset)
{
    FileStorage* obj = Nan::ObjectWrap::Unwrap<FileStorage>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<int>(obj->fs_.get().file_index_at_offset(info[0]->Int32Value()))));
}
