var express = require('express');
var app = express();

function randomIntInc(low, high) {
    return Math.floor(Math.random() * (high - low + 1) + low)
}

//Middleware
app.set('view engine', 'ejs');
app.use(express.static('static'));


let sport = "fa fa-running";
let bus = "fa fa-train";
let atom = "fas fa-atom";
let health = "fas fa-comment-medical";
let book = "fa fa-book";
as2D= new Array(); // an array of "whatever"
as2D[0]= [health, health, book, bus];
as2D[1]= [bus,book,atom,health];
as2D[2]= [atom,health,atom,book];
as2D[3]= [bus,sport,sport,health];
as2D[4]= [atom,sport,bus,health];
as2D[5]= [book,sport,atom,health];

en2D= new Array(); // an array of "whatever"
en2D[0]= [true,false,true, true];
en2D[1]= [true,true,true, true];
en2D[2]= [true,true,true, false];
en2D[3]= [true,false,true, true];
en2D[4]= [true,true,true, true];
en2D[5]= [true,true,true, true];

win2D= new Array(); // an array of "whatever"
win2D[0]= ['win', 'loose', 'loose', 'loose'];
win2D[1]= ['loose', 'loose', 'loose', 'loose'];
win2D[2]= ['loose', 'loose', 'loose', 'loose'];
win2D[3]= ['loose', 'loose', 'loose', 'loose'];
win2D[4]= ['loose', 'loose', 'loose', 'loose'];
win2D[5]= ['loose', 'loose', 'loose', 'loose'];

fact = [
    "Every year smokers burn through 5.5 trillion cigarettes",
    "Cigarette butts are the biggest ocean contaminant",
    "A single butt in just one liter of water can poison and kill a fish.",
    "Cigarette butts cause a surprising number of fires every year.",
    "Depending on the conditions of the area the cigarette butt is discarded in, it can take 18 months to 10 years for a cigarette filter to decompose.",
    "Smoking materials like cigarettes, pipes, and cigars, cause around 90,000 fires every year in the United States and are the number one cause of fire-related deaths.",
    "There are more than 1 billion smokers in the world today, and if current trends continue, that number is expected to increase to 1.6 billion by the year 2025.",
    "China is home to more than 300 million smokers (one-third of the world's smokers) and they consume approximately 2.3 trillion cigarettes a year.",
    "Worldwide, approximately 10 million cigarettes are purchased a minute, 15 billion are sold each day, and upwards of 5 trillion are produced and used on an annual basis.",
    "Five trillion cigarette filters weigh approximately 2 billion pounds.",
    "All these cigarette butts cost big bucks to clean up. Cities spend between $3 million and $16 million on cigarette clean-up.",
    "1.69 billion pounds of cigarette butts winding up as toxic trash each year.",
    "A recent study found that a cigarette butt was only about 38 percent decomposed after two years.",
    "Cigarette butts have long been the single most collected item on the world’s beaches, with a total of more than 60 million collected over 32 years.",
    "In 10 years there may be more cigarette butts in the World than fish.if people don’t change in the mentality."
]

//app.use(function(req, res){
//    res.render('app', {as2D, en2D, win2D})
//});
app.get('/', function(req, res) {
    res.render('app', {as2D, en2D, win2D})
});
app.get('/win', function(req, res) {
    res.render('win', {curr_fact: fact[randomIntInc(0,14)]})
});
app.get('/loose', function(req, res) {
    res.render('loose', {curr_fact: fact[randomIntInc(0,14)]})
});

app.listen(80);