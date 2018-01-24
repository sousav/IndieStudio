var Clients = require('../schema/Clients.js');
var Room    = require('../schema/Rooms.js');

exports.join = function(socket, io, msg_str) {
    console.log("RECEIVING from " + socket.id + ": \'joining someone\': " + msg_str);
    var msg = JSON.parse(msg_str);
    Clients.find({'_id': msg.id.toObjectId()}).populate('roomID').exec(function(err, clientList) {
	if(clientList.length != 0) {
	    Clients.find({'shortID': msg.dest}).populate('roomID').exec(function(err, clientList2) {
		if(clientList2.length != 0) {
		    var self = clientList[0];
		    var target = clientList2[0];

		    if (target.connected == false) {
			//TODO emit error message
		    } else {
			Room.update({"_id": self.roomID}, {$pull: {'clients': self._id}}, function(err, result) {
			    if (target.roomID == null) {
				var newRoom = Room({
				    'clients': []
				});
				newRoom.save(function(err, resultRoom) {
				    if (resultRoom) {
					Clients.update({"_id": msg.id.toObjectId()}, {$set: {'roomID': resultRoom.id}}, function(err, resultPush1) {
					    if (resultPush1) {
						Clients.update({"shortID": msg.dest}, {$set: {'roomID': resultRoom.id}}, function(err, resultPush2) {
						    if (resultPush2) {
							Room.update({"_id": resultRoom.id}, {$push: {'clients': self._id}}, function(err, result) {
							    if (result) {
								Room.update({"_id": resultRoom.id}, {$push: {'clients': target._id}}, function(err, result) {

								    Room.find({'_id': resultRoom.id}).populate('clients').exec(function(err, roomResultF) {
									if (roomResultF.length != 0) {
									    for (var i = 0; i < roomResultF[0].clients.length; i++) {
										var json_res = {'connected_to': target.shortID};
										if (io.sockets.connected[roomResultF[0].clients[i].socketID] != undefined) {
										    console.log("EMITING   to   " + roomResultF[0].clients[i].socketID + ": \'connected_to\': " + JSON.stringify(json_res));
										    io.sockets.connected[roomResultF[0].clients[i].socketID].emit('connected_to', json_res);
										}
									    }

									    for (var i = 0; i < roomResultF[0].clients.length; i++) {
										if (roomResultF[0].clients[i].socketID != socket.id) {
										    var json_res = {'car_id': self.shortID, 'car_no': self.carNumber};
										    if (io.sockets.connected[roomResultF[0].clients[i].socketID] != undefined) {
											console.log("EMITING   to   " + roomResultF[0].clients[i].socketID + ": \'add car\': " + JSON.stringify(json_res));
											io.sockets.connected[roomResultF[0].clients[i].socketID].emit('add car', json_res);
										    }
										}
									    }

									    for (var i = 0; i < roomResultF[0].clients.length; i++) {
										if (roomResultF[0].clients[i].socketID != socket.id) {
										    var json_res = {'car_id': roomResultF[0].clients[i].shortID, 'car_no': roomResultF[0].clients[i].carNumber};
										    console.log("EMITING   to   " + socket.id + ": \'add car\': " + JSON.stringify(json_res));
										    socket.emit('add car', json_res);
										}
									    }
									}
								    });
								});
							    }
							});
						    }
						});
					    }
					});
				    }
				});
			    } else {
				Clients.update({"_id": msg.id.toObjectId()}, {$set: {'roomID': target.roomID}}, function(err, resultPush1) {
				    if (resultPush1) {
					Room.update({"_id": target.roomID}, {$push: {'clients': self._id}}, function(err, result) {
					    if (result) {
						Room.find({'_id': target.roomID}).populate('clients').exec(function(err, roomResultF) {
						    if (roomResultF.length != 0) {
							for (var i = 0; i < roomResultF[0].clients.length; i++) {
							    var json_res = {'connected_to': target.shortID};
							    if (io.sockets.connected[roomResultF[0].clients[i].socketID] != undefined) {
								console.log("EMITING   to   " + roomResultF[0].clients[i].socketID + ": \'connected_to\': " + JSON.stringify(json_res));
								io.sockets.connected[roomResultF[0].clients[i].socketID].emit('connected_to', json_res);
							    }
							}

							for (var i = 0; i < roomResultF[0].clients.length; i++) {
							    if (roomResultF[0].clients[i].socketID != socket.id) {
								var json_res = {'car_id': self.shortID, 'car_no': self.carNumber};
								if (io.sockets.connected[roomResultF[0].clients[i].socketID] != undefined) {
								    console.log("EMITING   to   " + roomResultF[0].clients[i].socketID + ": \'add car\': " + JSON.stringify(json_res));
								    io.sockets.connected[roomResultF[0].clients[i].socketID].emit('add car', json_res);
								}
							    }
							}

							for (var i = 0; i < roomResultF[0].clients.length; i++) {
							    if (roomResultF[0].clients[i].socketID != socket.id) {
								var json_res = {'car_id': roomResultF[0].clients[i].shortID, 'car_no': roomResultF[0].clients[i].carNumber};
								console.log("EMITING   to   " + socket.id + ": \'add car\': " + JSON.stringify(json_res));
								socket.emit('add car', json_res);
							    }
							}
						    }
						});

					    }
					});
				    }
				});
			    }
			});
		    }
		}
	    });
	}
    });
}
