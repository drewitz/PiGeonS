.PHONY: clean
LDFLAGS = -L$(HOME)/installs/include
CXXFLAGS = -I$(HOME)/installs/include

OBJECT_FILES = geod.o crossratio.o polygon.o main.o cpctclif.o

pigeons: $(OBJECT_FILES)
	$(CXX) -o pigeons $(OBJECT_FILES) $(LDFLAGS)

$(OBJECT_FILES): clif.h

clean:
	rm -fv pigeons
	rm -fv *.o
	rm -fv *~

test: test.o cpctclif.o
	$(CXX) -o test test.o cpctclif.o $(LDFLAGS)
