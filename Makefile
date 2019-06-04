all: recommender

recommender: content.o predict.o
	g++ main.cpp content.o predict.o -std=c++11 -g -o recommender -O3 -Wall

predict.o: predict.cpp
	g++ predict.cpp -std=c++11 -g -c -o predict.o -O3 -Wall
	
content.o: content.cpp
	g++ content.cpp -std=c++11 -g -c -o content.o -O3 -Wall

clean:
	rm predict.o
	rm content.o
