
```
cd ~/Developer
```

```
git clone --depth 1 https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi.git
```
> Response
```python
Cloning into 'Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi'...
remote: Enumerating objects: 458, done.
remote: Counting objects: 100% (458/458), done.
remote: Compressing objects: 100% (334/334), done.
remote: Total 458 (delta 75), reused 398 (delta 57), pack-reused 0
Receiving objects: 100% (458/458), 138.87 MiB | 8.67 MiB/s, done.
Resolving deltas: 100% (75/75), done.
Updating files: 100% (332/332), done.
```

```
mv Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi Freenove_Kit
```

```
cd Freenove_Kit/Code/C_Code/04.1.1_BreathingLED
```

```
gcc BreathingLED.c -o BreathingLED -lwiringPi
```

```
sudo ./BreathingLED
```
> Response:
```python
Program is starting ... 

^C
```
