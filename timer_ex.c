#include <stdio.h>
#include <time.h>
#include <signal.h>

timer_t timer_id;
//#define sigNo SIGALRM
#define sigNo SIGRTMIN

void start_timer(void)
{

struct sigevent te;
struct itimerspec value;

/* Set and enable alarm */
te.sigev_notify = SIGEV_SIGNAL;
te.sigev_signo = sigNo;
te.sigev_value.sival_ptr = CLOCK_REALTIME;

timer_create (CLOCK_REALTIME, &te, &timer_id);

value.it_value.tv_sec = 1;
value.it_value.tv_nsec = 0;

value.it_interval.tv_sec = 1;
value.it_interval.tv_nsec = 0;
timer_settime (timer_id, 0, &value, NULL);

}

void stop_timer(void)
{


struct itimerspec value;

value.it_value.tv_sec = 0;
value.it_value.tv_nsec = 0;

value.it_interval.tv_sec = 0;
value.it_interval.tv_nsec = 0;

timer_settime (timer_id, 0, &value, NULL);


}


void timer_callback(int sig) {
 printf(" Catched timer signal: %d ... !!\n", sig);

}

int main(int ac, char **av)
{
    //(void) signal(SIGALRM, timer_callback);
//    (void) signal(SIGRTMIN, timer_callback);
 struct sigaction        sa;

    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = (void *)timer_callback;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sigNo, &sa, NULL) == -1)
    {
        printf("sigaction error\n");
        return -1;
    }

    start_timer();
    while(1);
}
