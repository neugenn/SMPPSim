sdk_dir = ../../../src/sdk
timer = $(sdk_dir)/timer
lock = $(sdk_dir)/lock
threads = $(sdk_dir)/threads
test_app = test

include $(sdk_dir)/SdkLibMakefile

CXXFLAGS = $(DEBUG) -Wall -I. -I$(timer) -I$(lock) -I$(threads) -I/usr/local/include

all: $(test_app)
	./$(test_app)

$(test_app) : LFLAGS = -L$(sdk_dir) -l$(SDK) -L/usr/local/lib -lcppunit 
$(test_app): $(SDKLIB) TimerTests.o TimerControllerTests.o main.o 
	$(CXX) $(CXXFLAGS) *.o -o $(test_app) $(LFLAGS)

TimerTests.o: CXXFLAGS += -c 
TimerTests.o: TimerTests.h TimerTests.cpp

TimerControllerTests.o: CXXFLAGS += -c
TimerControllerTests.o: TimerControllerTests.h TimerControllerTests.cpp

main.o: CXXFLAGS += -c
main.o: main.cpp

$(SDKLIB):
	cd $(sdk_dir) && $(MAKE)
	cp $(sdk_dir)/$@ .

clean:
	@-rm -rf *.o
	@-rm -rf $(SDKLIB) 
	@-rm -rf $(test_app)*

.PHONY: clean $(SDKLIB)

