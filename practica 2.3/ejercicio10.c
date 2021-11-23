T1: $ sleep 600 // esto lo repito siempre

T2: $ kill -s SIGHUP 21398
T1: Hangup

T2: $ kill -s SIGINT 21617
T1: // Se termina el proceso

T2: $ kill -SIGSTOP 21680
T1: [1]+  Stopped                 sleep 600
T2: $ kill -SIGCONT 21680
T1: $ jobs
T1: [1]+  Running                 sleep 600 &

T2: $ kill -SIGKILL 21939
T1: Killed
