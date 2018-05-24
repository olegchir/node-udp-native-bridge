var PORT = 11111;
var HOST = '127.0.0.1';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
    console.log(remote.address + ':' + remote.port + ' - ' + utf8IntArrayToString(message));

});

server.bind(PORT, HOST);

var utf8IntArrayToString = function (data) {
    var result = "[";
    var elem = null;
    for (let i = 0; i < data.length; i++) {
        elem = data[i];
        result += elem;
        if (i !== data.length - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
};