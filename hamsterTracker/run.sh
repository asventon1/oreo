arduino-cli compile --fqbn esp8266:esp8266:generic hamsterTracker.ino/hamsterTracker.ino
sudo chmod a+rw /dev/ttyUSB0
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:generic hamsterTracker.ino
