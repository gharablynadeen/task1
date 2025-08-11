all: build run

build:
	g++ -g main1.cpp

run:
	./a.exe

clean:
	rm a.exe