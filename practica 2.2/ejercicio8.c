usuario_local@pto0502:~$ stat .
  Fichero: .
  Tamaño: 4096      	Bloques: 8          Bloque E/S: 4096   directorio
Dispositivo: 809h/2057d	Nodo-i: 1179649     Enlaces: 46
Acceso: (0755/drwxr-xr-x)  Uid: (  555/usuario_local)   Gid: (  100/   users)
Acceso: 2021-11-08 09:30:59.916116648 +0100
Modificación: 2021-11-08 09:27:18.853445776 +0100
      Cambio: 2021-11-08 09:27:18.853445776 +0100
    Creación: -

usuario_local@pto0502:~$ stat . -f
  Fichero: "."
    ID: 4f876f450ded8cc6 Longnombre: 255     Tipo: ext2/ext3
Tam. bloque: 4096       Tam. bloque fundamental: 4096
Bloques: Total: 38442491   Libres: 36920927   Disponibles: 34950778
Nodos-i: Total: 9830400    Libres: 9576709

usuario_local@pto0502:~$ stat . -c %b
8
usuario_local@pto0502:~$ stat . -c %B
512
