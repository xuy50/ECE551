CFLAGES=-Wall -Werror -std=gnu99
test_subseq: test-subseq.o maxSeq.o
	gcc -o test_subseq test-subseq.o maxSeq.o
test-subseq.o: test-subseq.c
	gcc $(CFLAGES) -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc $(CFLAGES) -pedantic -c maxSeq.c

PHONY: clean
clean:
	rm -f *~ *.o test_subSeq
