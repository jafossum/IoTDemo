#!/bin/bash

echo ""
echo "type the following to make the Subscriber ready to receive"
echo " $ /usr/bin/mosquitto_sub -h mosquitto-host -i testSub -t debug"
echo ""

docker run -it --rm --name mosquitto-sub --network mosquitto mosquitto-clients
