/*
 * Copyright (c) 2013 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Seth Hoenig
 *    Allan Stockdill-Mander
 *    Mike Robertson
 */
package main
import(
	"fmt"
	"log"
	"os"
	"time"
	"github.com/eclipse/paho.mqtt.golang"
)
var f mqtt.MessageHandler=func(client mqtt.Client,msg mqtt.Message){
	log.Printf("TOPIC: %s\n",msg.Topic())
	log.Printf("PAYLO: %s\n",msg.Payload())
}
func main(){
	mqtt.ERROR=log.New(os.Stdout,"[ERROR] ",0)
	mqtt.CRITICAL=log.New(os.Stdout,"[CRIT] ",0)
	mqtt.WARN=log.New(os.Stdout,"[WARN]  ",0)
	mqtt.DEBUG=log.New(os.Stdout,"[DEBUG] ",0)
	opts:=mqtt.NewClientOptions().AddBroker("tcp://localhost:1883").SetClientID("go_paho")
	opts.SetKeepAlive(2*time.Second)
	opts.SetDefaultPublishHandler(f)
	opts.SetPingTimeout(1*time.Second)
	c:=mqtt.NewClient(opts)
	if token:=c.Connect();token.Wait()&&token.Error()!=nil{
		panic(token.Error())
	}
	if token:=c.Subscribe("sometopic",0,nil);token.Wait()&&token.Error()!=nil{
		fmt.Println(token.Error())
		os.Exit(1)
	}
	for i:=0;i<5;i++{
		text:=fmt.Sprintf("this is msg #%d!",i)
		token:=c.Publish("sometopic",0,false,text)
		token.Wait()
	}
	time.Sleep(6*time.Second)
	if token:=c.Unsubscribe("sometopic");token.Wait()&&token.Error()!=nil{
		fmt.Println(token.Error())
		os.Exit(1)
	}
	c.Disconnect(250)
	time.Sleep(5*time.Second)
}
