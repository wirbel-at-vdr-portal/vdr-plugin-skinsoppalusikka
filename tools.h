/*
 * tools.h: The 'soppalusikka' VDR skin
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef __SKINSOPPALUSIKKA_TOOLS_H
#define __SKINSOPPALUSIKKA_TOOLS_H

#include <vdr/tools.h>

char *strcatrealloc(char *dest, const char *src);
char *strncatrealloc(char *dest, const char *src, size_t len);
char *striptags(char *str);

#endif // __SKINSOPPALUSIKKA_TOOLS_H
