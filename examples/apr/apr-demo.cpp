/*
 * =====================================================================================
 *
 *       Filename:  apr-demo.cpp
 *
 *    Description:  apr demo
 *
 *        Version:  1.0
 *        Created:  2014/08/08 21时14分59秒
 *       Revision:  none
 *       Compiler:  gcc/g++
 *
 *         Author:  bbxyard (Brian), bbxyard@gmail.com 
 *      Copyright:  copyright (c) 2014, LGPL, bbxyard, http://www.bbxyard.com
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <string>
#include <iostream>

#include "apr-1/apr.h"
#include "apr-1/apr_pools.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  apr_pool_test
 *       Author:  bbxyard
 *      Created:  2014/08/08 21时26分11秒
 *  Description:  apr memory pool
 * =====================================================================================
 */
void apr_pool_test()
{
   // global init
   apr_initialize();

   apr_pool_t* parent = NULL;
   apr_pool_t* son = NULL;
   apr_pool_create(&parent, NULL);
   apr_pool_create(&son, parent);
     char* buff = (char*)apr_palloc(son, 1024);
     strcpy(buff, "this is apr test string base apr_palloc");
     fprintf(stdout, "hello: %s\n", buff);
   apr_pool_destroy(son);
   apr_pool_destroy(parent);

   // global fini
   apr_terminate();
} /* -----  end of function apr_pool_test  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *       Author:  bbxyard
 *      Created:  2014/08/08 21时24分41秒
 *  Description:  
 * =====================================================================================
 */
int main (int argc, char *argv[])
{
    apr_pool_test();
    return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */
