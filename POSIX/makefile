.PHONY: all clean run

CXXFLAGS :=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXXFLAGS += -lrt
endif
ifeq ($(UNAME_S),Darwin)
	CXXFLAGS +=
endif

all: clean
	g++ $(CXXFLAGS) fakeclient.cpp -o fakeclient

clean:
	rm -f fakeclient

run:
	./fakeclient