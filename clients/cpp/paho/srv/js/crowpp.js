crowpp.add_header("Content-Type","text/plain");
try{
	{//write sample
		crowpp.write(["&req",crow.req].join(":"));
		crowpp.write("\n");
		crowpp.write(["&res",crow.res].join(":"));
		crowpp.write("\n");
		for(var i=0;i<8;i++){
			crowpp.write(Math.random());
			crowpp.write("\n");
		}
	}
	/*
	{//exec proc sample
		var fd=std.popen("tree ./obj","r");
		var line;
		while((line=fd.getline())!=null){
			crowpp.write(line);
			crowpp.write("\n");
		}
	}
	{//exec proc sample
		var fd=std.popen("curl http://localhost:8081/version","r");
		var line;
		while((line=fd.getline())!=null){
			crowpp.write(line);
			crowpp.write("\n");
		}
	}

	{//read file sample
		var rdfile=std.open("./Makefile","r");
		do{
			crowpp.write(rdfile.getline());
			crowpp.write("\n");
		}while(!rdfile.eof());
		rdfile.close();
	}
	*/
	crowpp.write(crowpp.get_loglevel());
	crowpp.set_loglevel("debug");
	crowpp.write(crowpp.get_loglevel());
	crowpp.set_loglevel("error");
	crowpp.write(crowpp.get_loglevel());
	crowpp.set_concurrency(1);
	crowpp.set_multithreaded();
	crowpp.set_concurrency(4);
	crowpp.set_port(8081);
	crowpp.write(crowpp.remoteIpAddress());crowpp.write("\n");
	crowpp.write(crowpp.get_url_param("k0"));crowpp.write("\n");
	//crowpp.run();
}catch(e){
	crowpp.write(e.toString());
}
crowpp.end();
//crowpp.stop();
