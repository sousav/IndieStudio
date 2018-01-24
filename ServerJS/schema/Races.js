var mongoose = require('mongoose');

var Schema = mongoose.Schema;

var raceSchema = new Schema({
    raceID: Number,
    leader: {type: mongoose.Schema.Types.ObjectId, ref: 'Client'},
    clients: [{type: mongoose.Schema.Types.ObjectId, ref: 'Client'}]
});

module.exports = mongoose.model('Race', raceSchema);


