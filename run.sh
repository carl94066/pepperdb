set -e

g++ -Wall main.cc sharded_map.cc common.cc -std=c++11 -O2 -lboost_system -lglog -lgflags -o main.o

time ./main.o --logtostderr
