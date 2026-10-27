#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>

#define STACK_SIZE (1024 * 1024)

int container_child(void* arg) {
    char** argv = (char**)arg;
    printf("[Container] Child process started inside isolated namespace. PID: %d\n", getpid());
    
    // Execute target program inside sandbox
    if (execvp(argv[0], argv) == -1) {
        perror("[Container] execvp failed");
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    printf("[Host] Initializing isolated container runtime sandbox...\n");
    char* stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("Failed to allocate stack memory");
        exit(1);
    }

    // Clone child in isolated PID, UTS, and Mount namespaces
    int flags = CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD;
    pid_t pid = clone(container_child, stack + STACK_SIZE, flags, &argv[1]);
    if (pid == -1) {
        perror("Failed to clone child namespace process");
        free(stack);
        exit(1);
    }

    printf("[Host] Spawned container child process with Host PID: %d\n", pid);
    waitpid(pid, NULL, 0);
    printf("[Host] Container terminated cleanly.\n");

    free(stack);
    return 0;
}
