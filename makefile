CC = g++
CFLAGS = -Wall -Wextra
LIBS = -L"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/lib" -lwordnet
INCLUDE = -I"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/include"

all: dailywords.cpp wordnet_wrapper.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o Dailywords dailywords.cpp wordnet_wrapper.cpp $(LIBS)

clean:
	rm -f Dailywords