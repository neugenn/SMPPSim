sdk_dir = ../../../src/sdk
timer = $(sdk_dir)/timer
lock = $(sdk_dir)/lock
threads = $(sdk_dir)/threads
lib = smppsdk
test_app = test

CXXFLAGS = $(DEBUG) -Wall -I. -I$(timer) -I$(lock) -I$(threads) -I/usr/local/include

all: $(test_app)
	./$(test_app)

$(test_app) : LFLAGS = -L$(sdk_dir) -l$(lib) -L/usr/local/lib -lcppunit 
$(test_app): lib$(lib).dll TimerTests.o TimerControllerTests.o main.o 
	$(CXX) $(CXXFLAGS) *.o -o $(test_app) $(LFLAGS)

TimerTests.o: CXXFLAGS += -c 
TimerTests.o: TimerTests.h TimerTests.cpp

TimerControllerTests.o: CXXFLAGS += -c
TimerControllerTests.o: TimerControllerTests.h TimerControllerTests.cpp

main.o: CXXFLAGS += -c
main.o: main.cpp

libsmppsdk.dll:
	cd $(sdk_dir) && $(MAKE)
	cp $(sdk_dir)/$@ .

clean:
	@-rm -rf *.o
	@-rm -rf lib*
	@-rm -rf $(test_app)*

.PHONY: clean libsmppsdk.dll

