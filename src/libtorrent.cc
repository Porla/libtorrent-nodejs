#include <nan.h>

#include "bdecode.h"
#include "read_resume_data.h"
#include "session.h"
#include "settings_pack.h"
#include "torrent_handle.h"
#include "torrent_info.h"

NAN_MODULE_INIT(InitAll)
{
    lt::BDecode::Init(target);
    lt::BDecodeNode::Init(target);
    lt::ReadResumeData::Init(target);
    lt::Session::Init(target);
    lt::SettingsPack::Init(target);
    lt::TorrentHandle::Init(target);
    lt::TorrentInfo::Init(target);
}

NODE_MODULE(libtorrent, InitAll)
