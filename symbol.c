/*
 * symbol.c: The 'soppalusikka' VDR skin
 *
 * $Id: $
 */

#include "common.h"
#include "tools.h"
#include "config.h"
#include "symbol.h"
#include <vdr/device.h>

#include "symbols/audio.xpm"
#include "symbols/audioleft.xpm"
#include "symbols/audioright.xpm"
#include "symbols/dolbydigital.xpm"
#include "symbols/encrypted.xpm"
#include "symbols/ffwd.xpm"
#include "symbols/ffwd1.xpm"
#include "symbols/ffwd2.xpm"
#include "symbols/ffwd3.xpm"
#include "symbols/frew.xpm"
#include "symbols/frew1.xpm"
#include "symbols/frew2.xpm"
#include "symbols/frew3.xpm"
#include "symbols/pause.xpm"
#include "symbols/play.xpm"
#include "symbols/radio.xpm"
#include "symbols/recording.xpm"
#include "symbols/running.xpm"
#include "symbols/sfwd.xpm"
#include "symbols/sfwd1.xpm"
#include "symbols/sfwd2.xpm"
#include "symbols/sfwd3.xpm"
#include "symbols/srew.xpm"
#include "symbols/srew1.xpm"
#include "symbols/srew2.xpm"
#include "symbols/srew3.xpm"
#include "symbols/teletext.xpm"
#include "symbols/vps.xpm"
#include "symbols/eventparttimer.xpm"
#include "symbols/eventtimer.xpm"
#include "symbols/eventvps.xpm"
#include "symbols/eventrunning.xpm"
#include "symbols/eventrecording.xpm"
#include "symbols/recordingnew.xpm"

static cBitmap bmAudio(audio_xpm);
static cBitmap bmAudioLeft(audioleft_xpm);
static cBitmap bmAudioRight(audioright_xpm);
static cBitmap bmDolbyDigital(dolbydigital_xpm);
static cBitmap bmEncrypted(encrypted_xpm);
static cBitmap bmFastForward(ffwd_xpm);
static cBitmap bmFastForward1(ffwd1_xpm);
static cBitmap bmFastForward2(ffwd2_xpm);
static cBitmap bmFastForward3(ffwd3_xpm);
static cBitmap bmFastReverse(frew_xpm);
static cBitmap bmFastReverse1(frew1_xpm);
static cBitmap bmFastReverse2(frew2_xpm);
static cBitmap bmFastReverse3(frew3_xpm);
static cBitmap bmPause(pause_xpm);
static cBitmap bmPlay(play_xpm);
static cBitmap bmRadio(radio_xpm);
static cBitmap bmRecording(recording_xpm);
static cBitmap bmRunning(running_xpm);
static cBitmap bmSlowForward(sfwd_xpm);
static cBitmap bmSlowForward1(sfwd1_xpm);
static cBitmap bmSlowForward2(sfwd2_xpm);
static cBitmap bmSlowForward3(sfwd3_xpm);
static cBitmap bmSlowReverse(srew_xpm);
static cBitmap bmSlowReverse1(srew1_xpm);
static cBitmap bmSlowReverse2(srew2_xpm);
static cBitmap bmSlowReverse3(srew3_xpm);
static cBitmap bmTeletext(teletext_xpm);
static cBitmap bmVPS(vps_xpm);
static cBitmap bmEventPartTimer(eventparttimer_xpm);
static cBitmap bmEventTimer(eventtimer_xpm);
static cBitmap bmEventVPS(eventvps_xpm);
static cBitmap bmEventRunning(eventrunning_xpm);
static cBitmap bmEventRecording(eventrecording_xpm);
static cBitmap bmRecordingNew(recordingnew_xpm);

cSoppalusikkaSymbolCache SoppalusikkaSymbolCache;

cSoppalusikkaSymbolCache::cSoppalusikkaSymbolCache()
: xFactorM(1.0),
  yFactorM(1.0),
  antiAliasM(false)
{
  Populate();
}

cSoppalusikkaSymbolCache::~cSoppalusikkaSymbolCache()
{
  Flush();
}

void cSoppalusikkaSymbolCache::Refresh()
{
  int width, height;
  double aspect, xfactor, yfactor;
  cDevice::PrimaryDevice()->GetOsdSize(width, height, aspect);
  debug("cSoppalusikkaSymbolCache::Refresh(): %dx%d", width, height);
  xfactor = (double)width / DEFAULT_WIDTH;
  yfactor = (double)height / DEFAULT_HEIGHT;
  if (!DoubleEqual(xfactor, xFactorM) || !DoubleEqual(yfactor, yFactorM)) {
     xFactorM = xfactor;
     yFactorM = yfactor;
     Populate();
     }
}

bool cSoppalusikkaSymbolCache::Populate(void)
{
  debug("cSoppalusikkaSymbolCache::Populate(): %.02fx%.02f ", xFactorM, yFactorM);
  if (!DoubleEqual(0.0, xFactorM) || !DoubleEqual(0.0, yFactorM)) {
     Flush();
     // pushing order must follow the enumeration
     cacheM.push_back(bmAudio.Scaled(xFactorM, yFactorM, antiAliasM));          // SYMBOL_AUDIO
     cacheM.push_back(bmAudioLeft.Scaled(xFactorM, yFactorM, antiAliasM));      // SYMBOL_AUDIO_LEFT
     cacheM.push_back(bmAudioRight.Scaled(xFactorM, yFactorM, antiAliasM));     // SYMBOL_AUDIO_RIGHT
     cacheM.push_back(bmDolbyDigital.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_DOLBY_DIGITAL
     cacheM.push_back(bmEncrypted.Scaled(xFactorM, yFactorM, antiAliasM));      // SYMBOL_ENCRYPTED
     cacheM.push_back(bmFastForward.Scaled(xFactorM, yFactorM, antiAliasM));    // SYMBOL_FFWD
     cacheM.push_back(bmFastForward1.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD1
     cacheM.push_back(bmFastForward2.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD2
     cacheM.push_back(bmFastForward3.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD3
     cacheM.push_back(bmFastReverse.Scaled(xFactorM, yFactorM, antiAliasM));    // SYMBOL_FREW
     cacheM.push_back(bmFastReverse1.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW1
     cacheM.push_back(bmFastReverse2.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW2
     cacheM.push_back(bmFastReverse3.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW3
     cacheM.push_back(bmPause.Scaled(xFactorM, yFactorM, antiAliasM));          // SYMBOL_PAUSE
     cacheM.push_back(bmPlay.Scaled(xFactorM, yFactorM, antiAliasM));           // SYMBOL_PLAY
     cacheM.push_back(bmRadio.Scaled(xFactorM, yFactorM, antiAliasM));          // SYMBOL_RADIO
     cacheM.push_back(bmRecording.Scaled(xFactorM, yFactorM, antiAliasM));      // SYMBOL_RECORDING
     cacheM.push_back(bmRunning.Scaled(xFactorM, yFactorM, antiAliasM));        // SYMBOL_RUNNING
     cacheM.push_back(bmSlowForward.Scaled(xFactorM, yFactorM, antiAliasM));    // SYMBOL_SFWD
     cacheM.push_back(bmSlowForward1.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD1
     cacheM.push_back(bmSlowForward2.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD2
     cacheM.push_back(bmSlowForward3.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD3
     cacheM.push_back(bmSlowReverse.Scaled(xFactorM, yFactorM, antiAliasM));    // SYMBOL_SREW
     cacheM.push_back(bmSlowReverse1.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW1
     cacheM.push_back(bmSlowReverse2.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW2
     cacheM.push_back(bmSlowReverse3.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW3
     cacheM.push_back(bmTeletext.Scaled(xFactorM, yFactorM, antiAliasM));       // SYMBOL_TELETEXT
     cacheM.push_back(bmVPS.Scaled(xFactorM, yFactorM, antiAliasM));            // SYMBOL_VPS
     cacheM.push_back(bmEventPartTimer.Scaled(xFactorM, yFactorM, antiAliasM)); // SYMBOL_EVENT_PARTTIMER
     cacheM.push_back(bmEventTimer.Scaled(xFactorM, yFactorM, antiAliasM));     // SYMBOL_EVENT_TIMER
     cacheM.push_back(bmEventVPS.Scaled(xFactorM, yFactorM, antiAliasM));       // SYMBOL_EVENT_VPS
     cacheM.push_back(bmEventRunning.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_EVENT_RUNNING
     cacheM.push_back(bmEventRecording.Scaled(xFactorM, yFactorM, antiAliasM)); // SYMBOL_EVENT_RECORDING
     cacheM.push_back(bmRecordingNew.Scaled(xFactorM, yFactorM, antiAliasM));   // SYMBOL_RECORDING_NEW

     return true;
     }

  return false;
}

bool cSoppalusikkaSymbolCache::Flush(void)
{
  debug("cSoppalusikkaSymbolCache::Flush()");
  if (!cacheM.empty()) {
     for (unsigned int i = 0; i < cacheM.size(); ++i) {
         cBitmap *bmp = cacheM[i];
         DELETENULL(bmp);
         }
     cacheM.clear();
     }
  return true;
}

cBitmap& cSoppalusikkaSymbolCache::Get(unsigned int symbolP)
{
  cBitmap *bitmapM = NULL;

  if (symbolP < cacheM.size())
     bitmapM = cacheM[symbolP];

  return *bitmapM;
}
