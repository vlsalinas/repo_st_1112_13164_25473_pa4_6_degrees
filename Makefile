# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)


ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections extension Timer.o



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o ActorNode.o	Union.o Timer.o

actorconnections: ActorGraph.o ActorNode.o Union.o Timer.o

extension: extension_graph.o extension_node.o Timer.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: Union.o ActorNode.o ActorGraph.h

# UnionFind.hpp ActorEdge.h Movie.h

ActorNode.o: ActorNode.h

Union.o: ActorNode.o Union.h

extension_graph.o: extension_node.o extension_graph.h

Timer.o: Timer.h
extension_node.o: extension_node.h


clean:
	rm -f pathfinder *.o core*
	rm -f actorconnections *.o core*
	rm -f extension *.o core*

