FROM resin/rpi-raspbian:stretch

MAINTAINER John A. Fossum <jafossum@gmail.com>
LABEL Description="Eclipse Mosquitto MQTT Host"

RUN apt update && \
    apt install -y mosquitto && \
    rm -rf /var/lib/apt/lists/*

CMD ["/usr/sbin/mosquitto", "-c", "/etc/mosquitto/mosquitto.conf"]