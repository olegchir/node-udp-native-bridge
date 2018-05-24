//Configuration options

//Don't forget to run with: --max-old-space-size=4096 on a high load!

var PORT = 11111;
var HOST = '127.0.0.1';
var numberOfPackets = 0;
var maxNumberOfPackets = 1000;

//======================================================================================================================

var dgram = require('dgram');
var NanoTimer = require('nanotimer');
var microtime = require('microtime')

var exit = function() {
    process.exit();
};

var startTime = null;
var endTime = null;

var message = Buffer.from('0');
var client = dgram.createSocket('udp4');
var interval = null;

var generateData = function(nanotimer) {
    if (numberOfPackets > maxNumberOfPackets ) {
        endTime = microtime.now();
        console.info("We're finished here!");
        nanotimer.clearInterval();

        var microsecondPrecision = 1000000;
        var timeDiff = endTime - startTime;
        var timeDiffSeconds = timeDiff / microsecondPrecision;
        var throughput = numberOfPackets / timeDiffSeconds;

        console.log("Overall time: %d msec (%d sec), %d packets in a second", timeDiff, timeDiffSeconds, throughput);
        exit();
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

startTime = microtime.now();
nanoTimer.setInterval(generateData, [nanoTimer], '1n', errFunc);

client.close();
