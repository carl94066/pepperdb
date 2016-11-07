set -e

g++ -Wall main.cc common.cc -std=c++11 -O3 -lglog -lgflags -o main.o

time ./main.o --logtostderr
