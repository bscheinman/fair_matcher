OBJECTS=trade_client

all: $(OBJECTS)

trade_client: *.h *.cpp
	$(CXX) $(CXXFLAGS) -I../shared/trade_data -I../shared/network -o $@ trade_client.cpp client_session.cpp \
		../shared/network/network_session.o \
		../shared/network/network_utils.o \
		../shared/trade_data/messages.o \
		$(LDFLAGS) -g

clean:
	rm -rf *.dSYM *~ *.o $(OBJECTS)

include ../trading.build
