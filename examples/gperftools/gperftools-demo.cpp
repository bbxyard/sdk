/*
 * =====================================================================================
 *
 *       Filename:  gperftools-demo.cpp
 *
 *    Description:  google perfmance tools demo
 *
 *        Version:  1.0
 *        Created:  2014年08月28日 14时39分12秒
 *       Revision:  none
 *       Compiler:  gcc/g++
 *
 *         Author:  bbxyard (Brian), bbxyard@gmail.com 
 *      Copyright:  copyright (c) 2014, LGPL, bbxyard, http://www.bbxyard.com
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gperftools/profiler.h>

// SIGUSER1: start profiling
// SIGUSER2: stop  profiling

#ifndef SIGUSER1
#define SIGUSER1  10
#define SIGUSER2  12
#endif

static char gs_app_prof_file[260] = {0};

static void gprof_callback(int signum)
{
    switch (signum)
    {
    case SIGUSER1:
        fprintf(stdout, "Catch the signal ProfilerStart\n");
        ProfilerStart(gs_app_prof_file);
        break;
    case SIGUSER2:
        fprintf(stdout, "Catch the signal ProfilerStop\n");
        ProfilerStop();
        break;
    case SIGINT:
    case SIGQUIT:
        fprintf(stdout, "Catch the signal %d exit\n", signum);
        gprof_callback(SIGUSER2);
        exit(signum);
        break;
    }
}

static void setup_signal()
{
    struct sigaction profstat;
    profstat.sa_handler = gprof_callback;
    profstat.sa_flags   = 0;
    sigemptyset(&profstat.sa_mask);
    sigaddset(&profstat.sa_mask, SIGUSER1);
    sigaddset(&profstat.sa_mask, SIGUSER2);
    sigaddset(&profstat.sa_mask, SIGINT);
    sigaddset(&profstat.sa_mask, SIGQUIT);

    if (sigaction(SIGUSER1, &profstat, NULL) < 0)
    {
        fprintf(stderr, "Fail to connect signal SIGUSER1 with start profiling\n");
    }
    if (sigaction(SIGUSER2, &profstat, NULL) < 0)
    {
        fprintf(stderr, "Fail to connect signal SIGUSER2 with stop  profiling\n");
    }
    if (sigaction(SIGINT, &profstat, NULL) < 0 || sigaction(SIGQUIT, &profstat, NULL) <0)
    {
        fprintf(stderr, "Fail to connect signal SIGINT, SIGQUIT\n");
    }
}

int do_loop()
{
    char buffer1 [1024];
    char buffer2 [1024];
    int n = 0;
    for(int i = 0; i < 10000000; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            n |= i%100 + j/100;
        }
        memset(buffer1,0xa,1024);
        memcpy(buffer2,buffer1,1024);
    }
    return n;
}

void run()
{
    for (int i = 1; ; ++i)
    {
        fprintf(stdout, "execute loop run [%dth] start\n", i); 
        fprintf(stdout, "execute loop run [%dth] stop result=%d\n", i, do_loop());
    }
}
 
int main0(int argc, char** argv)
{
    char prof_file[1024]={0};
    snprintf(prof_file, 1023, "%s_%d.prof", argv[0], getpid());
    ProfilerStart(prof_file);
    fprintf(stdout, "result:  %d\n", do_loop() );
    ProfilerStop();
    return 0;
}

int main(int argc, char* argv[])
{
    snprintf(gs_app_prof_file, sizeof(gs_app_prof_file) - 1, "%s_%d.prof", argv[0], getpid());
    setup_signal();
    run();
    return 0;
}
