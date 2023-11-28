CXX = clang++ -std=c++20
CXXFLAGS = -Wall -g -MMD
LIBFLAGS = -lX11
SOURCES = $(wildcard *.cc)
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC=sorcery

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LIBFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)

