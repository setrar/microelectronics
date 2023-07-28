# IDE


#### :a: [Visual Studio Code on Raspberry Pi](https://code.visualstudio.com/docs/setup/raspberry-pi)

```
sudo apt update
sudo apt install code
```

- [ ] [Setup Rust Dev Environment with VS Code in Raspberry Pi 3 B+](https://www.youtube.com/watch?v=O9d8kiZQUT4)

#### :b: [Install Arduino IDE on Raspberry Pi](https://www.raspberrypi-spy.co.uk/2020/12/install-arduino-ide-on-raspberry-pi/)

```
sudo apt update
sudo apt install arduino
```

```
  > Open the IDE
  > Menu > Electronics > Arduino IDE
  > Now under the “Tools” menu select “Board” followed by “Boards Manager”.
  > In the search box type “pico” and press “Enter”. The search result should present you with “Arduino Mbed OS RP2040 Boards” by the “Arduino”.
  > Click “Install”
```

- [ ] Post Install

```
sudo ~/.arduino15/packages/arduino/hardware/mbed_rp2040/4.0.4/post_install.sh
```
> Reload rules...


# References

- [ ] [Can not upload to Raspberry Pi Pico](https://forum.arduino.cc/t/can-not-upload-to-raspberry-pi-pico/882573/2)
- [ ] [How to Program Raspberry Pi Pico With the Arduino IDE](https://www.tomshardware.com/how-to/program-raspberry-pi-pico-with-arduino-ide)
