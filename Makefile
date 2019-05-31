all: recommender

recommender: matrix.o model.o
	g++ main.cpp matrix.o model.o -std=c++11 -g -o recommender -O3 -Wall

model.o: model.cpp
	g++ model.cpp -std=c++11 -g -c -o model.o -O3 -Wall

matrix.o: matrix.cpp
	g++ matrix.cpp -std=c++11 -g -c -o matrix.o -O3 -Wall

clean:
	rm matrix.o
	rm model.o
