.PHONY: clean
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

OBJECT_FILES = geod.o crossratio.o polygon.o main.o

glugon: geod.o polygon.o crossratio.o main.o 
	$(CXX) -o glugon main.o geod.o crossratio.o polygon.o $(LDFLAGS)

$(OBJECT_FILES): clif.h

clean:
	rm -fv glugon
	rm -fv *.o
