all: bin/tracksplits

bin/tracksplits: src/tracksplits.cpp
	g++ -std=c++11 -o bin/tracksplits src/tracksplits.cpp

clean:
	rm -f bin/tracksplits

