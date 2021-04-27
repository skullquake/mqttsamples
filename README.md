# Setting MQTT for use with Mendix

* Install WSL/Use Linux
* sudo apt-get install mosquitto
* mosquitto
  * by default will be installed as a system service
  * default configuration at /snap/mosquitto/current/default_config.conf
  * default port is 1883
* install paho c
	mkdir -p ~/src/eclipse
	cd ~/src/eclipse
	wget https://github.com/eclipse/paho.mqtt.c/archive/refs/heads/master.zip
	unzip ./master.zip
	rm ./master.zip
	cd ./paho.mqtt.c-master
	mkdir ./build
	cd ./build
	cmake -DCMAKE_INSTALL_PREFIX ../
	make -j8
	sudo make install -j8
	* depending on configuration files might be written to
		/usr/lib
		or
		/usr/lib/x86_64-linux-gnu/
* install paho cpp
	//https://github.com/eclipse/paho.mqtt.cpp/issues/225
	mkdir -p ~/src/eclipse
	cd ~/src/eclipse
	wget https://github.com/eclipse/paho.mqtt.cpp/archive/refs/heads/master.zip
	unzip ./master.zip
	rm ./master.zip
	cd paho.mqtt.cpp-master
	mkdir ./build
	cd ./build
	cmake -DCMAKE_INSTALL_PREFIX -DPAHO_MQTT_C_LIBRARIES=/usr/lib/x86_64-linux-gnu/ ../
	make -j8
	sudo make install -j8


~/src/eclipse/paho.mqtt.cpp-master/build$ cmake -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu -DCMAKE_INSTALL_PREFIX=/usr -DPAHO_MQTT_C_LIBRARIES=/usr/lib/x86_64-linux-gnu/libpaho-mqtt3c.so ../
