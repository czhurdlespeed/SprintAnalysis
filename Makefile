bin/trackspilts: src/trackspilts.cpp
	g++ -std=c++11 -o bin/trackspilts src/trackspilts.cpp

clean:
	rm -f bin/trackspilts

