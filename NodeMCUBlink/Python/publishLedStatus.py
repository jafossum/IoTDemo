# Make sure paho-mqtt is installed:
# pip install paho-mqtt

import paho.mqtt.publish as publish
import time

host = "iot-raspi.local"
x = 0

while True:
    print("Sending %s ..." % x)

    publish.single(
        topic="ledStatus", 
        payload="%s" % x, 
        hostname=host)

    x = int(not x)
    time.sleep(1)
