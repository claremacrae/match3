.EXPORT_ALL_VARIABLES:

EXTERNALS   := externals
OBJS    	:= $(patsubst %.cpp, %.o, $(shell find src -iname *.cpp))

all: all_linux all_win
run: run_linux run_win
clean: clean_win clean_linux

all_%:
	make -f Makefile.$* all

run_%:
	make -f Makefile.$* run

clean_%:
	make -f Makefile.$* clean

mocks:
	find include -iname *.hpp | xargs -i% $(EXTERNALS)/gmockgen/gmock.py -c test/config/gmock.conf -l game -d test/mocks % -- $(CXXFLAGS)

