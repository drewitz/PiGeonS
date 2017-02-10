.PHONY: run
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

run: glugon
	./glugon

glugon: geod.o pentagon.o glugon.o 
	$(CXX) -o glugon glugon.o geod.o pentagon.o $(LDFLAGS)
