
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
: logodir(""), usesinglearea(0), showauxinfo(1), showlogo(0), showvps(1),
  showduration(1), showsymbols(0), showprogressbar(1), cachesize(100)
{
}

cSoppalusikkaConfig::~cSoppalusikkaConfig()
{
}

void cSoppalusikkaConfig::SetLogoDir(const char *logodirP)
{
  debug("cSoppalusikkaConfig::SetLogoDir(%s)", logodirP);
  logodir = cString(logodirP);
}
