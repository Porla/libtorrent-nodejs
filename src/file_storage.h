#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class file_storage;
}

namespace lt
{
    class FileStorage : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        libtorrent::file_storage const& GetWrapped();

    private:
        explicit FileStorage(std::reference_wrapper<const libtorrent::file_storage> fs);

        static NAN_METHOD(New);

        static NAN_METHOD(IsValid);
        // TODO: Reserve
        // TODO: AddFile
        // TODO: RenameFile
        // TODO: MapBlock
        // TODO: MapFile
        static NAN_METHOD(NumFiles);
        static NAN_METHOD(TotalSize);
        static NAN_METHOD(NumPieces);
        static NAN_METHOD(PieceLength);
        static NAN_METHOD(PieceSize);
        static NAN_METHOD(Name);
        static NAN_METHOD(IsLoaded);
        static NAN_METHOD(Hash);
        static NAN_METHOD(Symlink);
        static NAN_METHOD(Mtime);
        static NAN_METHOD(FilePath);
        static NAN_METHOD(FileName);
        static NAN_METHOD(FileSize);
        static NAN_METHOD(PadFileAt);
        static NAN_METHOD(FileOffset);
        static NAN_METHOD(FilePathHash);
        static NAN_METHOD(AllPathHashes);
        static NAN_METHOD(Paths);
        static NAN_METHOD(FileFlags);
        static NAN_METHOD(FileAbsolutePath);
        static NAN_METHOD(FileIndexAtOffset);
        // TODO file_name_ptr
        // TODO file_name_len

        static Nan::Persistent<v8::Function> constructor;

        std::reference_wrapper<const libtorrent::file_storage> fs_;
    };
}

#endif
