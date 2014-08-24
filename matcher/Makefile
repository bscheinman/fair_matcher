OBJECTS=match_server

all: $(OBJECTS)

match_server: *.h *.cpp
	$(CXX) $(CXXFLAGS) -I../shared/trade_data -o match_server match_server.cpp server_session.cpp matcher_engine.cpp orderbook.cpp \
		../shared/network/network_session.o \
		../shared/network/network_utils.o \
		../shared/trade_data/messages.o \
		$(LDFLAGS) -g

clean:
	rm -rf *.dSYM *~ *.o $(OBJECTS)

include ../trading.build
