network_src = ../network
logging_src = ../logging
dataType_src = dataType
pdu_src = pdu
objects = PduDataType.o Integer.o OctetString.o COctetString.o AsciiValidation.o DecimalValidation.o \
	HexValidation.o PduHeader.o Pdu.o BindTransmitter.o BindTransmitterResp.o EnquireLink.o EnquireLinkRes.o
 
CXXFLAGS += $(DEBUG) -c -Wall -fpic 
VPATH = $(dataType_src):$(pdu_src)

include SmppLibMakefile

all: $(SMPPLIB)

CXXFLAGS += -I$(network_src) -I$(logging_src)
$(SMPPLIB): $(objects)
	$(CXX) $(DEBUG) -shared -o $@ $(objects)

session.o: session.cpp

PduDataType.o: PduDataType.cpp
	$(CXX) $(CXXFLAGS) $^

OctetString.o: OctetString.cpp
	$(CXX) $(CXXFLAGS) $^

Integer.o: Integer.cpp
	$(CXX) $(CXXFLAGS) $^

COctetString.o: COctetString.cpp
	$(CXX) $(CXXFLAGS) $^

AsciiValidation.o: AsciiValidation.cpp
	$(CXX) $(CXXFLAGS) $^

DecimalValidation.o: DecimalValidation.cpp
	$(CXX) $(CXXFLAGS) $^

HexValidation.o: HexValidation.cpp
	$(CXX) $(CXXFLAGS) $^

CXXFLAGS += -I$(dataType_src)
PduHeader.o: PduHeader.cpp
	$(CXX) $(CXXFLAGS) $^

Pdu.o: Pdu.cpp
	$(CXX) $(CXXFLAGS) $^

BindTransmitter.o: BindTransmitter.cpp
	$(CXX) $(CXXFLAGS) $^

BindTransmitterResp.o: BindTransmitterResp.cpp
	$(CXX) $(CXXFLAGS) $^

EnquireLink.o: EnquireLink.cpp
	$(CXX) $(CXXFLAGS) $^

EnquireLinkRes.o: EnquireLinkRes.cpp
	$(CXX) $(CXXFLAGS) $^

clean:
	@-rm -f $(SMPPLIB)
	@-rm -f $(objects)

