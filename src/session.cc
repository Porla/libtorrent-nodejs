#include "session.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/bdecode.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_status.hpp>

#include "add_torrent_params.h"
#include "alert_types.h"
#include "bdecode.h"
#include "entry.h"
#include "settings_pack.h"
#include "torrent_handle.h"
#include "torrent_info.h"
#include "torrent_status.h"

using lt::Session;

Nan::Persistent<v8::Function> Session::constructor;

class SessionWaitForAlertWorker : public Nan::AsyncWorker
{
public:
    SessionWaitForAlertWorker(
        Nan::Callback* callback,
        libtorrent::session* session,
        int timeout)
        : Nan::AsyncWorker(callback),
        session_(session),
        timeout_(timeout),
        alert_(nullptr)
    {
    }

    ~SessionWaitForAlertWorker() {}

    void Execute()
    {
        alert_ = session_->wait_for_alert(std::chrono::milliseconds(timeout_));
    }

    void HandleOKCallback()
    {
        Nan::HandleScope scope;

        v8::Local<v8::Value> argv[] =
        {
            Nan::Null(),
            Nan::New<v8::Boolean>(alert_ != nullptr)
        };

        callback->Call(2, argv);
    }

private:
    libtorrent::session* session_;
    int timeout_;
    libtorrent::alert* alert_;
};

NAN_MODULE_INIT(Session::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("session").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "add_torrent", AddTorrent);
    Nan::SetPrototypeMethod(tpl, "apply_settings", ApplySettings);
    Nan::SetPrototypeMethod(tpl, "async_add_torrent", AsyncAddTorrent);
    Nan::SetPrototypeMethod(tpl, "get_settings", GetSettings);
    Nan::SetPrototypeMethod(tpl, "get_torrent_status", GetTorrentStatus);
    Nan::SetPrototypeMethod(tpl, "is_listening", IsListening);
    Nan::SetPrototypeMethod(tpl, "is_paused", IsPaused);
    Nan::SetPrototypeMethod(tpl, "load_state", LoadState);
    Nan::SetPrototypeMethod(tpl, "pause", Pause);
    Nan::SetPrototypeMethod(tpl, "pop_alerts", PopAlerts);
    Nan::SetPrototypeMethod(tpl, "post_torrent_updates", PostTorrentUpdates);
    Nan::SetPrototypeMethod(tpl, "remove_torrent", RemoveTorrent);
    Nan::SetPrototypeMethod(tpl, "save_state", SaveState);
    Nan::SetPrototypeMethod(tpl, "wait_for_alert", WaitForAlert);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("session").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

Session::Session()
{
    wrap_ = new libtorrent::session();
}

Session::Session(libtorrent::settings_pack& settings)
{
    wrap_ = new libtorrent::session(settings);
}

Session::~Session()
{
    delete wrap_;
}

NAN_METHOD(Session::New)
{
    if (info.IsConstructCall())
    {
        Session* obj = nullptr;

        if (info.Length() > 0 && info[0]->IsObject())
        {
            auto params = info[0]->ToObject();
            auto settings = Nan::New("settings").ToLocalChecked();

            if (params->Has(settings) && params->Get(settings)->IsObject())
            {
                v8::Local<v8::Object> settingsObject = params->Get(settings)->ToObject();
                SettingsPack* pack = Nan::ObjectWrap::Unwrap<SettingsPack>(settingsObject);
                obj = new Session(pack->GetWrapped());
            }
        }

        if (obj == nullptr)
        {
            obj = new Session();
        }

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        Nan::ThrowError("Use 'new' to create instances of 'session'.");
    }
}

NAN_METHOD(Session::AddTorrent)
{
    if (!info[0]->IsObject())
    {
        Nan::ThrowTypeError("Invalid type - expected 'object'.");
        return;
    }

    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    v8::Local<v8::Object> p = info[0]->ToObject();

    libtorrent::add_torrent_params params = AddTorrentParams::FromObject(p);

    libtorrent::error_code ec;
    libtorrent::torrent_handle th = obj->wrap_->add_torrent(params, ec);

    if (ec)
    {
        Nan::ThrowError(ec.message().c_str());
        return;
    }

    v8::Local<v8::External> ext = Nan::New<v8::External>(static_cast<void*>(&th));
    info.GetReturnValue().Set(TorrentHandle::NewInstance(ext));
}

NAN_METHOD(Session::ApplySettings)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    SettingsPack* sp = Nan::ObjectWrap::Unwrap<SettingsPack>(info[0]->ToObject());

    obj->wrap_->apply_settings(sp->GetWrapped());
}

NAN_METHOD(Session::AsyncAddTorrent)
{
    if (!info[0]->IsObject())
    {
        Nan::ThrowTypeError("Invalid type - expected 'object'.");
        return;
    }

    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    v8::Local<v8::Object> p = info[0]->ToObject();

    libtorrent::add_torrent_params params = AddTorrentParams::FromObject(p);

    obj->wrap_->async_add_torrent(params);
}

NAN_METHOD(Session::GetSettings)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    libtorrent::settings_pack sp = obj->wrap_->get_settings();

    v8::Local<v8::External> ext = Nan::New<v8::External>(static_cast<void*>(&sp));
    info.GetReturnValue().Set(SettingsPack::NewInstance(ext));
}

NAN_METHOD(Session::GetTorrentStatus)
{
    Nan::ThrowError("Not fully working.");
    return;

    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    v8::Local<v8::Function> func = info[0].As<v8::Function>();

    std::vector<libtorrent::torrent_status> list;
    obj->wrap_->get_torrent_status(&list, [func](const libtorrent::torrent_status& ts) {
        const unsigned argc = 1;

        v8::Local<v8::Object> status = TorrentStatus::CreateObject(ts);
        v8::Local<v8::Value> argv[argc] = { status };
        v8::Local<v8::Value> ret = Nan::MakeCallback(Nan::GetCurrentContext()->Global(), func, argc, argv);

        return ret->BooleanValue();
    });

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<uint32_t>(list.size()));

    for (uint32_t i = 0; i < arr->Length(); i++)
    {
        arr->Set(i, TorrentStatus::CreateObject(list.at(i)));
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(Session::IsListening)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    info.GetReturnValue().Set(obj->wrap_->is_listening());
}

NAN_METHOD(Session::IsPaused)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    info.GetReturnValue().Set(obj->wrap_->is_paused());
}

NAN_METHOD(Session::LoadState)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    libtorrent::entry e = Entry::FromJson(info[0]);
    
    std::vector<char> buf;
    libtorrent::bencode(std::back_inserter(buf), e);

    libtorrent::bdecode_node node;
    libtorrent::error_code ec;
    libtorrent::bdecode(&buf[0], &buf[0] + buf.size(), node, ec);

    if (ec)
    {
        Nan::ThrowError(ec.message().c_str());
        return;
    }

    obj->wrap_->load_state(node);
}

NAN_METHOD(Session::Pause)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    obj->wrap_->pause();
}

NAN_METHOD(Session::PopAlerts)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    std::vector<libtorrent::alert*> alerts;
    obj->wrap_->pop_alerts(&alerts);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<int>(alerts.size()));

    for (uint32_t idx = 0; idx < alerts.size(); idx++)
    {
        v8::Local<v8::Object> al = AlertTypes::ToObject(alerts.at(idx));
        arr->Set(idx, al);
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(Session::PostTorrentUpdates)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    obj->wrap_->post_torrent_updates();
}

NAN_METHOD(Session::RemoveTorrent)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());
    TorrentHandle* th = Nan::ObjectWrap::Unwrap<TorrentHandle>(info[0]->ToObject());

    int options = 0;

    if (info.Length() >= 2 && info[1]->IsObject())
    {
        auto params = info[1]->ToObject();
        auto remove_files = Nan::New("delete_files").ToLocalChecked();

        if (params->Has(remove_files)
            && params->Get(remove_files)->IsBoolean()
            && params->Get(remove_files)->ToBoolean()->Value())
        {
            options = libtorrent::session::options_t::delete_files;
        }
    }

    obj->wrap_->remove_torrent(th->GetWrapped(), options);
}

NAN_METHOD(Session::SaveState)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    libtorrent::entry e;
    obj->wrap_->save_state(e);

    info.GetReturnValue().Set(Entry::ToJson(e));
}

NAN_METHOD(Session::WaitForAlert)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    int timeout = info[0]->Int32Value();
    Nan::Callback *callback = new Nan::Callback(info[1].As<v8::Function>());

    Nan::AsyncQueueWorker(new SessionWaitForAlertWorker(callback, obj->wrap_, timeout));
}
