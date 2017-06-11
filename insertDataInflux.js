const Influx = require('influxdb-nodejs');
const client = new Influx('http://127.0.0.1:8086/testInflux');
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
    microgear.setAlias("NODEMCU_BAESLab");
 /*   setInterval(function() {
        microgear.chat('mygear', 'Hello world.');
    },1000);*/
});

microgear.on('message', function(topic,body) {
    console.log('incoming : '+' : '+body);

    const fieldSchema = {
      host: 'string',
      xxx: 'string',
      yyyy: 'float',
    };

    client.write('test')
      .field({
        host: "xxxx",
        xxx: "yyyy",
        yyyy: body,
      })
      .then(() => console.info('write point success'))
      .catch(console.error);
});

microgear.on('closed', function() {
    console.log('Closed...');
});

microgear.connect(APPID);
