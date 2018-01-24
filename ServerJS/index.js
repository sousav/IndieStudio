var http = require('http');
var mongoose   = require('mongoose');
var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end();
});
var io = require('socket.io').listen(app);
var stringExtension = require('./extension/string.js');

// SCHEMA
var Clients = require('./schema/Clients.js');
var Room    = require('./schema/Rooms.js');


// Event
var Login       = require('./Event/login.js');
var JoinRoom    = require('./Event/join_room.js');
var Forward     = require('./Event/forward.js');
var RaceManager = require('./Event/race.js');
var Utils       = require('./Event/utils.js');

mongoose.connect('mongodb://localhost:27017/IDC_db');

io.on('connection', function(socket) {
    console.log("Client         " + socket.id + " connected.");
    socket.emit('give your id', { message: 'Welcome!' });

    // CLIENT DISCONNECTED
    socket.on('disconnect', function() {
	Login.disconnect(socket, io);
    });

    socket.on('debug', function (msg) {
	console.log("RECEIVING from " + socket.id + ": \'debug\': " + msg);
    });
    
    // REGISTER NEW USER / LOGIN KNOWN USERS
    socket.on('id client is', function(msg) {
	Login.login(socket, msg);
    });
    
    // CLIENT TELL US TO CHANGE HIS CAR_ID
    socket.on('carNum changed', function(msg) {
	Login.setCar(socket, msg);
    });
    
    // CLIENT WANT TO JOIN SOMEONE
    socket.on('joining someone', function(msg) {
	JoinRoom.join(socket, io, msg);
    });

    // CLIENT WANT TO SEND POSITION TO OTHER PLAYER IN THE ROOM
    socket.on('send pos', function(msg) {
	Forward.forwardPosition(socket, io, msg);
    });

    // CLIENT WANT TO SEND HIS ENGINE PARAMETERS TO OTHER PLAYER IN THE ROOM
    socket.on('send engine', function(msg) {
	Forward.forwardEngine(socket, io, msg);
    });

    // CLIENT ENTERED A COURSE LOBBY
    socket.on('create race', function(msg) {
	RaceManager.createRace(socket, io, msg);
    });

    // CLIENT IS LEAVING A COURSE LOBBY
    socket.on('leave race', function(msg) {
	RaceManager.leaveRace(socket, io, msg);
    });

    //CLIENT WANT TO START RACE BEEING LEADER
    socket.on('starting race', function(msg) {
	RaceManager.startRace(socket, io, msg);
    });

    // CLIENT WANT TO GET HIS OWN MONEY
    socket.on('get money', function(msg) {
	Utils.getMoney(socket, io, msg);
    });
    
});

app.listen(3000);
