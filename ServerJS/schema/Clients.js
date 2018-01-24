var mongoose = require('mongoose');

var Schema = mongoose.Schema;

var clientsSchema = new Schema({
    shortID: String,
    socketID: String,
    connected: Boolean,
    carNumber: {type: Number, default: 0},
    money: {type: Number, default: 0},
    roomID: {type: mongoose.Schema.Types.ObjectId, ref: 'Room'},
    raceID: {type: mongoose.Schema.Types.ObjectId, ref: 'Race'},

    posX: {type: Number, default: 0},
    posY: {type: Number, default: 0},
    posZ: {type: Number, default: 0},
    
    rotX: {type: Number, default: 0},
    rotY: {type: Number, default: 0},
    rotZ: {type: Number, default: 0},

    LinearX: {type: Number, default: 0},
    LinearY: {type: Number, default: 0},
    LinearZ: {type: Number, default: 0},
    
    AngularX: {type: Number, default: 0},
    AngularY: {type: Number, default: 0},
    AngularZ: {type: Number, default: 0},
    
    engine: {type: Number, default: 0},
    breaking: {type: Number, default: 0},
    steering: {type: Number, default: 0}
});

module.exports = mongoose.model('Client', clientsSchema);


