const mongoose = require("mongoose");
const gameSchema = new mongoose.Schema({
    game : {
        type : String,
        required : true
    },
    gamedata : {
        type : JSON,
        required : true
    },
    updatedAt : {
        type : Date,
        default : Date.now
    }
});
module.exports = mongoose.model("game", gameSchema);