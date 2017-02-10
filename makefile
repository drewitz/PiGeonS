.PHONY: clean
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

glugon: geod.o polygon.o crossratio.o main.o 
	$(CXX) -o glugon main.o geod.o crossratio.o polygon.o $(LDFLAGS)

clean:
	rm -fv glugon
	rm -fv *.o
