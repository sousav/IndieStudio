var Clients = require('../schema/Clients.js');
var Room    = require('../schema/Rooms.js');
var Race    = require('../schema/Races.js');

exports.disconnect = function(socket, io) {
    console.log("Client         " + socket.id + " disconnected.");
    Clients.find({'socketID': socket.id}, function(err, clientList) {
	if (clientList.length != 0) {
	    Race.find({'_id': clientList[0].raceID}).populate('clients').populate('leader').exec(function(err, raceResultF) {
		if (raceResultF.length != 0) {
		    for (var i = 0; i < raceResultF[0].clients.length; i++) {
			if (raceResultF[0].clients[i].socketID != socket.id) {
			    var isLeader = false;
			    if (clientList[0].shortID == raceResultF[0].leader.shortID) {
				isLeader = true;
			    }
			    var json_res = {'short_id': clientList[0].shortID, 'is_leader': isLeader};
			    if (io.sockets.connected[raceResultF[0].clients[i].socketID] != undefined) {
				console.log("EMITING   to   " + raceResultF[0].clients[i].socketID + ": \'leave race\': " + JSON.stringify(json_res));
				io.sockets.connected[raceResultF[0].clients[i].socketID].emit('leave race', json_res);
			    }
			}
		    }
		    if (clientList[0].shortID == raceResultF[0].leader.shortID) {
			for (var i = 0; i < raceResultF[0].clients.length; i++) {
			    Clients.update({"_id": raceResultF[0].clients[i]._id}, {$set: {'raceID': null}}, function(err, result) {});
			}
			Race.update({"_id": clientList[0].raceID}, {$set: {'clients': [], 'raceID': -1}}, function(err, result) {});
		    } else {
			Race.update({"_id": clientList[0].raceID}, {$pull: {'clients': clientList[0]._id}}, function(err, result) {
			    Clients.update({"_id": clientList[0]._id}, {$set: {'raceID': null}}, function(err, result) {});
			});
		    }
		}
		Room.find({'_id': clientList[0].roomID}).populate('clients').exec(function(err, roomResultF) {
		    if (roomResultF.length != 0) {
			for (var i = 0; i < roomResultF[0].clients.length; i++) {
			    if (roomResultF[0].clients[i].socketID != socket.id) {
				var json_res = {'short_id': clientList[0].shortID};
				if (io.sockets.connected[roomResultF[0].clients[i].socketID] != undefined) {
				    console.log("EMITING   to   " + roomResultF[0].clients[i].socketID + ": \'delete car\': " + JSON.stringify(json_res));
				    io.sockets.connected[roomResultF[0].clients[i].socketID].emit('delete car', json_res);
				}
			    }
			}
			Room.update({"_id": clientList[0].roomID}, {$pull: {'clients': clientList[0]._id}}, function(err, result) {
			    Clients.update({"socketID": socket.id}, {$set: {'connected': false, 'roomID': null, 'raceID': null}}, function(err, result) {});
			});
		    } else {
			Clients.update({"socketID": socket.id}, {$set: {'connected': false, 'roomID': null, 'raceID': null}}, function(err, result) {});
		    }
		});
	    });
	}
    });
}

exports.login = function(socket, msg) {
    console.log("RECEIVING from " + socket.id + ": \'id client is\': " + msg);
    var msg_obj = JSON.parse(msg);
    Clients.find({'_id': msg_obj.id.toObjectId()}, function(err, clientList) {
	if(clientList.length == 0) {
	    var newClient = Clients({
		'socketID': socket.id,
		'connected': true,
		'shortID': "-1",
		'money': 200,
		"roomID": null,
		"raceID": null
	    });
	    newClient.save(function(err, result) {
		if (result) {
		    Clients.update({"_id": result.id.toObjectId()}, {$set: {'shortID': result.id.substr(result.id.length - 4)}}, function(err, result) {});
		    
		    var json_res = {'new_id': result._id + "", 'short_id': result.id.substr(result.id.length - 4)};
		    console.log("EMITING   to   " + socket.id + ": \'change id\': " + JSON.stringify(json_res));
		    socket.emit('change id', json_res);
		}
	    });
	} else {
	    Clients.update({"_id": msg_obj.id.toObjectId()}, {$set: {'socketID': socket.id, 'roomID': null, 'connected': true}}, function(err, result) {});
	    
	    var json_res = {'new_id': clientList[0]._id + "", 'short_id': clientList[0].shortID};
	    console.log("EMITING   to   " + socket.id + ": \'change id\': " + JSON.stringify(json_res));
	    socket.emit('change id', json_res);
	}
    });
}

exports.setCar = function(socket, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'carNum changed\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}, function(err, clientList) {
	if(clientList.length != 0) {
	    Clients.update({"_id": msg.id.toObjectId()}, {$set: {'carNumber': msg.nbr}}, function(err, result) {});
	}
    });
}
