protocol_src = ../../../src/protocol
dataType_src = $(protocol_src)/dataType
test_app = test
objects = OneByteIntegerTests.o TwoByteIntegerTests.o OctetStringTests.o \
	COctetStringTests.o AsciiValidationTests.o DecimalValidationTests.o HexValidationTests.o main.o

include $(protocol_src)/SmppLibMakefile

CXXFLAGS += $(DEBUG) -Wall -I$(dataType_src)

all: $(test_app)
	./$(test_app)

$(test_app): LFLAGS = -L$(protocol_src) -l$(SMPP) -L/usr/local/lib -l cppunit
$(test_app): $(SMPPLIB) $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(test_app) $(LFLAGS)

OneByteIntegerTests.o: OneByteIntegerTests.cpp

TwoByteIntegerTests.o: TwoByteIntegerTests.cpp

OctetStringTests.o: OctetStringTests.cpp

COctetStringTests.o: COctetStringTests.cpp

AsciiValidationTests.o: AsciiValidationTests.cpp

DecimalValidationTests.o: DecimalValidationTests.cpp

HexValidationTests.o: HexValidationTests.cpp

main.o: main.cpp


$(SMPPLIB):
	cd $(protocol_src) && $(MAKE)
	cp $(protocol_src)/$@ .

clean:
	@-rm -rf $(objects)
	@-rm -rf $(SMPPLIB)
	@-rm -rf $(test_app)*

.PHONY: clean $(SMPPLIB)
