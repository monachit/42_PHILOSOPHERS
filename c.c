#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    int ret;

    ret = gettimeofday(&tv, NULL);
    if (ret == 0) {
        printf("Seconds: %ld\n", tv.tv_sec);
        printf("Microseconds: %ld\n", tv.tv_usec);
    } else {
        perror("gettimeofday");
    }

    return 0;
}

