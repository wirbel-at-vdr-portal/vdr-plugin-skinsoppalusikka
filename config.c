
/*
 * config.c: 'Soppalusikka' skin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <stdlib.h>
#include "common.h"
#include "config.h"

cSoppalusikkaConfig SoppalusikkaConfig;

cSoppalusikkaConfig::cSoppalusikkaConfig()
: logodir(""), showauxinfo(1), showlogo(0), showvps(1),
  showduration(1), showsymbols(0), showprogressbar(1),
  cachesize(100)
{
}

cSoppalusikkaConfig::~cSoppalusikkaConfig()
{
}

void cSoppalusikkaConfig::SetLogoDir(const char *logodirP)
{
  debug("%s(%s)", __PRETTY_FUNCTION__, logodirP);
  logodir = cString(logodirP);
}
