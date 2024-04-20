const mongoose=require("mongoose");
require("dotenv").config();
const dbconnect=()=>{
    mongoose.connect(process.env.DATABASE_URL,{
        useNewUrlParser:true,
        useUnifiedTopology: true,
    })
    .then(()=>{console.log("Connection secure");})
    .catch((error)=>{console.log(error);})
}
module.exports=dbconnect;