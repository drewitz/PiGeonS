.PHONY: clean
LDFLAGS = -L/home/drewitzs/install/include
CXXFLAGS = -I/home/drewitzs/install/include

OBJECT_FILES = geod.o crossratio.o polygon.o main.o cpctclif.o

glugon: geod.o polygon.o crossratio.o main.o 
	$(CXX) -o glugon $(OBJECT_FILES) $(LDFLAGS)

$(OBJECT_FILES): clif.h

clean:
	rm -fv glugon
	rm -fv *.o

test: test.o cpctclif.o
	$(CXX) -o test test.o cpctclif.o $(LDFLAGS)
