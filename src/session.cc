#include "Session.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/session.hpp>

#include "bdecode.h"
#include "torrent_handle.h"
#include "torrent_info.h"

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
    Nan::Callback* callback_;
    libtorrent::session* session_;
    int timeout_;
    libtorrent::alert* alert_;
};

NAN_MODULE_INIT(Session::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("session").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "add_dht_router", AddDhtRouter);
    Nan::SetPrototypeMethod(tpl, "add_torrent", AddTorrent);
    Nan::SetPrototypeMethod(tpl, "async_add_torrent", AsyncAddTorrent);
    Nan::SetPrototypeMethod(tpl, "is_listening", IsListening);
    Nan::SetPrototypeMethod(tpl, "is_paused", IsPaused);
    Nan::SetPrototypeMethod(tpl, "load_state", LoadState);
    Nan::SetPrototypeMethod(tpl, "pop_alerts", PopAlerts);
    Nan::SetPrototypeMethod(tpl, "wait_for_alert", WaitForAlert);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("session").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

Session::Session()
{
    wrap_ = new libtorrent::session();
}

Session::~Session()
{
    delete wrap_;
}

libtorrent::add_torrent_params Session::GetAddTorrentParams(const v8::Local<v8::Object>& object)
{
    auto ti = Nan::New("ti").ToLocalChecked();

    // Validate
    if (object->Has(ti) && !object->Get(ti)->IsObject())
    {
        Nan::ThrowTypeError("Property 'ti' should be an object type.");
    }

    libtorrent::add_torrent_params params;
    params.active_time = object->Get(Nan::New("active_time").ToLocalChecked())->Int32Value();
    params.save_path = *Nan::Utf8String(object->Get(Nan::New("save_path").ToLocalChecked())->ToString());
    params.ti = Nan::ObjectWrap::Unwrap<TorrentInfo>(object->Get(ti)->ToObject())->GetWrapped();

    return params;
}

NAN_METHOD(Session::New)
{
    if (info.IsConstructCall())
    {
        Session *obj = new Session();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        Nan::ThrowError("Use 'new' to create instances of 'session'.");
    }
}

NAN_METHOD(Session::AddDhtRouter)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    std::string host = *Nan::Utf8String(info[0]->ToString());
    int port = Nan::To<int>(info[1]).FromJust();

    obj->wrap_->add_dht_router({ host, port });
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

    libtorrent::add_torrent_params params = GetAddTorrentParams(p);

    libtorrent::error_code ec;
    libtorrent::torrent_handle th = obj->wrap_->add_torrent(params, ec);

    if (ec)
    {
        Nan::ThrowError(ec.message().c_str());
        return;
    }

    v8::Local<v8::External> ext = v8::External::New(info.GetIsolate(), static_cast<void*>(&th));
    info.GetReturnValue().Set(TorrentHandle::NewInstance(ext));
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

    libtorrent::add_torrent_params params = GetAddTorrentParams(p);

    obj->wrap_->async_add_torrent(params);
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
    BDecodeNode* node = Nan::ObjectWrap::Unwrap<BDecodeNode>(info[0]->ToObject());

    obj->wrap_->load_state(node->GetWrapped());
}

NAN_METHOD(Session::PopAlerts)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    std::vector<libtorrent::alert*> alerts;
    obj->wrap_->pop_alerts(&alerts);

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(static_cast<int>(alerts.size()));

    for (uint32_t idx = 0; idx < alerts.size(); idx++)
    {
        v8::Local<v8::Object> al = Nan::New<v8::Object>();
        al->Set(Nan::New("message").ToLocalChecked(), Nan::New(alerts[idx]->message()).ToLocalChecked());
        al->Set(Nan::New("type").ToLocalChecked(), Nan::New(alerts[idx]->type()));

        arr->Set(idx, al);
    }

    info.GetReturnValue().Set(arr);
}

NAN_METHOD(Session::WaitForAlert)
{
    Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.This());

    int timeout = Nan::To<int>(info[0]).FromJust();
    Nan::Callback *callback = new Nan::Callback(info[1].As<v8::Function>());

    Nan::AsyncQueueWorker(new SessionWaitForAlertWorker(callback, obj->wrap_, timeout));
}
