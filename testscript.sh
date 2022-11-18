#/bin/bash

echo msgA 100000 > fifo2.txt
sleep 0.1
echo msgB 5000 > fifo1.txt
sleep 0.1
echo msgB 5000 > fifo3.txt
sleep 0.1
echo msgB 50024230 > fifo4.txt
sleep 0.1
echo msgB 5056345600 > fifo5.txt
sleep 0.1
echo msgB 500456340 > fifo6.txt
sleep 0.1
echo msgB 503456300 > fifo7.txt
sleep 0.1
echo msgB 50062345240 > fifo8.txt
sleep 0.1
echo msgB 34534532 > fifo9.txt
sleep 0.1
