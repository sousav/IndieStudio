var Clients = require('../schema/Clients.js');
var Room    = require('../schema/Rooms.js');
var Race    = require('../schema/Races.js');

exports.getMoney = function(socket, io, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'get money\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}).exec(function(err, clientList) {
	if(clientList.length != 0) {
	    var json_res = {'money': clientList[0].money};
	    console.log("EMITING   to   " + socket.id + ": \'get money\': " + JSON.stringify(json_res));
	    socket.emit('get money', json_res);
	}
    });
}
