#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/time.hpp>

#include "torrent_info.h"

using lt::AddTorrentParams;

libtorrent::add_torrent_params AddTorrentParams::FromObject(v8::Local<v8::Object> object)
{
    libtorrent::add_torrent_params params;

    auto active_time = Nan::New("active_time").ToLocalChecked();
    auto file_priorities = Nan::New("file_priorities").ToLocalChecked();
    auto flags = Nan::New("flags").ToLocalChecked();
    auto info_hash = Nan::New("info_hash").ToLocalChecked();
    auto max_connections = Nan::New("max_connections").ToLocalChecked();
    auto max_uploads = Nan::New("max_uploads").ToLocalChecked();
    auto save_path = Nan::New("save_path").ToLocalChecked();
    auto ti = Nan::New("ti").ToLocalChecked();

    if (object->Has(file_priorities) && object->Get(file_priorities)->IsArray())
    {
        v8::Local<v8::Array> arr = object->Get(file_priorities).As<v8::Array>();

        for (uint32_t i = 0; i < arr->Length(); i++)
        {
            params.file_priorities.push_back(static_cast<uint8_t>(arr->Get(i)->Int32Value()));
        }
    }

    if (object->Has(flags) && object->Get(flags)->IsInt32())
    {
        params.flags = static_cast<libtorrent::add_torrent_params::flags_t>(object->Get(flags)->Int32Value());
    }

    if (object->Has(active_time) && object->Get(active_time)->IsNumber())
    {
        params.active_time = object->Get(active_time)->ToNumber()->Int32Value();
    }

    if (object->Has(info_hash) && object->Get(info_hash)->IsString())
    {
        std::string ih = *Nan::Utf8String(object->Get(info_hash));
        params.info_hash = libtorrent::sha1_hash(ih);
    }

    if (object->Has(max_connections) && object->Get(max_connections)->IsInt32())
    {
        params.max_connections = object->Get(max_connections)->Int32Value();
    }

    if (object->Has(max_uploads) && object->Get(max_uploads)->IsInt32())
    {
        params.max_uploads = object->Get(max_uploads)->Int32Value();
    }

    if (object->Has(save_path) && object->Get(save_path)->IsString())
    {
        params.save_path = *Nan::Utf8String(object->Get(save_path)->ToString());
    }

    if (object->Has(ti) && object->Get(ti)->IsObject())
    {
        params.ti = Nan::ObjectWrap::Unwrap<TorrentInfo>(object->Get(ti)->ToObject())->GetWrapped();
    }

    return params;
}

v8::Local<v8::Object> AddTorrentParams::ToObject(libtorrent::add_torrent_params& params)
{
    Nan::EscapableHandleScope scope;
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    obj->Set(Nan::New("active_time").ToLocalChecked(), Nan::New(params.active_time));
    obj->Set(Nan::New("added_time").ToLocalChecked(), Nan::New(static_cast<double>(params.added_time)));

    if (params.banned_peers.size() > 0)
    {
        v8::Local<v8::Array> bp = Nan::New<v8::Array>(static_cast<int>(params.banned_peers.size()));
        int i = 0;

        for (auto& endpoint : params.banned_peers)
        {
            v8::Local<v8::Array> ep = Nan::New<v8::Array>(2);
            ep->Set(0, Nan::New(endpoint.address().to_string()).ToLocalChecked());
            ep->Set(1, Nan::New(endpoint.port()));

            bp->Set(i, ep);
            i += 1;
        }

        obj->Set(Nan::New("banned_peers").ToLocalChecked(), bp);
    }

    obj->Set(Nan::New("completed_time").ToLocalChecked(), Nan::New(static_cast<double>(params.completed_time)));

    if (params.dht_nodes.size() > 0)
    {
        v8::Local<v8::Array> dn = Nan::New<v8::Array>(static_cast<int>(params.dht_nodes.size()));
        int i = 0;

        for (auto& node : params.dht_nodes)
        {
            v8::Local<v8::Array> n = Nan::New<v8::Array>(2);
            n->Set(0, Nan::New(node.first).ToLocalChecked());
            n->Set(1, Nan::New(node.second));

            dn->Set(i, n);
            i += 1;
        }

        obj->Set(Nan::New("dht_nodes").ToLocalChecked(), dn);
    }

    obj->Set(Nan::New("download_limit").ToLocalChecked(), Nan::New(params.download_limit));
    // extensions - obj->Set(Nan::New("download_limit").ToLocalChecked(), Nan::New(params..extensions));

    if (params.file_priorities.size() > 0)
    {
        v8::Local<v8::Array> fp = Nan::New<v8::Array>(static_cast<int>(params.file_priorities.size()));
        int i = 0;

        for (auto prio : params.file_priorities)
        {
            fp->Set(i, Nan::New(prio));
            i += 1;
        }

        obj->Set(Nan::New("file_priorities").ToLocalChecked(), fp);
    }

    obj->Set(Nan::New("finished_time").ToLocalChecked(), Nan::New(params.finished_time));
    obj->Set(Nan::New("flags").ToLocalChecked(), Nan::New(static_cast<double>(params.flags)));
    // have_pieces - obj->Set(Nan::New("flags").ToLocalChecked(), Nan::New(static_cast<double>(params.have_pieces)));

    if (params.http_seeds.size() > 0)
    {
        v8::Local<v8::Array> hs = Nan::New<v8::Array>(static_cast<int>(params.http_seeds.size()));
        int i = 0;

        for (auto seed : params.http_seeds)
        {
            hs->Set(i, Nan::New(seed).ToLocalChecked());
            i += 1;
        }

        obj->Set(Nan::New("http_seeds").ToLocalChecked(), hs);
    }

    std::stringstream ss;
    ss << params.info_hash;
    obj->Set(Nan::New("info_hash").ToLocalChecked(), Nan::New(ss.str()).ToLocalChecked());

    obj->Set(Nan::New("last_seen_complete").ToLocalChecked(), Nan::New(static_cast<double>(params.last_seen_complete)));
    obj->Set(Nan::New("max_connections").ToLocalChecked(), Nan::New(params.max_connections));
    obj->Set(Nan::New("max_uploads").ToLocalChecked(), Nan::New(params.max_uploads));

    if (params.merkle_tree.size() > 0)
    {
        v8::Local<v8::Array> mt = Nan::New<v8::Array>(static_cast<int>(params.merkle_tree.size()));
        int i = 0;

        for (auto hash : params.merkle_tree)
        {
            std::stringstream hss;
            hss << hash;

            mt->Set(i, Nan::New(hss.str()).ToLocalChecked());
            i += 1;
        }

        obj->Set(Nan::New("merkle_tree").ToLocalChecked(), mt);
    }

    obj->Set(Nan::New("name").ToLocalChecked(), Nan::New(params.name).ToLocalChecked());
    obj->Set(Nan::New("num_complete").ToLocalChecked(), Nan::New(params.num_complete));
    obj->Set(Nan::New("num_downloaded").ToLocalChecked(), Nan::New(params.num_downloaded));
    obj->Set(Nan::New("num_incomplete").ToLocalChecked(), Nan::New(params.num_incomplete));
    // peers - obj->Set(Nan::New("num_incomplete").ToLocalChecked(), Nan::New(params.peers));
    // piece priorities - obj->Set(Nan::New("num_incomplete").ToLocalChecked(), Nan::New(params.piece_priorities));
    // renamed files - obj->Set(Nan::New("num_incomplete").ToLocalChecked(), Nan::New(params.renamed_files));
    obj->Set(Nan::New("save_path").ToLocalChecked(), Nan::New(params.save_path).ToLocalChecked());
    obj->Set(Nan::New("seeding_time").ToLocalChecked(), Nan::New(params.seeding_time));
    // storage - obj->Set(Nan::New("seeding_time").ToLocalChecked(), Nan::New(params.storage));
    obj->Set(Nan::New("storage_mode").ToLocalChecked(), Nan::New(params.storage_mode));
    // ti - obj->Set(Nan::New("storage_mode").ToLocalChecked(), Nan::New(params.ti));
    obj->Set(Nan::New("total_downloaded").ToLocalChecked(), Nan::New(static_cast<double>(params.total_downloaded)));
    obj->Set(Nan::New("total_uploaded").ToLocalChecked(), Nan::New(static_cast<double>(params.total_uploaded)));
    obj->Set(Nan::New("trackerid").ToLocalChecked(), Nan::New(params.trackerid).ToLocalChecked());
    // trackers - obj->Set(Nan::New("trackerid").ToLocalChecked(), Nan::New(params.trackers).ToLocalChecked());
    // tracker tiers - obj->Set(Nan::New("trackerid").ToLocalChecked(), Nan::New(params.tracker_tiers));
    // unfinished pieces - obj->Set(Nan::New("trackerid").ToLocalChecked(), Nan::New(params.unfinished_pieces));
    obj->Set(Nan::New("upload_limit").ToLocalChecked(), Nan::New(params.upload_limit));
    obj->Set(Nan::New("url").ToLocalChecked(), Nan::New(params.url).ToLocalChecked());
    // url seeds - obj->Set(Nan::New("url").ToLocalChecked(), Nan::New(params.url_seeds).ToLocalChecked());
    // user data - obj->Set(Nan::New("url").ToLocalChecked(), Nan::New(params.userdata).ToLocalChecked());
    // verified pieces - obj->Set(Nan::New("url").ToLocalChecked(), Nan::New(params.verified_pieces).ToLocalChecked());
    obj->Set(Nan::New("version").ToLocalChecked(), Nan::New(params.version));

    return scope.Escape(obj);
}
