# Game

**Download**
```
git clone --recursive git@github.com:krzysztof-jusiak/game.git
```

**Compilation**
 + linux
```
make -f Makefile.linux externals build run
```

 + cross mingw on linux
```
make -f Makefile.mingw_linux externals build run
```

 + windows
```
externals\unix\make.exe -f Makefile.mingw_win externals build run
```

**Speed up compilation times**
```sh
make CXX="ccache g++" -f Makefile.linux build -j4
```

**Screenshots**
 + ![ScreenShot](https://raw.github.com/krzysztof-jusiak/game/gh-pages/screenshots/board.png)
 + ![ScreenShot](https://raw.github.com/krzysztof-jusiak/game/gh-pages/screenshots/game_over.png)

