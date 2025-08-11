# all: build run

# build:
# 	g++ -g main1.cpp
# 	g++ -g main1.cpp FileManager.cpp 
# 	-ID:\Internship\Siemens\task1\task1\FileManager.h    


# run:
# 	./a.exe

# clean:
# 	rm a.exe

CXX      = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -I.

.PHONY: all run clean

all: a.exe

a.exe: main1.o FileManager.o
	$(CXX) $(CXXFLAGS) -o a.exe main1.o FileManager.o

main1.o: main1.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c main1.cpp

FileManager.o: FileManager.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

run: a.exe
	./a.exe

clean:
	- if exist a.exe del /Q a.exe
	- if exist *.o del /Q *.o
