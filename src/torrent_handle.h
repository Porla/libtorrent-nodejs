#ifndef TORRENTHANDLE_H
#define TORRENTHANDLE_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    struct torrent_handle;
}

namespace plt
{
    class TorrentHandle : public Nan::ObjectWrap
    {
    public:
        libtorrent::torrent_handle& GetWrapped();

        static NAN_MODULE_INIT(Init);
        static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

    private:
        explicit TorrentHandle(std::unique_ptr<libtorrent::torrent_handle> params);
        ~TorrentHandle();

        static NAN_METHOD(New);

        static NAN_METHOD(AddPiece);
        static NAN_METHOD(ReadPiece);
        static NAN_METHOD(HavePiece);
        static NAN_METHOD(GetPeerInfo);
        static NAN_METHOD(Status);
        static NAN_METHOD(GetDownloadQueue);
        static NAN_METHOD(SetPieceDeadline);
        static NAN_METHOD(ResetPieceDeadline);
        static NAN_METHOD(ClearPieceDeadlines);
        static NAN_METHOD(FileProgress);
        static NAN_METHOD(FileStatus);
        static NAN_METHOD(ClearError);
        static NAN_METHOD(Trackers);
        static NAN_METHOD(ReplaceTrackers);
        static NAN_METHOD(AddTracker);
        static NAN_METHOD(AddUrlSeed);
        static NAN_METHOD(RemoveUrlSeed);
        static NAN_METHOD(UrlSeeds);
        static NAN_METHOD(AddHttpSeed);
        static NAN_METHOD(RemoveHttpSeed);
        static NAN_METHOD(HttpSeeds);
        // TODO: static NAN_METHOD(AddExtension);
        static NAN_METHOD(SetMetadata);
        static NAN_METHOD(IsValid);
        static NAN_METHOD(Pause);
        static NAN_METHOD(Resume);
        static NAN_METHOD(FlushCache);
        static NAN_METHOD(ForceRecheck);
        static NAN_METHOD(SaveResumeData);
        static NAN_METHOD(NeedSaveResumeData);
        static NAN_METHOD(QueuePosition);
        static NAN_METHOD(QueuePositionUp);
        static NAN_METHOD(QueuePositionDown);
        static NAN_METHOD(QueuePositionTop);
        static NAN_METHOD(QueuePositionBottom);
        static NAN_METHOD(SetSslCertificate);
        static NAN_METHOD(SetSslCertificateBuffer);
        static NAN_METHOD(TorrentFile);
        static NAN_METHOD(UseInterface);
        static NAN_METHOD(PieceAvailability);
        static NAN_METHOD(PiecePriority);
        static NAN_METHOD(PrioritizePieces);
        static NAN_METHOD(GetPiecePriorities);
        static NAN_METHOD(FilePriority);
        static NAN_METHOD(PrioritizeFiles);
        static NAN_METHOD(GetFilePriorities);
        static NAN_METHOD(ForceReannounce);
        static NAN_METHOD(ForceDhtAnnounce);
        static NAN_METHOD(ScrapeTracker);
        static NAN_METHOD(SetUploadLimit);
        static NAN_METHOD(UploadLimit);
        static NAN_METHOD(SetDownloadLimit);
        static NAN_METHOD(DownloadLimit);
        static NAN_METHOD(ConnectPeer);
        static NAN_METHOD(SetMaxUploads);
        static NAN_METHOD(MaxUploads);
        static NAN_METHOD(SetMaxConnections);
        static NAN_METHOD(MaxConnections);
        static NAN_METHOD(MoveStorage);
        static NAN_METHOD(RenameFile);
        static NAN_METHOD(InfoHash);
        static NAN_METHOD(Id);

        static Nan::Persistent<v8::Function> constructor;

        std::unique_ptr<libtorrent::torrent_handle> th_;
    };
}

#endif
