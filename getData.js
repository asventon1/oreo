let fs = require('fs');

let data = require('./data.json');
console.log(data);

data.rpm = [20, 50, 22, 100, 90, 50];
data.time = [1591408303];



console.log(data);
fs.writeFileSync('./data.json', JSON.stringify(data));