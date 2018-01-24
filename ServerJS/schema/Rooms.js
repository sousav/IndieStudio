var mongoose = require('mongoose');

var Schema = mongoose.Schema;

var roomSchema = new Schema({
    clients: [{type: mongoose.Schema.Types.ObjectId, ref: 'Client'}],
    races: [{type: mongoose.Schema.Types.ObjectId, ref: 'Race'}]
});

module.exports = mongoose.model('Room', roomSchema);


