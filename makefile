all:
	g++ -std=c++17 -I ../cadmium_v2/include -I include main_auction.cpp && ./a.out 4

run:
	./a.out 4

clean:
	rm -f *.o
	rm -f *.csv
	rm -f bid