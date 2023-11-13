all:
	g++ -std=c++17 -I ../cadmium_v2/include -I include main_auction.cpp && ./a.out

run:
	./a.out

clean:
	rm -f *.o
	rm -f *.csv
	rm -f bid