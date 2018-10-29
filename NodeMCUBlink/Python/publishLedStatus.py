# Make sure paho-mqtt is installed:
# pip install paho-mqtt

import paho.mqtt.publish as publish
from time import sleep

host = "iot-raspi.local"
topic = "ledStatus"

x = 0
while True:
    print("Sending %s ..." % x)

    publish.single(
        topic=topic, 
        payload="%s" % x, 
        hostname=host)

    x = int(not x)
    sleep(1)
