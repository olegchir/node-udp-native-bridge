//Configuration options

//Don't forget to run with: --max-old-space-size=4096 on a high load!

var PORT = 11111;
var HOST = '127.0.0.1';
var numberOfPackets = 0;
var maxNumberOfPackets = 10;

//======================================================================================================================

var dgram = require('dgram');
var NanoTimer = require('nanotimer');

var message = Buffer.from('0');
var client = dgram.createSocket('udp4');

var generateData = function(controller) {
    if (numberOfPackets > maxNumberOfPackets ) {
        console.info("We're finished here!");
        controller.nanotimer.clearInterval(controller.interval());
        process.exit();
    }
    try {
        client.send(message, 0, message.length, PORT, HOST, function (err, bytes) {
            if (err) {
                console.error(err);
            } else {
                numberOfPackets++;
                message = Buffer.from(numberOfPackets.toString());
                console.log('UDP message sent to ' + HOST + ':' + PORT);
            }
        });
    } catch (e) {
        if (e.code === "ERR_SOCKET_DGRAM_NOT_RUNNING") {
            console.warn("Waiting for UDP server...");

            client = null;
            delete client;

            client = dgram.createSocket('udp4');
        } else {
            console.error(e);
        }
    }
};

var errFunc = function(err) {
    if(err) {
        console.error(err);
    }
};

var nanoTimer = new NanoTimer();

var interval = null;
var controller = {nanotimer: nanoTimer, interval: function() {return interval;} };

interval = nanoTimer.setInterval(generateData, [controller], '1n', errFunc);

client.close();
