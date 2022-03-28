# SVG_Parser
- A full-stack CRUD application that parses SVG files through XML and displays various location properties
- Implementing a dynamic frontend with jQuery that allows the user to log into a MySQL database and store information related to the SVG files. (MySQL part is under progress) 
- Integrating the full C backend with Node.js through the ffi-napi library.






https://user-images.githubusercontent.com/95400232/159369822-9adfd1f3-bb2b-4c77-bd55-441aa2f11857.mp4

## UI breakdown
### File Log Panel
    - This panel displays the list of all valid SVG files on the server, including all the files uploaded from client and the all
      files created from scratch by the client.
    - The panel contains a link to the downloadable SVG file, and a summary of that file’s properties:
        • Image thumbnail (clickable download). 
        • File name (clickable download)
        • File size.
        • Total number of rectangles
        • Total number of circles
        • Total number of paths
        • Total number of groups
        
### SVG View Panel
    - This panel shows components in the currently open file, one line per component.
    - Above the panel, there is a drop-down list of file names. The list will contain only valid SVG files.
    
Functionalities:
- Upload SVG Files



## Installation of Node App

### 1. Install dependancies

```Bash
# From the root of the directory
npm install
```


## Directory Structure

```Bash
# This contains the Backend Node Server, with my Web Application and API
app.js

# These are the package configuration files for npm to install dependencies
package.json
package-lock.json

# This is the Frontend HTML file that you see when you visit the document root
public/index.html

# This is the Frontend browser JavaScript file
public/index.js

# This is the Frontend Custom Style Sheet file
public/style.css

# This is the directory for uploaded .svg files
upload/

# This is the directory where I put all my C parser code
parser/
```



#### Browser JavaScript

How to $.ajax: https://stackoverflow.com/a/22964077/5698848

```JavaScript
// I'm using jQuery library
// document.ready just means this JS runs when the document element (body) is loaded
// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {

// This is an Asynchronous JavaScript Request (AJAX) using jQuery
// We can use this to query our API endpoints
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type -  
        url: '/someendpoint',   //The server endpoint we are connecting to
        success: function (data) {
            /*  Do something with returned object
            Note that what we get is an object, not a string, 
            so we do not need to parse it on the server.
            JavaScript really does handle JSONs seamlessly
            */
            $('#blah').html("On page load, Received string '"+JSON.stringify(data)+"' from server");
            //We write the object to the console to show that the request was successful
            console.log(data);  
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
// When you "submit" an HTML form, the default action is to redirect to another page
// This overrides it and allows us to make an AJAX request and edit data on the page
    $('#someform').submit(function(e){
        $('#blah').html("Callback from the form");
        e.preventDefault();
        $.ajax({});
    });
});
```


### NodeJS Libraries

```JavaScript
// Strict Mode
'use strict'

// This gives me direct access to C functions from our library

const ffi = require('ffi-napi');

// Express App library
const express = require("express");
const app     = express();

// Path utility library
const path    = require("path");

// File Upload library

const fileUpload = require('express-fileupload');
app.use(fileUpload());

// File reading and manipulating library
const fs = require('fs');

// Minimization, this is to obfuscate JavaScript
// Obfuscation and Minimization are ways to reduce payload size
// And to get scripts to clients quicker because of the smaller size
const JavaScriptObfuscator = require('javascript-obfuscator');
```





