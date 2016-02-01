EXENAME = calcy
OBJS = main.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

# token.o : token.h
# 	$(CXX) $(CXXFLAGS) token.h

# ast.o : ast.h
# 	$(CXX) $(CXXFLAGS) ast.h

clean :
	-rm -f *.o $(EXENAME)
