#include <nan.h>

#include "add_torrent_params.h"
#include "bdecode.h"
#include "read_resume_data.h"
#include "session.h"

NAN_MODULE_INIT(InitAll)
{
    lt::AddTorrentParams::Init(target);
    lt::BDecode::Init(target);
    lt::BDecodeNode::Init(target);
    lt::ReadResumeData::Init(target);
    lt::Session::Init(target);
}

NODE_MODULE(libtorrent, InitAll)
