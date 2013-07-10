EXTERNALS 		?= externals
GMOCK 			?= gmock-1.6.0

#BIN             ?= bin/game.exe
#TEST            ?= bin/game_ut.exe
#CXX 			= $(EXTERNALS)/mingw32/bin/i686-w64-mingw32-g++
#CXXFLAGS    	?= -std=c++11 -U main -D BOOST_THREAD_USE_LIB -Iinclude -I$(EXTERNALS)/boost_1_52_0 -I$(EXTERNALS)/SDL2-2.0.0/include -I$(EXTERNALS)/SDL2_image-2.0.0 -I$(EXTERNALS)/di/include -D BOOST_DI_NO_CXX11_FEATURES
#LIBS            ?= -Lbin -lSDL2 -lSDL2_image -lboost_system -lboost_thread_win32

BIN             ?= bin/game
TEST            ?= bin/game_ut
CXX             ?= g++
CXXFLAGS    	?= -std=c++11 -Wall -Wextra -Werror -Iinclude -I$(EXTERNALS)/boost_1_52_0 -I$(EXTERNALS)/SDL2-2.0.0/include -I$(EXTERNALS)/SDL2_image-2.0.0 -I$(EXTERNALS)/di/include -D BOOST_DI_NO_CXX11_FEATURES
LIBS            ?= -L$(EXTERNALS)/linux/boost_1_52_0/stage/lib -L$(EXTERNALS)/SDL2-2.0.0/build/.libs -L$(EXTERNALS)/SDL2_image-2.0.0/.libs -lSDL2 -lSDL2_image -lpthread -lboost_chrono -lboost_thread -lboost_system

all: clean $(patsubst %.cpp, %.o, $(shell find src -iname *.cpp)) $(BIN)
	
test: clean $(patsubst %.cpp, %.o, $(shell find src test -iname *.cpp)) $(TEST)
	
src/%.o:
	$(CXX) $(CXXFLAGS) -c $(patsubst %.o, %.cpp, $@) -o bin/$(shell echo $* | tr '/' '_').o

test/%.o:
	$(CXX) $(CXXFLAGS) -Itest -I$(EXTERNALS)/$(GMOCK)/include -I$(EXTERNALS)/$(GMOCK)/gtest/include -c $(patsubst %.o, %.cpp, $@)  -o bin/$(shell echo $* | tr '/' '_').o

$(BIN):
	$(CXX) $(CXXFLAGS) -o $(BIN) $(shell find bin -iname *.o) $(LIBS)

$(TEST):
	$(CXX) $(CXXFLAGS) -o $(TEST) $(shell find bin -iname *.o) $(LIBS) -L$(EXTERNALS)/$(GMOCK)/lib/.libs -L$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs -lgtest -lgmock
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs:$(EXTERNALS)/$(GMOCK)/lib/.libs" ./$(TEST)

run:
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(EXTERNALS)/SDL2-2.0.0/build/.libs:$(EXTERNALS)/SDL2_image-2.0.0/.libs" bin/game

mocks:
	find include -iname *.hpp | xargs $(EXTERNALS)/gmockgen/gmock.py -c test/config/gmock.conf -l game -d test/mocks

clean:
	rm -f bin/*.o $(BIN) $(TEST)

