

#### use next two lines for Mac
###CC = clang++
###CCFLAGS = -std=gnu++2a -stdlib=libc++

EXECS = sim
OBJS = TrafficSimulator.o Animator.o VehicleBase.o Lanes.o Spawn.o TrafficLight.o
CC = g++
CFLAGS = -std=c++17;

all: $(EXECS);

sim: $(OBJS);
	$(CC) -Wall  $(CCFLAGS) TrafficSimulator.o Animator.o VehicleBase.o Lanes.o Spawn.o TrafficLight.o -o sim

VehicleBase.o: VehicleBase.cpp VehicleBase.h
	$(CC) -g -Wall  $(CCFLAGS) -c VehicleBase.cpp

TrafficLight.o: TrafficLight.cpp TrafficLight.h Animator.h
	$(CC) -g -Wall  $(CCFLAGS) -c TrafficLight.cpp

Lanes.o: Lanes.cpp Lanes.h VehicleBase.h
	$(CC) -g -Wall  $(CCFLAGS) -c Lanes.cpp

Spawn.o: Spawn.cpp Spawn.h VehicleBase.h
	$(CC) -g -Wall  $(CCFLAGS) -c Spawn.cpp	

Animator.o: Animator.cpp Animator.h VehicleBase.h
	$(CC) -g -Wall  $(CCFLAGS) -c Animator.cpp 

TrafficSimulator.o: TrafficSimulator.cpp Animator.h VehicleBase.h Lanes.h Spawn.h TrafficLight.h
	$(CC) -g -Wall $(CCFLAGS) -c TrafficSimulator.cpp

clean:
	/bin/rm -f *.o sim