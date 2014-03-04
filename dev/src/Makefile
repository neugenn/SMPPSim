logging_src = logging
sdk_src = sdk
network_src = network
protocol_src = protocol
modules = $(sdk_src) $(logging_src) $(network_src) $(protocol_src)

application = smscsim.exe

CXXFLAGS = $(DEBUG) -Wall -I$(network_src) -I$(logging_src) -I$(protocol_src) -I$(sdk_src)

all : $(application) 

$(application) : $(modules) smscsim.o
	$(CXX) $(CXXFLAGS) $(logging_src)/*.o $(network_src)/*.o $(protocol_src)/*.o smscsim.o -o $(application) \
	 -lpthread -L$(sdk_src) -lsmppsdk

$(modules):
	$(MAKE) --directory=$@

smscsim.o: smscsim.cpp

clean:
	cd $(logging_src) && $(MAKE) $@
	cd $(network_src) && $(MAKE) $@
	cd $(sdk_src) && $(MAKE) $@
	cd $(protocol_src) && $(MAKE) $@
	@-rm -f $(application)
	@-rm -f *.o 

.PHONY: clean $(modules)
