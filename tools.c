/*
 * tools.c: The 'soppalusikka' VDR skin
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <stdlib.h>
#include "common.h"
#include "tools.h"

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

char *strncatrealloc(char *dest, const char *src, size_t len)
{
  if (src) {
     size_t l = strlen(dest) + min(strlen(src), len) + 1;
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
  char *r, *c;
  int t = 0, d = 0;
  bool s = false;
  r = str;
  c = str;
  while (*str != '\0') {
    if (*str == '<') {
       t++;
       s = true;
       }
    else if (*str == '>') {
       t--;
       }
    else if (t < 1) {
       *(c++) = *str;
       }
    else if (s) {
       if (*str == '/') {
          d--;
          }
       else {
          d++;
          }
       if (d < 1) {
          *(c++) = '\n';
          }
       else if (d > 1) {
          *(c++) = ' ';
          }
       s = false;
       }
    str++;
    }
  *c = '\0';
  return r;
}

