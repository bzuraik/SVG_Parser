'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

// Function to get current filenames
// in directory with specific extension

//******************** Your code goes here ********************

let sharedLib = ffi.Library('./libsvgparser', {
  'JSONString': [ 'string', ['string', 'string']],
  'JSONStringRect': [ 'string', ['string', 'string'] ],
  'JSONStringCirc': [ 'string', ['string', 'string'] ],
  'JSONStringPath': [ 'string', ['string', 'string'] ],
  'JSONStringGroup': [ 'string', ['string', 'string'] ],
  'JSONStringTandD': [ 'string', ['string', 'string'] ],
  'scaleShape': [ 'string', ['string', 'string','string','int', 'string']]			//return type first, argument list second
	
});
 

 

app.get('/endpoint1', function(req , res){
  let files = fs.readdirSync('uploads');
  const retStr = new Array();
  const c = [];
  let bool;
  files.forEach(file => {
    if (path.extname(file) == ".svg")
    {
      let c1 = (sharedLib.JSONString('./uploads/'+file, './uploads/svg.xsd'));
      if(c1!== null)
      {
        let c2 = JSON.parse(c1);
        c.push(c2);
        retStr.push(file)
      }
      
      
    }
  })
  res.send(
    {
      somethingElse: retStr,
      JSONString: c,
    }
  );
});



app.get('/endpoint2', function(req , res){
  let files = fs.readdirSync('uploads');
  const retStr = new Array();
  const c = [];
  let R1, R2;
  let C1, C2;
  let P1, P2;
  let G1, G2;
  let TD1,TD3;
  let num = 0;
  files.forEach(file => {
    if (path.extname(file) == ".svg")
    {

      R1 = (sharedLib.JSONStringRect('./uploads/'+req.query.data1, './uploads/svg.xsd'));
      R2 = JSON.parse(R1);

      C1 = (sharedLib.JSONStringCirc('./uploads/'+req.query.data1, './uploads/svg.xsd'));
      C2 = JSON.parse(C1);

      P1 = (sharedLib.JSONStringPath('./uploads/'+req.query.data1, './uploads/svg.xsd'));
      P2 = JSON.parse(P1);

      G1 = (sharedLib.JSONStringGroup('./uploads/'+req.query.data1, './uploads/svg.xsd'));
      G2 = JSON.parse(G1);

      TD1 = (sharedLib.JSONStringTandD('./uploads/'+req.query.data1, './uploads/svg.xsd'));
      TD3 = JSON.parse(TD1);


      retStr.push(file)
      
    }  
  })
  res.send(
    {
      somethingElse: retStr,
      JSONRect: R2,
      JSONCirc: C2,
      JSONPath: P2,
      JSONGroup: G2,
      JSONTnD: TD3,

    }
  );
});


app.get('/endpoint3', function(req , res){

  let value = (sharedLib.scaleShape('./uploads/'+req.query.data1, './uploads/svg.xsd', req.query.data2, req.query.data3, req.query.data4));
  
  res.send(
    {
      
      bool: value

    }
  );
});

app.get('/endpoint4', function(req , res){

  var obj = new Object();
   obj.title = req.query.title;
   obj.descr  = req.query.desc;
  var jsonString= JSON.stringify(obj);
   
  
  res.send(
    {
      
      bool: value

    }
  );
});



app.listen(portNum);
console.log('Running app at localhost: ' + portNum);