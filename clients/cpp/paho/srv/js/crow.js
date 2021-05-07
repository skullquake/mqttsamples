crow.add_header(crow.res,"Content-Type","text/plain");
try{
	{//write sample
		crow.write(crow.res,["&req",crow.req].join(":"));
		crow.write(crow.res,"\n");
		crow.write(crow.res,["&res",crow.res].join(":"));
		crow.write(crow.res,"\n");
		for(var i=0;i<8;i++){
			crow.write(crow.res,Math.random());
			crow.write(crow.res,"\n");
		}
	}
	{//exec proc sample
		var fd=std.popen("tree ./obj","r");
		var line;
		while((line=fd.getline())!=null){
			crow.write(crow.res,line);
			crow.write(crow.res,"\n");
		}
	}
	{//exec proc sample
		var fd=std.popen("curl http://localhost:8081/version","r");
		var line;
		while((line=fd.getline())!=null){
			crow.write(crow.res,line);
			crow.write(crow.res,"\n");
		}
	}

	{//read file sample
		var rdfile=std.open("./Makefile","r");
		do{
			crow.write(crow.res,rdfile.getline());
			crow.write(crow.res,"\n");
		}while(!rdfile.eof());
		rdfile.close();
	}
}catch(e){
	crow.write(crow.res,e.toString());
}
crow.end(crow.res);
