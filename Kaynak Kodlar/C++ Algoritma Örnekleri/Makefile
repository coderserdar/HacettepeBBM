CXX=g++
CXXFLAGS=-O2 -Wall -g -pg
LDFLAGS=-pg

project: project.o ops.o
	$(CXX) $(LDFLAGS) project.o ops.o -o project

project.o: project.cpp
	$(CXX) $(CXXFLAGS) -c project.cpp -o project.o

ops.o: ops.cpp
	$(CXX) $(CXXFLAGS) -c ops.cpp -o ops.o

clean:
	rm -f *.o project a.out gmon.out
	rm -f `find . -type f -perm 755`
