var MicroGear = require('microgear');

const APPID  = "SmartLiving";
const KEY    = "KHU7aM4YzWKZWEC";
const SECRET = "QLTCNDCmJJb1sqlZWSO7YnEMO";

var microgear = MicroGear.create({
    key : KEY,
    secret : SECRET
});

microgear.on('connected', function() {
    console.log('Connected...');
    microgear.setAlias("mygear");
    setInterval(function() {
        microgear.chat('mygear', 'Hello world.');
    },1000);
});

microgear.on('message', function(topic,body) {
    console.log('incoming : '+topic+' : '+body);
});

microgear.on('closed', function() {
    console.log('Closed...');
});

microgear.connect(APPID);