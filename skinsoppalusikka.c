/*
 * soppalusikka.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "common.h"
#include "config.h"
#include "i18n.h"
#include "logo.h"
#include "soppalusikka.h"
#include <getopt.h>
#include <vdr/plugin.h>

#if defined(VDRVERSNUM) && VDRVERSNUM < 10344
#error "You don't exist! Go away! Upgrade yourself!"
#endif

static const char *VERSION        = "0.0.2";
static const char *DESCRIPTION    = "Soppalusikka skin";

class cPluginSkinSoppalusikka : public cPlugin {
private:
  // add any member variables or functions you may need here.
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
  virtual void Setup(void);
protected:
  virtual eOSState ProcessKey(eKeys Key);
  virtual void Store(void);
public:
  cPluginSkinSoppalusikkaSetup(void);
};

cPluginSkinSoppalusikka::cPluginSkinSoppalusikka(void)
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
  static struct option long_options[] = {
       { "logodir", required_argument, NULL, 'l' },
       { NULL }
     };

  int c;
  while ((c = getopt_long(argc, argv, "l:", long_options, NULL)) != -1) {
        switch (c) {
          case 'l': SoppalusikkaConfig.SetLogoDir(optarg);
                    break;
          default:  return false;
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
  RegisterI18n(Phrases);
  // set logo directory
  if (!SoppalusikkaConfig.GetLogoDir())
     SoppalusikkaConfig.SetLogoDir(cPlugin::ConfigDirectory(PLUGIN_NAME_I18N));
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
  if      (!strcasecmp(Name, "ShowLogo"))     SoppalusikkaConfig.showlogo     = atoi(Value);
  else if (!strcasecmp(Name, "CacheSize"))    SoppalusikkaConfig.cachesize    = atoi(Value);
  else if (!strcasecmp(Name, "UseChannelId")) SoppalusikkaConfig.usechannelid = atoi(Value);
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
  // return help text for SVDRP commands this plugin implements
  return NULL;
}

cString cPluginSkinSoppalusikka::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  // process SVDRP commands this plugin implements
  return NULL;
}

cPluginSkinSoppalusikkaSetup::cPluginSkinSoppalusikkaSetup(void)
{
  // create setup menu
  debug("cPluginSkinSoppalusikkaSetup()");
  data = SoppalusikkaConfig;
  Setup();
}

void cPluginSkinSoppalusikkaSetup::Setup(void)
{
  // update setup display
  int current = Current();

  Clear();

  Add(new cMenuEditBoolItem(   tr("Show channel logos"),       &data.showlogo, tr("no"), tr("yes")));
  if (data.showlogo)
     Add(new cMenuEditBoolItem(tr("Identify channel by"),      &data.usechannelid, tr("name"), tr("data")));
  Add(new cMenuEditIntItem(    tr("Channel logo cache size"),  &data.cachesize, 0, 1000));
  Add(new cOsdItem(            tr("Flush channel logo cache"), osUser1));

  SetCurrent(Get(current));
  Display();
}

void cPluginSkinSoppalusikkaSetup::Store(void)
{
  // store setup data
  debug("cPluginSkinSoppalusikkaSetup::Store()");
  SoppalusikkaConfig = data;
  SetupStore("ShowLogo",     SoppalusikkaConfig.showlogo);
  SetupStore("CacheSize",    SoppalusikkaConfig.cachesize);
  SetupStore("UseChannelId", SoppalusikkaConfig.usechannelid);
  // resize logo cache
  SoppalusikkaLogoCache.Resize(SoppalusikkaConfig.cachesize);
}

eOSState cPluginSkinSoppalusikkaSetup::ProcessKey(eKeys Key)
{
  // process key presses
  int oldshowlogo = data.showlogo;

  eOSState state = cMenuSetupPage::ProcessKey(Key);
  if (Key != kNone && (data.showlogo != oldshowlogo)) {                                                                                                                           
     Setup();
     }
  else if (state == osUser1) {
     Skins.Message(mtInfo, tr("Flushing channel logo cache..."));
     SoppalusikkaLogoCache.Flush();
     Skins.Message(mtInfo, NULL);
     return osContinue;
     }
  return state;
}

VDRPLUGINCREATOR(cPluginSkinSoppalusikka); // don't touch this!
