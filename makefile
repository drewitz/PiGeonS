.PHONY: run
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

run: glugon
	./glugon

glugon: glugon.o geod.cpp
	$(CXX) -o glugon glugon.o $(LDFLAGS)
