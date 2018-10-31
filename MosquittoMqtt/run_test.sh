#!/bin/bash

# Detecting OS
terminal_cmd=''
OS="`uname`"
echo ""
case $OS in
  'Linux')
    echo "Found Linux OperatingSystem. Using Xterm..."
    terminal_cmd='xterm -e'
    ;;
  'Darwin') 
    echo "Found MAC OperatingSystem. Using Terminal..."
    terminal_cmd='open -a Terminal'
    ;;
  '*')
    echo "Not valid. Exiting"
    exit 1
    ;;
esac

echo "Creating docker network..."
docker network create mosquitto

echo "Starting Docker Host..."
$terminal_cmd ./start_mosquitto_host.sh &

echo "Starting Docker Sub Client..."
$terminal_cmd ./start_mosquitto_sub.sh &

echo "Starting Docker Pub Client..."
$terminal_cmd ./start_mosquitto_pub.sh &

echo "####"
echo "type the following to make the Subscriber ready to receive"
echo " $ mosquitto_sub -h mosquitto-host -i testSub -t debug"

echo ""
echo "type the following to make the Publisher send"
echo " $ mosquitto_pub -h mosquitto-host -i testPublish -t debug -m 'Hello World'"
echo "####"
echo ""

read -p "Press any key to exit... "

docker stop mosquitto-pub mosquitto-sub mosquitto-host

