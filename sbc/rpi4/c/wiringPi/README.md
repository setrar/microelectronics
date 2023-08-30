


- [ ] Test with `C`

```c
#include <wiringPi.h>
#include <stdio.h>

#define ledPin 0 //define the led pin number

int main(void)
{
   printf("Program is starting ... \n"); 
   wiringPiSetup(); //Initialize wiringPi.

   pinMode(ledPin, OUTPUT);//Set the pin mode
   printf("Using pin%d\n",ledPin); //Output information on terminal 
   while(1){
      digitalWrite(ledPin, HIGH); //Make GPIO output HIGH level
      printf("led turned on >>>\n"); //Output information on terminal 
      delay(1000); //Wait for 1 second 
      digitalWrite(ledPin, LOW); //Make GPIO output LOW level
      printf("led turned off <<<\n"); //Output information on terminal 
      delay(1000); //Wait for 1 second
   }
}
```

- [ ] Compile and run

```bash
gcc Blink.c -o Blink -lwiringPi ; \
./Blink
```

<img src=../images/IMG_4405.jpg width=50% height=50% > </img>

# References

- [ ] [Raspberry Pi OS with desktop 64 bit Debian version: 11 (bullseye)](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64.img.xz)
```
brew install --cask raspberry-pi-imager
```
- [ ] [GPIO and the 40-pin Header](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)
- [ ] [Processing.org](https://processing.org)
```
brew install processing
```
