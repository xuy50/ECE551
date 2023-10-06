CFLAGES=-Wall -Werror -pedantic -std=gnu99
test_all_power: test-power.o power.o
	gcc -o test_all_power test-power.o power.o
test-power.o: test-power.c
	gcc $(CFLAGES) -c test-power.c
power.o: power.c
	gcc $(CFLAGES) -c power.c

.PHONY: clean
clean:
	rm -f *~ *.o test_all_power
