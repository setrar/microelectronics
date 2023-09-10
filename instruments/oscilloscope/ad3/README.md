# :signal_strength: [Analog Discovery 3](https://digilent.com/reference/test-and-measurement/analog-discovery-3/start)

#### [MyProduct Waveforms Download Link](https://cloud.digilent.com/myproducts/waveform?pc=1&tab=2)

| MyProduct Waveforms Binary Download Link |
|-|
| [MacOS: digilent.waveforms_v3.20.1.dmg](https://digilent.s3.us-west-2.amazonaws.com/Software/Waveforms2015/3.20.1/digilent.waveforms_v3.20.1.dmg) |
| [Adept for Linux Runtime](https://digilent.s3.us-west-2.amazonaws.com/Software/Adept2+Runtime/2.27.9/digilent.adept.runtime_2.27.9-armhf.deb)
| [Debian: digilent.waveforms_3.20.1_arm64.deb](https://digilent.s3.us-west-2.amazonaws.com/Software/Waveforms2015/3.20.1/digilent.waveforms_3.20.1_arm64.deb) |

- [ ] [adept-runtime-download](https://lp.digilent.com/complete-adept-runtime-download)

```
wget https://digilent.s3.us-west-2.amazonaws.com/Software/Adept2+Runtime/2.27.9/digilent.adept.runtime_2.27.9-armhf.deb
```

```
sudo dpkg --install digilent.adept.runtime_2.27.9-armhf.deb
```

```
wget https://digilent.s3.us-west-2.amazonaws.com/Software/Waveforms2015/3.20.1/digilent.waveforms_3.20.1_arm64.deb
```

```
sudo dpkg --install digilent.waveforms_3.20.1_arm64.deb
```

<img src=images/digilent-mac-install.png width=50% height=50% > </img>

# References

- [ ]  [Analog Discovery 3:](https://digilent.com/shop/analog-discovery-3/)
- [ ] [ :tv: EEVblog 1552 - Digilent Analog Discovery 3](https://www.youtube.com/watch?v=5SbNnaMM1tQ)
- [ ] [Spying on SPI with the Analog Discovery 3](https://www.hackster.io/whitney-knitter/spying-on-spi-with-the-analog-discovery-3-e26c43)


## :x: Errors

- [ ] Package digilent.adept.runtime is not installed.

```
sudo dpkg --install digilent.waveforms_3.20.1_arm64.deb
```
> Returns:
```
Selecting previously unselected package digilent.waveforms.
(Reading database ... 96925 files and directories currently installed.)
Preparing to unpack digilent.waveforms_3.20.1_arm64.deb ...
Unpacking digilent.waveforms (3.20.1) ...
dpkg: dependency problems prevent configuration of digilent.waveforms:
 digilent.waveforms depends on digilent.adept.runtime (>= 2.26.1); however:
  Package digilent.adept.runtime is not installed.
 digilent.waveforms depends on libqt5multimedia5-plugins; however:
  Package libqt5multimedia5-plugins is not installed.
 digilent.waveforms depends on libqt5scripttools5; however:
  Package libqt5scripttools5 is not installed.

dpkg: error processing package digilent.waveforms (--install):
 dependency problems - leaving unconfigured
Processing triggers for gnome-menus (3.36.0-1) ...
Processing triggers for desktop-file-utils (0.26-1) ...
Processing triggers for mailcap (3.69) ...
Processing triggers for man-db (2.9.4-2) ...
Processing triggers for shared-mime-info (2.0-1) ...
Errors were encountered while processing:
 digilent.waveforms
```
