#include "torrent_handle.h"

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "torrent_info.h"
#include "torrent_status.h"

using lt::TorrentHandle;

Nan::Persistent<v8::Function> TorrentHandle::constructor;

TorrentHandle::TorrentHandle(std::unique_ptr<libtorrent::torrent_handle> th)
    : th_(std::move(th))
{
}

TorrentHandle::~TorrentHandle()
{
}

libtorrent::torrent_handle& TorrentHandle::GetWrapped()
{
    return *th_.get();
}

NAN_MODULE_INIT(TorrentHandle::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("torrent_handle").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Methods
    Nan::SetPrototypeMethod(tpl, "add_piece", AddPiece);
    Nan::SetPrototypeMethod(tpl, "read_piece", ReadPiece);
    Nan::SetPrototypeMethod(tpl, "have_piece", HavePiece);
    Nan::SetPrototypeMethod(tpl, "get_peer_info", GetPeerInfo);
    Nan::SetPrototypeMethod(tpl, "status", Status);
    Nan::SetPrototypeMethod(tpl, "get_download_queue", GetDownloadQueue);
    Nan::SetPrototypeMethod(tpl, "set_piece_deadline", SetPieceDeadline);
    Nan::SetPrototypeMethod(tpl, "reset_piece_deadline", ResetPieceDeadline);
    Nan::SetPrototypeMethod(tpl, "clear_piece_deadlines", ClearPieceDeadlines);
    Nan::SetPrototypeMethod(tpl, "file_progress", FileProgress);
    Nan::SetPrototypeMethod(tpl, "file_status", FileStatus);
    Nan::SetPrototypeMethod(tpl, "clear_error", ClearError);
    Nan::SetPrototypeMethod(tpl, "trackers", Trackers);
    Nan::SetPrototypeMethod(tpl, "replace_trackers", ReplaceTrackers);
    Nan::SetPrototypeMethod(tpl, "add_tracker", AddTracker);
    Nan::SetPrototypeMethod(tpl, "add_url_seed", AddUrlSeed);
    Nan::SetPrototypeMethod(tpl, "remove_url_seed", RemoveUrlSeed);
    Nan::SetPrototypeMethod(tpl, "url_seeds", UrlSeeds);
    Nan::SetPrototypeMethod(tpl, "add_http_seed", AddHttpSeed);
    Nan::SetPrototypeMethod(tpl, "remove_http_seed", RemoveHttpSeed);
    Nan::SetPrototypeMethod(tpl, "http_seeds", HttpSeeds);
    Nan::SetPrototypeMethod(tpl, "set_metadata", SetMetadata);
    Nan::SetPrototypeMethod(tpl, "is_valid", IsValid);
    Nan::SetPrototypeMethod(tpl, "pause", Pause);
    Nan::SetPrototypeMethod(tpl, "resume", Resume);
    Nan::SetPrototypeMethod(tpl, "stop_when_ready", StopWhenReady);
    Nan::SetPrototypeMethod(tpl, "set_upload_mode", SetUploadMode);
    Nan::SetPrototypeMethod(tpl, "set_share_mode", SetShareMode);
    Nan::SetPrototypeMethod(tpl, "flush_cache", FlushCache);
    Nan::SetPrototypeMethod(tpl, "apply_ip_filter", ApplyIpFilter);
    Nan::SetPrototypeMethod(tpl, "force_recheck", ForceRecheck);
    Nan::SetPrototypeMethod(tpl, "save_resume_data", SaveResumeData);
    Nan::SetPrototypeMethod(tpl, "need_save_resume_data", NeedSaveResumeData);
    Nan::SetPrototypeMethod(tpl, "auto_managed", AutoManaged);
    Nan::SetPrototypeMethod(tpl, "queue_position", QueuePosition);
    Nan::SetPrototypeMethod(tpl, "queue_position_up", QueuePositionUp);
    Nan::SetPrototypeMethod(tpl, "queue_position_down", QueuePositionDown);
    Nan::SetPrototypeMethod(tpl, "queue_position_top", QueuePositionTop);
    Nan::SetPrototypeMethod(tpl, "queue_position_bottom", QueuePositionBottom);
    Nan::SetPrototypeMethod(tpl, "set_ssl_certificate", SetSslCertificate);
    Nan::SetPrototypeMethod(tpl, "set_ssl_certificate_buffer", SetSslCertificateBuffer);
    Nan::SetPrototypeMethod(tpl, "torrent_file", TorrentFile);
    Nan::SetPrototypeMethod(tpl, "use_interface", UseInterface);
    Nan::SetPrototypeMethod(tpl, "piece_availability", PieceAvailability);
    Nan::SetPrototypeMethod(tpl, "piece_priority", PiecePriority);
    Nan::SetPrototypeMethod(tpl, "prioritize_pieces", PrioritizePieces);
    Nan::SetPrototypeMethod(tpl, "piece_priorities", PiecePriorities);
    Nan::SetPrototypeMethod(tpl, "file_priority", FilePriority);
    Nan::SetPrototypeMethod(tpl, "prioritize_files", PrioritizeFiles);
    Nan::SetPrototypeMethod(tpl, "file_priorities", FilePriorities);
    Nan::SetPrototypeMethod(tpl, "force_reannounce", ForceReannounce);
    Nan::SetPrototypeMethod(tpl, "force_dht_announce", ForceDhtAnnounce);
    Nan::SetPrototypeMethod(tpl, "scrape_tracker", ScrapeTracker);
    Nan::SetPrototypeMethod(tpl, "set_upload_limit", SetUploadLimit);
    Nan::SetPrototypeMethod(tpl, "upload_limit", UploadLimit);
    Nan::SetPrototypeMethod(tpl, "set_download_limit", SetDownloadLimit);
    Nan::SetPrototypeMethod(tpl, "download_limit", DownloadLimit);
    Nan::SetPrototypeMethod(tpl, "set_sequential_download", SetSequentialDownload);
    Nan::SetPrototypeMethod(tpl, "connect_peer", ConnectPeer);
    Nan::SetPrototypeMethod(tpl, "set_max_uploads", SetMaxUploads);
    Nan::SetPrototypeMethod(tpl, "max_uploads", MaxUploads);
    Nan::SetPrototypeMethod(tpl, "set_max_connections", SetMaxConnections);
    Nan::SetPrototypeMethod(tpl, "max_connections", MaxConnections);
    Nan::SetPrototypeMethod(tpl, "move_storage", MoveStorage);
    Nan::SetPrototypeMethod(tpl, "rename_file", RenameFile);
    Nan::SetPrototypeMethod(tpl, "super_seeding", SuperSeeding);
    Nan::SetPrototypeMethod(tpl, "info_hash", InfoHash);
    Nan::SetPrototypeMethod(tpl, "id", Id);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("torrent_handle").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(TorrentHandle::New)
{
    if (info.IsConstructCall())
    {
        libtorrent::torrent_handle* th = static_cast<libtorrent::torrent_handle*>(info[0].As<v8::External>()->Value());
        
        TorrentHandle* obj = new TorrentHandle(std::make_unique<libtorrent::torrent_handle>(*th));
        obj->Wrap(info.This());

        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}

v8::Local<v8::Object> TorrentHandle::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(TorrentHandle::AddPiece)
{
}

NAN_METHOD(TorrentHandle::ReadPiece)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->read_piece(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::HavePiece)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    int idx = info[0]->Int32Value();
    info.GetReturnValue().Set(Nan::New(obj->th_->have_piece(idx)));
}

NAN_METHOD(TorrentHandle::GetPeerInfo)
{
}

NAN_METHOD(TorrentHandle::Status)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    libtorrent::torrent_status st = obj->th_->status();

    info.GetReturnValue().Set(TorrentStatus::CreateObject(st));
}

NAN_METHOD(TorrentHandle::GetDownloadQueue)
{
}

NAN_METHOD(TorrentHandle::SetPieceDeadline)
{
}

NAN_METHOD(TorrentHandle::ResetPieceDeadline)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->reset_piece_deadline(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::ClearPieceDeadlines)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->clear_piece_deadlines();
}

NAN_METHOD(TorrentHandle::FileProgress)
{
}

NAN_METHOD(TorrentHandle::FileStatus)
{
}

NAN_METHOD(TorrentHandle::ClearError)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->clear_error();
}

NAN_METHOD(TorrentHandle::Trackers)
{
}

NAN_METHOD(TorrentHandle::ReplaceTrackers)
{
}

NAN_METHOD(TorrentHandle::AddTracker)
{
}

NAN_METHOD(TorrentHandle::AddUrlSeed)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->add_url_seed(*Nan::Utf8String(info[0]));
}

NAN_METHOD(TorrentHandle::RemoveUrlSeed)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->remove_url_seed(*Nan::Utf8String(info[0]));
}

NAN_METHOD(TorrentHandle::UrlSeeds)
{
}

NAN_METHOD(TorrentHandle::AddHttpSeed)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->add_http_seed(*Nan::Utf8String(info[0]));
}

NAN_METHOD(TorrentHandle::RemoveHttpSeed)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->remove_http_seed(*Nan::Utf8String(info[0]));
}

NAN_METHOD(TorrentHandle::HttpSeeds)
{
}

NAN_METHOD(TorrentHandle::SetMetadata)
{
}

NAN_METHOD(TorrentHandle::IsValid)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->is_valid()));
}

NAN_METHOD(TorrentHandle::Pause)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    // TODO: flags
    obj->th_->pause();
}

NAN_METHOD(TorrentHandle::Resume)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->resume();
}

NAN_METHOD(TorrentHandle::StopWhenReady)
{
}

NAN_METHOD(TorrentHandle::SetUploadMode)
{
}

NAN_METHOD(TorrentHandle::SetShareMode)
{
}

NAN_METHOD(TorrentHandle::FlushCache)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->flush_cache();
}

NAN_METHOD(TorrentHandle::ApplyIpFilter)
{
}

NAN_METHOD(TorrentHandle::ForceRecheck)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->force_recheck();
}

NAN_METHOD(TorrentHandle::SaveResumeData)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    // TODO: flags
    obj->th_->save_resume_data();
}

NAN_METHOD(TorrentHandle::NeedSaveResumeData)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->need_save_resume_data()));
}

NAN_METHOD(TorrentHandle::AutoManaged)
{
}

NAN_METHOD(TorrentHandle::QueuePosition)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->queue_position();
}

NAN_METHOD(TorrentHandle::QueuePositionUp)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->queue_position_up();
}

NAN_METHOD(TorrentHandle::QueuePositionDown)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->queue_position_down();
}

NAN_METHOD(TorrentHandle::QueuePositionTop)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->queue_position_top();
}

NAN_METHOD(TorrentHandle::QueuePositionBottom)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->queue_position_bottom();
}

NAN_METHOD(TorrentHandle::SetSslCertificate)
{
}

NAN_METHOD(TorrentHandle::SetSslCertificateBuffer)
{
}

NAN_METHOD(TorrentHandle::TorrentFile)
{
}

NAN_METHOD(TorrentHandle::UseInterface)
{
}

NAN_METHOD(TorrentHandle::PieceAvailability)
{
}

NAN_METHOD(TorrentHandle::PiecePriority)
{
}

NAN_METHOD(TorrentHandle::PrioritizePieces)
{
}

NAN_METHOD(TorrentHandle::PiecePriorities)
{
}

NAN_METHOD(TorrentHandle::FilePriority)
{
}

NAN_METHOD(TorrentHandle::PrioritizeFiles)
{
}

NAN_METHOD(TorrentHandle::FilePriorities)
{
}

NAN_METHOD(TorrentHandle::ForceReannounce)
{
}

NAN_METHOD(TorrentHandle::ForceDhtAnnounce)
{
}

NAN_METHOD(TorrentHandle::ScrapeTracker)
{
}

NAN_METHOD(TorrentHandle::SetUploadLimit)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_upload_limit(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::UploadLimit)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->upload_limit()));
}

NAN_METHOD(TorrentHandle::SetDownloadLimit)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_download_limit(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::DownloadLimit)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->download_limit()));
}

NAN_METHOD(TorrentHandle::SetSequentialDownload)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_sequential_download(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::ConnectPeer)
{
}

NAN_METHOD(TorrentHandle::SetMaxUploads)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_max_uploads(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::MaxUploads)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->max_uploads()));
}

NAN_METHOD(TorrentHandle::SetMaxConnections)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_max_connections(info[0]->Int32Value());
}

NAN_METHOD(TorrentHandle::MaxConnections)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->max_connections()));
}

NAN_METHOD(TorrentHandle::MoveStorage)
{
}

NAN_METHOD(TorrentHandle::RenameFile)
{
}

NAN_METHOD(TorrentHandle::SuperSeeding)
{
}

NAN_METHOD(TorrentHandle::InfoHash)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::stringstream ss;
    ss << obj->th_->info_hash();
    info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}

NAN_METHOD(TorrentHandle::Id)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->id()));
}
