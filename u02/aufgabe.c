#include<signal.h>
#include<stdio.h>

int v[3] = {0, 0, 0};
void handler(int sig) {
v[0]++;
}
int main() {
int pid[3];
signal(SIGUSR1, handler);
pid[0] = fork();
pid[1] = getpid();
pid[2] = fork();
if (pid[0] == pid[2]) {
v[1]++;
sleep(4);
} else if (pid[1] == getppid()) {
sleep(3);
v[2]++;
sleep(2);
} else if (pid[1] == getpid()) {
sleep(1);
v[2]++;
kill(pid[2], SIGUSR1);
wait(NULL);
if (pid[0] > 0) {
v[1]++;
wait(NULL);
}
}
printf("%d %d %d\n", v[0], v[1], v[2]);
}
