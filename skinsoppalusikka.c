/*
 * soppalusikka.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <getopt.h>
#include <vdr/plugin.h>
#include "common.h"
#include "config.h"
#include "logo.h"
#include "setup.h"
#include "soppalusikka.h"

#if defined(APIVERSNUM) && APIVERSNUM < 20200
#error "VDR-2.2.0 API version or greater is required!"
#endif

#ifndef GITVERSION
#define GITVERSION ""
#endif

static const char VERSION[]     = "2.2.1" GITVERSION;
static const char DESCRIPTION[] = trNOOP("Soppalusikka skin");

class cPluginSkinSoppalusikka : public cPlugin {
private:
  bool isLogoDirSetM;

public:
  cPluginSkinSoppalusikka(void);
  virtual ~cPluginSkinSoppalusikka();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return tr(DESCRIPTION); }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual void MainThreadHook(void) {}
  virtual cString Active(void) { return NULL; }
  virtual const char *MainMenuEntry(void) { return NULL; }
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *nameP, const char *valueP);
  virtual bool Service(const char *idP, void *dataP = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *commandP, const char *optionP, int &replyCodeP);
  };

cPluginSkinSoppalusikka::cPluginSkinSoppalusikka(void)
: isLogoDirSetM(false)
{
  // initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
  debug("cPluginSkinSoppalusikka()");
}

cPluginSkinSoppalusikka::~cPluginSkinSoppalusikka()
{
  // clean up after yourself!
}

const char *cPluginSkinSoppalusikka::CommandLineHelp(void)
{
  // return a string that describes all known command line options.
  return "  -l <LOGODIR>, --logodir=<LOGODIR>  Define a directory for channel logos.\n";
}

bool cPluginSkinSoppalusikka::ProcessArgs(int argc, char *argv[])
{
  // implement command line argument processing here if applicable.
  static const struct option long_options[] = {
       { "logodir", required_argument, NULL, 'l' },
       { NULL,      no_argument,       NULL, 0   }
     };

  int c;
  while ((c = getopt_long(argc, argv, "l:", long_options, NULL)) != -1) {
        switch (c) {
          case 'l':
               SoppalusikkaConfig.SetLogoDir(optarg);
               isLogoDirSetM = true;
               break;
          default:
               return false;
          }
        }
  return true;
}

bool cPluginSkinSoppalusikka::Initialize(void)
{
  // initialize any background activities the plugin shall perform.
  debug("cPluginSkinSoppalusikka::Initialize()");
  return true;
}

bool cPluginSkinSoppalusikka::Start(void)
{
  // start any background activities the plugin shall perform.
  debug("cPluginSkinSoppalusikka::Start()");
  // set logo directory
  if (!isLogoDirSetM) {
     SoppalusikkaConfig.SetLogoDir(cPlugin::ResourceDirectory(PLUGIN_NAME_I18N));
     isLogoDirSetM = true;
     }
  // resize logo cache
  SoppalusikkaLogoCache.Resize(SoppalusikkaConfig.cachesize);
  // create skin
  new cSkinSoppalusikka;
  return true;
}

void cPluginSkinSoppalusikka::Stop(void)
{
  // stop any background activities the plugin shall perform.
  debug("cPluginSkinSoppalusikka::Stop()");
}

void cPluginSkinSoppalusikka::Housekeeping(void)
{
  // perform any cleanup or other regular tasks.
}

cOsdObject *cPluginSkinSoppalusikka::MainMenuAction(void)
{
  // perform the action when selected from the main VDR menu.
  return NULL;
}

cMenuSetupPage *cPluginSkinSoppalusikka::SetupMenu(void)
{
  // return a setup menu in case the plugin supports one.
  debug("cPluginSkinSoppalusikka::SetupMenu()");
  return new cSkinSoppalusikkaSetup();
}

bool cPluginSkinSoppalusikka::SetupParse(const char *nameP, const char *valueP)
{
  // parse your own setup parameters and store their values.
  debug("cPluginSkinSoppalusikka::SetupParse()");
  if      (!strcasecmp(nameP, "ShowAuxInfo"))     SoppalusikkaConfig.showauxinfo     = atoi(valueP);
  else if (!strcasecmp(nameP, "ShowProgressBar")) SoppalusikkaConfig.showprogressbar = atoi(valueP);
  else if (!strcasecmp(nameP, "ShowSymbols"))     SoppalusikkaConfig.showsymbols     = atoi(valueP);
  else if (!strcasecmp(nameP, "ShowLogo"))        SoppalusikkaConfig.showlogo        = atoi(valueP);
  else if (!strcasecmp(nameP, "ShowVPS"))         SoppalusikkaConfig.showvps         = atoi(valueP);
  else if (!strcasecmp(nameP, "ShowDuration"))    SoppalusikkaConfig.showduration    = atoi(valueP);
  else if (!strcasecmp(nameP, "CacheSize"))       SoppalusikkaConfig.cachesize       = atoi(valueP);
  else return false;

  return true;
}

bool cPluginSkinSoppalusikka::Service(const char *idP, void *dataP)
{
  // handle custom service requests from other plugins
  return false;
}

const char **cPluginSkinSoppalusikka::SVDRPHelpPages(void)
{
  static const char *HelpPages[] = {
    "FLSH\n"
    "    Flush logo cache.",
    NULL
    };
  return HelpPages;
}

cString cPluginSkinSoppalusikka::SVDRPCommand(const char *commandP, const char *optionP, int &replyCodeP)
{
  if (strcasecmp(commandP, "FLSH") == 0) {
     SoppalusikkaLogoCache.Flush();
     return cString("Logo cache flushed");
     }
  return NULL;
}

VDRPLUGINCREATOR(cPluginSkinSoppalusikka); // don't touch this!
