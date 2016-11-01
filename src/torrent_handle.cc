#include "torrent_handle.h"

#include <libtorrent/announce_entry.hpp>
#include <libtorrent/peer_info.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#if defined(__APPLE__) && __cplusplus <= 201103
    #include "_aux/std_make_unique.h"
#endif

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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    int pieceIndex = info[0]->Int32Value();
    const char* data = node::Buffer::Data(info[1]);
    int flags = 0;

    if (info.Length() >= 3)
    {
        flags = info[0]->Int32Value();
    }

    obj->th_->add_piece(pieceIndex, data, flags);
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    
    std::vector<libtorrent::peer_info> peers;
    obj->th_->get_peer_info(peers);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(peers.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        libtorrent::peer_info& pi = peers.at(i);

        v8::Local<v8::Object> p = Nan::New<v8::Object>();
        p->Set(Nan::New("busy_requests").ToLocalChecked(), Nan::New(pi.busy_requests));
        p->Set(Nan::New("client").ToLocalChecked(), Nan::New(pi.client).ToLocalChecked());
        p->Set(Nan::New("connection_type").ToLocalChecked(), Nan::New(pi.connection_type));
        p->Set(Nan::New("downloading_block_index").ToLocalChecked(), Nan::New(pi.downloading_block_index));
        p->Set(Nan::New("downloading_piece_index").ToLocalChecked(), Nan::New(pi.downloading_piece_index));
        p->Set(Nan::New("downloading_progress").ToLocalChecked(), Nan::New(pi.downloading_progress));
        p->Set(Nan::New("downloading_total").ToLocalChecked(), Nan::New(pi.downloading_total));
        p->Set(Nan::New("download_queue_length").ToLocalChecked(), Nan::New(pi.download_queue_length));
        // TODO: p->Set(Nan::New("download_queue_time").ToLocalChecked(), Nan::New(pi.download_queue_time));
        p->Set(Nan::New("download_rate_peak").ToLocalChecked(), Nan::New(pi.download_rate_peak));
        p->Set(Nan::New("down_speed").ToLocalChecked(), Nan::New(pi.down_speed));
        p->Set(Nan::New("estimated_reciprocation_rate").ToLocalChecked(), Nan::New(pi.estimated_reciprocation_rate));
        p->Set(Nan::New("failcount").ToLocalChecked(), Nan::New(pi.failcount));
        p->Set(Nan::New("flags").ToLocalChecked(), Nan::New(pi.flags));

        v8::Local<v8::Array> ip = Nan::New<v8::Array>(2);
        ip->Set(0, Nan::New(pi.ip.address().to_string()).ToLocalChecked());
        ip->Set(1, Nan::New(pi.ip.port()));
        p->Set(Nan::New("ip").ToLocalChecked(), ip);

        // TODO: p->Set(Nan::New("ip").ToLocalChecked(), pi.last_active);
        // TODO: p->Set(Nan::New("ip").ToLocalChecked(), pi.last_request);

        v8::Local<v8::Array> local_endpoint = Nan::New<v8::Array>(2);
        local_endpoint->Set(0, Nan::New(pi.local_endpoint.address().to_string()).ToLocalChecked());
        local_endpoint->Set(1, Nan::New(pi.local_endpoint.port()));
        p->Set(Nan::New("local_endpoint").ToLocalChecked(), local_endpoint);

        p->Set(Nan::New("num_hashfails").ToLocalChecked(), Nan::New(pi.num_hashfails));
        p->Set(Nan::New("num_pieces").ToLocalChecked(), Nan::New(pi.num_pieces));
        p->Set(Nan::New("payload_down_speed").ToLocalChecked(), Nan::New(pi.payload_down_speed));
        p->Set(Nan::New("payload_up_speed").ToLocalChecked(), Nan::New(pi.payload_up_speed));
        p->Set(Nan::New("pending_disk_bytes").ToLocalChecked(), Nan::New(pi.pending_disk_bytes));
        p->Set(Nan::New("pending_disk_read_bytes").ToLocalChecked(), Nan::New(pi.pending_disk_read_bytes));

        std::stringstream ss;
        ss << pi.pid;
        p->Set(Nan::New("pid").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());

        // TODO: p->Set(Nan::New("pid").ToLocalChecked(), Nan::New(pi.pieces).ToLocalChecked());
        p->Set(Nan::New("progress").ToLocalChecked(), Nan::New(pi.progress));
        p->Set(Nan::New("progress_ppm").ToLocalChecked(), Nan::New(pi.progress_ppm));
        p->Set(Nan::New("queue_bytes").ToLocalChecked(), Nan::New(pi.queue_bytes));
        p->Set(Nan::New("read_state").ToLocalChecked(), Nan::New(pi.read_state));
        p->Set(Nan::New("receive_buffer_size").ToLocalChecked(), Nan::New(pi.receive_buffer_size));
        p->Set(Nan::New("receive_buffer_watermark").ToLocalChecked(), Nan::New(pi.receive_buffer_watermark));
        p->Set(Nan::New("receive_quota").ToLocalChecked(), Nan::New(pi.receive_quota));
        p->Set(Nan::New("requests_in_buffer").ToLocalChecked(), Nan::New(pi.requests_in_buffer));
        p->Set(Nan::New("request_timeout").ToLocalChecked(), Nan::New(pi.request_timeout));
        p->Set(Nan::New("rtt").ToLocalChecked(), Nan::New(pi.rtt));
        p->Set(Nan::New("send_buffer_size").ToLocalChecked(), Nan::New(pi.send_buffer_size));
        p->Set(Nan::New("send_quota").ToLocalChecked(), Nan::New(pi.send_quota));
        p->Set(Nan::New("source").ToLocalChecked(), Nan::New(pi.source));
        p->Set(Nan::New("target_dl_queue_length").ToLocalChecked(), Nan::New(pi.target_dl_queue_length));
        p->Set(Nan::New("timed_out_requests").ToLocalChecked(), Nan::New(pi.timed_out_requests));
        p->Set(Nan::New("total_download").ToLocalChecked(), Nan::New(static_cast<double>(pi.total_download)));
        p->Set(Nan::New("total_upload").ToLocalChecked(), Nan::New(static_cast<double>(pi.total_upload)));
        p->Set(Nan::New("upload_queue_length").ToLocalChecked(), Nan::New(pi.upload_queue_length));
        p->Set(Nan::New("upload_rate_peak").ToLocalChecked(), Nan::New(pi.upload_rate_peak));
        p->Set(Nan::New("up_speed").ToLocalChecked(), Nan::New(pi.up_speed));
        p->Set(Nan::New("used_receive_buffer").ToLocalChecked(), Nan::New(pi.used_receive_buffer));
        p->Set(Nan::New("used_send_buffer").ToLocalChecked(), Nan::New(pi.used_send_buffer));
        p->Set(Nan::New("write_state").ToLocalChecked(), Nan::New(pi.write_state));

        arr->Set(i, p);
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::Status)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    libtorrent::torrent_status st = obj->th_->status();

    info.GetReturnValue().Set(TorrentStatus::CreateObject(st));
}

NAN_METHOD(TorrentHandle::GetDownloadQueue)
{
    // TODO
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(TorrentHandle::SetPieceDeadline)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    int piece = info[0]->Int32Value();
    int deadline = info[1]->Int32Value();
    int flags = 0;

    if (info.Length() >= 3)
    {
        flags = info[2]->Int32Value();
    }

    obj->th_->set_piece_deadline(piece, deadline, flags);
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    int flags = 0;
    
    if (info.Length() >= 1)
    {
        flags = info[0]->Int32Value();
    }

    std::vector<int64_t> progress;
    obj->th_->file_progress(progress, flags);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(progress.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(static_cast<double>(progress.at(i))));
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::FileStatus)
{
    // TODO
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(TorrentHandle::ClearError)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->clear_error();
}

NAN_METHOD(TorrentHandle::Trackers)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::vector<libtorrent::announce_entry> trackers = obj->th_->trackers();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(trackers.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        libtorrent::announce_entry& ae = trackers.at(i);

        v8::Local<v8::Object> t = Nan::New<v8::Object>();
        t->Set(Nan::New("complete_sent").ToLocalChecked(), Nan::New(ae.complete_sent));
        t->Set(Nan::New("fails").ToLocalChecked(), Nan::New(ae.fails));
        t->Set(Nan::New("fail_limit").ToLocalChecked(), Nan::New(ae.fail_limit));

        if (ae.last_error)
        {
            v8::Local<v8::Object> err = Nan::New<v8::Object>();
            err->Set(Nan::New("message").ToLocalChecked(), Nan::New(ae.last_error.message()).ToLocalChecked());
            err->Set(Nan::New("value").ToLocalChecked(), Nan::New(ae.last_error.value()));
            t->Set(Nan::New("last_error").ToLocalChecked(), err);
        }

        t->Set(Nan::New("message").ToLocalChecked(), Nan::New(ae.message).ToLocalChecked());
        // TODO: t->Set(Nan::New("min_announce").ToLocalChecked(), Nan::New(ae.min_announce).ToLocalChecked());
        // TODO: t->Set(Nan::New("next_announce").ToLocalChecked(), Nan::New(ae.next_announce).ToLocalChecked());
        t->Set(Nan::New("scrape_complete").ToLocalChecked(), Nan::New(ae.scrape_complete));
        t->Set(Nan::New("scrape_downloaded").ToLocalChecked(), Nan::New(ae.scrape_downloaded));
        t->Set(Nan::New("scrape_incomplete").ToLocalChecked(), Nan::New(ae.scrape_incomplete));
        t->Set(Nan::New("source").ToLocalChecked(), Nan::New(ae.source));
        t->Set(Nan::New("start_sent").ToLocalChecked(), Nan::New(ae.start_sent));
        t->Set(Nan::New("tier").ToLocalChecked(), Nan::New(ae.tier));
        t->Set(Nan::New("trackerid").ToLocalChecked(), Nan::New(ae.trackerid).ToLocalChecked());
        t->Set(Nan::New("triggered_manually").ToLocalChecked(), Nan::New(ae.triggered_manually));
        t->Set(Nan::New("updating").ToLocalChecked(), Nan::New(ae.updating));
        t->Set(Nan::New("url").ToLocalChecked(), Nan::New(ae.url).ToLocalChecked());
        t->Set(Nan::New("verified").ToLocalChecked(), Nan::New(ae.verified));

        arr->Set(i, t);
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::ReplaceTrackers)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    v8::Local<v8::Array> arr = info[0].As<v8::Array>();
    std::vector<libtorrent::announce_entry> trackers;

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        v8::Local<v8::Object> t = arr->Get(i)->ToObject();
        libtorrent::announce_entry ae;

        if (t->Has(Nan::New("url").ToLocalChecked()))
        {
            ae.url = *Nan::Utf8String(t->Get(Nan::New("url").ToLocalChecked()));
        }

        if (t->Has(Nan::New("tier").ToLocalChecked()))
        {
            ae.tier = t->Get(Nan::New("tier").ToLocalChecked())->Int32Value();
        }

        trackers.push_back(ae);
    }

    obj->th_->replace_trackers(trackers);
}

NAN_METHOD(TorrentHandle::AddTracker)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    libtorrent::announce_entry ae;
    
    v8::Local<v8::Object> t = info[0]->ToObject();

    if (t->Has(Nan::New("url").ToLocalChecked()))
    {
        ae.url = *Nan::Utf8String(t->Get(Nan::New("url").ToLocalChecked()));
    }
    
    if (t->Has(Nan::New("tier").ToLocalChecked()))
    {
        ae.tier = t->Get(Nan::New("tier").ToLocalChecked())->Int32Value();
    }

    obj->th_->add_tracker(ae);
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::set<std::string> seeds = obj->th_->url_seeds();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(seeds.size()));
    uint32_t i = 0;

    for (std::string item : seeds)
    {
        arr->Set(i, Nan::New(item).ToLocalChecked());
        i += 1;
    }

    info.GetReturnValue().Set(arr);
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::set<std::string> seeds = obj->th_->http_seeds();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(seeds.size()));
    uint32_t i = 0;

    for (std::string item : seeds)
    {
        arr->Set(i, Nan::New(item).ToLocalChecked());
        i += 1;
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::SetMetadata)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    // TODO
    Nan::ThrowError("Not implemented.");
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->stop_when_ready(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::SetUploadMode)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_upload_mode(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::SetShareMode)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->set_share_mode(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::FlushCache)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->flush_cache();
}

NAN_METHOD(TorrentHandle::ApplyIpFilter)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->apply_ip_filter(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::ForceRecheck)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->force_recheck();
}

NAN_METHOD(TorrentHandle::SaveResumeData)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    int flags = info.Length() > 0 ? info[0]->Int32Value() : 0;
    obj->th_->save_resume_data(flags);
}

NAN_METHOD(TorrentHandle::NeedSaveResumeData)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->need_save_resume_data()));
}

NAN_METHOD(TorrentHandle::AutoManaged)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->auto_managed(info[0]->BooleanValue());
}

NAN_METHOD(TorrentHandle::QueuePosition)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->th_->queue_position()));
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    v8::Local<v8::Object> params = info[0]->ToObject();

    std::string certificate = *Nan::Utf8String(params->Get(Nan::New("certificate").ToLocalChecked()));
    std::string private_key = *Nan::Utf8String(params->Get(Nan::New("private_key").ToLocalChecked()));
    std::string dh_params = *Nan::Utf8String(params->Get(Nan::New("dh_params").ToLocalChecked()));
    std::string passphrase = "";
    
    if (params->Has(Nan::New("passphrase").ToLocalChecked()))
    {
        passphrase = *Nan::Utf8String(params->Get(Nan::New("dh_params").ToLocalChecked()));
    }

    obj->th_->set_ssl_certificate(
        certificate,
        private_key,
        dh_params,
        passphrase);
}

NAN_METHOD(TorrentHandle::SetSslCertificateBuffer)
{
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(TorrentHandle::TorrentFile)
{
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(TorrentHandle::UseInterface)
{
    Nan::ThrowError("Not implemented.");
}

NAN_METHOD(TorrentHandle::PieceAvailability)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::vector<int> avail;
    obj->th_->piece_availability(avail);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(avail.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(avail.at(i)));
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::PiecePriority)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    if (info.Length() == 1)
    {
        info.GetReturnValue().Set(Nan::New(obj->th_->piece_priority(info[0]->Int32Value())));
    }
    else if (info.Length() >= 2)
    {
        obj->th_->piece_priority(
            info[0]->Int32Value(),
            info[1]->Int32Value());
    }
    else
    {
        Nan::ThrowError("Invalid number of arguments.");
    }
}

NAN_METHOD(TorrentHandle::PrioritizePieces)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    v8::Local<v8::Array> arr = info[0].As<v8::Array>();

    if (arr->Length() <= 0)
    {
        return;
    }

    if (arr->Get(0)->IsObject())
    {
        // [ { index: 1, priority: 1 }]

        std::vector<std::pair<int, int>> prios;

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            v8::Local<v8::Object> pi = arr->Get(i)->ToObject();
            int index = pi->Get(Nan::New("index").ToLocalChecked())->Int32Value();
            int priority = pi->Get(Nan::New("priority").ToLocalChecked())->Int32Value();

            prios.push_back({ index, priority });
        }

        obj->th_->prioritize_pieces(prios);

    }
    else if (arr->Get(0)->IsNumber())
    {
        // [ 1, 2 ]

        std::vector<int> prios;

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            prios.push_back(arr->Get(i)->Int32Value());
        }

        obj->th_->prioritize_pieces(prios);
    }
    else
    {
        Nan::ThrowError("Invalid priority array.");
    }
}

NAN_METHOD(TorrentHandle::PiecePriorities)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::vector<int> prios = obj->th_->piece_priorities();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(prios.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(prios.at(i)));
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::FilePriority)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    if (info.Length() == 1)
    {
        info.GetReturnValue().Set(Nan::New(obj->th_->file_priority(info[0]->Int32Value())));
    }
    else if (info.Length() >= 2)
    {
        obj->th_->file_priority(
            info[0]->Int32Value(),
            info[1]->Int32Value());
    }
    else
    {
        Nan::ThrowError("Invalid number of arguments.");
    }
}

NAN_METHOD(TorrentHandle::PrioritizeFiles)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    v8::Local<v8::Array> arr = info[0].As<v8::Array>();

    if (arr->Length() <= 0)
    {
        return;
    }

    if (arr->Get(0)->IsNumber())
    {
        std::vector<int> prios;

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            prios.push_back(arr->Get(i)->Int32Value());
        }

        obj->th_->prioritize_files(prios);
    }
    else
    {
        Nan::ThrowError("Invalid priority array.");
    }
}

NAN_METHOD(TorrentHandle::FilePriorities)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    std::vector<int> prios = obj->th_->file_priorities();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(prios.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(prios.at(i)));
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentHandle::ForceReannounce)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->force_reannounce(
        info.Length() >= 1 ? info[0]->Int32Value() : 0,
        info.Length() >= 2 ? info[1]->Int32Value() : -1);
}

NAN_METHOD(TorrentHandle::ForceDhtAnnounce)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->force_dht_announce();
}

NAN_METHOD(TorrentHandle::ScrapeTracker)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->scrape_tracker(info.Length() >= 1 ? info[0]->Int32Value() : -1);
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());

    v8::Local<v8::Array> ep = info[0].As<v8::Array>();
    auto address = boost::asio::ip::address::from_string(*Nan::Utf8String(ep->Get(0)));
    auto port = ep->Get(1)->Int32Value();

    boost::asio::ip::tcp::endpoint endpoint(address, static_cast<unsigned short>(port));
    obj->th_->connect_peer(endpoint);
    // TODO source, flags
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
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->move_storage(
        *Nan::Utf8String(info[0]),
        info.Length() >= 2 ? info[1]->Int32Value() : 0);
}

NAN_METHOD(TorrentHandle::RenameFile)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->rename_file(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
}

NAN_METHOD(TorrentHandle::SuperSeeding)
{
    TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.This());
    obj->th_->super_seeding(info[0]->BooleanValue());
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
