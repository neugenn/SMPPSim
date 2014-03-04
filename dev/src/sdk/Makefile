threads_src = threads
lock_src = lock
timer_src = timer
objects = lock.o mutex.o thread.o posixthread.o timer.o TimerController.o

CXXFLAGS = $(DEBUG)
VPATH=$(threads_src):$(threads_src)/posix:$(lock_src):$(lock_src)/posix:$(timer_src)

all : libsmppsdk.so 

libsmppsdk.so: $(objects)
	$(CXX) -shared -o $@ *.o

lock.o: CXXFLAGS += -c -Wall -fpic -I$(lock_src) -I$(lock_src)/posix 
lock.o: lock.cpp 
	$(CXX) $(CXXFLAGS) $^

mutex.o: CXXFLAGS += -c -Wall -fpic -I$(lock_src)/posix -I$(lock_src)
mutex.o: mutex.cpp 
	$(CXX) $(CXXFLAGS) $^

thread.o: CXXFLAGS += -c -Wall -fpic -I$(threads_src) -I$(threads_src)/posix 
thread.o: thread.cpp 
	$(CXX) $(CXXFLAGS) $^

posixthread.o: CXXFLAGS += -c -Wall -fpic -I$(threads_src) -I$(threads_src)/posix 
posixthread.o: posixthread.cpp 
	$(CXX) $(CXXFLAGS) $^

timer.o: CXXFLAGS += -c -Wall -fpic -I. -I$(timer_src) -I$(lock_src) -I$(threads_src)
timer.o: timer.cpp 
	$(CXX) $(CXXFLAGS) $^

TimerController.o: CXXFLAGS += -c -Wall -fpic -I. -I$(timer_src) -I$(lock_src) -I$(threads_src)
TimerController.o: TimerController.cpp 
	$(CXX) $(CXXFLAGS) $^

clean : 
	@-rm -rf *.o
	@-rm -rf lib*

.PHONY: clean
