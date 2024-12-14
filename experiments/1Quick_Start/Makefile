CC = g++
CFLAGS = -std=c++11 -O1

TARGET = matrixMultiplication

SRCS = matrixMultiplication.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f -r $(TARGET) $(OBJS)
