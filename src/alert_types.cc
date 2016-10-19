#include "alert_types.h"

#include <libtorrent/alert_types.hpp>

#include "add_torrent_params.h"
#include "torrent_handle.h"
#include "torrent_status.h"

using lt::AlertTypes;

v8::Local<v8::Object> AlertTypes::ToObject(libtorrent::alert* alert)
{
    Nan::EscapableHandleScope scope;
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    obj->Set(Nan::New("category").ToLocalChecked(), Nan::New(alert->category()));
    obj->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->message()).ToLocalChecked());
    // todo: timestamp
    obj->Set(Nan::New("type").ToLocalChecked(), Nan::New(alert->type()));
    obj->Set(Nan::New("what").ToLocalChecked(), Nan::New(alert->what()).ToLocalChecked());

    // Get the alert
    switch (alert->type())
    {
    case libtorrent::torrent_added_alert::alert_type:
        ToTorrentAddedAlert(obj, static_cast<libtorrent::torrent_added_alert*>(alert));
        break;
    case libtorrent::torrent_removed_alert::alert_type:
        ToTorrentRemovedAlert(obj, static_cast<libtorrent::torrent_removed_alert*>(alert));
        break;
    case libtorrent::read_piece_alert::alert_type:
        ToReadPieceAlert(obj, static_cast<libtorrent::read_piece_alert*>(alert));
        break;
    case libtorrent::file_completed_alert::alert_type:
        ToFileCompletedAlert(obj, static_cast<libtorrent::file_completed_alert*>(alert));
        break;
    case libtorrent::file_renamed_alert::alert_type:
        ToFileRenamedAlert(obj, static_cast<libtorrent::file_renamed_alert*>(alert));
        break;
    case libtorrent::file_rename_failed_alert::alert_type:
        ToFileRenameFailedAlert(obj, static_cast<libtorrent::file_rename_failed_alert*>(alert));
        break;
    case libtorrent::performance_alert::alert_type:
        ToPerformanceAlert(obj, static_cast<libtorrent::performance_alert*>(alert));
        break;
    case libtorrent::state_changed_alert::alert_type:
        ToStateChangedAlert(obj, static_cast<libtorrent::state_changed_alert*>(alert));
        break;
    case libtorrent::tracker_error_alert::alert_type:
        ToTrackerErrorAlert(obj, static_cast<libtorrent::tracker_error_alert*>(alert));
        break;
    case libtorrent::tracker_warning_alert::alert_type:
        ToTrackerWarningAlert(obj, static_cast<libtorrent::tracker_warning_alert*>(alert));
        break;
    case libtorrent::scrape_reply_alert::alert_type:
        ToScrapeReplyAlert(obj, static_cast<libtorrent::scrape_reply_alert*>(alert));
        break;
    case libtorrent::scrape_failed_alert::alert_type:
        ToScrapeFailedAlert(obj, static_cast<libtorrent::scrape_failed_alert*>(alert));
        break;
    case libtorrent::tracker_reply_alert::alert_type:
        ToTrackerReplyAlert(obj, static_cast<libtorrent::tracker_reply_alert*>(alert));
        break;
    case libtorrent::dht_reply_alert::alert_type:
        ToDhtReplyAlert(obj, static_cast<libtorrent::dht_reply_alert*>(alert));
        break;
    case libtorrent::tracker_announce_alert::alert_type:
        ToTrackerAnnounceAlert(obj, static_cast<libtorrent::tracker_announce_alert*>(alert));
        break;
    case libtorrent::hash_failed_alert::alert_type:
        ToHashFailedAlert(obj, static_cast<libtorrent::hash_failed_alert*>(alert));
        break;
    case libtorrent::peer_ban_alert::alert_type:
        ToPeerBanAlert(obj, static_cast<libtorrent::peer_ban_alert*>(alert));
        break;
    case libtorrent::peer_unsnubbed_alert::alert_type:
        ToPeerUnsnubbedAlert(obj, static_cast<libtorrent::peer_unsnubbed_alert*>(alert));
        break;
    case libtorrent::peer_snubbed_alert::alert_type:
        ToPeerSnubbedAlert(obj, static_cast<libtorrent::peer_snubbed_alert*>(alert));
        break;
    case libtorrent::peer_error_alert::alert_type:
        ToPeerErrorAlert(obj, static_cast<libtorrent::peer_error_alert*>(alert));
        break;
    case libtorrent::peer_connect_alert::alert_type:
        ToPeerConnectAlert(obj, static_cast<libtorrent::peer_connect_alert*>(alert));
        break;
    case libtorrent::peer_disconnected_alert::alert_type:
        ToPeerDisconnectedAlert(obj, static_cast<libtorrent::peer_disconnected_alert*>(alert));
        break;
    case libtorrent::invalid_request_alert::alert_type:
        ToInvalidRequestAlert(obj, static_cast<libtorrent::invalid_request_alert*>(alert));
        break;
    case libtorrent::torrent_finished_alert::alert_type:
        ToTorrentFinishedAlert(obj, static_cast<libtorrent::torrent_finished_alert*>(alert));
        break;
    case libtorrent::piece_finished_alert::alert_type:
        ToPieceFinishedAlert(obj, static_cast<libtorrent::piece_finished_alert*>(alert));
        break;
    case libtorrent::request_dropped_alert::alert_type:
        ToRequestDroppedAlert(obj, static_cast<libtorrent::request_dropped_alert*>(alert));
        break;
    case libtorrent::block_timeout_alert::alert_type:
        ToBlockTimeoutAlert(obj, static_cast<libtorrent::block_timeout_alert*>(alert));
        break;
    case libtorrent::block_finished_alert::alert_type:
        ToBlockFinishedAlert(obj, static_cast<libtorrent::block_finished_alert*>(alert));
        break;
    case libtorrent::block_downloading_alert::alert_type:
        ToBlockDownloadingAlert(obj, static_cast<libtorrent::block_downloading_alert*>(alert));
        break;
    case libtorrent::unwanted_block_alert::alert_type:
        ToUnwantedBlockAlert(obj, static_cast<libtorrent::unwanted_block_alert*>(alert));
        break;
    case libtorrent::storage_moved_alert::alert_type:
        ToStorageMovedAlert(obj, static_cast<libtorrent::storage_moved_alert*>(alert));
        break;
    case libtorrent::storage_moved_failed_alert::alert_type:
        ToStorageMovedFailedAlert(obj, static_cast<libtorrent::storage_moved_failed_alert*>(alert));
        break;
    case libtorrent::torrent_deleted_alert::alert_type:
        ToTorrentDeletedAlert(obj, static_cast<libtorrent::torrent_deleted_alert*>(alert));
        break;
    case libtorrent::torrent_delete_failed_alert::alert_type:
        ToTorrentDeleteFailedAlert(obj, static_cast<libtorrent::torrent_delete_failed_alert*>(alert));
        break;
    case libtorrent::save_resume_data_alert::alert_type:
        ToSaveResumeDataAlert(obj, static_cast<libtorrent::save_resume_data_alert*>(alert));
        break;
    case libtorrent::save_resume_data_failed_alert::alert_type:
        ToSaveResumeDataFailedAlert(obj, static_cast<libtorrent::save_resume_data_failed_alert*>(alert));
        break;
    case libtorrent::torrent_paused_alert::alert_type:
        ToTorrentPausedAlert(obj, static_cast<libtorrent::torrent_paused_alert*>(alert));
        break;
    case libtorrent::torrent_resumed_alert::alert_type:
        ToTorrentResumedAlert(obj, static_cast<libtorrent::torrent_resumed_alert*>(alert));
        break;
    case libtorrent::torrent_checked_alert::alert_type:
        ToTorrentCheckedAlert(obj, static_cast<libtorrent::torrent_checked_alert*>(alert));
        break;
    case libtorrent::url_seed_alert::alert_type:
        ToUrlSeedAlert(obj, static_cast<libtorrent::url_seed_alert*>(alert));
        break;
    case libtorrent::file_error_alert::alert_type:
        ToFileErrorAlert(obj, static_cast<libtorrent::file_error_alert*>(alert));
        break;
    case libtorrent::metadata_failed_alert::alert_type:
        ToMetadataFailedAlert(obj, static_cast<libtorrent::metadata_failed_alert*>(alert));
        break;
    case libtorrent::metadata_received_alert::alert_type:
        ToMetadataReceivedAlert(obj, static_cast<libtorrent::metadata_received_alert*>(alert));
        break;
    case libtorrent::udp_error_alert::alert_type:
        ToUdpErrorAlert(obj, static_cast<libtorrent::udp_error_alert*>(alert));
        break;
    case libtorrent::external_ip_alert::alert_type:
        ToExternalIpAlert(obj, static_cast<libtorrent::external_ip_alert*>(alert));
        break;
    case libtorrent::listen_failed_alert::alert_type:
        ToListenFailedAlert(obj, static_cast<libtorrent::listen_failed_alert*>(alert));
        break;
    case libtorrent::listen_succeeded_alert::alert_type:
        ToListenSucceededAlert(obj, static_cast<libtorrent::listen_succeeded_alert*>(alert));
        break;
    case libtorrent::portmap_error_alert::alert_type:
        ToPortmapErrorAlert(obj, static_cast<libtorrent::portmap_error_alert*>(alert));
        break;
    case libtorrent::portmap_alert::alert_type:
        ToPortmapAlert(obj, static_cast<libtorrent::portmap_alert*>(alert));
        break;
    case libtorrent::portmap_log_alert::alert_type:
        ToPortmapLogAlert(obj, static_cast<libtorrent::portmap_log_alert*>(alert));
        break;
    case libtorrent::fastresume_rejected_alert::alert_type:
        ToFastresumeRejectedAlert(obj, static_cast<libtorrent::fastresume_rejected_alert*>(alert));
        break;
    case libtorrent::peer_blocked_alert::alert_type:
        ToPeerBlockedAlert(obj, static_cast<libtorrent::peer_blocked_alert*>(alert));
        break;
    case libtorrent::dht_announce_alert::alert_type:
        ToDhtAnnounceAlert(obj, static_cast<libtorrent::dht_announce_alert*>(alert));
        break;
    case libtorrent::dht_get_peers_alert::alert_type:
        ToDhtGetPeersAlert(obj, static_cast<libtorrent::dht_get_peers_alert*>(alert));
        break;
    case libtorrent::stats_alert::alert_type:
        ToStatsAlert(obj, static_cast<libtorrent::stats_alert*>(alert));
        break;
    case libtorrent::cache_flushed_alert::alert_type:
        ToCacheFlushedAlert(obj, static_cast<libtorrent::cache_flushed_alert*>(alert));
        break;
    case libtorrent::anonymous_mode_alert::alert_type:
        ToAnonymousModeAlert(obj, static_cast<libtorrent::anonymous_mode_alert*>(alert));
        break;
    case libtorrent::lsd_peer_alert::alert_type:
        ToLsdPeerAlert(obj, static_cast<libtorrent::lsd_peer_alert*>(alert));
        break;
    case libtorrent::trackerid_alert::alert_type:
        ToTrackeridAlert(obj, static_cast<libtorrent::trackerid_alert*>(alert));
        break;
    case libtorrent::dht_bootstrap_alert::alert_type:
        ToDhtBootstrapAlert(obj, static_cast<libtorrent::dht_bootstrap_alert*>(alert));
        break;
    case libtorrent::torrent_error_alert::alert_type:
        ToTorrentErrorAlert(obj, static_cast<libtorrent::torrent_error_alert*>(alert));
        break;
    case libtorrent::torrent_need_cert_alert::alert_type:
        ToTorrentNeedCertAlert(obj, static_cast<libtorrent::torrent_need_cert_alert*>(alert));
        break;
    case libtorrent::incoming_connection_alert::alert_type:
        ToIncomingConnectionAlert(obj, static_cast<libtorrent::incoming_connection_alert*>(alert));
        break;
    case libtorrent::add_torrent_alert::alert_type:
        ToAddTorrentAlert(obj, static_cast<libtorrent::add_torrent_alert*>(alert));
        break;
    case libtorrent::state_update_alert::alert_type:
        ToStateUpdateAlert(obj, static_cast<libtorrent::state_update_alert*>(alert));
        break;
    case libtorrent::mmap_cache_alert::alert_type:
        ToMmapCacheAlert(obj, static_cast<libtorrent::mmap_cache_alert*>(alert));
        break;
    case libtorrent::session_stats_alert::alert_type:
        ToSessionStatsAlert(obj, static_cast<libtorrent::session_stats_alert*>(alert));
        break;
    case libtorrent::dht_error_alert::alert_type:
        ToDhtErrorAlert(obj, static_cast<libtorrent::dht_error_alert*>(alert));
        break;
    case libtorrent::dht_immutable_item_alert::alert_type:
        ToDhtImmutableItemAlert(obj, static_cast<libtorrent::dht_immutable_item_alert*>(alert));
        break;
    case libtorrent::dht_mutable_item_alert::alert_type:
        ToDhtMutableItemAlert(obj, static_cast<libtorrent::dht_mutable_item_alert*>(alert));
        break;
    case libtorrent::dht_put_alert::alert_type:
        ToDhtPutAlert(obj, static_cast<libtorrent::dht_put_alert*>(alert));
        break;
    case libtorrent::i2p_alert::alert_type:
        ToI2pAlert(obj, static_cast<libtorrent::i2p_alert*>(alert));
        break;
    case libtorrent::dht_outgoing_get_peers_alert::alert_type:
        ToDhtOutgoingGetPeersAlert(obj, static_cast<libtorrent::dht_outgoing_get_peers_alert*>(alert));
        break;
    case libtorrent::log_alert::alert_type:
        ToLogAlert(obj, static_cast<libtorrent::log_alert*>(alert));
        break;
    case libtorrent::torrent_log_alert::alert_type:
        ToTorrentLogAlert(obj, static_cast<libtorrent::torrent_log_alert*>(alert));
        break;
    case libtorrent::peer_log_alert::alert_type:
        ToPeerLogAlert(obj, static_cast<libtorrent::peer_log_alert*>(alert));
        break;
    case libtorrent::lsd_error_alert::alert_type:
        ToLsdErrorAlert(obj, static_cast<libtorrent::lsd_error_alert*>(alert));
        break;
    case libtorrent::dht_stats_alert::alert_type:
        ToDhtStatsAlert(obj, static_cast<libtorrent::dht_stats_alert*>(alert));
        break;
    case libtorrent::incoming_request_alert::alert_type:
        ToIncomingRequestAlert(obj, static_cast<libtorrent::incoming_request_alert*>(alert));
        break;
    case libtorrent::dht_log_alert::alert_type:
        ToDhtLogAlert(obj, static_cast<libtorrent::dht_log_alert*>(alert));
        break;
    case libtorrent::dht_pkt_alert::alert_type:
        ToDhtPktAlert(obj, static_cast<libtorrent::dht_pkt_alert*>(alert));
        break;
    case libtorrent::dht_get_peers_reply_alert::alert_type:
        ToDhtGetPeersReplyAlert(obj, static_cast<libtorrent::dht_get_peers_reply_alert*>(alert));
        break;
    case libtorrent::dht_direct_response_alert::alert_type:
        ToDhtDirectResponseAlert(obj, static_cast<libtorrent::dht_direct_response_alert*>(alert));
        break;
    case libtorrent::picker_log_alert::alert_type:
        ToPickerLogAlert(obj, static_cast<libtorrent::picker_log_alert*>(alert));
        break;
    case libtorrent::session_error_alert::alert_type:
        ToSessionErrorAlert(obj, static_cast<libtorrent::session_error_alert*>(alert));
        break;
    }

    return scope.Escape(obj);
}

void AlertTypes::ToTorrentAlert(v8::Local<v8::Object> obj, libtorrent::torrent_alert* alert)
{
    v8::Local<v8::External> ext = Nan::New<v8::External>(static_cast<void*>(&alert->handle));
    obj->Set(Nan::New("handle").ToLocalChecked(), TorrentHandle::NewInstance(ext));
    obj->Set(Nan::New("torrent_name").ToLocalChecked(), Nan::New(alert->torrent_name()).ToLocalChecked());
}

void AlertTypes::ToPeerAlert(v8::Local<v8::Object> obj, libtorrent::peer_alert* alert)
{
    ToTorrentAlert(obj, alert);
    // TODO: ip
    // TODO: pid
}

void AlertTypes::ToTrackerAlert(v8::Local<v8::Object> obj, libtorrent::tracker_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("tracker_url").ToLocalChecked(), Nan::New(alert->tracker_url()).ToLocalChecked());
}

void AlertTypes::ToTorrentAddedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_added_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToTorrentRemovedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_removed_alert* alert)
{
    ToTorrentAlert(obj, alert);
    
    std::stringstream ss;
    ss << alert->info_hash;

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
}

void AlertTypes::ToReadPieceAlert(v8::Local<v8::Object> obj, libtorrent::read_piece_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->ec)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->ec.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->ec.value()));

        obj->Set(Nan::New("ec").ToLocalChecked(), err);
    }
    else
    {
        // TODO: This buffer might leak, I don't know.
        // Investigate!
        obj->Set(Nan::New("buffer").ToLocalChecked(), Nan::NewBuffer(alert->buffer.get(), alert->size).ToLocalChecked());
    }

    obj->Set(Nan::New("piece").ToLocalChecked(), Nan::New(alert->piece));
    obj->Set(Nan::New("size").ToLocalChecked(), Nan::New(alert->size));
}

void AlertTypes::ToFileCompletedAlert(v8::Local<v8::Object> obj, libtorrent::file_completed_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("index").ToLocalChecked(), Nan::New(alert->index));
}

void AlertTypes::ToFileRenamedAlert(v8::Local<v8::Object> obj, libtorrent::file_renamed_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("index").ToLocalChecked(), Nan::New(alert->index));
    obj->Set(Nan::New("new_name").ToLocalChecked(), Nan::New(alert->new_name()).ToLocalChecked());
}

void AlertTypes::ToFileRenameFailedAlert(v8::Local<v8::Object> obj, libtorrent::file_rename_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    v8::Local<v8::Object> err = Nan::New<v8::Object>();
    err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
    err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
    
    obj->Set(Nan::New("index").ToLocalChecked(), Nan::New(alert->index));
    obj->Set(Nan::New("error").ToLocalChecked(), err);
}

void AlertTypes::ToPerformanceAlert(v8::Local<v8::Object> obj, libtorrent::performance_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("warning_code").ToLocalChecked(), Nan::New(alert->warning_code));
}

void AlertTypes::ToStateChangedAlert(v8::Local<v8::Object> obj, libtorrent::state_changed_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("state").ToLocalChecked(), Nan::New(alert->state));
    obj->Set(Nan::New("prev_state").ToLocalChecked(), Nan::New(alert->prev_state));
}

void AlertTypes::ToTrackerErrorAlert(v8::Local<v8::Object> obj, libtorrent::tracker_error_alert* alert)
{
    ToTrackerAlert(obj, alert);

    v8::Local<v8::Object> err = Nan::New<v8::Object>();
    err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
    err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));

    obj->Set(Nan::New("error").ToLocalChecked(), err);
    obj->Set(Nan::New("error_message").ToLocalChecked(), Nan::New(alert->error_message()).ToLocalChecked());
    obj->Set(Nan::New("status_code").ToLocalChecked(), Nan::New(alert->status_code));
    obj->Set(Nan::New("times_in_row").ToLocalChecked(), Nan::New(alert->times_in_row));
}

void AlertTypes::ToTrackerWarningAlert(v8::Local<v8::Object> obj, libtorrent::tracker_warning_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("warning_message").ToLocalChecked(), Nan::New(alert->warning_message()).ToLocalChecked());
}

void AlertTypes::ToScrapeReplyAlert(v8::Local<v8::Object> obj, libtorrent::scrape_reply_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("complete").ToLocalChecked(), Nan::New(alert->complete));
    obj->Set(Nan::New("incomplete").ToLocalChecked(), Nan::New(alert->incomplete));
}

void AlertTypes::ToScrapeFailedAlert(v8::Local<v8::Object> obj, libtorrent::scrape_failed_alert* alert)
{
    ToTrackerAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("error_message").ToLocalChecked(), Nan::New(alert->error_message()).ToLocalChecked());
}

void AlertTypes::ToTrackerReplyAlert(v8::Local<v8::Object> obj, libtorrent::tracker_reply_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("num_peers").ToLocalChecked(), Nan::New(alert->num_peers));
}

void AlertTypes::ToDhtReplyAlert(v8::Local<v8::Object> obj, libtorrent::dht_reply_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("num_peers").ToLocalChecked(), Nan::New(alert->num_peers));
}

void AlertTypes::ToTrackerAnnounceAlert(v8::Local<v8::Object> obj, libtorrent::tracker_announce_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("event").ToLocalChecked(), Nan::New(alert->event));
}

void AlertTypes::ToHashFailedAlert(v8::Local<v8::Object> obj, libtorrent::hash_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToPeerBanAlert(v8::Local<v8::Object> obj, libtorrent::peer_ban_alert* alert)
{
    ToPeerAlert(obj, alert);
}

void AlertTypes::ToPeerUnsnubbedAlert(v8::Local<v8::Object> obj, libtorrent::peer_unsnubbed_alert* alert)
{
    ToPeerAlert(obj, alert);
}

void AlertTypes::ToPeerSnubbedAlert(v8::Local<v8::Object> obj, libtorrent::peer_snubbed_alert* alert)
{
    ToPeerAlert(obj, alert);
}

void AlertTypes::ToPeerErrorAlert(v8::Local<v8::Object> obj, libtorrent::peer_error_alert* alert)
{
    ToPeerAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation));
}

void AlertTypes::ToPeerConnectAlert(v8::Local<v8::Object> obj, libtorrent::peer_connect_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("socket_type").ToLocalChecked(), Nan::New(alert->socket_type));
}

void AlertTypes::ToPeerDisconnectedAlert(v8::Local<v8::Object> obj, libtorrent::peer_disconnected_alert* alert)
{
    ToPeerAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation));
    obj->Set(Nan::New("reason").ToLocalChecked(), Nan::New(alert->reason));
    obj->Set(Nan::New("socket_type").ToLocalChecked(), Nan::New(alert->socket_type));
}

void AlertTypes::ToInvalidRequestAlert(v8::Local<v8::Object> obj, libtorrent::invalid_request_alert* alert)
{
    ToPeerAlert(obj, alert);

    v8::Local<v8::Object> request = Nan::New<v8::Object>();
    request->Set(Nan::New("length").ToLocalChecked(), Nan::New(alert->request.length));
    request->Set(Nan::New("piece").ToLocalChecked(), Nan::New(alert->request.piece));
    request->Set(Nan::New("start").ToLocalChecked(), Nan::New(alert->request.start));
    
    obj->Set(Nan::New("request").ToLocalChecked(), request);
    obj->Set(Nan::New("peer_interested").ToLocalChecked(), Nan::New(alert->peer_interested));
    obj->Set(Nan::New("we_have").ToLocalChecked(), Nan::New(alert->we_have));
    obj->Set(Nan::New("withheld").ToLocalChecked(), Nan::New(alert->withheld));
}

void AlertTypes::ToTorrentFinishedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_finished_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToPieceFinishedAlert(v8::Local<v8::Object> obj, libtorrent::piece_finished_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToRequestDroppedAlert(v8::Local<v8::Object> obj, libtorrent::request_dropped_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("block_index").ToLocalChecked(), Nan::New(alert->block_index));
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToBlockTimeoutAlert(v8::Local<v8::Object> obj, libtorrent::block_timeout_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("block_index").ToLocalChecked(), Nan::New(alert->block_index));
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToBlockFinishedAlert(v8::Local<v8::Object> obj, libtorrent::block_finished_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("block_index").ToLocalChecked(), Nan::New(alert->block_index));
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToBlockDownloadingAlert(v8::Local<v8::Object> obj, libtorrent::block_downloading_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("block_index").ToLocalChecked(), Nan::New(alert->block_index));
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToUnwantedBlockAlert(v8::Local<v8::Object> obj, libtorrent::unwanted_block_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("block_index").ToLocalChecked(), Nan::New(alert->block_index));
    obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New(alert->piece_index));
}

void AlertTypes::ToStorageMovedAlert(v8::Local<v8::Object> obj, libtorrent::storage_moved_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("storage_path").ToLocalChecked(), Nan::New(alert->storage_path()).ToLocalChecked());
}

void AlertTypes::ToStorageMovedFailedAlert(v8::Local<v8::Object> obj, libtorrent::storage_moved_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("file_path").ToLocalChecked(), Nan::New(alert->file_path()).ToLocalChecked());
    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation).ToLocalChecked());
}

void AlertTypes::ToTorrentDeletedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_deleted_alert* alert)
{
    ToTorrentAlert(obj, alert);

    std::stringstream ss;
    ss << alert->info_hash;

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
}

void AlertTypes::ToTorrentDeleteFailedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_delete_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    std::stringstream ss;
    ss << alert->info_hash;

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
}

void AlertTypes::ToSaveResumeDataAlert(v8::Local<v8::Object> obj, libtorrent::save_resume_data_alert* alert)
{
    ToTorrentAlert(obj, alert);
    // TODO: resume data obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
}

void AlertTypes::ToSaveResumeDataFailedAlert(v8::Local<v8::Object> obj, libtorrent::save_resume_data_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToTorrentPausedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_paused_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToTorrentResumedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_resumed_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToTorrentCheckedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_checked_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToUrlSeedAlert(v8::Local<v8::Object> obj, libtorrent::url_seed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("error_message").ToLocalChecked(), Nan::New(alert->error_message()).ToLocalChecked());
    obj->Set(Nan::New("server_url").ToLocalChecked(), Nan::New(alert->server_url()).ToLocalChecked());
}

void AlertTypes::ToFileErrorAlert(v8::Local<v8::Object> obj, libtorrent::file_error_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("filename").ToLocalChecked(), Nan::New(alert->filename()).ToLocalChecked());
    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation).ToLocalChecked());
}

void AlertTypes::ToMetadataFailedAlert(v8::Local<v8::Object> obj, libtorrent::metadata_failed_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToMetadataReceivedAlert(v8::Local<v8::Object> obj, libtorrent::metadata_received_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToUdpErrorAlert(v8::Local<v8::Object> obj, libtorrent::udp_error_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    v8::Local<v8::Array> endpoint = Nan::New<v8::Array>(2);
    endpoint->Set(0, Nan::New(alert->endpoint.address().to_string()).ToLocalChecked());
    endpoint->Set(1, Nan::New(alert->endpoint.port()));

    obj->Set(Nan::New("endpoint").ToLocalChecked(), endpoint);
}

void AlertTypes::ToExternalIpAlert(v8::Local<v8::Object> obj, libtorrent::external_ip_alert* alert)
{
    obj->Set(Nan::New("external_address").ToLocalChecked(), Nan::New(alert->external_address.to_string()).ToLocalChecked());
}

void AlertTypes::ToListenFailedAlert(v8::Local<v8::Object> obj, libtorrent::listen_failed_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("address").ToLocalChecked(), Nan::New(alert->address.to_string()).ToLocalChecked());
    obj->Set(Nan::New("listen_interface").ToLocalChecked(), Nan::New(alert->listen_interface()).ToLocalChecked());
    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation));
    obj->Set(Nan::New("port").ToLocalChecked(), Nan::New(alert->port));
    obj->Set(Nan::New("sock_type").ToLocalChecked(), Nan::New(alert->sock_type));
}

void AlertTypes::ToListenSucceededAlert(v8::Local<v8::Object> obj, libtorrent::listen_succeeded_alert* alert)
{
    obj->Set(Nan::New("address").ToLocalChecked(), Nan::New(alert->address.to_string()).ToLocalChecked());
    obj->Set(Nan::New("port").ToLocalChecked(), Nan::New(alert->port));
    obj->Set(Nan::New("sock_type").ToLocalChecked(), Nan::New(alert->sock_type));
}

void AlertTypes::ToPortmapErrorAlert(v8::Local<v8::Object> obj, libtorrent::portmap_error_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("map_type").ToLocalChecked(), Nan::New(alert->map_type));
    obj->Set(Nan::New("mapping").ToLocalChecked(), Nan::New(alert->mapping));
}

void AlertTypes::ToPortmapAlert(v8::Local<v8::Object> obj, libtorrent::portmap_alert* alert)
{
    obj->Set(Nan::New("external_port").ToLocalChecked(), Nan::New(alert->external_port));
    obj->Set(Nan::New("map_type").ToLocalChecked(), Nan::New(alert->map_type));
    obj->Set(Nan::New("mapping").ToLocalChecked(), Nan::New(alert->mapping));
    obj->Set(Nan::New("protocol").ToLocalChecked(), Nan::New(alert->protocol));
}

void AlertTypes::ToPortmapLogAlert(v8::Local<v8::Object> obj, libtorrent::portmap_log_alert* alert)
{
    obj->Set(Nan::New("log_message").ToLocalChecked(), Nan::New(alert->log_message()).ToLocalChecked());
    obj->Set(Nan::New("map_type").ToLocalChecked(), Nan::New(alert->map_type));
}

void AlertTypes::ToFastresumeRejectedAlert(v8::Local<v8::Object> obj, libtorrent::fastresume_rejected_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("file_path").ToLocalChecked(), Nan::New(alert->file_path()).ToLocalChecked());
    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation).ToLocalChecked());
}

void AlertTypes::ToPeerBlockedAlert(v8::Local<v8::Object> obj, libtorrent::peer_blocked_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("reason").ToLocalChecked(), Nan::New(alert->reason));
}

void AlertTypes::ToDhtAnnounceAlert(v8::Local<v8::Object> obj, libtorrent::dht_announce_alert* alert)
{
    std::stringstream ss;
    ss << alert->info_hash;

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
    obj->Set(Nan::New("ip").ToLocalChecked(), Nan::New(alert->ip.to_string()).ToLocalChecked());
    obj->Set(Nan::New("port").ToLocalChecked(), Nan::New(alert->port));
}

void AlertTypes::ToDhtGetPeersAlert(v8::Local<v8::Object> obj, libtorrent::dht_get_peers_alert* alert)
{
    std::stringstream ss;
    ss << alert->info_hash;
    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
}

void AlertTypes::ToStatsAlert(v8::Local<v8::Object> obj, libtorrent::stats_alert* alert)
{
    ToTorrentAlert(obj, alert);

    v8::Local<v8::Object> channels = Nan::New<v8::Object>();
    channels->Set(Nan::New("download_ip_protocol").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::download_ip_protocol]));
    channels->Set(Nan::New("download_payload").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::download_payload]));
    channels->Set(Nan::New("download_protocol").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::download_protocol]));
    channels->Set(Nan::New("upload_ip_protocol").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::upload_ip_protocol]));
    channels->Set(Nan::New("upload_payload").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::upload_payload]));
    channels->Set(Nan::New("upload_protocol").ToLocalChecked(), Nan::New(alert->transferred[libtorrent::stats_alert::stats_channel::upload_protocol]));

    obj->Set(Nan::New("transferred").ToLocalChecked(), channels);
    obj->Set(Nan::New("interval").ToLocalChecked(), Nan::New(alert->interval));
}

void AlertTypes::ToCacheFlushedAlert(v8::Local<v8::Object> obj, libtorrent::cache_flushed_alert* alert)
{
    ToTorrentAlert(obj, alert);
}

void AlertTypes::ToAnonymousModeAlert(v8::Local<v8::Object> obj, libtorrent::anonymous_mode_alert* alert)
{
    ToTorrentAlert(obj, alert);

    obj->Set(Nan::New("kind").ToLocalChecked(), Nan::New(alert->kind));
    obj->Set(Nan::New("str").ToLocalChecked(), Nan::New(alert->str).ToLocalChecked());
}

void AlertTypes::ToLsdPeerAlert(v8::Local<v8::Object> obj, libtorrent::lsd_peer_alert* alert)
{
    ToPeerAlert(obj, alert);
}

void AlertTypes::ToTrackeridAlert(v8::Local<v8::Object> obj, libtorrent::trackerid_alert* alert)
{
    ToTrackerAlert(obj, alert);
    obj->Set(Nan::New("tracker_id").ToLocalChecked(), Nan::New(alert->tracker_id()).ToLocalChecked());
}

void AlertTypes::ToDhtBootstrapAlert(v8::Local<v8::Object> obj, libtorrent::dht_bootstrap_alert* alert)
{
}

void AlertTypes::ToTorrentErrorAlert(v8::Local<v8::Object> obj, libtorrent::torrent_error_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("filename").ToLocalChecked(), Nan::New(alert->filename()).ToLocalChecked());
}

void AlertTypes::ToTorrentNeedCertAlert(v8::Local<v8::Object> obj, libtorrent::torrent_need_cert_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToIncomingConnectionAlert(v8::Local<v8::Object> obj, libtorrent::incoming_connection_alert* alert)
{
    v8::Local<v8::Array> endpoint = Nan::New<v8::Array>(2);
    endpoint->Set(0, Nan::New(alert->ip.address().to_string()).ToLocalChecked());
    endpoint->Set(1, Nan::New(alert->ip.port()));

    obj->Set(Nan::New("ip").ToLocalChecked(), endpoint);
    obj->Set(Nan::New("socket_type").ToLocalChecked(), Nan::New(alert->socket_type));
}

void AlertTypes::ToAddTorrentAlert(v8::Local<v8::Object> obj, libtorrent::add_torrent_alert* alert)
{
    ToTorrentAlert(obj, alert);

    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("params").ToLocalChecked(), AddTorrentParams::ToObject(alert->params));
}

void AlertTypes::ToStateUpdateAlert(v8::Local<v8::Object> obj, libtorrent::state_update_alert* alert)
{
    v8::Local<v8::Array> status = Nan::New<v8::Array>(static_cast<int>(alert->status.size()));

    for (uint32_t i = 0; i < status->Length(); i++)
    {
        libtorrent::torrent_status st = alert->status.at(i);
        status->Set(i, TorrentStatus::CreateObject(st));
    }

    obj->Set(Nan::New("status").ToLocalChecked(), status);
}

void AlertTypes::ToMmapCacheAlert(v8::Local<v8::Object> obj, libtorrent::mmap_cache_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToSessionStatsAlert(v8::Local<v8::Object> obj, libtorrent::session_stats_alert* alert)
{
    // TODO
}

void AlertTypes::ToDhtErrorAlert(v8::Local<v8::Object> obj, libtorrent::dht_error_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }

    obj->Set(Nan::New("operation").ToLocalChecked(), Nan::New(alert->operation));
}

void AlertTypes::ToDhtImmutableItemAlert(v8::Local<v8::Object> obj, libtorrent::dht_immutable_item_alert* alert)
{
    std::stringstream ss;
    ss << alert->target;

    obj->Set(Nan::New("target").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
    // TODO item
}

void AlertTypes::ToDhtMutableItemAlert(v8::Local<v8::Object> obj, libtorrent::dht_mutable_item_alert* alert)
{
    // TODO
}

void AlertTypes::ToDhtPutAlert(v8::Local<v8::Object> obj, libtorrent::dht_put_alert* alert)
{
    // TODO
}

void AlertTypes::ToI2pAlert(v8::Local<v8::Object> obj, libtorrent::i2p_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToDhtOutgoingGetPeersAlert(v8::Local<v8::Object> obj, libtorrent::dht_outgoing_get_peers_alert* alert)
{
    std::stringstream info_hash;
    info_hash << alert->info_hash;

    std::stringstream obfuscated_info_hash;
    obfuscated_info_hash << alert->obfuscated_info_hash;

    // TODO ip

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(info_hash.str()).ToLocalChecked());
    obj->Set(Nan::New("obfuscated_info_hash").ToLocalChecked(), Nan::New(obfuscated_info_hash.str()).ToLocalChecked());
}

void AlertTypes::ToLogAlert(v8::Local<v8::Object> obj, libtorrent::log_alert* alert)
{
    obj->Set(Nan::New("msg").ToLocalChecked(), Nan::New(alert->msg()).ToLocalChecked());
}

void AlertTypes::ToTorrentLogAlert(v8::Local<v8::Object> obj, libtorrent::torrent_log_alert* alert)
{
    ToTorrentAlert(obj, alert);
    obj->Set(Nan::New("msg").ToLocalChecked(), Nan::New(alert->msg()).ToLocalChecked());
}

void AlertTypes::ToPeerLogAlert(v8::Local<v8::Object> obj, libtorrent::peer_log_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("direction").ToLocalChecked(), Nan::New(alert->direction));
    obj->Set(Nan::New("event_type").ToLocalChecked(), Nan::New(alert->event_type).ToLocalChecked());
    obj->Set(Nan::New("msg").ToLocalChecked(), Nan::New(alert->msg()).ToLocalChecked());
}

void AlertTypes::ToLsdErrorAlert(v8::Local<v8::Object> obj, libtorrent::lsd_error_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}

void AlertTypes::ToDhtStatsAlert(v8::Local<v8::Object> obj, libtorrent::dht_stats_alert* alert)
{
    v8::Local<v8::Array> active_requests = Nan::New<v8::Array>(static_cast<uint32_t>(alert->active_requests.size()));

    for (uint32_t i = 0; i < active_requests->Length(); i++)
    {
        libtorrent::dht_lookup& ar = alert->active_requests.at(i);

        v8::Local<v8::Object> req = Nan::New<v8::Object>();
        req->Set(Nan::New("type").ToLocalChecked(), Nan::New(ar.type).ToLocalChecked());
        req->Set(Nan::New("outstanding_requests").ToLocalChecked(), Nan::New(ar.outstanding_requests));
        req->Set(Nan::New("timeouts").ToLocalChecked(), Nan::New(ar.timeouts));
        req->Set(Nan::New("responses").ToLocalChecked(), Nan::New(ar.responses));
        req->Set(Nan::New("branch_factor").ToLocalChecked(), Nan::New(ar.branch_factor));
        req->Set(Nan::New("nodes_left").ToLocalChecked(), Nan::New(ar.nodes_left));
        req->Set(Nan::New("last_sent").ToLocalChecked(), Nan::New(ar.last_sent));
        req->Set(Nan::New("first_timeout").ToLocalChecked(), Nan::New(ar.first_timeout));

        std::stringstream ss;
        ss << ar.target;
        req->Set(Nan::New("target").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());

        active_requests->Set(i, req);
    }

    v8::Local<v8::Array> routing_table = Nan::New<v8::Array>(static_cast<uint32_t>(alert->routing_table.size()));

    for (uint32_t i = 0; i < routing_table->Length(); i++)
    {
        libtorrent::dht_routing_bucket& rb = alert->routing_table.at(i);

        v8::Local<v8::Object> buck = Nan::New<v8::Object>();
        buck->Set(Nan::New("num_nodes").ToLocalChecked(), Nan::New(rb.num_nodes));
        buck->Set(Nan::New("num_replacements").ToLocalChecked(), Nan::New(rb.num_replacements));
        buck->Set(Nan::New("last_active").ToLocalChecked(), Nan::New(rb.last_active));

        routing_table->Set(i, buck);
    }

    obj->Set(Nan::New("active_requests").ToLocalChecked(), active_requests);
    obj->Set(Nan::New("routing_table").ToLocalChecked(), routing_table);
}

void AlertTypes::ToIncomingRequestAlert(v8::Local<v8::Object> obj, libtorrent::incoming_request_alert* alert)
{
    ToPeerAlert(obj, alert);
    // TODO: req
}

void AlertTypes::ToDhtLogAlert(v8::Local<v8::Object> obj, libtorrent::dht_log_alert* alert)
{
    obj->Set(Nan::New("log_message").ToLocalChecked(), Nan::New(alert->log_message()).ToLocalChecked());
    obj->Set(Nan::New("module").ToLocalChecked(), Nan::New(alert->module));
}

void AlertTypes::ToDhtPktAlert(v8::Local<v8::Object> obj, libtorrent::dht_pkt_alert* alert)
{
    obj->Set(Nan::New("dir").ToLocalChecked(), Nan::New(alert->dir));
    // TODO
}

void AlertTypes::ToDhtGetPeersReplyAlert(v8::Local<v8::Object> obj, libtorrent::dht_get_peers_reply_alert* alert)
{
    std::stringstream ss;
    ss << alert->info_hash;

    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());
    obj->Set(Nan::New("num_peers").ToLocalChecked(), Nan::New(alert->num_peers()));
    // TODO: peers
}

void AlertTypes::ToDhtDirectResponseAlert(v8::Local<v8::Object> obj, libtorrent::dht_direct_response_alert* alert)
{
    // TODO
}

void AlertTypes::ToPickerLogAlert(v8::Local<v8::Object> obj, libtorrent::picker_log_alert* alert)
{
    ToPeerAlert(obj, alert);
    obj->Set(Nan::New("picker_flags").ToLocalChecked(), Nan::New(alert->picker_flags));
    // TODO: blocks
}

void AlertTypes::ToSessionErrorAlert(v8::Local<v8::Object> obj, libtorrent::session_error_alert* alert)
{
    if (alert->error)
    {
        v8::Local<v8::Object> err = Nan::New<v8::Object>();
        err->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->error.message()).ToLocalChecked());
        err->Set(Nan::New("value").ToLocalChecked(), Nan::New(alert->error.value()));
        obj->Set(Nan::New("error").ToLocalChecked(), err);
    }
}
