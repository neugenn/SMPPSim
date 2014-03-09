sdk_dir = ../../../src/sdk
sharedptr_src = $(sdk_dir)/sharedptr
lock_src = $(sdk_dir)/lock
test_app = test
objects = smartptrtests.o main.o

include $(sdk_dir)/SdkLibMakefile

CXXFLAGS = $(DEBUG) -Wall -I. -I$(sharedptr_src) -I$(lock_src) -I/usr/local/include
CPPFLAGS = -DUNIT_TEST

all: $(test_app)
	./$(test_app)

$(test_app) : LFLAGS = -L$(sdk_dir) -l$(SDK) -L/usr/local/lib -lcppunit
$(test_app): $(SDKLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)

smartptrtests.o: smartptrtests.cpp smartptrtests.h $(sharedptr_src)/sharedptr.h

main.o: main.cpp

$(SDKLIB):
	cd $(sdk_dir) && $(MAKE)
	cp $(sdk_dir)/$@ .

clean:
	@-rm -rf $(objects)
	@-rm -rf $(SDKLIB)
	@-rm -rf $(test_app)

.PHONY: clean $(SDKLIB)
