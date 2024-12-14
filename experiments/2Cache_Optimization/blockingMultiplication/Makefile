CC = icc
CFLAGS = -std=c++11 -O1

TARGET = matrixMultiplication

SRCS = matrixMultiplication.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(PAPI_LIB)

%.o: %.cpp
	$(CC) $(CFLAGS) $(PAPI_INC) -c $< -o $@

clean:
	rm -f -r $(TARGET) $(OBJS) job.ou* pap*
