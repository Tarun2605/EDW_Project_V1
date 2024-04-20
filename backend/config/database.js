const mongoose=require("mongoose");
require("dotenv").config();
const dbconnect=()=>{
    mongoose.connect("mongodb+srv://steelandmasterquantor:Qm6LEmbrVZLQ2CCc@edwgamev1.2jiloro.mongodb.net/",{
        useNewUrlParser:true,
        useUnifiedTopology: true,
    })
    .then(()=>{console.log("Connection secure");})
    .catch((error)=>{console.log(error);})
}
module.exports=dbconnect;