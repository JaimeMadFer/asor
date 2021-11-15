$ sudo renice -n -10 2313
2313 (process ID) old priority 0, new priority -10

$ ps -l
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000  2313  1796  0  70 -10 - 29151 do_wai pts/0    00:00:00 bash
0 R  1000  2603  2313  0  70 -10 - 38300 -	pts/0    00:00:00 ps


$ sudo chrt -f -p 12 2313

$ ps -l
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000  2313  1796  0  47   - - 29151 do_wai pts/0    00:00:00 bash
0 R  1000  2773  2313  0  47   - - 38300 -	pts/0    00:00:00 ps
