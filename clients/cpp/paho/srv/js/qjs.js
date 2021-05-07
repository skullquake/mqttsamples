crow.add_header(crow.res,"Content-Type","text/plain");
try{
	{//write sample
		crow.write(crow.res,["&req",crow.req].join(":"));
		crow.write(crow.res,"\n");
		crow.write(crow.res,["&res",crow.res].join(":"));
		crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test2));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test2.vv));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test2.vs));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test2.ss));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test2.css));crow.write(crow.res,"\n");
		crow.write(crow.res,test2.vv());crow.write(crow.res,"\n");
		crow.write(crow.res,test2.vs());crow.write(crow.res,"\n");
		crow.write(crow.res,test2.ss("lorem"));crow.write(crow.res,"\n");
		crow.write(crow.res,test2.css());crow.write(crow.res,"\n");

		crow.write(crow.res,typeof(test3));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test3.vv));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test3.vs));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test3.ss));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(test3.css));crow.write(crow.res,"\n");
		crow.write(crow.res,test3.vv());crow.write(crow.res,"\n");
		crow.write(crow.res,test3.vs());crow.write(crow.res,"\n");
		crow.write(crow.res,test3.ss("lorem"));crow.write(crow.res,"\n");
		//crow.write(crow.res,test3.css());crow.write(crow.res,"\n");

		crow.write(crow.res,typeof(crowpp));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(crowpp.add_header));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(crowpp.write));crow.write(crow.res,"\n");
		crow.write(crow.res,typeof(crowpp.end));crow.write(crow.res,"\n");
	}
}catch(e){
	crow.write(crow.res,e.toString());
}
crow.end(crow.res);
