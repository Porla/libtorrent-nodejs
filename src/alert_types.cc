#include "alert_types.h"

#include <libtorrent/alert_types.hpp>

using lt::AlertTypes;

v8::Local<v8::Object> AlertTypes::ToObject(libtorrent::alert* alert)
{
    Nan::EscapableHandleScope scope;
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    obj->Set(Nan::New("category").ToLocalChecked(), Nan::New(alert->category()));
    obj->Set(Nan::New("message").ToLocalChecked(), Nan::New(alert->message()).ToLocalChecked());
    // todo: timestamp
    obj->Set(Nan::New("type").ToLocalChecked(), Nan::New(alert->type()));
    obj->Set(Nan::New("what").ToLocalChecked(), Nan::New(alert->what()).ToLocalChecked());

    // Get the alert
    switch (alert->type())
    {
    case libtorrent::torrent_added_alert::alert_type:
        ToTorrentAddedAlert(obj, static_cast<libtorrent::torrent_added_alert*>(alert));
        break;
    }

    return scope.Escape(obj);
}


void AlertTypes::ToTorrentAlert(v8::Local<v8::Object> obj, libtorrent::torrent_alert* alert)
{
}

void AlertTypes::ToTorrentAddedAlert(v8::Local<v8::Object> obj, libtorrent::torrent_added_alert* alert)
{
    ToTorrentAlert(obj, alert);
}
