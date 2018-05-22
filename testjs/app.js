const nb = require('../build/Release/node_native_buffer');

const buffer = new nb.NativeBuffer();
console.log(buffer);

buffer.start();


var seconds_left = 30;
var interval = setInterval(function() {
    console.log(--seconds_left);
    if (seconds_left === 27) {
        buffer.stop();
        buffer.join();
    }
    if (seconds_left <= 0)
    {
        return 0;
    }
}, 1000);
