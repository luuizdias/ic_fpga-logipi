#/bin/bash

for i in $(seq 2 2 2048); 
do
	echo "$i"
	./read_write_time $i
	sleep 1
done	