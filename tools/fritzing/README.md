# Install Fritzing

Attempt to Install Fritzing by following the below insstall instructions:

https://github.com/fritzing/fritzing-app/wiki/1.1-Mac-notes


## QT

- [ ] Install QT

```
brew install qt
```
> Response:
```python
You can add Homebrew's Qt to QtCreator's "Qt Versions" in:
  Preferences > Qt Versions > Link with Qt...
pressing "Choose..." and selecting as the Qt installation path:
  /usr/local
```

- [ ] Install QT Creator

```
brew install --cask qt-creator
```

- [ ] Adjust QT Creator's runtime


| Setting Up | Result |
|-|-|
| <img src=images/qt-creator-preferences.png widtth='' height='' > </img> | <img src=images/qt-creator-preferences-result.png widtth='' height='' > </img> |

### :b: In `~/Developer` folder

```
git clone https://github.com/fritzing/fritzing-app.git
```
