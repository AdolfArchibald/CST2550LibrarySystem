CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic


# Define object files
OBJ_PERSON = person.o
OBJ_DATE = date.o
OBJ_BOOK = book.o

# Main executable
MAIN_EXECUTABLE = librarySystem

.PHONY: all clean

all: $(MAIN_EXECUTABLE)

# Compile main executable
$(MAIN_EXECUTABLE): main.cpp $(OBJ_PERSON) $(OBJ_DATE) $(OBJ_BOOK)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(OBJ_PERSON): person.cpp person.h date.h book.h
	$(CXX) $(CXXFLAGS) -c -o $@ person.cpp

$(OBJ_DATE): date.cpp date.h
	$(CXX) $(CXXFLAGS) -c -o $@ date.cpp

$(OBJ_BOOK): book.cpp book.h date.h
	$(CXX) $(CXXFLAGS) -c -o $@ book.cpp

# main.o: main.cpp person.h date.h book.h
# 	$(CXX) $(CXXFLAGS) -c -o $@ main.cpp

clean:
	rm -f *.o
	rm $(MAIN_EXECUTABLE)
