.PHONY: clean
LDFLAGS = -L$(HOME)/installs/include
CXXFLAGS = -I$(HOME)/installs/include

OBJECT_FILES = geod.o crossratio.o polygon.o main.o cpctclif.o

glugon: $(OBJECT_FILES)
	$(CXX) -o glugon $(OBJECT_FILES) $(LDFLAGS)

$(OBJECT_FILES): clif.h

clean:
	rm -fv glugon
	rm -fv *.o
	rm -fv *~

test: test.o cpctclif.o
	$(CXX) -o test test.o cpctclif.o $(LDFLAGS)
