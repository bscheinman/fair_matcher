.PHONY: proto

all: proto $(patsubst %.cpp, %.o, $(wildcard *.cpp)) $(patsubst %.cc, %.o, $(wildcard *.cc))
	rm -f messages.o
	ld -r *.o -o messages.o

proto:
	protoc -I=./proto --cpp_out=. ./proto/*.proto
	#protoc -I=./proto --cxx11_out=. ./proto/*.proto

%.o: %.cpp %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
	

clean:
	rm *.pb.h *.pb.cc *.o

include ../../trading.build
