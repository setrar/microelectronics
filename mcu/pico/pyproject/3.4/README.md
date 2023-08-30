[3.4 Liquid Crystal Display](https://docs.sunfounder.com/projects/euler-kit/en/latest/pyproject/py_lcd.html)


- [ ] [Upload Library](https://docs.sunfounder.com/projects/euler-kit/en/latest/pyproject/python_start/download_add.html#add-libraries-py) to the RPI PICO

<img src=images/upload-library.png width='25%' height='25%' > </img>

- [ ] Run the program

```python
from lcd1602 import LCD
import utime

lcd = LCD()
string = " Akory!\n"
lcd.message(string)
utime.sleep(2)
string = "    Lahaly! Eh!"
lcd.message(string)
utime.sleep(2)
lcd.clear()
```

- [ ] See by yourself

<img src=images/IMG_4396.jpg width='50%' height='50%' > </img>
