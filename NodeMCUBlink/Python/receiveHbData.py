# Make sure paho-mqtt is installed:
# pip install paho-mqtt

import paho.mqtt.subscribe as subscribe

host = "iot-raspi.local"
topic = "heartbeat"

def on_hb(client, userdata, message):
    print("Data received: %s - %s" % (message.topic, message.payload))

print("Waitig for messages with topic: %s ..." % topic)

subscribe.callback(
    callback=on_hb, 
    topics=topic, 
    hostname=host)
