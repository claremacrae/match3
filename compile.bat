"mingw32\bin\i686-w64-mingw32-g++.exe" -Dmain=SDL_main -Iboost_1_52_0 -ISDL2 -c main.cpp
"mingw32\bin\i686-w64-mingw32-g++.exe" -o main.exe main.o -static-libgcc -static-libstdc++  -L. -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows

