#include "torrent_info.h"

#include <sstream>

#include <libtorrent/announce_entry.hpp>
#include <libtorrent/torrent_info.hpp>

#include "bdecode.h"

using lt::TorrentInfo;

Nan::Persistent<v8::Function> TorrentInfo::constructor;

TorrentInfo::TorrentInfo(std::shared_ptr<libtorrent::torrent_info> ti)
    : ti_(ti)
{
}

TorrentInfo::~TorrentInfo()
{
}

std::shared_ptr<libtorrent::torrent_info> TorrentInfo::GetWrapped()
{
    return ti_;
}

NAN_MODULE_INIT(TorrentInfo::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("torrent_info").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Methods
    Nan::SetPrototypeMethod(tpl, "files", Files);
    Nan::SetPrototypeMethod(tpl, "orig_files", OrigFiles);
    Nan::SetPrototypeMethod(tpl, "rename_file", RenameFile);
    Nan::SetPrototypeMethod(tpl, "add_tracker", AddTracker);
    Nan::SetPrototypeMethod(tpl, "trackers", Trackers);
    Nan::SetPrototypeMethod(tpl, "similar_torrents", SimilarTorrents);
    Nan::SetPrototypeMethod(tpl, "collections", Collections);
    Nan::SetPrototypeMethod(tpl, "add_url_seed", AddUrlSeed);
    Nan::SetPrototypeMethod(tpl, "add_http_seed", AddHttpSeed);
    Nan::SetPrototypeMethod(tpl, "web_seeds", WebSeeds);
    Nan::SetPrototypeMethod(tpl, "set_web_seeds", SetWebSeeds);
    Nan::SetPrototypeMethod(tpl, "total_size", TotalSize);
    Nan::SetPrototypeMethod(tpl, "piece_length", PieceLength);
    Nan::SetPrototypeMethod(tpl, "num_pieces", NumPieces);
    Nan::SetPrototypeMethod(tpl, "info_hash", InfoHash);
    Nan::SetPrototypeMethod(tpl, "num_files", NumFiles);
    Nan::SetPrototypeMethod(tpl, "map_block", MapBlock);
    Nan::SetPrototypeMethod(tpl, "map_file", MapFile);
    Nan::SetPrototypeMethod(tpl, "load", Load);
    Nan::SetPrototypeMethod(tpl, "unload", Unload);
    Nan::SetPrototypeMethod(tpl, "ssl_cert", SslCert);
    Nan::SetPrototypeMethod(tpl, "is_valid", IsValid);
    Nan::SetPrototypeMethod(tpl, "priv", Priv);
    Nan::SetPrototypeMethod(tpl, "is_i2p", IsI2p);
    Nan::SetPrototypeMethod(tpl, "piece_size", PieceSize);
    Nan::SetPrototypeMethod(tpl, "hash_for_piece", HashForPiece);
    Nan::SetPrototypeMethod(tpl, "is_loaded", IsLoaded);
    Nan::SetPrototypeMethod(tpl, "merkle_tree", MerkleTree);
    Nan::SetPrototypeMethod(tpl, "set_merkle_tree", SetMerkleTree);
    Nan::SetPrototypeMethod(tpl, "name", Name);
    Nan::SetPrototypeMethod(tpl, "creation_date", CreationDate);
    Nan::SetPrototypeMethod(tpl, "creator", Creator);
    Nan::SetPrototypeMethod(tpl, "comment", Comment);
    Nan::SetPrototypeMethod(tpl, "nodes", Nodes);
    Nan::SetPrototypeMethod(tpl, "add_node", AddNode);
    Nan::SetPrototypeMethod(tpl, "parse_info_section", ParseInfoSection);
    Nan::SetPrototypeMethod(tpl, "metadata", Metadata);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("torrent_info").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::New)
{
    if (info.IsConstructCall())
    {
        TorrentInfo* obj = nullptr;

        if (info.Length() > 0 && info[0]->IsExternal())
        {
            std::shared_ptr<libtorrent::torrent_info>* ti = static_cast<std::shared_ptr<libtorrent::torrent_info>*>(info[0].As<v8::External>()->Value());
            obj = new TorrentInfo(*ti);
        }
        else if (info.Length() > 0 && info[0]->IsObject())
        {
            BDecodeNode* node = Nan::ObjectWrap::Unwrap<BDecodeNode>(info[0]->ToObject());

            libtorrent::error_code ec;
            obj = new TorrentInfo(std::make_shared<libtorrent::torrent_info>(node->GetWrapped(), ec));
        }
        else if (info.Length() > 0 && info[0]->IsString())
        {
            std::string path = *Nan::Utf8String(info[0]);

            libtorrent::error_code ec;
            libtorrent::torrent_info ti(path, ec);

            if (ec)
            {
                Nan::ThrowError(ec.message().c_str());
                return;
            }

            obj = new TorrentInfo(std::make_shared<libtorrent::torrent_info>(ti));
        }
        else
        {
            Nan::ThrowError("Error!");
            return;
        }

        if (obj == nullptr)
        {
            Nan::ThrowError("Failed to construct torrent info");            
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

v8::Local<v8::Object> TorrentInfo::NewInstance(v8::Local<v8::Value> arg)
{
    Nan::EscapableHandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

    return scope.Escape(instance);
}

NAN_METHOD(TorrentInfo::Files)
{

}

NAN_METHOD(TorrentInfo::OrigFiles)
{

}

NAN_METHOD(TorrentInfo::RenameFile)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    obj->ti_->rename_file(info[0]->Int32Value(), *Nan::Utf8String(info[0]));
}

NAN_METHOD(TorrentInfo::AddTracker)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    obj->ti_->add_tracker(*Nan::Utf8String(info[0]), info.Length() >= 1 ? info[0]->Int32Value() : 0);
}

NAN_METHOD(TorrentInfo::Trackers)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    std::vector<libtorrent::announce_entry> trackers = obj->ti_->trackers();

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

NAN_METHOD(TorrentInfo::SimilarTorrents)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    std::vector<libtorrent::sha1_hash> similar = obj->ti_->similar_torrents();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(similar.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        std::stringstream ss;
        ss << similar.at(i);

        arr->Set(i, Nan::New(ss.str()).ToLocalChecked());
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentInfo::Collections)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    std::vector<std::string> collections = obj->ti_->collections();

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(collections.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, Nan::New(collections.at(i)).ToLocalChecked());
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(TorrentInfo::AddUrlSeed)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::AddHttpSeed)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::WebSeeds)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::SetWebSeeds)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::TotalSize)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(static_cast<double>(obj->ti_->total_size())));
}

NAN_METHOD(TorrentInfo::PieceLength)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->piece_length()));
}

NAN_METHOD(TorrentInfo::NumPieces)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->num_pieces()));
}

NAN_METHOD(TorrentInfo::InfoHash)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    std::stringstream ss;
    ss << obj->ti_->info_hash();

    info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::NumFiles)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->num_files()));
}

NAN_METHOD(TorrentInfo::MapBlock)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::MapFile)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::Load)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::Unload)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    obj->ti_->unload();
}

NAN_METHOD(TorrentInfo::SslCert)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->ssl_cert()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::IsValid)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->is_valid()));
}

NAN_METHOD(TorrentInfo::Priv)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->priv()));
}

NAN_METHOD(TorrentInfo::IsI2p)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->is_i2p()));
}

NAN_METHOD(TorrentInfo::PieceSize)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->piece_size(info[0]->Int32Value())));
}

NAN_METHOD(TorrentInfo::HashForPiece)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    std::stringstream ss;
    ss << obj->ti_->hash_for_piece(info[0]->Int32Value());

    info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::IsLoaded)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->is_loaded()));
}

NAN_METHOD(TorrentInfo::MerkleTree)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::SetMerkleTree)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::Name)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->name()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::CreationDate)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::Creator)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->creator()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::Comment)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->comment()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::Nodes)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::AddNode)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::ParseInfoSection)
{
    Nan::ThrowError("Not implemented");
}

NAN_METHOD(TorrentInfo::Metadata)
{
    Nan::ThrowError("Not implemented");
}
