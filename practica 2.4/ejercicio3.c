$ mkfifo tub
$ ls -l tub
$ stat tub
T1: $ echo "Hola" > tub
T2: $ cat tub
T2: Hola
