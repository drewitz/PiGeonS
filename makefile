.PHONY: run
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

run: glugon
	./glugon

glugon: geod.o pentagon.o main.o 
	$(CXX) -o glugon main.o geod.o pentagon.o $(LDFLAGS)
