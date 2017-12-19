#ifndef TORRENTINFO_H
#define TORRENTINFO_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class torrent_info;
}

namespace plt
{
    class TorrentInfo : public Nan::ObjectWrap
    {
    public:
        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

        std::shared_ptr<libtorrent::torrent_info> GetWrapped();

    private:
        explicit TorrentInfo(std::shared_ptr<libtorrent::torrent_info> ti);
        ~TorrentInfo();

        static NAN_METHOD(New);

        static NAN_METHOD(Files);
        static NAN_METHOD(OrigFiles);
        static NAN_METHOD(RenameFile);
        // TODO: remap files
        static NAN_METHOD(AddTracker);
        static NAN_METHOD(Trackers);
        static NAN_METHOD(SimilarTorrents);
        static NAN_METHOD(Collections);
        static NAN_METHOD(AddUrlSeed);
        static NAN_METHOD(AddHttpSeed);
        static NAN_METHOD(WebSeeds);
        static NAN_METHOD(SetWebSeeds);
        static NAN_METHOD(TotalSize);
        static NAN_METHOD(PieceLength);
        static NAN_METHOD(NumPieces);
        static NAN_METHOD(InfoHash);
        static NAN_METHOD(NumFiles);
        static NAN_METHOD(MapBlock);
        static NAN_METHOD(MapFile);
        static NAN_METHOD(Load);
        static NAN_METHOD(SslCert);
        static NAN_METHOD(IsValid);
        static NAN_METHOD(Priv);
        static NAN_METHOD(IsI2p);
        static NAN_METHOD(PieceSize);
        static NAN_METHOD(HashForPiece);
        // TODO: hash for piece ptr
        static NAN_METHOD(IsLoaded);
        static NAN_METHOD(MerkleTree);
        static NAN_METHOD(SetMerkleTree);
        static NAN_METHOD(Name);
        static NAN_METHOD(CreationDate);
        static NAN_METHOD(Creator);
        static NAN_METHOD(Comment);
        static NAN_METHOD(Nodes);
        static NAN_METHOD(AddNode);
        static NAN_METHOD(ParseInfoSection);
        // TODO info
        // TODO  swap?
        static NAN_METHOD(Metadata);

        static Nan::Persistent<v8::Function> constructor;

        std::shared_ptr<libtorrent::torrent_info> ti_;
    };
}

#endif
