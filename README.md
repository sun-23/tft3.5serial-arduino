# tft3.5serial-arduino

serialTFT-test.ino is file to control serial tft (Aduino uno + 3.5inch TFT Shield) by SERIAL (PIN 0,1) of ARDUINO UNO 

tft3.5serial.ino is firmware of diy serial tft (Aduino uno + 3.5inch TFT Shield) to read command by SERIAL (PIN 0,1) of arduino


# you must not connect before upload code because it will error when upload (pin 0,1 same as a SERIAL USB port) you must connect after upload code

# On Uno, Nano, Mini, and Mega, pins 0 and 1 are used for communication with the computer. Connecting anything to these pins can interfere with that communication, including causing failed uploads to the board.

device | serial tft | <-----> | arduino uno 
--- | --- | --- | ---
pin | 0 | <-----> | 1 
pin | 1 | <-----> | 0

