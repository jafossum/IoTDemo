#!/bin/bash

docker run --name mosquitto-host -it -p 1883:1883 --network mosquitto --rm eclipse-mosquitto
