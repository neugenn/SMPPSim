sdk_dir = ../../../src/sdk
timer = $(sdk_dir)/timer
lock = $(sdk_dir)/lock
threads = $(sdk_dir)/threads
test_app = test
objects = TimerTests.o TimerControllerTests.o timerimpltests.o mocktimer.o mocktimercontroller.o main.o

include $(sdk_dir)/SdkLibMakefile

CXXFLAGS = $(DEBUG) -Wall -I. -I$(timer) -I$(lock) -I$(threads) -I/usr/local/include

all: $(test_app)
	./$(test_app)

$(test_app) : LFLAGS = -L$(sdk_dir) -l$(SDK) -L/usr/local/lib -lcppunit 
$(test_app): $(SDKLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)

TimerTests.o: TimerTests.cpp TimerTests.h

TimerControllerTests.o: TimerControllerTests.cpp TimerControllerTests.h

timerimpltests.o: timerimpltests.cpp  timerimpltests.h

mocktimer.o: mocktimer.cpp mocktimer.h

mocktimercontroller.o: mocktimercontroller.cpp mocktimercontroller.h

main.o: main.cpp

$(SDKLIB):
	cd $(sdk_dir) && $(MAKE)
	cp $(sdk_dir)/$@ .

clean:
	@-rm -rf $(objects) 
	@-rm -rf $(SDKLIB) 
	@-rm -rf $(test_app)*

.PHONY: clean $(SDKLIB)

