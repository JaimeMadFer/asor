 mkdir directorio
$ ls -ld directorio
drwxrwxr-x 2 cursoredes cursoredes 6 Nov  6 19:32 directorio

$ chmod u-x,g-x,o-x directorio
$ ls -ld directorio
drw-rw-r-- 2 cursoredes cursoredes 6 Nov  6 19:32 directorio

$ cd directorio
bash: cd: directorio: Permission denied
