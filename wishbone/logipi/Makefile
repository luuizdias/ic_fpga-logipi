CC = gcc


all: read_wishbone write_wishbone test_wishbone read_write read_write_time

clean:
	rm -f *.a *.o write_wishbone read_wishbone test_wishbone read_write read_write_time

wishbone_wrapper.o: wishbone_wrapper.c
	$(CC) -c wishbone_wrapper.c

read_wishbone : read_wishbone.c wishbone_wrapper.o
	$(CC) -o $@ read_wishbone.c wishbone_wrapper.o

write_wishbone : write_wishbone.c wishbone_wrapper.o
	$(CC) -o $@ write_wishbone.c wishbone_wrapper.o

test_wishbone : test_wishbone.c wishbone_wrapper.o
	$(CC) -o $@ test_wishbone.c wishbone_wrapper.o

read_write : read_write.c wishbone_wrapper.o
	$(CC) -o $@ read_write.c wishbone_wrapper.o

read_write_time : read_write_time.c wishbone_wrapper.o
	$(CC) -o $@ read_write_time.c wishbone_wrapper.o
