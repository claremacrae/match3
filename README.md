# Game

**Download**
```sh
git clone --recursive git@github.com:krzysztof-jusiak/game.git
```

**Compilation**
 + linux
```sh
make -f Makefile.linux externals build run
```

 + cross mingw on linux
```sh
make -f Makefile.mingw_linux externals build run
```

 + windows
```sh
externals/unix/make.exe -f Makefile.mingw_win externals build run
```

**Speed up compilation times**
```sh
make CXX="ccache g++" -f Makefile.linux build -j4
```

