/*
 * tools.c: The 'soppalusikka' VDR skin
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "common.h"
#include "tools.h"
#include <stdlib.h>

char *strcatrealloc(char *dest, const char *src)
{
  if (src) {
     int l = strlen(dest) + strlen(src) + 1;
     dest = (char *)realloc(dest, l);
     if (dest)
        strcat(dest, src);
     else
        esyslog("ERROR: out of memory!");
  }
  return dest;
}

char *strncatrealloc(char *dest, const char *src, unsigned int len)
{
  if (src) {
     int l = strlen(dest) + min(strlen(src), len) + 1;
     dest = (char *)realloc(dest, l);
     if (dest)
        strncat(dest, src, min(strlen(src), len));
     else
        esyslog("ERROR: out of memory!");
  }
  return dest;
}

char *striptags(char *str)
{
  char *c, t = 0, *r;
  c = str;
  r = str;
  while (*str != '\0') {
    if (*str == '<')
       t++;
    else if (*str == '>') 
       t--;
    else if (t < 1)
       *(c++) = *str;
    str++;
    }
  *c = '\0';
  return r;
}
