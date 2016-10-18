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
    };
}

#endif
