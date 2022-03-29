// Put all onload AJAX calls here, and event listeners
jQuery(document).ready(function() {
    // On page-load AJAX Example
    // var input = $( "input" ).first().val();
    // var filenameUploaded = input.substring(12);
    
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/endpoint1',   //The server endpoint we are connecting to
        data: {
            // data: filenameUploaded
            
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */  $("#FileChose").hide();
                $("#ScaleOption").hide();
                $("#scaleORadd").hide();
                $("#editTitle-desc").hide();

                $("#Edit").on('click', function() {
                    $("#EditORADD").hide();
                    $("#FileChose").show();
                    
                });
                $("#Confirm").on('click', function() {
                    $("#FileChose").hide();
                    $("#scaleORadd").show();
                    
                });

                $("#Scale").on('click', function() {
                    $("#FileChose").hide();
                    $("#scaleORadd").hide();
                    $("#ScaleOption").show();   
                });

                $("#Back1").on('click', function() {
                    $("#FileChose").hide();
                    $("#EditORADD").show();
                });

                $("#Back2").on('click', function() {
                    $("#scaleORadd").hide();
                    $("#FileChose").show();
                });

                $("#Back3").on('click', function() {
                    $("#ScaleOption").hide();
                    $("#scaleORadd").show();
                });

                $('button').on('click', function(){
                    $('button').removeClass('selected');
                    $(this).addClass('selected');
                    $('#scale').attr('readonly', false);
                });
                $("#ShapesAdd").hide();
                $("#Back4").hide();
                $("#TandD").hide();
                $("#Add").on('click', function() {
                    $("#EditORADD").hide();
                    $("#ShapesAdd").show();
                    $("#Back4").show();
                    $("#TandD").show();
                    
                });

                $("#Back4").on('click', function() {
                    $("#EditORADD").show();
                    $("#ShapesAdd").hide();
                    $("#Back4").hide();
                    $("#TandD").hide();
                    
                });
                $("#AddSh").hide();
                $("#Back5").hide();
                $("#AddShape").on('click', function() {
                    $("#FileChose").hide();
                    $("#scaleORadd").hide();
                    $("#AddSh").show();
                    $("#Back5").show();
                });

                $("#Back5").on('click', function() {
                    $("#scaleORadd").show();
                    $("#Back5").hide();
                    $("#AddSh").hide();
                });
                
                $("#title-desc").on('click', function() {
                    $("#scaleORadd").hide();
                    $("#editTitle-desc").show();
                    $("#Back6").show();
                });

                $("#Back6").on('click', function() {
                    $("#scaleORadd").show();
                    $("#Back6").hide();
                    $("#editTitle-desc").hide();
                });
                
            
            // jQuery('#blah').html("On page load, received string " + data.somethingElse +"from server");
            var select = document.getElementById("selectNumber");

            for(var i = 0; i < data.somethingElse.length; i++) {
                var opt = data.somethingElse[i];
                var el = document.createElement("option");
                el.textContent = opt;
                el.value = opt;
                select.appendChild(el);
            }

            var select = document.getElementById("selectNumber2");

            for(var i = 0; i < data.somethingElse.length; i++) {
                var opt = data.somethingElse[i];
                var el = document.createElement("option");
                el.textContent = opt;
                el.value = opt;
                select.appendChild(el);
            }
            
            var table = document.getElementById("table");
            var cont = document.getElementById("cont");
            for (var i = 0; i <data.somethingElse.length; i++) { 
                
                
                var rows = table.insertRow();
                var cell1 = rows.insertCell(0);
                var cell2 = rows.insertCell(1);
                var cell3 = rows.insertCell(2);
                var cell4 = rows.insertCell(3);
                var cell5 = rows.insertCell(4);
                var cell6 = rows.insertCell(5);
                var cell7 = rows.insertCell(6);
            // var cell1 = row.insertCell(0);
            // var cell2 = row.insertCell(1);
                // cell1.innerHTML = i+1;
                
                cell1.setAttribute("class", "image"+[i]);//images
                cell1.setAttribute("id", "image");
                var img = "<img src='/uploads/"+data.somethingElse[i]+"'>";
                $(".image"+[i]).append(img);


                // cell2.innerHTML = data.somethingElse[i];//filenames
                var img = "<a href='"+data.somethingElse[i]+"' download>"+data.somethingElse[i]+"</a>";
                cell2.setAttribute("class", "filename"+[i]);
                $(".filename"+[i]).append(img);

                cell3.innerHTML = "1kb";//filesize

                cell4.innerHTML = data.JSONString[i].numRect;//Rect
                // cell4.setAttribute("class", "Rect");
                
                cell5.appendChild(document.createTextNode(data.JSONString[i].numCirc));//Circ

                cell6.innerHTML = data.JSONString[i].numPaths;//Paths

                cell7.innerHTML = data.JSONString[i].numGroups;//Group
                // var el = document.createElement('img');
                
                // table.appendChild(el)   
                
            
            }
            
            
            //We write the object to the console to show that the request was successful
            // console.log(data); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            window.alert("On page load, received error from server");
            console.log(error); 
        }
    });

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#myForm').change(function(e){
        
        // $('#rows5').remove();
        let id = $('#selectNumber').val();
        let id2 = $('#selectNumber2').val();
        var num;
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/endpoint2',
            data: {
                data1: id,
                data2: id2
            },

            success: function (data) {
                
                for (var i = 0; i <= 3000; i++){
                    $('#rows').remove();
                }
                var table = document.getElementById("tg2");
                // $('.Secondary').reset();
                for (var i = 0; i <data.somethingElse.length; i++){

                    if((id.localeCompare(data.somethingElse[i])) == 0)
                    {
                        
                        $("#bigImage").attr("src","uploads/"+data.somethingElse[i]);// chnaging big image
                        $(".title").html(data.JSONTnD.title);
                        $(".desc").html(data.JSONTnD.desc);
                        for (var j = 0; j <data.JSONRect.length; j++){ // RECTS
                            num++;
                            var rows = table.insertRow();
                            rows.setAttribute("id", "rows");
                            var cell1 = rows.insertCell(0);
                            cell1.setAttribute("class", "Secondary");
                            cell1.innerHTML = "Rectangle "+(j+1);//filesiz

                            var cell2 = rows.insertCell(1);
                            cell2.setAttribute("class", "Secondary");
                            let units = data.JSONRect[j].units;
                            if(data.JSONRect[j].units == "")
                            {
                                units = " ";
                            }
                            cell2.appendChild(document.createTextNode("Upper left corner: x = "+data.JSONRect[j].x+units+", "+"y = "+data.JSONRect[j].y+units+", "+ "width = "+data.JSONRect[j].w+units+", "+ "height = "+data.JSONRect[j].h+units+" "));
                            
                            var cell3 = rows.insertCell(2);
                            cell3.setAttribute("class", "Secondary");
                            cell3.innerHTML = data.JSONRect[j].numAttr;//filesiz
                        }
                        for (var j = 0; j <data.JSONCirc.length; j++){ // Circ
                            num++;
                            var rows = table.insertRow();
                            rows.setAttribute("id", "rows");
                            var cell1 = rows.insertCell(0);
                            cell1.setAttribute("class", "Secondary");
                            cell1.innerHTML = "Circle "+(j+1);

                            var cell2 = rows.insertCell(1);
                            cell2.setAttribute("class", "Secondary");
                            let units = data.JSONCirc[j].units;
                            if(data.JSONCirc[j].units == "")
                            {
                                units = " ";
                            }
                            cell2.appendChild(document.createTextNode("Centre: cx = "+data.JSONCirc[j].cx+units+", "+"cy = "+data.JSONCirc[j].cy+units+", "+ "r = "+data.JSONCirc[j].r+units+", "));
                            
                            var cell3 = rows.insertCell(2);
                            cell3.setAttribute("class", "Secondary");
                            cell3.innerHTML = data.JSONCirc[j].numAttr;//filesiz
                        }
                        for (var j = 0; j <data.JSONPath.length; j++){ // Path
                            num++;
                            var rows = table.insertRow();
                            rows.setAttribute("id", "rows");
                            var cell1 = rows.insertCell(0);
                            cell1.setAttribute("class", "Secondary");
                            cell1.innerHTML = "Path "+(j+1);

                            var cell2 = rows.insertCell(1);
                            cell2.setAttribute("class", "Secondary");
                            cell2.appendChild(document.createTextNode("data = "+data.JSONPath[j].d));
                            
                            var cell3 = rows.insertCell(2);
                            cell3.setAttribute("class", "Secondary");
                            cell3.innerHTML = data.JSONPath[j].numAttr;//filesiz
                        }
                        for (var j = 0; j <data.JSONGroup.length; j++){ // Path
                            num++;
                            var rows = table.insertRow();
                            rows.setAttribute("id", "rows");
                            var cell1 = rows.insertCell(0);
                            cell1.setAttribute("class", "Secondary");
                            cell1.innerHTML = "Group "+(j+1);

                            var cell2 = rows.insertCell(1);
                            cell2.setAttribute("class", "Secondary");
                            cell2.appendChild(document.createTextNode("children = "+data.JSONGroup[j].children));
                            
                            var cell3 = rows.insertCell(2);
                            cell3.setAttribute("class", "Secondary");
                            cell3.innerHTML = data.JSONGroup[j].numAttr;//filesiz
                        }
                        
                        // $("#bigImage").attr("src","uploads/"+data.somethingElse[i]);
                    } 
                }
                
                // $('#filename').html(data1);
                //We write the object to the console to show that the request was successful
                // console.log(data); 
                
            },
            fail: function(error) {
                // Non-200 return, do something with error
                alert("On page load, received error from server");
                console.log(error); 
            }
            //Create an object for connecting to another waypoint
        });
    });

    $('#ConfirmScale').on('click', function(e){
        
        // $('.test').html("boring");
        // $('#rows5').remove();
        let id = $('#selectNumber2').val();
        let elem = $('input[name="option"]:checked').val();
        let index = 2;
        let value =  $('#factor').val();;
        
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            type: 'get',            //Request type
            dataType: 'text',       //Data type - we will use JSON for almost everything 
            url: '/endpoint3',
            data: {
                data1: id,
                data2: elem,
                data3: index,
                data4: value
                
            },

            success: function (data) {
                        location.reload();
                    
                
                
            },
            fail: function(error) {
                // Non-200 return, do something with error
                window.alert("On page load, received error from server");
                console.log(error); 
            }
            //Create an object for connecting to another waypoint
        });
    });

});




// document.getElementById('test').addEventListener('click', function() {
//     var singleValues = $( "#test" ).val();
//     alert(singleValues);s
// }, false);

