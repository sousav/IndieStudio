var Clients = require('../schema/Clients.js');
var Room    = require('../schema/Rooms.js');
var Race    = require('../schema/Races.js');

exports.createRace = function(socket, io, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'create race\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}).populate('roomID').populate('raceID').exec(function(err, clientList) {
	if(clientList.length != 0) {
	    if (clientList[0].roomID == null || clientList[0].raceID != null) {
		return;
	    }
	    var self = clientList[0];
	    Room.find({'_id': self.roomID}).populate('clients').populate('races').exec(function(err, roomResultF) {
		if (roomResultF.length != 0) {
		    for (var i = 0; i < roomResultF[0].races.length; i++) {
			if (roomResultF[0].races[i].raceID == msg.race_id) {
			    joinRace(socket, io, msg, self, roomResultF[0].races[i]);
			    return;
			}
		    }
		    createNewRace(socket, io, msg, self);
		}
	    });
	}
    });
}

exports.leaveRace = function(socket, io, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'leave race\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}, function(err, clientList) {
	if (clientList.length != 0) {
	    Race.find({'_id': clientList[0].raceID}).populate('clients').populate('leader').exec(function(err, raceResultF) {
		if (raceResultF.length != 0) {
		    for (var i = 0; i < raceResultF[0].clients.length; i++) {
			if (raceResultF[0].clients[i].socketID != socket.id) {
			    var isLeader = false;
			    if (clientList[0].shortID == raceResultF[0].leader.shortID) {
				isLeader = true;
			    }
			    if (isLeader == true) {
				
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
			    Clients.update({"_id": msg.id.toObjectId()}, {$set: {'raceID': null}}, function(err, result) {});
			});
		    }
		}
	    });
	}
    });
}

exports.startRace = function(socket, io, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'starting race\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}, function(err, clientList) {
	if (clientList.length != 0) {
	    var self = clientList[0];
	    if (self.roomID == null) {
		startRaceCounterOffline(socket, io, msg);
	    } else {
		Room.find({'_id': self.roomID}).populate('clients').exec(function(err, roomList) {
		    if (roomList.length != 0) {
			var room = roomList[0];
			Race.find({'_id': self.raceID}).populate('leader').populate('clients').exec(function(err, raceList) {
			    if (raceList.length != 0) {
				var race = raceList[0];
				if (race.leader.shortID == self.shortID) {
				    createAI(socket, io, msg, self, room, race, function() {
					startRaceCounterOnline(socket, io, msg, self, room, race); 
				    });
				} else {
				    var json_res = {error: "Only the leader, #" + race.leader.shortID + " can choose to start the race!!"};
				    console.log("EMITING   to   " + socket.id + ": \'error message\': " + JSON.stringify(json_res));
				    socket.emit('error message', json_res);
				}
			    }
			});
		    }
		});
	    }
	}
    });
}

function createAI(socket, io, msg, self, room, race, callback) {
    for (var i = race.clients.length; i < 4; i++) {
	var newClient = Clients({
	    'socketID': undefined,
	    'connected': true,
	    'shortID': "ai" + i,
	    'money': 0,
	    "roomID": null,
	    "raceID": race._id
	});
	newClient.save(function(err, result) {
	    if (result) {
		Race.update({"_id": race._id}, {$push: {'clients': result._id}}, function(err, resultUpdate) {
		    if (resultUpdate) {
			for (var j = 0; j < race.clients.length; j++) {
			    if (io.sockets.connected[race.clients[j].socketID] != undefined) {
				var isLeader = (race.leader.shortID == race.clients[j].shortID);
				var json_res = {"short_id": result.shortID, 'leader': isLeader};
				console.log("EMITING   to   " + race.clients[j].socketID + ": \'add race ai\': " + JSON.stringify(json_res));
				io.sockets.connected[race.clients[j].socketID].emit('add race ai', json_res);
			    }
			}
		    }
		});
	    }
	});
    }
    setTimeout(function () {
	callback();
    }, 500);
}
    
function startRaceCounterOnline(socket, io, msg, self, room, race) {
    setTimeout(function () {
	for (var j = 0; j < race.clients.length; j++) {
	    if (io.sockets.connected[race.clients[j].socketID] != undefined) {
		var json_res = {error: "!!!!  3  !!!!"};
		console.log("EMITING   to   " + race.clients[j].socketID + ": \'error message\': " + JSON.stringify(json_res));
		io.sockets.connected[race.clients[j].socketID].emit('error message', json_res);
	    }
	}
    }, 1000);
    
    setTimeout(function () {
	for (var j = 0; j < race.clients.length; j++) {
	    if (io.sockets.connected[race.clients[j].socketID] != undefined) {
		var json_res = {error: "!!!!  2  !!!!"};
		console.log("EMITING   to   " + race.clients[j].socketID + ": \'error message\': " + JSON.stringify(json_res));
		io.sockets.connected[race.clients[j].socketID].emit('error message', json_res);
	    }
	}
    }, 2000);
    
    setTimeout(function () {
	for (var j = 0; j < race.clients.length; j++) {
	    if (io.sockets.connected[race.clients[j].socketID] != undefined) {
		var json_res = {error: "!!!!  1  !!!!"};
		console.log("EMITING   to   " + race.clients[j].socketID + ": \'error message\': " + JSON.stringify(json_res));
		io.sockets.connected[race.clients[j].socketID].emit('error message', json_res);
	    }
	}
    }, 3000);
    
    setTimeout(function () {
	for (var j = 0; j < race.clients.length; j++) {
	    if (io.sockets.connected[race.clients[j].socketID] != undefined) {
		var json_res = {error: "!!!!  GOOO  !!!!"};
		console.log("EMITING   to   " + race.clients[j].socketID + ": \'error message\': " + JSON.stringify(json_res));
		io.sockets.connected[race.clients[j].socketID].emit('error message', json_res);
	    }
	}
	for (var j = 0; j < race.clients.length; j++) {
	    if (io.sockets.connected[race.clients[j].socketID] != undefined) {	
		var json_res = {};
		console.log("EMITING   to   " + race.clients[j].socketID + ": \'start race\': " + JSON.stringify(json_res));
		io.sockets.connected[race.clients[j].socketID].emit('start race', json_res);
	    }
	}
    }, 4000);
}

function startRaceCounterOffline(socket, io, msg) {
    setTimeout(function () {
	var json_res = {error: "!!!!  3  !!!!"};
	console.log("EMITING   to   " + socket.id + ": \'error message\': " + JSON.stringify(json_res));
	socket.emit('error message', json_res);
    }, 1000);
    
    setTimeout(function () {
	var json_res = {error: "!!!!  2  !!!!"};
	console.log("EMITING   to   " + socket.id + ": \'error message\': " + JSON.stringify(json_res));
	socket.emit('error message', json_res);
    }, 2000);
    
    setTimeout(function () {
	var json_res = {error: "!!!!  1  !!!!"};
	console.log("EMITING   to   " + socket.id + ": \'error message\': " + JSON.stringify(json_res));
	socket.emit('error message', json_res);
    }, 3000);
    
    setTimeout(function () {
	var json_res = {error: "!!!!  GOOOO  !!!!"};
	console.log("EMITING   to   " + socket.id + ": \'error message\': " + JSON.stringify(json_res));
	socket.emit('error message', json_res);

	var json_res = {};
	console.log("EMITING   to   " + socket.id + ": \'start race\': " + JSON.stringify(json_res));
	socket.emit('start race', json_res);
    }, 4000);
}

function joinRace(socket, io, msg, self, race) {
    Race.update({"_id": race._id}, {$push: {'clients': self._id}}, function(err, result) {
	if (result) {
	    Clients.update({"_id": self._id}, {$set: {'raceID': race._id}}, function(err, result) {
		if (result) {
		    Race.find({'_id': race._id}).populate('clients').exec(function(err, raceResultF) {
			if (raceResultF.length != 0) {
			    for (var i = 0; i < raceResultF[0].clients.length; i++) {
				if (raceResultF[0].clients[i].socketID != socket.id) {
				    if (io.sockets.connected[raceResultF[0].clients[i].socketID] != undefined) {
					var json_res = {'short_id': self.shortID, 'nb_total': raceResultF[0].clients.length - 1};
					console.log("EMITING   to   " + raceResultF[0].clients[i].socketID + ": \'join race\': " + JSON.stringify(json_res));
					io.sockets.connected[raceResultF[0].clients[i].socketID].emit('join race', json_res);
				    }
				}
			    }
			    
			    for (var i = 0; i < raceResultF[0].clients.length; i++) {
				if (raceResultF[0].clients[i].socketID != socket.id) {
				    var json_res = {'short_id': raceResultF[0].clients[i].shortID, 'nb_total': raceResultF[0].clients.length - 1};
				    console.log("EMITING   to   " + socket.id + ": \'join race\': " + JSON.stringify(json_res));
				    socket.emit('join race', json_res);
				}
			    }
			}
		    });
		}
	    });
	}
    });
}

function createNewRace(socket, io, msg, self) {
    var newRace = Race({
	'raceID': msg.race_id,
	'leader': self._id,
	'clients': [self._id]
    });
    newRace.save(function(err, resultRace) {
	if (resultRace) {
	    Room.update({"_id": self.roomID}, {$push: {'races': resultRace.id}}, function(err, result) {
		if (result) {
		    Clients.update({"_id": self._id}, {$set: {'raceID': resultRace.id}}, function(err, result) {
			if (result) {
			    var json_res = {'short_id': "null", 'nb_total': 0};
			    console.log("EMITING   to   " + socket.id + ": \'join race\': " + JSON.stringify(json_res));
			    socket.emit('join race', json_res);
			}
		    });   
		}
	    });
	}
    });
}
