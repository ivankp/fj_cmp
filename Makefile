CFLAGS := -std=c++11 -Wall -O3

FJ_DIR    := $(shell fastjet-config --prefix)
FJ_CFLAGS := -I$(FJ_DIR)/include
FJ_LIBS   := -L$(FJ_DIR)/lib -lfastjet

ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS   := $(shell root-config --libs)

.PHONY: all clean

all: fj rand

fj: fj.cc
	g++ $(CFLAGS) $(FJ_CFLAGS) $^ -o $@ $(FJ_LIBS)

rand: rand.cc
	g++ $(CFLAGS) $(ROOT_CFLAGS) $^ -o $@ $(ROOT_LIBS)

clean:
	@rm -vf fj *.o

