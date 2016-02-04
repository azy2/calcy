EXENAME = calcy
OBJS = main.o eval.o parser.o
TESTS = tests
TESTOBJS = tests.o eval.o parser.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y

all : $(EXENAME) $(TESTS)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

eval.o : eval.cpp
	$(CXX) $(CXXFLAGS) eval.cpp

parser.o : parser.cpp
	$(CXX) $(CXXFLAGS) parser.cpp

tests : $(TESTOBJS)
	$(LD) $(TESTOBJS) $(LDFLAGS) -lboost_unit_test_framework -o $(TESTS)

tests.o : tests.cpp
	$(CXX) $(CXXFLAGS) tests.cpp

# token.o : token.h
# 	$(CXX) $(CXXFLAGS) token.h

# ast.o : ast.h
# 	$(CXX) $(CXXFLAGS) ast.h

clean :
	-rm -f *.o $(EXENAME) tests
