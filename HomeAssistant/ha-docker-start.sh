# Starts a HomeAssistant docker instance.

docker run --name="home-assistant" -v $PWD/config-ha:/config -e "TZ=Europe/Oslo" -p 8123:8123 --rm homeassistant/home-assistant

