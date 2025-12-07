CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -flto -I src

SRCS = src/main.cpp src/Graph.cpp src/MinHeap.cpp src/Dijkstra.cpp src/AStar.cpp src/NameLookup.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = planner

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: all
