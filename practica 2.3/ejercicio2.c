#include <stdio.h>
#include <sched.h>

int main(int argc, char **argv)
{
        int plan, prior, prior_max, prior_min, pid;
        struct sched_param st;
        char *cadena_plan;

		pid = getpid();
        plan = sched_getscheduler(pid);
        sched_getparam(pid, &st);
        prior_max = sched_get_priority_max(plan);
        prior_min = sched_get_priority_min(plan);

        switch (plan)
        {
		case SCHED_FIFO:
                cadena_plan = "FIFO";
                break;
        case SCHED_RR:
                cadena_plan = "Round Robin";
                break;
        case SCHED_OTHER:
                cadena_plan = "Estándar";
                break;
        default:
                cadena_plan = "Desconocido";
        }

        printf("Política de planificación: %s\n", cadena_plan);
        printf("Prioridad: %i\n", st.sched_priority);
        printf("Prioridad máxima: %i\n", prior_max);
        printf("Prioridad mínima: %i\n", prior_min);

        return 0;
}
