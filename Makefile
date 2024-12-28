.DEFAULT_GOAL := build

build:
	g++ *.cpp devices/*.cpp
.PHONY:build

run:	build
	./a.out
.PHONY:run

clean:
	rm ./*.out
.PHONY:clean

