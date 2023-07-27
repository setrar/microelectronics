# Pico Wake Word


```
sudo apt install minicom
```

```
minicom -b 115200 -o -D /dev/ttyACM0
```
> Response:
```python
Welcome to minicom 2.8

OPTIONS: I18n 
Port /dev/ttyACM0, 23:49:29

Press CTRL-A Z for help on special keys

OK>OK
MPY: soft reboot
raw REPL; CTRL-B to exit
>
MicroPython v1.20.0 on 2023-04-26; Raspberry Pi Pico with RP2040
Type "help()" for more information.
>>> 
```

# References

- [ ] [MicroSpeech Wake Word example on the Raspberry Pi Pico. This is a port of the example on the TensorFlow repository.](https://github.com/henriwoodcock/pico-wake-word/)
