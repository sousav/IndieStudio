// Extending String to cast any String to mongoose objectID
String.prototype.toObjectId = function() {
    var ObjectId = (require('mongoose').Types.ObjectId);
    if (ObjectId.isValid(this.toString())) {
	return new ObjectId(this.toString());
    } else {
	return new ObjectId("zzzzzzzzzzzz");
    }
};
