/*
 * =====================================================================================
 *
 *       Filename:  htmlcxx-demo.cpp
 *
 *    Description:  copy from htmlcxx sample
 *
 *        Version:  1.0
 *        Created:  2014年08月08日 18时13分28秒
 *       Revision:  none
 *       Compiler:  gcc/g++
 *
 *         Author:  bbxyard (Brian), bbxyard@gmail.com 
 *      Copyright:  copyright (c) 2014, LGPL, bbxyard, http://www.bbxyard.com
 *
 * =====================================================================================
 */

#include <iostream>
#include "htmlcxx/html/ParserDom.h"
#include <stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *       Author:  bbxyard
 *      Created:  2014年08月08日 18时22分11秒
 *  Description:  
 * =====================================================================================
 */
int main (int argc, char *argv[])
{
  using namespace std;
  using namespace htmlcxx;
  
  //Parse some html code
  string html = "<html><body>hey<A href=\"www.bbxyard.com\">myhome</A></body></html>";
  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);
  //Print whole DOM tree
  cout << dom << endl;
  
  //Dump all links in the tree
  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();
  for (; it != end; ++it)
  {
     if (strcasecmp(it->tagName().c_str(), "A") == 0)
     {
       it->parseAttributes();
       cout << it->attribute("href").second << endl;
     }
  }
  
  //Dump all text of the document
  it = dom.begin();
  end = dom.end();
  for (; it != end; ++it)
  {
    if ((!it->isTag()) && (!it->isComment()))
    {
      cout << it->text() << " ";
    }
  }
  cout << endl;
  return 0;
}

