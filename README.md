arduino-cli board attach -b esp8266:esp8266:d1_mini_clone flipdot_driver

arduino-cli lib list

arduino-cli lib search WiFiManager

arduino-cli lib install WiFiManager

arduino-cli compile -e flipdot_driver/

arduino-cli upload -i flipdot_driver/build/esp8266.esp8266.d1_mini_clone/flipdot_driver.ino.bin  -p 192.168.1.103 -l network