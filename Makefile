EXTERNALS 		?= externals
GMOCK 			?= gmock-1.6.0
BIN             ?= bin/game
TEST            ?= bin/game_ut
CXX             ?= g++
CXXFLAGS    	?= -std=c++11 -Wall -Wextra -Werror -Iinclude -I$(EXTERNALS)/di/include -D BOOST_DI_NO_CXX11_FEATURES
LIBS            ?= -lSDL -lSDL_image -lpthread

all: clean $(patsubst %.cpp, %.o, $(shell find src -iname *.cpp)) $(BIN)
	
test: clean $(patsubst %.cpp, %.o, $(shell find src test -iname *.cpp)) $(TEST)
	
src/%.o:
	$(CXX) $(CXXFLAGS) -c $(patsubst %.o, %.cpp, $@)  -o bin/$(shell echo $* | tr '/' '_').o

test/%.o:
	$(CXX) $(CXXFLAGS) -Itest -I$(EXTERNALS)/$(GMOCK)/include -I$(EXTERNALS)/$(GMOCK)/gtest/include -c $(patsubst %.o, %.cpp, $@)  -o bin/$(shell echo $* | tr '/' '_').o

$(BIN):
	$(CXX) $(CXXFLAGS) -o $(BIN) $(shell find bin -iname *.o) $(LIBS)

$(TEST):
	$(CXX) $(CXXFLAGS) -o $(TEST) $(shell find bin -iname *.o) $(LIBS) -L$(EXTERNALS)/$(GMOCK)/lib/.libs -L$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs -lgtest -lgmock
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(EXTERNALS)/$(GMOCK)/gtest/lib/.libs:$(EXTERNALS)/$(GMOCK)/lib/.libs" ./$(TEST)

mocks:
	find include -iname *.hpp | xargs $(EXTERNALS)/gmock/gmock.py -c test/config/gmock.conf -l game -d test/mocks

clean:
	rm -f bin/*.o $(BIN) $(TEST)

