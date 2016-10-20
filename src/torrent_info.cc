#include "torrent_info.h"

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

NAN_METHOD(TorrentInfo::Name)
{
    TorrentInfo* obj = Nan::ObjectWrap::Unwrap<TorrentInfo>(info.This());
    info.GetReturnValue().Set(Nan::New(obj->ti_->name()).ToLocalChecked());
}
