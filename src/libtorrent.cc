#include <nan.h>

#include "add_torrent_params.h"
#include "bdecode.h"
#include "read_resume_data.h"
#include "session.h"
#include "torrent_handle.h"
#include "torrent_info.h"

NAN_MODULE_INIT(InitAll)
{
    lt::AddTorrentParams::Init(target);
    lt::BDecode::Init(target);
    lt::BDecodeNode::Init(target);
    lt::ReadResumeData::Init(target);
    lt::Session::Init(target);
    lt::TorrentHandle::Init(target);
    lt::TorrentInfo::Init(target);
}

NODE_MODULE(libtorrent, InitAll)
