$ sudo chrt -f -p 12 2313
$ gcc ejercicio2.c -o ej3
$ ./ej3

// La prioridad del programa es 12
// No, no se heredan los atributos de planificación, ya que esto solo ocurre con fork
