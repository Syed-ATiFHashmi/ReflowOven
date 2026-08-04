#pragma once
const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Reflow Oven</title>

<style>
body{
background:#202124;
color:white;
font-family:Arial;
text-align:center;
}
canvas{
background:#111;
border:1px solid #555;
margin-top:20px;
}
#temp{
font-size:48px;
color:#00ff55;
}
</style>

</head>

<body>

<h2>ESP8266 Reflow Oven</h2>

<div id="temp">0.0°C</div>

<canvas id="graph" width="900" height="450"></canvas>

<script>
const canvas=document.getElementById("graph");
const ctx=canvas.getContext("2d");
let values=[];
function drawGraph()
{
ctx.fillStyle="#111";
ctx.fillRect(0,0,900,450);
ctx.strokeStyle="#333";
for(let i=0;i<10;i++)
{
ctx.beginPath();
ctx.moveTo(0,i*45);
ctx.lineTo(900,i*45);
ctx.stroke();
}
for(let i=0;i<10;i++)
{
ctx.beginPath();
ctx.moveTo(i*90,0);
ctx.lineTo(i*90,450);
ctx.stroke();
}
ctx.strokeStyle="blue";
ctx.lineWidth=3;
ctx.beginPath();
ctx.moveTo(0,420);
ctx.lineTo(200,250);
ctx.lineTo(400,220);
ctx.lineTo(600,80);
ctx.lineTo(750,150);
ctx.lineTo(900,420);
ctx.stroke();
ctx.strokeStyle="red";
ctx.lineWidth=2;
ctx.beginPath();
for(let i=0;i<values.length;i++)
{
let x=i*3;
let y=420-values[i]*1.5;
if(i==0)
ctx.moveTo(x,y);
else
ctx.lineTo(x,y);
}
ctx.stroke();
}
function update()
{
fetch("/data")
.then(r=>r.json())
.then(j=>{
 document.getElementById("temp").innerHTML=j.temp.toFixed(1)+" °C";
 values.push(j.temp);
 if(values.length>300)
 values.shift();
 drawGraph();
});
}
setInterval(update,250);
</script>

</body>
</html>
)rawliteral";
