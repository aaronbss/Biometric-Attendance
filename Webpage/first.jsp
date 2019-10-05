<html>
    <head>
	

<body>
	
	 <div class="container-login100" style="background-image: url('static/tert2.jpg');">
	 </body>
        <meta name="viewport" content="width=device-width, initial-scale=1">  
<style>
/* Style the buttons */


/* Style the active class, and buttons on mouse-over */
.active, .btnd:hover {
    background-color: #0BA61C;
    color: green;
}
body{
    background-color: #efefef
}
html{
       padding-top: 100px;
}
</style>
           
        <title>FRCRCE STUDENT ATTENDANCE</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

          <link rel="stylesheet" href="newcss.css"> 
                  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

          
          
          
          <link href="asset/css/bootstrap.min.css" rel="stylesheet">
          <link href="css/bootstrap.css" rel="stylesheet">
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
       <!-- <script>
            $(document).ready(function(){
                $('#submit').on("click",function() {
                 //$("#course").change(function(){
                     var value = $('#course').val();
                      var value1 = $('#grade').val();
                     $.get("data.jsp",{course:value,grade:value1},function(data){
                      $("#javaquery").html(data);
                     });
                 });
             });
        </script> -->
          

        
        <style>
            
            
           {
                 height: 100%;
                
  
   margin: 0;
  background-repeat: no-repeat;
  background-attachment: fixed;
                
 background-size: cover;
  background-image: url(static\background.jpg);
  font-family: "Roboto", sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
            .form-group{
                
                color: white;
            }
            
            .text{
                color: white;
            }
            #submit{
                color: white;
            }
            
                       .button {
    background-color: #efefef; /* Green */
    border: none;
    color: white;
    padding: 9px 30px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    -webkit-transition-duration: 0.4s; /* Safari */
    transition-duration: 0.4s;
    cursor: pointer;
}

            
            
            .button5 {
    background-color: white;
    color: black;
    border: 2px solid #555555;
}

.button5:hover {
    background-color: #555555;
    color: white;
} 
         
            </style>
        
          
<style>  
body {  

    font-family: "Helvetica Neue",Helvetica,Arial,sans-serif;
    font-size: 14px;
    line-height: 1.42857143;
    color: #333;
    background-color: #dff0d8;
}  
</style>  

	
	
		
        
    </head>
    <body>
       <!-- <%response.setHeader("Cache-Control", "no-cache");
    response.setHeader("Cache-Control", "no-store");
    response.setHeader("Pragma", "no-cache");
    response.setDateHeader("Expires", 0);%>
             <%/*
                if(session.getAttribute("email")==null){
                     response.sendRedirect("loginn.jsp");
                }*/
%> -->
        <div class="wrapper">
        
        
        
        
         <nav class="navbar navbar-inverse navbar-fixed-top">
  <div class="container">
    <div class="navbar-header">
      <button class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="/">FR. CRCE STUDENT ATTENDANCE</a>
      <ul class="nav navbar-nav side-bar myDIV">
        <!--  <li class="side-bar tmargin btnd"><a href="register.jsp"><span class="glyphicon glyphicon-list">&nbsp;</span>Register</a></li>
      -->    <!-- <li class="side-bar btnd"><a href="addmarks.jsp"><span class="glyphicon glyphicon-flag">&nbsp;</span>V Marks</a></li>--> 
         <!--<li class="side-bar btnd active"><a href="first.jsp"><span class="glyphicon glyphicon-star">&nbsp;</span>View Students</a></li>-->
     <!--     <li class="side-bar btnd"><a href="addadmin.jsp"><span class="glyphicon glyphicon-certificate">&nbsp;</span>Add Admin</a></li>
          <li class="side-bar btnd"><a href="del.jsp"><span class="glyphicon glyphicon-signal">&nbsp;</span>Delete Student</a></li>
     -->     <li class="side-bar btnd"><a href="login"><span class="glyphicon glyphicon-cog">&nbsp;</span>Logout</a></li>
  
        </ul>
    </div>
  <!-- <div class="collapse navbar-collapse">
      <ul class="nav navbar-nav navbar-right">
        <li><a href="#"><span class="glyphicon glyphicon-user">&nbsp;</span>Hello Admin</a></li>
        <li class="active"><a title="View Website" href="#"><span class="glyphicon glyphicon-globe"></span></a></li>
        <li><a href="#">Logout</a></li>
      </ul>
    </div>-->
  </div>
            
            
            <div class="collapse navbar-collapse">
      
      
    <div id="sidebar">
      <!--<div class="container-fluid tmargin">
        <div class="input-group">
          
        </div>
      </div>--> 

         
   
    </div>

     
    </div>
            
            
</nav>
        
	
	
	 
		 
  
<div class="container-fluid">
  
  <div class="col-md-3">

    
  </div>     
			
        <br>
		
		<div>	
		
	

 </form>
          <div class='myDiv'>
	      <form role="form"  method="post" action="">
          <input class="button button5" type="submit"  name="VLSI" value="VLSI" />
         </form>
		  </div>
    	
		 
	     <form role="form"  method="post" action="" >
         <input class="button button5" type="submit"  name="Embedded Systems Attendance" value="Embedded Systems Attendance" />
         </form>
		  
		<form role="form"  method="post" action="">
        <input class="button button5" type="submit"  name="Digital Processing" value="Digital Processing" />
         </form>
		 
		 <form role="form"  method="post" action="">
        <input class="button button5" type="submit"  name="Lectures Conducted" value="Lectures Conducted" />
         </form>
		 
		<form role="form"  method="post" action="">
        <input class="button button5" type="submit"  name="Total Attendance" value="Total Attendance" />
         </form>
		 
		 
		 
</div>
<div class="container h-100">
            <div class="row align-items-center h-100">
                <div class="col-md-9 col-sm-10 mx-auto">
                    <div class="h-100 justify-content-center">
                        {% block content %}  {% endblock %}
              
                    </div>
                </div>
            </div>
        </div>
  </div>
</div>
            
             <script src="asset/js/bootstrap.min.js"></script>
    </body>
</html>



