.DELTE_ON_ERROR:
.DEFAULT_GOAL:=test
.PHONY: all bin test clean

SRC:=src
TAGS:=.tags
PROJ:=milleoculi

CINC:=$(wildcard $(SRC)/*.h)
CSRC:=$(wildcard $(SRC)/*.cpp)
COBJ:=$(SRC:%.cpp:%.o)
CBIN:=$(PROJ)

LFLAGS+=-Wl,-O,--warn-common
CFLAGS+=-std=c++0x -I$(SRC) -O2 -Wall -W -Werror -g
CTAGS?=$(shell (which ctags || echo ctags) 2> /dev/null)

all: $(TAGS) bin

bin: $(CBIN)

$(PROJ): $(CSRC) $(CINC)
	$(CXX) $(CFLAGS) -o $@ $(CSRC) $(LFLAGS)

test: all
	for test in $(CBIN) ; do ./$$test ; done
	for test in $(CBIN) ; do \
		valgrind --tool=memcheck --leak-check=full ./$$test ; done


$(TAGS): $(CSRC) $(CINC)
	$(CTAGS) -o $@ $^

clean:
	rm -rf $(TAGS) $(COBJ) $(CBIN)
