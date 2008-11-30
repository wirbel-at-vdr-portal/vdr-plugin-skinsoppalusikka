/*
 * config.h: 'Soppalusikka' skin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#ifndef __SKINSOPPALUSIKKA_CONFIG_H
#define __SKINSOPPALUSIKKA_CONFIG_H

struct cSoppalusikkaConfig
{
private:
  cString logodir;
public:
  cSoppalusikkaConfig();
  ~cSoppalusikkaConfig();
  void SetLogoDir(const char *logodirP);
  const char *GetLogoDir(void) { return logodir; }
  int showauxinfo;
  int showlogo;
  int showvps;
  int showduration; // 0 = remaining; 1 = total
  int showsymbols;
  int showprogressbar;
  int cachesize;
};

extern cSoppalusikkaConfig SoppalusikkaConfig;

#endif // __SKINSOPPALUSIKKA_CONFIG_H
