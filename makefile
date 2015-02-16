
all: 
	g++ -pthread -std=c++11 main.cpp PriceEntry.cpp TimeSeries.cpp csvline_populate.cpp normaltest.cpp -o scrub

clean:
	rm -rf *.o *.gch *.out


