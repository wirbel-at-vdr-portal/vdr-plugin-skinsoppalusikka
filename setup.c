/*
 * setup.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <vdr/menu.h>

#include "common.h"
#include "config.h"
#include "logo.h"
#include "setup.h"

cSkinSoppalusikkaSetup::cSkinSoppalusikkaSetup()
: dataM(SoppalusikkaConfig)
{
  // create setup menu
  debug("cSkinSoppalusikkaSetup()");
  SetMenuCategory(mcSetupPlugins);
  Setup();
  SetHelp(tr("Button$Flush cache"), NULL, NULL, NULL);
}

void cSkinSoppalusikkaSetup::Setup(void)
{
  // update setup display
  int current = Current();

  Clear();
  helpM.Clear();

  Add(new cMenuEditBoolItem(tr("Show auxiliary information"), &dataM.showauxinfo));
  helpM.Append(tr("Define whether any auxiliary information is shown in info menus."));

  Add(new cMenuEditBoolItem(tr("Show progressbar"), &dataM.showprogressbar));
  helpM.Append(tr("Define whether a progressbar is shown in schedule menu."));

  Add(new cMenuEditBoolItem(tr("Show symbols"), &dataM.showsymbols));
  helpM.Append(tr("Define whether symbols are shown in recordings and schedule menus."));

  Add(new cMenuEditBoolItem(tr("Show VPS in channel info"), &dataM.showvps));
  helpM.Append(tr("Define whether VPS information is shown in channel info menu."));

  Add(new cMenuEditBoolItem(tr("Show event duration in channel info"), &dataM.showduration, tr("remaining"), tr("total")));
  helpM.Append(tr("Define whether remaining or total event duration is shown in channel info menu."));

  Add(new cMenuEditBoolItem(tr("Show channel logos"), &dataM.showlogo));
  helpM.Append(tr("Define whether channels logos are shown in channel info menu.\n\nOnly XPM format is accepted: 64x48 pixel and max. 13 colors."));

  if (dataM.showlogo) {
     Add(new cMenuEditIntItem( tr("Channel logo cache size"), &dataM.cachesize, 0, 1000));
     helpM.Append(tr("Define the cache size for channel logos.\n\nThe bigger cache results faster zapping."));
    }

  SetCurrent(Get(current));
  Display();
}

void cSkinSoppalusikkaSetup::Store(void)
{
  // store setup data
  debug("cSkinSoppalusikkaSetup::Store()");
  SoppalusikkaConfig = dataM;
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

eOSState cSkinSoppalusikkaSetup::ProcessKey(eKeys keyP)
{
  // process key presses
  int oldshowlogo = dataM.showlogo;

  eOSState state = cMenuSetupPage::ProcessKey(keyP);

  if (keyP != kNone && (dataM.showlogo != oldshowlogo))
     Setup();

  if (state == osUnknown) {
     switch (keyP) {
       case kRed:
            Skins.Message(mtInfo, tr("Flushing channel logo cache..."));
            SoppalusikkaLogoCache.Flush();
            Skins.Message(mtInfo, NULL);
            state = osContinue;
            break;
       case kInfo:
            if (Current() < helpM.Size())
               return AddSubMenu(new cMenuText(cString::sprintf("%s - %s '%s'", tr("Help"), trVDR("Plugin"), PLUGIN_NAME_I18N), helpM[Current()]));
            break;
       default:
            break;
       }
     }

  return state;
}
