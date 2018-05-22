#include <nan.h>
#include "daemon.hpp"

NAN_METHOD(Hello) {
    auto message = Nan::New("Hello from Node Native Buffer!").ToLocalChecked();
    info.GetReturnValue().Set(message);
}

NAN_METHOD(Start) {
    Daemon::run();
}

NAN_MODULE_INIT(Initialize) {
    NAN_EXPORT(target, Hello);
    NAN_EXPORT(target, Start);
}

NODE_MODULE(node_native_buffer, Initialize);