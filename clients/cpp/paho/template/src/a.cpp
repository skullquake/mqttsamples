#include<iostream>
#include<sstream>
#include<mqtt/client.h>
#define ADDRESS "127.0.0.1"
#define CLIENT_ID "pahopp"
#define QOS 1
int main(int argc,char*argv[]){
	const std::string TOPIC{"Mx0"};
	const std::string PAYLOAD1{"Hello World!"};
	const char*PAYLOAD2="Hi there!";
	//Create a client
	mqtt::client cli(ADDRESS,CLIENT_ID);
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	try{
		//Connect to the client
		cli.connect(connOpts);
		//Publish using a message pointer.
		//auto msg=mqtt::make_message(TOPIC,PAYLOAD1);
		for(int i=0;i<512;i++){
			std::ostringstream oss;
			oss<<"test "<<i;
			auto msg=mqtt::make_message(TOPIC,oss.str().c_str());
			msg->set_qos(QOS);
			cli.publish(msg);
		}
		// Now try with itemized publish.
		cli.publish(TOPIC,PAYLOAD2,strlen(PAYLOAD2),0,false);
		//Disconnect
		cli.disconnect();
	}catch(const mqtt::exception&exc){
		std::cerr<<"Error: "<<exc.what()<<"["<<exc.get_reason_code()<<"]"<<std::endl;
		return 1;
	}
	return 0;
}
