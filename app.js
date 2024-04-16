const express = require('express');
const os = require('os');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
    res.send('Hello World!');
    console.log('Hello World!');
    }
);

app.listen(port, () => {
    let networkInterfaces = os.networkInterfaces();
    console.log(`Example app listening at http://localhost:${port}`);

    for (let interface in networkInterfaces) {
        for (let networkDetail of networkInterfaces[interface]) {
            if (networkDetail.family === 'IPv4' && !networkDetail.internal) {
                console.log(`Also accessible at http://${networkDetail.address}:${port}`);
            }
        }
    }
});