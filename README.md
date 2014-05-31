# Match3

**Download**
```
git clone --recursive git@github.com:krzysztof-jusiak/match3.git
```

**Compilation** (tested with gcc 4.8.1 and boost_1_54_0)
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
![ScreenShot](https://raw.github.com/krzysztof-jusiak/match3/gh-pages/screenshots/board.png)

