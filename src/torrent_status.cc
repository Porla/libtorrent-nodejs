#include "torrent_status.h"

#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "torrent_info.h"
#include "torrent_handle.h"

using lt::TorrentStatus;

v8::Local<v8::Object> TorrentStatus::CreateObject(v8::Isolate* isolate, libtorrent::torrent_status& ts)
{
    v8::Local<v8::Object> status = Nan::New<v8::Object>();

    if (ts.errc)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(ts.errc.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(ts.errc.value()));

        status->Set(Nan::New("errc").ToLocalChecked(), err);
    }

    status->Set(Nan::New("active_time").ToLocalChecked(), Nan::New(ts.active_time));
    status->Set(Nan::New("added_time").ToLocalChecked(), Nan::New(static_cast<double>(ts.added_time)));
    status->Set(Nan::New("all_time_download").ToLocalChecked(), Nan::New(static_cast<double>(ts.all_time_download)));
    status->Set(Nan::New("all_time_upload").ToLocalChecked(), Nan::New(static_cast<double>(ts.all_time_upload)));
    status->Set(Nan::New("announcing_to_dht").ToLocalChecked(), Nan::New(ts.announcing_to_dht));
    status->Set(Nan::New("announcing_to_lsd").ToLocalChecked(), Nan::New(ts.announcing_to_lsd));
    status->Set(Nan::New("announcing_to_trackers").ToLocalChecked(), Nan::New(ts.announcing_to_trackers));
    status->Set(Nan::New("auto_managed").ToLocalChecked(), Nan::New(ts.auto_managed));
    status->Set(Nan::New("block_size").ToLocalChecked(), Nan::New(ts.block_size));
    status->Set(Nan::New("completed_time").ToLocalChecked(), Nan::New(static_cast<double>(ts.completed_time)));
    status->Set(Nan::New("connections_limit").ToLocalChecked(), Nan::New(ts.connections_limit));
    status->Set(Nan::New("connect_candidates").ToLocalChecked(), Nan::New(ts.connect_candidates));
    status->Set(Nan::New("current_tracker").ToLocalChecked(), Nan::New(ts.current_tracker).ToLocalChecked());
    status->Set(Nan::New("distributed_copies").ToLocalChecked(), Nan::New(ts.distributed_copies));
    status->Set(Nan::New("distributed_fraction").ToLocalChecked(), Nan::New(ts.distributed_fraction));
    status->Set(Nan::New("distributed_full_copies").ToLocalChecked(), Nan::New(ts.distributed_full_copies));
    status->Set(Nan::New("download_payload_rate").ToLocalChecked(), Nan::New(ts.download_payload_rate));
    status->Set(Nan::New("download_rate").ToLocalChecked(), Nan::New(ts.download_rate));
    status->Set(Nan::New("down_bandwidth_queue").ToLocalChecked(), Nan::New(ts.down_bandwidth_queue));
    status->Set(Nan::New("error_file").ToLocalChecked(), Nan::New(ts.error_file));
    status->Set(Nan::New("finished_time").ToLocalChecked(), Nan::New(ts.finished_time));
    status->Set(Nan::New("handle").ToLocalChecked(), TorrentHandle::NewInstance(v8::External::New(isolate, static_cast<void*>(&ts.handle))));
    status->Set(Nan::New("has_incoming").ToLocalChecked(), Nan::New(ts.has_incoming));
    status->Set(Nan::New("has_metadata").ToLocalChecked(), Nan::New(ts.has_metadata));

    std::stringstream ss;
    ss << ts.info_hash;
    status->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());

    status->Set(Nan::New("ip_filter_applies").ToLocalChecked(), Nan::New(ts.ip_filter_applies));
    status->Set(Nan::New("is_finished").ToLocalChecked(), Nan::New(ts.is_finished));
    status->Set(Nan::New("is_seeding").ToLocalChecked(), Nan::New(ts.is_seeding));
    status->Set(Nan::New("last_scrape").ToLocalChecked(), Nan::New(ts.last_scrape));
    status->Set(Nan::New("last_seen_complete").ToLocalChecked(), Nan::New(static_cast<double>(ts.last_seen_complete)));
    status->Set(Nan::New("list_peers").ToLocalChecked(), Nan::New(ts.list_peers));
    status->Set(Nan::New("list_seeds").ToLocalChecked(), Nan::New(ts.list_seeds));
    status->Set(Nan::New("moving_storage").ToLocalChecked(), Nan::New(ts.moving_storage));
    status->Set(Nan::New("name").ToLocalChecked(), Nan::New(ts.name).ToLocalChecked());
    status->Set(Nan::New("need_save_resume").ToLocalChecked(), Nan::New(ts.need_save_resume));
    status->Set(Nan::New("next_announce").ToLocalChecked(), Nan::New(static_cast<double>(libtorrent::total_seconds(ts.next_announce))));
    status->Set(Nan::New("num_complete").ToLocalChecked(), Nan::New(ts.num_complete));
    status->Set(Nan::New("num_connections").ToLocalChecked(), Nan::New(ts.num_connections));
    status->Set(Nan::New("num_incomplete").ToLocalChecked(), Nan::New(ts.num_incomplete));
    status->Set(Nan::New("num_peers").ToLocalChecked(), Nan::New(ts.num_peers));
    status->Set(Nan::New("num_pieces").ToLocalChecked(), Nan::New(ts.num_pieces));
    status->Set(Nan::New("num_seeds").ToLocalChecked(), Nan::New(ts.num_seeds));
    status->Set(Nan::New("num_uploads").ToLocalChecked(), Nan::New(ts.num_uploads));
    status->Set(Nan::New("paused").ToLocalChecked(), Nan::New(ts.paused));
    // status->Set(Nan::New("paused").ToLocalChecked(), Nan::New(ts.pieces));
    status->Set(Nan::New("progress").ToLocalChecked(), Nan::New(ts.progress));
    status->Set(Nan::New("progress_ppm").ToLocalChecked(), Nan::New(ts.progress_ppm));
    status->Set(Nan::New("queue_position").ToLocalChecked(), Nan::New(ts.queue_position));
    status->Set(Nan::New("save_path").ToLocalChecked(), Nan::New(ts.save_path).ToLocalChecked());
    status->Set(Nan::New("seeding_time").ToLocalChecked(), Nan::New(ts.seeding_time));
    status->Set(Nan::New("seed_mode").ToLocalChecked(), Nan::New(ts.seed_mode));
    status->Set(Nan::New("seed_rank").ToLocalChecked(), Nan::New(ts.seed_rank));
    status->Set(Nan::New("sequential_download").ToLocalChecked(), Nan::New(ts.sequential_download));
    status->Set(Nan::New("share_mode").ToLocalChecked(), Nan::New(ts.share_mode));
    status->Set(Nan::New("state").ToLocalChecked(), Nan::New(ts.state));
    status->Set(Nan::New("stop_when_ready").ToLocalChecked(), Nan::New(ts.stop_when_ready));
    status->Set(Nan::New("storage_mode").ToLocalChecked(), Nan::New(ts.storage_mode));
    status->Set(Nan::New("super_seeding").ToLocalChecked(), Nan::New(ts.super_seeding));
    status->Set(Nan::New("time_since_download").ToLocalChecked(), Nan::New(ts.time_since_download));
    status->Set(Nan::New("time_since_upload").ToLocalChecked(), Nan::New(ts.time_since_upload));

    if (auto ti = ts.torrent_file.lock())
    {
        v8::Local<v8::External> ext = v8::External::New(isolate, static_cast<void*>(&ti));
        status->Set(Nan::New("torrent_file").ToLocalChecked(), TorrentInfo::NewInstance(ext));
    }

    status->Set(Nan::New("total_done").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_done)));
    status->Set(Nan::New("total_download").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_download)));
    status->Set(Nan::New("total_failed_bytes").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_failed_bytes)));
    status->Set(Nan::New("total_payload_download").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_payload_download)));
    status->Set(Nan::New("total_payload_upload").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_payload_upload)));
    status->Set(Nan::New("total_redundant_bytes").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_redundant_bytes)));
    status->Set(Nan::New("total_upload").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_upload)));
    status->Set(Nan::New("total_wanted").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_wanted)));
    status->Set(Nan::New("total_wanted_done").ToLocalChecked(), Nan::New(static_cast<double>(ts.total_wanted_done)));
    status->Set(Nan::New("uploads_limit").ToLocalChecked(), Nan::New(ts.uploads_limit));
    status->Set(Nan::New("upload_mode").ToLocalChecked(), Nan::New(ts.upload_mode));
    status->Set(Nan::New("upload_payload_rate").ToLocalChecked(), Nan::New(ts.upload_payload_rate));
    status->Set(Nan::New("upload_rate").ToLocalChecked(), Nan::New(ts.upload_rate));
    status->Set(Nan::New("up_bandwidth_queue").ToLocalChecked(), Nan::New(ts.up_bandwidth_queue));
    // status->Set(Nan::New("verified_pieces").ToLocalChecked(), Nan::New(ts.verified_pieces));

    return status;
}
