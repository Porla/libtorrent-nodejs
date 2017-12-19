#include <nan.h>

#include "bdecode.h"
#include "bencode.h"
#include "create_torrent.h"
#include "file_storage.h"
#include "read_resume_data.h"
#include "session.h"
#include "settings_pack.h"
#include "torrent_handle.h"
#include "torrent_info.h"

NAN_MODULE_INIT(InitAll)
{
    plt::BDecode::Init(target);
    plt::BEncode::Init(target);
    plt::CreateTorrent::Init(target);
    plt::FileStorage::Init(target);
    plt::ReadResumeData::Init(target);
    plt::Session::Init(target);
    plt::SettingsPack::Init(target);
    plt::TorrentHandle::Init(target);
    plt::TorrentInfo::Init(target);
}

NODE_MODULE(porla_libtorrent, InitAll)
