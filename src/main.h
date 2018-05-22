#include <nan.h>
#include "daemon.hpp"

class NativeBuffer : public Nan::ObjectWrap {
private:
    Daemon* daemon = nullptr;
public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(Start);
    static NAN_METHOD(Stop);
    static NAN_METHOD(Join);
    static Nan::Persistent<v8::FunctionTemplate> constructor;
};