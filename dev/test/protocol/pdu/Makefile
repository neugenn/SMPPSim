protocol_src = ../../../src/protocol
dataType_src = $(protocol_src)/dataType
pdu_src = $(protocol_src)/pdu
test_app = test
objects = PduHeaderTests.o BindTransmitterTests.o main.o

include $(protocol_src)/SmppLibMakefile

CXXFLAGS += $(DEBUG) -Wall -I$(dataType_src) -I$(pdu_src)

all: $(test_app)
	./$(test_app)

$(test_app): LFLAGS = -L$(protocol_src) -l$(SMPP) -L/usr/local/lib -l cppunit
$(test_app): $(SMPPLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)

PduHeaderTests.o: PduHeaderTests.cpp

BindTransmitterTests.o: BindTransmitterTests.cpp

main.o: main.cpp


$(SMPPLIB):
	@-rm -rf $(SMPPLIB)
	cd $(protocol_src) && $(MAKE)
	cp $(protocol_src)/$@ .

clean:
	@-rm -rf $(objects)
	@-rm -rf $(SMPPLIB)
	@-rm -rf $(test_app)*

.PHONY: clean $(SMPPLIB)
