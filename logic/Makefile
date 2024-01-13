CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic


# Object files to be compiled.
OBJ_PERSON = person.o
OBJ_DATE = date.o
OBJ_BOOK = book.o

OBJ_PERSON_TEST = personTest.o
OBJ_DATE_TEST = dateTest.o
OBJ_BOOK_TEST = bookTest.o

# Main executable and test executable.
MAIN_EXECUTABLE = librarySystem
TEST_EXECUTABLE = testLibrarySystem

LOGIC_FOLDER = ../logic
TESTING_FOLDER = ../testing

.PHONY: all clean test

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

# Remove all object files and executables when cleaning.
clean:
	rm -f *.o
	rm $(MAIN_EXECUTABLE)
	rm $(TEST_EXECUTABLE)

# Compile the test executable when testing.
test: $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TESTING_FOLDER)/systemTests.cpp $(OBJ_PERSON_TEST) $(OBJ_DATE_TEST) $(OBJ_BOOK_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(OBJ_PERSON_TEST): $(TESTING_FOLDER)/testingPerson.cpp $(LOGIC_FOLDER)/person.h $(LOGIC_FOLDER)/date.h $(LOGIC_FOLDER)/book.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(TESTING_FOLDER)/testingPerson.cpp

$(OBJ_DATE_TEST): $(TESTING_FOLDER)/testingDate.cpp $(LOGIC_FOLDER)/date.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(TESTING_FOLDER)/testingDate.cpp

$(OBJ_BOOK_TEST): $(TESTING_FOLDER)/testingBook.cpp $(LOGIC_FOLDER)/book.h $(LOGIC_FOLDER)/date.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(TESTING_FOLDER)/testingBook.cpp
