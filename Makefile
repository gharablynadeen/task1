all: build run

build:
	g++ -g main1.cpp
	g++ -g main1.cpp FileManager.cpp 


run:
	./a.exe

clean:
	rm a.exe