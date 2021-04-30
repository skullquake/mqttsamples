crow.add_header(crow.res,"Content-Type","text/plain");
try{
	function exec(cmd){
		var ret=null;
		var fd=std.popen(cmd,"r");
		var line;
		ret="";
		while((line=fd.getline())!=null){
			ret+=line+"\n";
			//crow.write(crow.res,line);
			//crow.write(crow.res,"\n");
		}
		return ret;
	}
	//crow.write(crow.res,exec("curl http://localhost:8081/version"));
	for(var i=0;i<32;i++){
		crow.write(crow.res,exec("ps -e"));
	}
}catch(e){
	crow.write(crow.res,e.toString());
}
crow.end(crow.res);
