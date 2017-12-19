#ifndef BENCODE_H
#define BENCODE_H

#include <memory>
#include <nan.h>

namespace libtorrent
{
    class entry;
}

namespace plt
{
    class BEncode
    {
    public:
        static NAN_MODULE_INIT(Init);
    };
}

#endif
