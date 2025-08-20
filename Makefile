CXX      = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -I.
#LDFLAGS  = -lgtest -lgtest_main -pthread  

.PHONY: all run clean

all: a.exe

a.exe: main1.o FileManager.o
	$(CXX) $(CXXFLAGS) -o a.exe main1.o FileManager.o $(LDFLAGS)   

main1.o: main1.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c main1.cpp

FileManager.o: FileManager.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

#test: unitTesting.o FileManager.o
#	$(CXX) $(CXXFLAGS) -o test.exe unitTesting.o FileManager.o $(LDFLAGS)

#unitTesting.o: unitTesting.cpp FileManager.h
#	$(CXX) $(CXXFLAGS) -c unitTesting.cpp

run: a.exe
	./a.exe

clean:
	- if exist a.exe del /Q a.exe
	- if exist *.o del /Q *.o
    #- if exist test.exe del /Q test.exe    