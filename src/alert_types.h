#ifndef ALERTTYPES_H
#define ALERTTYPES_H

#include <nan.h>

namespace libtorrent
{
    class alert;
    struct torrent_alert;
    struct peer_alert;
    struct tracker_alert;
    struct torrent_added_alert;
    struct torrent_removed_alert;
    struct read_piece_alert;
    struct file_completed_alert;
    struct file_renamed_alert;
    struct file_rename_failed_alert;
    struct performance_alert;
    struct state_changed_alert;
    struct tracker_error_alert;
    struct tracker_warning_alert;
    struct scrape_reply_alert;
    struct scrape_failed_alert;
    struct tracker_reply_alert;
    struct dht_reply_alert;
    struct tracker_announce_alert;
    struct hash_failed_alert;
    struct peer_ban_alert;
    struct peer_unsnubbed_alert;
    struct peer_snubbed_alert;
    struct peer_error_alert;
    struct peer_connect_alert;
    struct peer_disconnected_alert;
    struct invalid_request_alert;
    struct torrent_finished_alert;
    struct piece_finished_alert;
    struct request_dropped_alert;
    struct block_timeout_alert;
    struct block_finished_alert;
    struct block_downloading_alert;
    struct unwanted_block_alert;
    struct storage_moved_alert;
    struct storage_moved_failed_alert;
    struct torrent_deleted_alert;
    struct torrent_delete_failed_alert;
    struct save_resume_data_alert;
    struct save_resume_data_failed_alert;
    struct torrent_paused_alert;
    struct torrent_resumed_alert;
    struct torrent_checked_alert;
    struct url_seed_alert;
    struct file_error_alert;
    struct metadata_failed_alert;
    struct metadata_received_alert;
    struct udp_error_alert;
    struct external_ip_alert;
    struct listen_failed_alert;
    struct listen_succeeded_alert;
    struct portmap_error_alert;
    struct portmap_alert;
    struct portmap_log_alert;
    struct fastresume_rejected_alert;
    struct peer_blocked_alert;
    struct dht_announce_alert;
    struct dht_get_peers_alert;
    struct stats_alert;
    struct cache_flushed_alert;
    struct anonymous_mode_alert;
    struct lsd_peer_alert;
    struct trackerid_alert;
    struct dht_bootstrap_alert;
    struct torrent_error_alert;
    struct torrent_need_cert_alert;
    struct incoming_connection_alert;
    struct add_torrent_alert;
    struct state_update_alert;
    struct mmap_cache_alert;
    struct session_stats_alert;
}

namespace lt
{
    class AlertTypes
    {
    public:
        static v8::Local<v8::Object> ToObject(libtorrent::alert* alert);

    private:
        static void ToTorrentAlert(v8::Local<v8::Object> obj, libtorrent::torrent_alert* alert);
        static void ToPeerAlert(v8::Local<v8::Object> obj, libtorrent::peer_alert* alert);
        static void ToTrackerAlert(v8::Local<v8::Object> obj, libtorrent::tracker_alert* alert);
        static void ToTorrentAddedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_added_alert* alert);
        static void ToTorrentRemovedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_removed_alert* alert);
        static void ToReadPieceAlert(v8::Local<v8::Object> obj, libtorrent::read_piece_alert* alert);
        static void ToFileCompletedAlert(v8::Local<v8::Object> obj, libtorrent::file_completed_alert* alert);
        static void ToFileRenamedAlert(v8::Local<v8::Object> obj, libtorrent::file_renamed_alert* alert);
        static void ToFileRenameFailedAlert(v8::Local<v8::Object> obj, libtorrent::file_rename_failed_alert* alert);
        static void ToPerformanceAlert(v8::Local<v8::Object> obj, libtorrent::performance_alert* alert);
        static void ToStateChangedAlert(v8::Local<v8::Object> obj, libtorrent::state_changed_alert* alert);
        static void ToTrackerErrorAlert(v8::Local<v8::Object> obj, libtorrent::tracker_error_alert* alert);
        static void ToTrackerWarningAlert(v8::Local<v8::Object> obj, libtorrent::tracker_warning_alert* alert);
        static void ToScrapeReplyAlert(v8::Local<v8::Object> obj, libtorrent::scrape_reply_alert* alert);
        static void ToScrapeFailedAlert(v8::Local<v8::Object> obj, libtorrent::scrape_failed_alert* alert);
        static void ToTrackerReplyAlert(v8::Local<v8::Object> obj, libtorrent::tracker_reply_alert* alert);
        static void ToDhtReplyAlert(v8::Local<v8::Object> obj, libtorrent::dht_reply_alert* alert);
        static void ToTrackerAnnounceAlert(v8::Local<v8::Object> obj, libtorrent::tracker_announce_alert* alert);
        static void ToHashFailedAlert(v8::Local<v8::Object> obj, libtorrent::hash_failed_alert* alert);
        static void ToPeerBanAlert(v8::Local<v8::Object> obj, libtorrent::peer_ban_alert* alert);
        static void ToPeerUnsnubbedAlert(v8::Local<v8::Object> obj, libtorrent::peer_unsnubbed_alert* alert);
        static void ToPeerSnubbedAlert(v8::Local<v8::Object> obj, libtorrent::peer_snubbed_alert* alert);
        static void ToPeerErrorAlert(v8::Local<v8::Object> obj, libtorrent::peer_error_alert* alert);
        static void ToPeerConnectAlert(v8::Local<v8::Object> obj, libtorrent::peer_connect_alert* alert);
        static void ToPeerDisconnectedAlert(v8::Local<v8::Object> obj, libtorrent::peer_disconnected_alert* alert);
        static void ToInvalidRequestAlert(v8::Local<v8::Object> obj, libtorrent::invalid_request_alert* alert);
        static void ToTorrentFinishedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_finished_alert* alert);
        static void ToPieceFinishedAlert(v8::Local<v8::Object> obj, libtorrent::piece_finished_alert* alert);
        static void ToRequestDroppedAlert(v8::Local<v8::Object> obj, libtorrent::request_dropped_alert* alert);
        static void ToBlockTimeoutAlert(v8::Local<v8::Object> obj, libtorrent::block_timeout_alert* alert);
        static void ToBlockFinishedAlert(v8::Local<v8::Object> obj, libtorrent::block_finished_alert* alert);
        static void ToBlockDownloadingAlert(v8::Local<v8::Object> obj, libtorrent::block_downloading_alert* alert);
        static void ToUnwantedBlockAlert(v8::Local<v8::Object> obj, libtorrent::unwanted_block_alert* alert);
        static void ToStorageMovedAlert(v8::Local<v8::Object> obj, libtorrent::storage_moved_alert* alert);
        static void ToStorageMovedFailedAlert(v8::Local<v8::Object> obj, libtorrent::storage_moved_failed_alert* alert);
        static void ToTorrentDeletedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_deleted_alert* alert);
        static void ToTorrentDeleteFailedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_delete_failed_alert* alert);
        static void ToSaveResumeDataAlert(v8::Local<v8::Object> obj, libtorrent::save_resume_data_alert* alert);
        static void ToSaveResumeDataFailedAlert(v8::Local<v8::Object> obj, libtorrent::save_resume_data_failed_alert* alert);
        static void ToTorrentPausedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_paused_alert* alert);
        static void ToTorrentResumedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_resumed_alert* alert);
        static void ToTorrentCheckedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_checked_alert* alert);
        static void ToUrlSeedAlert(v8::Local<v8::Object> obj, libtorrent::url_seed_alert* alert);
        static void ToFileErrorAlert(v8::Local<v8::Object> obj, libtorrent::file_error_alert* alert);
        static void ToMetadataFailedAlert(v8::Local<v8::Object> obj, libtorrent::metadata_failed_alert* alert);
        static void ToMetadataReceivedAlert(v8::Local<v8::Object> obj, libtorrent::metadata_received_alert* alert);
        static void ToUdpErrorAlert(v8::Local<v8::Object> obj, libtorrent::udp_error_alert* alert);
        static void ToExternalIpAlert(v8::Local<v8::Object> obj, libtorrent::external_ip_alert* alert);
        static void ToListenFailedAlert(v8::Local<v8::Object> obj, libtorrent::listen_failed_alert* alert);
        static void ToListenSucceededAlert(v8::Local<v8::Object> obj, libtorrent::listen_succeeded_alert* alert);
        static void ToPortmapErrorAlert(v8::Local<v8::Object> obj, libtorrent::portmap_error_alert* alert);
        static void ToPortmapAlert(v8::Local<v8::Object> obj, libtorrent::portmap_alert* alert);
        static void ToPortmapLogAlert(v8::Local<v8::Object> obj, libtorrent::portmap_log_alert* alert);
        static void ToFastresumeRejectedAlert(v8::Local<v8::Object> obj, libtorrent::fastresume_rejected_alert* alert);
        static void ToPeerBlockedAlert(v8::Local<v8::Object> obj, libtorrent::peer_blocked_alert* alert);
        static void ToDhtAnnounceAlert(v8::Local<v8::Object> obj, libtorrent::dht_announce_alert* alert);
        static void ToDhtGetPeersAlert(v8::Local<v8::Object> obj, libtorrent::dht_get_peers_alert* alert);
        static void ToStatsAlert(v8::Local<v8::Object> obj, libtorrent::stats_alert* alert);
        static void ToCacheFlushedAlert(v8::Local<v8::Object> obj, libtorrent::cache_flushed_alert* alert);
        static void ToAnonymousModeAlert(v8::Local<v8::Object> obj, libtorrent::anonymous_mode_alert* alert);
        static void ToLsdPeerAlert(v8::Local<v8::Object> obj, libtorrent::lsd_peer_alert* alert);
        static void ToTrackeridAlert(v8::Local<v8::Object> obj, libtorrent::trackerid_alert* alert);
        static void ToDhtBootstrapAlert(v8::Local<v8::Object> obj, libtorrent::dht_bootstrap_alert* alert);
        static void ToTorrentErrorAlert(v8::Local<v8::Object> obj, libtorrent::torrent_error_alert* alert);
        static void ToTorrentNeedCertAlert(v8::Local<v8::Object> obj, libtorrent::torrent_need_cert_alert* alert);
        static void ToIncomingConnectionAlert(v8::Local<v8::Object> obj, libtorrent::incoming_connection_alert* alert);
        static void ToAddTorrentAlert(v8::Local<v8::Object> obj, libtorrent::add_torrent_alert* alert);
        static void ToStateUpdateAlert(v8::Local<v8::Object> obj, libtorrent::state_update_alert* alert);
        static void ToMmapCacheAlert(v8::Local<v8::Object> obj, libtorrent::mmap_cache_alert* alert);
        static void ToSessionStatsAlert(v8::Local<v8::Object> obj, libtorrent::session_stats_alert* alert);
    };
}

#endif
