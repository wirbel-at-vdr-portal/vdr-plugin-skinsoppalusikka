/*
 * config.c: 'Soppalusikka' skin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "common.h"
#include "config.h"

cSoppalusikkaConfig SoppalusikkaConfig;

cSoppalusikkaConfig::cSoppalusikkaConfig()
: logodir(NULL), showlogo(0), cachesize(50), usechannelid(0)
{
}

cSoppalusikkaConfig::~cSoppalusikkaConfig()
{
  if (logodir)
     DELETENULL(logodir);
}

void cSoppalusikkaConfig::SetLogoDir(const char *logodirP)
{
  debug("cSoppalusikkaConfig::SetLogoDir(%s)", logodirP);
  if (logodir)
     DELETENULL(logodir);
  logodir = strdup(logodirP);
}
