// Enlaces simbólicos

usuario_local@pto0502:~$ touch fichero
usuario_local@pto0502:~$ ls -i fichero
1186104 fichero
usuario_local@pto0502:~$ ln -s fichero fichero_ej10
usuario_local@pto0502:~$ ls -i fichero_ej10
1186107 fichero_ej10
usuario_local@pto0502:~$ ls -l fichero_ej10
lrwxrwxrwx 1 usuario_local users 7 nov  8 10:19 fichero_ej10 -> fichero

usuario_local@pto0502:~$ mkdir directorio
usuario_local@pto0502:~$ ls -id directorio
1186106 directorio
usuario_local@pto0502:~$ ln -s directorio directorio_ej10
usuario_local@pto0502:~$ ls -id directorio_ej10
1186101 directorio_ej10
usuario_local@pto0502:~$ ls -ld directorio_ej10
lrwxrwxrwx 1 usuario_local users 10 nov  8 10:32 directorio_ej10 -> directorio

// Enlaces rígidos

usuario_local@pto0502:~$ ln fichero r_fichero_ej10
usuario_local@pto0502:~$ stat r_fichero_ej10
  Fichero: r_fichero_ej10
  Tamaño: 0         	Bloques: 0          Bloque E/S: 4096   fichero regular vacío
Dispositivo: 809h/2057d	Nodo-i: 1186104     Enlaces: 2
Acceso: (0640/-rw-r-----)  Uid: (  555/usuario_local)   Gid: (  100/   users)
Acceso: 2021-11-08 10:16:13.648850002 +0100
Modificación: 2021-11-08 10:16:13.580850357 +0100
      Cambio: 2021-11-08 10:41:07.881847422 +0100
    Creación: -

usuario_local@pto0502:~$ ln directorio r_directorio_ej10
ln: directorio: no se permiten enlaces fuertes para directorios

// Si se borra un enlace rígido, el inodo pierde uno de los enlaces, pero el fichero aún se puede abrir
// Si se borra un enlace simbólico, el inodo se borra y el fichero o directorio creado ya no se puede abrir
// Si se borra el fichero original, el fichero se podrá abrir o modificar si se creó un enlace rígido previamente.
// 		Si por el contrario se creó un enlace simbólico, el ficheró no se abrirá.
