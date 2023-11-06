- [ ] [Start a Project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#start-a-project)

```
get_idf
```

```
cd ~/Developer/esp
cp -r $IDF_PATH/examples/get-started/hello_world .
```


- [ ] [Configure your project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#configure-your-project)

```
cd ~/Developer/esp/hello_world
idf.py set-target esp32s3
idf.py menuconfig
```
