EXTERNALS 		:= externals
GMOCK 			:= gmock-1.6.0

#BIN             := bin/win/game.exe
#TEST            := bin/win/game_ut.exe
#CXX 		    := $(EXTERNALS)/mingw32/bin/i686-w64-mingw32-g++
#CXXFLAGS        := -std=c++11 -Iinclude -I$(EXTERNALS)/boost_1_52_0 -I$(EXTERNALS)/SDL2-2.0.0/include -I$(EXTERNALS)/SDL2_image-2.0.0 -I$(EXTERNALS)/SDL_ttf-2.0.11 -I$(EXTERNALS)/di/include -D BOOST_DI_NO_CXX11_FEATURES
#LIBS            := -Lbin/win -lSDL2 -lSDL2_image -lSDL_ttf

BIN             := bin/linux/game
TEST            := bin/linux/game_ut
CXX             := g++
CXXFLAGS        := -std=c++11 -Wall -Wextra -Werror -D BOOST_DI_NO_CXX11_FEATURES -Iinclude -I$(EXTERNALS) -I$(EXTERNALS)/boost_1_52_0 -I$(EXTERNALS)/SDL2-2.0.0/include -I$(EXTERNALS)/SDL2_image-2.0.0 -I$(EXTERNALS)/SDL_ttf-2.0.11 -I$(EXTERNALS)/di/include
LIBS            := -Lbin/linux -lSDL2 -lSDL2_image -lSDL2_ttf-2.0 -lfreetype

all: clean $(patsubst %.cpp, %.o, $(shell find src -iname *.cpp)) $(BIN)
	
test: clean $(patsubst %.cpp, %.o, $(shell find src test -iname *.cpp)) $(TEST)
	
src/%.o:
	$(CXX) $(CXXFLAGS) -c $(patsubst %.o, %.cpp, $@) -o bin/linux/$(shell echo $* | tr '/' '_').o

test/%.o:
	$(CXX) $(CXXFLAGS) -Itest -I$(EXTERNALS)/$(GMOCK)/include -I$(EXTERNALS)/$(GMOCK)/gtest/include -c $(patsubst %.o, %.cpp, $@) -o bin/linux/$(shell echo $* | tr '/' '_').o

$(BIN):
	$(CXX) $(CXXFLAGS) -o $(BIN) $(shell find bin/linux -iname *.o) $(LIBS)

$(TEST):
	$(CXX) $(CXXFLAGS) -o $(TEST) $(shell find bin/linux -iname *.o) $(LIBS) -L$(EXTERNALS)/$(GMOCK)/lib/.libs -L$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs -lgtest -lgmock
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs:$(EXTERNALS)/$(GMOCK)/lib/.libs" ./$(TEST)

mocks:
	find include -iname *.hpp | xargs -i% $(EXTERNALS)/gmockgen/gmock.py -c test/config/gmock.conf -l game -d test/mocks % -- $(CXXFLAGS)

clean:
	rm -f bin/*.o $(BIN) $(TEST)

