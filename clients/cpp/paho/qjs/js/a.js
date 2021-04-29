console.log(new Date().getTime()+":"+"./js/a.js:start");
console.log(new Date().getTime()+":topic:"+topic)
console.log(new Date().getTime()+":message:"+message)
console.log(new Date().getTime()+":"+os.platform);
try{
	console.log(new Date().getTime()+":"+os.exec("ls",{
		block:true,
		stdout:function(a){
			console.log("X");
		}
	}));
}catch(e){
	console.log(new Date().getTime()+":"+e.toString());
}
try{
	//var p=std.popen("tree ./","r");
	//var p=std.popen("find ./","r");
	var p=std.popen("find /proc","r");
	//var p=std.popen("ps -es","r");
	var line;
	var buf=[];
	while((line=p.getline())!=null){
		buf.push(line);
	}
	for(var i=0;i<32;i++){
		console.log(i);
		mqtt.publish("cpp_exec_res",""+i);
	}
}catch(e){
	console.log(new Date().getTime()+":"+e.toString());
}

std.evalScript(`console.log(42);`);
os.setTimeout(function(){
	console.log("./js/a.js:cb");
},10)
/*
*/
/*
*/
os.sleep(1000);
console.log(new Date().getTime()+":"+"./js/a.js:end");
