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

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gperftools/profiler.h>
using namespace std;
 
int loopop()
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
 
int main(int argc,char** argv)
{
    char program[1024]={0};
    snprintf(program,1023,"%s_%d.prof",argv[0],getpid());
    ProfilerStart(program);
    printf("result:  %d\n", (loopop)() );
    ProfilerStop();
    return 0;
}

