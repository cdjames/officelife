# to execute the makefile on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

# replace 'your_file' below with your actual source file names.
# add more if needed.
CXX = g++
CXXFLAGS =  
# CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
# CXXFLAGS += -g #debugging

LDFLAGS = 
# LDFLAGS = -lboost_date_time

SRCS = Creature.cpp Goblin.cpp Barbarian.cpp Reptile.cpp Bluemen.cpp Shadow.cpp
SRCS += Stack.cpp Queue.cpp IntStack.cpp
SRCS += Team.cpp Tournament.cpp
# SRCS += game.cpp 
SRCS += main.cpp 

OBJS = ${SRCS:.cpp=.o}
LNKS := ${OBJS}

HDRS = ${SRCS:.cpp=.hpp}

# HDRS = Creature.cpp Goblin.cpp Barbarian.cpp Reptile.cpp Bluemen.cpp Shadow.cpp
# HDRS += Stack.hpp Queue.hpp IntStack.hpp
# HDRS += Team.hpp Tournament.hpp

# ${OBJS}: %.o : %.hpp

PROG1 = game
# PROG1 = main

# ${PROG1}: ${SRCS} ${HDRS} # works well
# 	${CXX} ${SRCS} -o $@
#following also works

${PROG1}: ${OBJS} ${HDRS}
	${CXX} ${LDFLAGS} ${OBJS} -o $@

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

link:
	${CXX} ${LDFLAGS} ${LNKS} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}
