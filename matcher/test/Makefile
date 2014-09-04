OBJECTS=orderbook_test

all: $(OBJECTS)

orderbook_test: orderbook_test.cpp ../orderbook.cpp
	$(CXX) $(CXXFLAGS) -I.. -I../../shared/trade_data -o $@ $^ \
		../../shared/trade_data/messages.o \
		$(LDFLAGS) -g

clean:
	rm -rf *.dSYM *~ *.o $(OBJECTS)

include ../../trading.build
