# Make sure paho-mqtt is installed:
# pip install paho-mqtt

import paho.mqtt.publish as publish
import time

host = "iot-raspi.local"
#host = "localhost"

while True:
    print("Sending 0...")
    publish.single("ledStatus", "0", hostname=host)

    time.sleep(1)

    print("Sending 1...")
    publish.single("ledStatus", "1", hostname=host)

    time.sleep(1)

