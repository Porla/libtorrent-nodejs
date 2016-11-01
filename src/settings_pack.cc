#include "settings_pack.h"

#include <libtorrent/settings_pack.hpp>

#if defined(__APPLE__) && __cplusplus <= 201103
    #include "_aux/std_make_unique.h"
#endif

#define PORLA_ENUM_SET_BOOL(obj, member) \
    obj->Set(Nan::New(#member).ToLocalChecked(), Nan::New(libtorrent::settings_pack::bool_types::member));

#define PORLA_ENUM_SET_INT(obj, member) \
    obj->Set(Nan::New(#member).ToLocalChecked(), Nan::New(libtorrent::settings_pack::int_types::member));

#define PORLA_ENUM_SET_STR(obj, member) \
    obj->Set(Nan::New(#member).ToLocalChecked(), Nan::New(libtorrent::settings_pack::string_types::member));

using lt::SettingsPack;

Nan::Persistent<v8::Function> SettingsPack::constructor;

SettingsPack::SettingsPack(std::unique_ptr<libtorrent::settings_pack> sp)
    : sp_(std::move(sp))
{
}

SettingsPack::~SettingsPack()
{
}

libtorrent::settings_pack& SettingsPack::GetWrapped()
{
    return *sp_.get();
}

NAN_MODULE_INIT(SettingsPack::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("settings_pack").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "get_bool", GetBool);
    Nan::SetPrototypeMethod(tpl, "get_int", GetInt);
    Nan::SetPrototypeMethod(tpl, "get_str", GetStr);
    Nan::SetPrototypeMethod(tpl, "set_bool", SetBool);
    Nan::SetPrototypeMethod(tpl, "set_int", SetInt);
    Nan::SetPrototypeMethod(tpl, "set_str", SetStr);

    v8::Local<v8::Object> bool_types = Nan::New<v8::Object>();
    PORLA_ENUM_SET_BOOL(bool_types, allow_i2p_mixed);
    PORLA_ENUM_SET_BOOL(bool_types, allow_multiple_connections_per_ip);
    PORLA_ENUM_SET_BOOL(bool_types, allow_partial_disk_writes);
    PORLA_ENUM_SET_BOOL(bool_types, always_send_user_agent);
    PORLA_ENUM_SET_BOOL(bool_types, announce_crypto_support);
    PORLA_ENUM_SET_BOOL(bool_types, announce_to_all_tiers);
    PORLA_ENUM_SET_BOOL(bool_types, announce_to_all_trackers);
    PORLA_ENUM_SET_BOOL(bool_types, anonymous_mode);
    PORLA_ENUM_SET_BOOL(bool_types, apply_ip_filter_to_trackers);
    PORLA_ENUM_SET_BOOL(bool_types, auto_manage_prefer_seeds);
    PORLA_ENUM_SET_BOOL(bool_types, auto_sequential);
    PORLA_ENUM_SET_BOOL(bool_types, ban_web_seeds);
    PORLA_ENUM_SET_BOOL(bool_types, broadcast_lsd);
    PORLA_ENUM_SET_BOOL(bool_types, close_redundant_connections);
    PORLA_ENUM_SET_BOOL(bool_types, coalesce_reads);
    PORLA_ENUM_SET_BOOL(bool_types, coalesce_writes);
    PORLA_ENUM_SET_BOOL(bool_types, disable_hash_checks);
    PORLA_ENUM_SET_BOOL(bool_types, dont_count_slow_torrents);
    PORLA_ENUM_SET_BOOL(bool_types, dont_flush_write_cache);
    PORLA_ENUM_SET_BOOL(bool_types, enable_dht);
    PORLA_ENUM_SET_BOOL(bool_types, enable_incoming_tcp);
    PORLA_ENUM_SET_BOOL(bool_types, enable_incoming_utp);
    PORLA_ENUM_SET_BOOL(bool_types, enable_lsd);
    PORLA_ENUM_SET_BOOL(bool_types, enable_natpmp);
    PORLA_ENUM_SET_BOOL(bool_types, enable_outgoing_tcp);
    PORLA_ENUM_SET_BOOL(bool_types, enable_outgoing_utp);
    PORLA_ENUM_SET_BOOL(bool_types, enable_upnp);
    PORLA_ENUM_SET_BOOL(bool_types, force_proxy);
    PORLA_ENUM_SET_BOOL(bool_types, incoming_starts_queued_torrents);
    PORLA_ENUM_SET_BOOL(bool_types, listen_system_port_fallback);
    PORLA_ENUM_SET_BOOL(bool_types, lock_files);
    PORLA_ENUM_SET_BOOL(bool_types, no_atime_storage);
    PORLA_ENUM_SET_BOOL(bool_types, no_connect_privileged_ports);
    PORLA_ENUM_SET_BOOL(bool_types, no_recheck_incomplete_resume);
    PORLA_ENUM_SET_BOOL(bool_types, prefer_rc4);
    PORLA_ENUM_SET_BOOL(bool_types, prefer_udp_trackers);
    PORLA_ENUM_SET_BOOL(bool_types, prioritize_partial_pieces);
    PORLA_ENUM_SET_BOOL(bool_types, proxy_hostnames);
    PORLA_ENUM_SET_BOOL(bool_types, proxy_peer_connections);
    PORLA_ENUM_SET_BOOL(bool_types, proxy_tracker_connections);
    PORLA_ENUM_SET_BOOL(bool_types, rate_limit_ip_overhead);
    PORLA_ENUM_SET_BOOL(bool_types, report_redundant_bytes);
    PORLA_ENUM_SET_BOOL(bool_types, report_true_downloaded);
    PORLA_ENUM_SET_BOOL(bool_types, report_web_seed_downloads);
    PORLA_ENUM_SET_BOOL(bool_types, seeding_outgoing_connections);
    PORLA_ENUM_SET_BOOL(bool_types, send_redundant_have);
    PORLA_ENUM_SET_BOOL(bool_types, smooth_connects);
    PORLA_ENUM_SET_BOOL(bool_types, strict_end_game_mode);
    PORLA_ENUM_SET_BOOL(bool_types, strict_super_seeding);
    PORLA_ENUM_SET_BOOL(bool_types, support_merkle_torrents);
    PORLA_ENUM_SET_BOOL(bool_types, support_share_mode);
    PORLA_ENUM_SET_BOOL(bool_types, upnp_ignore_nonrouters);
    PORLA_ENUM_SET_BOOL(bool_types, use_dht_as_fallback);
    PORLA_ENUM_SET_BOOL(bool_types, use_disk_cache_pool);
    PORLA_ENUM_SET_BOOL(bool_types, use_parole_mode);
    PORLA_ENUM_SET_BOOL(bool_types, use_read_cache);
    PORLA_ENUM_SET_BOOL(bool_types, volatile_read_cache);
    Nan::GetFunction(tpl).ToLocalChecked()->Set(Nan::New("bool_types").ToLocalChecked(), bool_types);

    v8::Local<v8::Object> int_types = Nan::New<v8::Object>();
    PORLA_ENUM_SET_INT(int_types, active_checking);
    PORLA_ENUM_SET_INT(int_types, active_dht_limit);
    PORLA_ENUM_SET_INT(int_types, active_downloads);
    PORLA_ENUM_SET_INT(int_types, active_limit);
    PORLA_ENUM_SET_INT(int_types, active_loaded_limit);
    PORLA_ENUM_SET_INT(int_types, active_lsd_limit);
    PORLA_ENUM_SET_INT(int_types, active_seeds);
    PORLA_ENUM_SET_INT(int_types, active_tracker_limit);
    PORLA_ENUM_SET_INT(int_types, aio_max);
    PORLA_ENUM_SET_INT(int_types, aio_threads);
    PORLA_ENUM_SET_INT(int_types, alert_mask);
    PORLA_ENUM_SET_INT(int_types, alert_queue_size);
    PORLA_ENUM_SET_INT(int_types, allowed_enc_level);
    PORLA_ENUM_SET_INT(int_types, allowed_fast_set_size);
    PORLA_ENUM_SET_INT(int_types, auto_manage_interval);
    PORLA_ENUM_SET_INT(int_types, auto_manage_startup);
    PORLA_ENUM_SET_INT(int_types, auto_scrape_interval);
    PORLA_ENUM_SET_INT(int_types, auto_scrape_min_interval);
    PORLA_ENUM_SET_INT(int_types, cache_buffer_chunk_size);
    PORLA_ENUM_SET_INT(int_types, cache_expiry);
    PORLA_ENUM_SET_INT(int_types, cache_size);
    PORLA_ENUM_SET_INT(int_types, cache_size_volatile);
    PORLA_ENUM_SET_INT(int_types, checking_mem_usage);
    PORLA_ENUM_SET_INT(int_types, choking_algorithm);
    PORLA_ENUM_SET_INT(int_types, connections_limit);
    PORLA_ENUM_SET_INT(int_types, connections_slack);
    PORLA_ENUM_SET_INT(int_types, connection_speed);
    PORLA_ENUM_SET_INT(int_types, connect_seed_every_n_download);
    PORLA_ENUM_SET_INT(int_types, decrease_est_reciprocation_rate);
    PORLA_ENUM_SET_INT(int_types, default_est_reciprocation_rate);
    PORLA_ENUM_SET_INT(int_types, dht_announce_interval);
    PORLA_ENUM_SET_INT(int_types, disk_io_read_mode);
    PORLA_ENUM_SET_INT(int_types, disk_io_write_mode);
    PORLA_ENUM_SET_INT(int_types, download_rate_limit);
    PORLA_ENUM_SET_INT(int_types, file_checks_delay_per_block);
    PORLA_ENUM_SET_INT(int_types, file_pool_size);
    PORLA_ENUM_SET_INT(int_types, handshake_timeout);
    PORLA_ENUM_SET_INT(int_types, i2p_port);
    PORLA_ENUM_SET_INT(int_types, inactive_down_rate);
    PORLA_ENUM_SET_INT(int_types, inactive_up_rate);
    PORLA_ENUM_SET_INT(int_types, inactivity_timeout);
    PORLA_ENUM_SET_INT(int_types, increase_est_reciprocation_rate);
    PORLA_ENUM_SET_INT(int_types, initial_picker_threshold);
    PORLA_ENUM_SET_INT(int_types, in_enc_policy);
    PORLA_ENUM_SET_INT(int_types, listen_queue_size);
    PORLA_ENUM_SET_INT(int_types, local_service_announce_interval);
    PORLA_ENUM_SET_INT(int_types, max_allowed_in_request_queue);
    PORLA_ENUM_SET_INT(int_types, max_failcount);
    PORLA_ENUM_SET_INT(int_types, max_http_recv_buffer_size);
    PORLA_ENUM_SET_INT(int_types, max_metadata_size);
    PORLA_ENUM_SET_INT(int_types, max_out_request_queue);
    PORLA_ENUM_SET_INT(int_types, max_paused_peerlist_size);
    PORLA_ENUM_SET_INT(int_types, max_peerlist_size);
    PORLA_ENUM_SET_INT(int_types, max_peer_recv_buffer_size);
    PORLA_ENUM_SET_INT(int_types, max_pex_peers);
    PORLA_ENUM_SET_INT(int_types, max_queued_disk_bytes);
    PORLA_ENUM_SET_INT(int_types, max_rejects);
    PORLA_ENUM_SET_INT(int_types, max_retry_port_bind);
    PORLA_ENUM_SET_INT(int_types, max_suggest_pieces);
    PORLA_ENUM_SET_INT(int_types, min_announce_interval);
    PORLA_ENUM_SET_INT(int_types, min_reconnect_time);
    PORLA_ENUM_SET_INT(int_types, mixed_mode_algorithm);
    PORLA_ENUM_SET_INT(int_types, network_threads);
    PORLA_ENUM_SET_INT(int_types, num_optimistic_unchoke_slots);
    PORLA_ENUM_SET_INT(int_types, num_outgoing_ports);
    PORLA_ENUM_SET_INT(int_types, num_want);
    PORLA_ENUM_SET_INT(int_types, optimistic_disk_retry);
    PORLA_ENUM_SET_INT(int_types, optimistic_unchoke_interval);
    PORLA_ENUM_SET_INT(int_types, outgoing_port);
    PORLA_ENUM_SET_INT(int_types, out_enc_policy);
    PORLA_ENUM_SET_INT(int_types, peer_connect_timeout);
    PORLA_ENUM_SET_INT(int_types, peer_timeout);
    PORLA_ENUM_SET_INT(int_types, peer_tos);
    PORLA_ENUM_SET_INT(int_types, peer_turnover);
    PORLA_ENUM_SET_INT(int_types, peer_turnover_cutoff);
    PORLA_ENUM_SET_INT(int_types, peer_turnover_interval);
    PORLA_ENUM_SET_INT(int_types, piece_timeout);
    PORLA_ENUM_SET_INT(int_types, predictive_piece_announce);
    PORLA_ENUM_SET_INT(int_types, proxy_port);
    PORLA_ENUM_SET_INT(int_types, proxy_type);
    PORLA_ENUM_SET_INT(int_types, read_cache_line_size);
    PORLA_ENUM_SET_INT(int_types, recv_socket_buffer_size);
    PORLA_ENUM_SET_INT(int_types, request_queue_time);
    PORLA_ENUM_SET_INT(int_types, request_timeout);
    PORLA_ENUM_SET_INT(int_types, seeding_piece_quota);
    PORLA_ENUM_SET_INT(int_types, seed_choking_algorithm);
    PORLA_ENUM_SET_INT(int_types, seed_time_limit);
    PORLA_ENUM_SET_INT(int_types, seed_time_ratio_limit);
    PORLA_ENUM_SET_INT(int_types, send_buffer_low_watermark);
    PORLA_ENUM_SET_INT(int_types, send_buffer_watermark);
    PORLA_ENUM_SET_INT(int_types, send_buffer_watermark_factor);
    PORLA_ENUM_SET_INT(int_types, send_socket_buffer_size);
    PORLA_ENUM_SET_INT(int_types, share_mode_target);
    PORLA_ENUM_SET_INT(int_types, share_ratio_limit);
    PORLA_ENUM_SET_INT(int_types, stop_tracker_timeout);
    PORLA_ENUM_SET_INT(int_types, suggest_mode);
    PORLA_ENUM_SET_INT(int_types, tick_interval);
    PORLA_ENUM_SET_INT(int_types, torrent_connect_boost);
    PORLA_ENUM_SET_INT(int_types, tracker_backoff);
    PORLA_ENUM_SET_INT(int_types, tracker_completion_timeout);
    PORLA_ENUM_SET_INT(int_types, tracker_maximum_response_length);
    PORLA_ENUM_SET_INT(int_types, tracker_receive_timeout);
    PORLA_ENUM_SET_INT(int_types, udp_tracker_token_expiry);
    PORLA_ENUM_SET_INT(int_types, unchoke_interval);
    PORLA_ENUM_SET_INT(int_types, unchoke_slots_limit);
    PORLA_ENUM_SET_INT(int_types, upload_rate_limit);
    PORLA_ENUM_SET_INT(int_types, urlseed_pipeline_size);
    PORLA_ENUM_SET_INT(int_types, urlseed_timeout);
    PORLA_ENUM_SET_INT(int_types, urlseed_wait_retry);
    PORLA_ENUM_SET_INT(int_types, utp_connect_timeout);
    PORLA_ENUM_SET_INT(int_types, utp_fin_resends);
    PORLA_ENUM_SET_INT(int_types, utp_gain_factor);
    PORLA_ENUM_SET_INT(int_types, utp_loss_multiplier);
    PORLA_ENUM_SET_INT(int_types, utp_min_timeout);
    PORLA_ENUM_SET_INT(int_types, utp_num_resends);
    PORLA_ENUM_SET_INT(int_types, utp_syn_resends);
    PORLA_ENUM_SET_INT(int_types, utp_target_delay);
    PORLA_ENUM_SET_INT(int_types, whole_pieces_threshold);
    PORLA_ENUM_SET_INT(int_types, write_cache_line_size);
    Nan::GetFunction(tpl).ToLocalChecked()->Set(Nan::New("int_types").ToLocalChecked(), int_types);

    v8::Local<v8::Object> str_types = Nan::New<v8::Object>();
    PORLA_ENUM_SET_STR(str_types, announce_ip);
    PORLA_ENUM_SET_STR(str_types, dht_bootstrap_nodes);
    PORLA_ENUM_SET_STR(str_types, handshake_client_version);
    PORLA_ENUM_SET_STR(str_types, i2p_hostname);
    PORLA_ENUM_SET_STR(str_types, listen_interfaces);
    PORLA_ENUM_SET_STR(str_types, mmap_cache);
    PORLA_ENUM_SET_STR(str_types, outgoing_interfaces);
    PORLA_ENUM_SET_STR(str_types, peer_fingerprint);
    PORLA_ENUM_SET_STR(str_types, proxy_hostname);
    PORLA_ENUM_SET_STR(str_types, proxy_password);
    PORLA_ENUM_SET_STR(str_types, proxy_username);
    PORLA_ENUM_SET_STR(str_types, user_agent);
    Nan::GetFunction(tpl).ToLocalChecked()->Set(Nan::New("str_types").ToLocalChecked(), str_types);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("settings_pack").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SettingsPack::New)
{
    if (info.IsConstructCall())
    {
        SettingsPack* obj = nullptr;

        if (info.Length() > 0 && info[0]->IsExternal())
        {
            libtorrent::settings_pack* sp = static_cast<libtorrent::settings_pack*>(info[0].As<v8::External>()->Value());
            obj = new SettingsPack(std::make_unique<libtorrent::settings_pack>(*sp));
        }
        else
        {
            obj = new SettingsPack(std::make_unique<libtorrent::settings_pack>());
        }

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}

NAN_METHOD(SettingsPack::GetBool)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::bool_types>(info[0]->Int32Value());
    info.GetReturnValue().Set(Nan::New(obj->sp_->get_bool(name)));
}

NAN_METHOD(SettingsPack::GetInt)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::int_types>(info[0]->Int32Value());
    info.GetReturnValue().Set(Nan::New(obj->sp_->get_int(name)));
}

NAN_METHOD(SettingsPack::GetStr)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::string_types>(info[0]->Int32Value());
    info.GetReturnValue().Set(Nan::New(obj->sp_->get_str(name)).ToLocalChecked());
}

v8::Local<v8::Object> SettingsPack::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(SettingsPack::SetBool)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::bool_types>(info[0]->Int32Value());
    bool value = info[1]->BooleanValue();
    obj->sp_->set_bool(name, value);
}

NAN_METHOD(SettingsPack::SetInt)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::bool_types>(info[0]->Int32Value());
    int value = info[1]->Int32Value();
    obj->sp_->set_int(name, value);
}

NAN_METHOD(SettingsPack::SetStr)
{
    SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.This());
    int name = static_cast<libtorrent::settings_pack::string_types>(info[0]->Int32Value());
    std::string value = *Nan::Utf8String(info[1]);
    obj->sp_->set_str(name, value);
}
