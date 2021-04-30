console.log("test "+new Date().getTime());
console.log(typeof(crow));
console.log(typeof(crow.req));
console.log(typeof(crow.res));
crow.add_header(crow.res,"K","V")
crow.write(crow.res,"BODY")
