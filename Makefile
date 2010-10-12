.DELTE_ON_ERROR:
.DEFAULT_GOAL:=test
.PHONY: all bin test clean

SRC:=src
TAGS:=.tags
PROJ:=milleoculi
TDATA:=/dev/null testdata

CINC:=$(wildcard $(SRC)/*.h)
CSRC:=$(wildcard $(SRC)/*.cpp)
COBJ:=$(SRC:%.cpp:%.o)
CBIN:=$(PROJ)

LFLAGS+=-Wl,-O,--warn-common -ladns
CFLAGS+=-std=c++0x -I$(SRC) -O2 -Wall -W -Werror -g
CTAGS?=$(shell (which ctags || echo ctags) 2> /dev/null)

all: $(TAGS) bin

bin: $(CBIN)

$(PROJ): $(CSRC) $(CINC)
	$(CXX) $(CFLAGS) -o $@ $(CSRC) $(LFLAGS)

test: all $(TDATA)
	for test in $(CBIN) ; do for data in $(TDATA) ; do \
		./$$test < $$data && \
		valgrind --tool=memcheck --leak-check=full -v \
			./$$test < $(TDATA) ; done ; done

$(TAGS): $(CSRC) $(CINC)
	$(CTAGS) -o $@ $^

clean:
	rm -rf $(TAGS) $(COBJ) $(CBIN)
