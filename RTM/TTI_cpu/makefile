CXX = clang++
MPICXX = mpic++
OPT = -g
SVEFLAGS = -std=c++11 ${OPT} -fopenmp -pthread -march=armv8.4-a+sve -O3 -ffast-math -fomit-frame-pointer
SMEFLAGS = -std=c++11 ${OPT} -fopenmp -pthread -march=armv8.6-a+sve+sme -mcpu=linxicore6100 -O3 -ffast-math -fomit-frame-pointer -Wno-undefined-arm-za -Wno-undefined-arm-streaming
LDFLAGS = -Wall -fopenmp -lm -lpthread
LDLIBS = $(LDFLAGS)

targets = benchmark-rtm
objects = main.o rtm_native.o rtm_brick_sme.o

.PHONY : default
default : all

all : $(targets)

benchmark-rtm : main.o rtm_native.o rtm_brick_sme.o
	$(CXX) -o $@ $^ $(LDLIBS)

%.o : %.c common.h
	$(CXX) -c $(SVEFLAGS) $< -o $@

rtm_brick_sme.o : rtm_brick_sme.cpp common.h
	$(CXX) -c $(SMEFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(targets) $(objects)
