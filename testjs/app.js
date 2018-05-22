const {Start} = require('../build/Release/node_native_buffer');
Start();

var seconds_left = 3;
var interval = setInterval(function() {
    console.log(--seconds_left);
    if (seconds_left <= 0)
    {
        return 0;
    }
}, 1000);
