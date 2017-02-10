.PHONY: clean
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

glugon: geod.o pentagon.o main.o 
	$(CXX) -o glugon main.o geod.o pentagon.o $(LDFLAGS)

clean:
	rm -fv glugon
	rm -fv *.o
