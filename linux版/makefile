main:main.o platform.o
	g++ -o main main.o platform.o
main.o:main.cpp platform.h
	g++ -o main.o -c main.cpp
tools.o:platform.cpp platform.h
	g++ -o platform.o -c platform.cpp
clean:
	rm *.o
	rm main
