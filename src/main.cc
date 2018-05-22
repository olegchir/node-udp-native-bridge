#include <nan.h>
#include "main.h"

Nan::Persistent<v8::FunctionTemplate> NativeBuffer::constructor;

NAN_MODULE_INIT(NativeBuffer::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(NativeBuffer::New);

    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("NativeBuffer").ToLocalChecked());

    Nan::SetPrototypeMethod(ctor, "start", Start);
    Nan::SetPrototypeMethod(ctor, "stop", Stop);
    Nan::SetPrototypeMethod(ctor, "join", Join);

    target->Set(Nan::New("NativeBuffer").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(NativeBuffer::New) {
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("NativeBuffer::New - called without new keyword").ToLocalChecked());
    }
    NativeBuffer* buffer = new NativeBuffer();
    buffer->daemon = new Daemon();
    buffer->Wrap(info.Holder());
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(NativeBuffer::Start) {
    NativeBuffer* buffer = Nan::ObjectWrap::Unwrap<NativeBuffer>(info.This());
    buffer->daemon->start();
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(NativeBuffer::Stop) {
    NativeBuffer* buffer = Nan::ObjectWrap::Unwrap<NativeBuffer>(info.This());
    buffer->daemon->stop();
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(NativeBuffer::Join) {
    NativeBuffer* buffer = Nan::ObjectWrap::Unwrap<NativeBuffer>(info.This());
    buffer->daemon->join();
    info.GetReturnValue().Set(info.Holder());
}

NODE_MODULE(node_native_buffer, NativeBuffer::Init);