#/bin/bash
sudo logi_loader logipi_wishbone.bit;
for j in $(seq 1 1 10);
do
echo "$j" 
for i in $(seq 2 2 2048); 
do
	echo "$i"
	./read_write_time $i $j
done	
done
