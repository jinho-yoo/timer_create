CC=gcc
timer2:timer2.c
        $(CC) -o $@ $< -lrt
timer1:timer1.c
        $(CC) -o $@ $< -lrt
timer:timer.c
        $(CC) -o $@ $< -lrt
clean:
        \rm timer timer1
        \rm timer2
