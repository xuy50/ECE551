CFLAGS = -Wall -Werror -pedantic -ggdb3 -std=gnu++98 -fprofile-arcs -ftest-coverage
LDFLAGS+=-lpthread $(CFLAGS)
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1:cyoa-step1.o Page.o
	g++ $(LDFLAGS) -o cyoa-step1 cyoa-step1.o Page.o
cyoa-step2:cyoa-step2.o Page.o
	g++ $(LDFLAGS) -o cyoa-step2 cyoa-step2.o Page.o
cyoa-step3:cyoa-step3.o Page.o
	g++ $(LDFLAGS) -o cyoa-step3 cyoa-step3.o Page.o
cyoa-step4:cyoa-step4.o Page.o
	g++ $(LDFLAGS) -o cyoa-step4 cyoa-step4.o Page.o
Page.o:Page.cpp Page.hpp
	g++ $(CFLAGS) -c Page.cpp
cyoa-step1.o:cyoa-step1.cpp Page.hpp
	g++ $(CFLAGS) -c cyoa-step1.cpp
cyoa-step2.o:cyoa-step2.cpp Page.hpp
	g++ $(CFLAGS) -c cyoa-step2.cpp
cyoa-step3.o:cyoa-step3.cpp Page.hpp
	g++ $(CFLAGS) -c cyoa-step3.cpp
cyoa-step4.o:cyoa-step4.cpp Page.hpp
	g++ $(CFLAGS) -c cyoa-step4.cpp

#.PHONY : clean
#clean:
#    rm -rf *.o *.gcov *.gcda *.gcno
