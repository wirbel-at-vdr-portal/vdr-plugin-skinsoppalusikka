/*
 * common.h: The 'soppalusikka' VDR skin
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef __SKINSOPPALUSIKKA_COMMON_H
#define __SKINSOPPALUSIKKA_COMMON_H

#include <vdr/tools.h>

#ifdef DEBUG
#define debug(x...) dsyslog("Soppalusikka: " x);
#define error(x...) esyslog("Soppalusikka: " x);
#else
#define debug(x...) ;
#define error(x...) esyslog("Soppalusikka: " x);
#endif

#define strcatrealloc(dest, src) \
  if (src) { \
     dest = (char *)realloc(dest, strlen(dest) + strlen(src) + 1); \
     if (dest) \
        strcat(dest, src); \
     else \
        error("ERROR: strcatrealloc out of memory!"); \
  }

#endif // __SKINSOPPALUSIKKA_COMMON_H
