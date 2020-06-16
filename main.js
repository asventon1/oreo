let express = require('express');
let fs = require('fs');
let bodyParser = require('body-parser');

let app = express();

app.use(bodyParser.urlencoded({extender: false}));
app.use(bodyParser.json());

app.set('view engine', 'ejs');
app.use(express.static('./public'));

app.get('/', function(req, res){
    res.render('index');
});

app.get('/rpmdata', function(req, res){
    let data = fs.readFileSync('./data.json');
    res.json(JSON.parse(data));
});

app.post('/postdata', function(req, res){
    
    let data = require('./data.json');
    //console.log(data);

    data.rpm.push(req.body.rpm);
    data.time.push(req.body.time-3600);

    //console.log(data);
    fs.writeFileSync('./data.json', JSON.stringify(data));
    
   //console.log(req.body);
});

app.listen(3000);
console.log('listening on port 3000');
