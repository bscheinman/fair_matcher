all:
	$(CXX) $(CXXFLAGS) -I../trade_data -c network_session.cpp -o network_session.o
	$(CXX) $(CXXFLAGS) -I../trade_data -c network_utils.cpp -o network_utils.o

clean:
	rm -rf *~ *.o

include ../../trading.build
