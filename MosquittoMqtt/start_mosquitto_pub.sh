#!/bin/bash

echo ""
echo "type the following to make the Publisher send"
echo " $ /usr/bin/mosquitto_pub -h mosquitto-host -i testPublish -t debug -m 'Hello World'"
echo ""

docker run -it --rm --name mosquitto-pub --network mosquitto mosquitto-clients
