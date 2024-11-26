CFLAGS=-ggdb3 -std=gnu++98 -pedantic -Wall -Werror
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS))
all: $(PROGS)
cyoa-step%: cyoa-step%.o eval3.o
	g++ -o $@ $^
%.o: %.cpp eval3.hpp
	g++ -g $(CFLAGS) -c $<
eval3.o : eval3.cpp eval3.hpp
	g++ -o eval3.o $(CFLAGS) -c eval3.cpp
.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS) *.o
