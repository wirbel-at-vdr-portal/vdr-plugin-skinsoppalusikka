/*
 * soppalusikka.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <getopt.h>
#include <vdr/plugin.h>
#include <vdr/menu.h>
#include "common.h"
#include "config.h"
#include "logo.h"
#include "soppalusikka.h"

#if defined(APIVERSNUM) && APIVERSNUM < 10735
#error "VDR-1.7.35 API version or greater is required!"
#endif

#ifndef GITVERSION
#define GITVERSION ""
#endif

static const char VERSION[]     = "1.7.9" GITVERSION;
static const char DESCRIPTION[] = trNOOP("Soppalusikka skin");

class cPluginSkinSoppalusikka : public cPlugin {
private:
  bool islogodirset;
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
  virtual bool SetupParse(const char *Name, const char *Value);
  virtual bool Service(const char *Id, void *Data = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
  };

class cPluginSkinSoppalusikkaSetup : public cMenuSetupPage {
private:
  cSoppalusikkaConfig data;
  cVector<const char*> help;
  void Setup(void);
protected:
  virtual eOSState ProcessKey(eKeys Key);
  virtual void Store(void);
public:
  cPluginSkinSoppalusikkaSetup(void);
};

cPluginSkinSoppalusikka::cPluginSkinSoppalusikka(void)
: islogodirset(false)
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
               islogodirset = true;
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
  if (!islogodirset) {
     SoppalusikkaConfig.SetLogoDir(cPlugin::ResourceDirectory(PLUGIN_NAME_I18N));
     islogodirset = true;
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
  return new cPluginSkinSoppalusikkaSetup();
}

bool cPluginSkinSoppalusikka::SetupParse(const char *Name, const char *Value)
{
  // parse your own setup parameters and store their values.
  debug("cPluginSkinSoppalusikka::SetupParse()");
  if      (!strcasecmp(Name, "ShowAuxInfo"))     SoppalusikkaConfig.showauxinfo     = atoi(Value);
  else if (!strcasecmp(Name, "ShowProgressBar")) SoppalusikkaConfig.showprogressbar = atoi(Value);
  else if (!strcasecmp(Name, "ShowSymbols"))     SoppalusikkaConfig.showsymbols     = atoi(Value);
  else if (!strcasecmp(Name, "ShowLogo"))        SoppalusikkaConfig.showlogo        = atoi(Value);
  else if (!strcasecmp(Name, "ShowVPS"))         SoppalusikkaConfig.showvps         = atoi(Value);
  else if (!strcasecmp(Name, "ShowDuration"))    SoppalusikkaConfig.showduration    = atoi(Value);
  else if (!strcasecmp(Name, "CacheSize"))       SoppalusikkaConfig.cachesize       = atoi(Value);
  else return false;

  return true;
}

bool cPluginSkinSoppalusikka::Service(const char *Id, void *Data)
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

cString cPluginSkinSoppalusikka::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  if (strcasecmp(Command, "FLSH") == 0) {
     SoppalusikkaLogoCache.Flush();
     return cString("Logo cache flushed");
     }
  return NULL;
}

cPluginSkinSoppalusikkaSetup::cPluginSkinSoppalusikkaSetup(void)
{
  // create setup menu
  debug("cPluginSkinSoppalusikkaSetup()");
  data = SoppalusikkaConfig;
  Setup();
  SetHelp(tr("Button$Flush cache"), NULL, NULL, NULL);
}

void cPluginSkinSoppalusikkaSetup::Setup(void)
{
  // update setup display
  int current = Current();

  Clear();
  help.Clear();

  Add(new cMenuEditBoolItem(tr("Show auxiliary information"), &data.showauxinfo));
  help.Append(tr("Define whether any auxiliary information is shown in info menus."));

  Add(new cMenuEditBoolItem(tr("Show progressbar"), &data.showprogressbar));
  help.Append(tr("Define whether a progressbar is shown in schedule menu."));

  Add(new cMenuEditBoolItem(tr("Show symbols"), &data.showsymbols));
  help.Append(tr("Define whether symbols are shown in recordings and schedule menus."));

  Add(new cMenuEditBoolItem(tr("Show VPS in channel info"), &data.showvps));
  help.Append(tr("Define whether VPS information is shown in channel info menu."));

  Add(new cMenuEditBoolItem(tr("Show event duration in channel info"), &data.showduration, tr("remaining"), tr("total")));
  help.Append(tr("Define whether remaining or total event duration is shown in channel info menu."));

  Add(new cMenuEditBoolItem(tr("Show channel logos"), &data.showlogo));
  help.Append(tr("Define whether channels logos are shown in channel info menu.\n\nOnly XPM format is accepted: 64x48 pixel and max. 13 colors."));

  if (data.showlogo) {
     Add(new cMenuEditIntItem( tr("Channel logo cache size"), &data.cachesize, 0, 1000));
     help.Append(tr("Define the cache size for channel logos.\n\nThe bigger cache results faster zapping."));
    }

  SetCurrent(Get(current));
  Display();
}

void cPluginSkinSoppalusikkaSetup::Store(void)
{
  // store setup data
  debug("cPluginSkinSoppalusikkaSetup::Store()");
  SoppalusikkaConfig = data;
  SetupStore("ShowAuxInfo",     SoppalusikkaConfig.showauxinfo);
  SetupStore("ShowProgressBar", SoppalusikkaConfig.showprogressbar);
  SetupStore("ShowSymbols",     SoppalusikkaConfig.showsymbols);
  SetupStore("ShowLogo",        SoppalusikkaConfig.showlogo);
  SetupStore("ShowVPS",         SoppalusikkaConfig.showvps);
  SetupStore("ShowDuration",    SoppalusikkaConfig.showduration);
  SetupStore("CacheSize",       SoppalusikkaConfig.cachesize);
  // resize logo cache
  SoppalusikkaLogoCache.Resize(SoppalusikkaConfig.cachesize);
}

eOSState cPluginSkinSoppalusikkaSetup::ProcessKey(eKeys Key)
{
  // process key presses
  int oldshowlogo = data.showlogo;

  eOSState state = cMenuSetupPage::ProcessKey(Key);

  if (Key != kNone && (data.showlogo != oldshowlogo))
     Setup();

  if (state == osUnknown) {
     switch (Key) {
       case kRed:
            Skins.Message(mtInfo, tr("Flushing channel logo cache..."));
            SoppalusikkaLogoCache.Flush();
            Skins.Message(mtInfo, NULL);
            state = osContinue;
            break;
       case kInfo:
            if (Current() < help.Size())
               return AddSubMenu(new cMenuText(cString::sprintf("%s - %s '%s'", tr("Help"), trVDR("Plugin"), PLUGIN_NAME_I18N), help[Current()]));
            break;
       default:
            break;
       }
     }

  return state;
}

VDRPLUGINCREATOR(cPluginSkinSoppalusikka); // don't touch this!
