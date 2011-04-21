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
  debug("%s(): %dx%d", __PRETTY_FUNCTION__, width, height);
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
  debug("%s(): %.02fx%.02f ", __PRETTY_FUNCTION__, xFactorM, yFactorM);
  if (!DoubleEqual(0.0, xFactorM) || !DoubleEqual(0.0, yFactorM)) {
     Flush();

     // pushing order must follow the enumeration - keep original proportions
     cacheM.Append(bmAudio.Scaled(yFactorM, yFactorM, antiAliasM));          // SYMBOL_AUDIO
     cacheM.Append(bmAudioLeft.Scaled(yFactorM, yFactorM, antiAliasM));      // SYMBOL_AUDIO_LEFT
     cacheM.Append(bmAudioRight.Scaled(yFactorM, yFactorM, antiAliasM));     // SYMBOL_AUDIO_RIGHT
     cacheM.Append(bmDolbyDigital.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_DOLBY_DIGITAL
     cacheM.Append(bmEncrypted.Scaled(yFactorM, yFactorM, antiAliasM));      // SYMBOL_ENCRYPTED
     cacheM.Append(bmFastForward.Scaled(yFactorM, yFactorM, antiAliasM));    // SYMBOL_FFWD
     cacheM.Append(bmFastForward1.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD1
     cacheM.Append(bmFastForward2.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD2
     cacheM.Append(bmFastForward3.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FFWD3
     cacheM.Append(bmFastReverse.Scaled(yFactorM, yFactorM, antiAliasM));    // SYMBOL_FREW
     cacheM.Append(bmFastReverse1.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW1
     cacheM.Append(bmFastReverse2.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW2
     cacheM.Append(bmFastReverse3.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_FREW3
     cacheM.Append(bmPause.Scaled(yFactorM, yFactorM, antiAliasM));          // SYMBOL_PAUSE
     cacheM.Append(bmPlay.Scaled(yFactorM, yFactorM, antiAliasM));           // SYMBOL_PLAY
     cacheM.Append(bmRadio.Scaled(yFactorM, yFactorM, antiAliasM));          // SYMBOL_RADIO
     cacheM.Append(bmRecording.Scaled(yFactorM, yFactorM, antiAliasM));      // SYMBOL_RECORDING
     cacheM.Append(bmRunning.Scaled(yFactorM, yFactorM, antiAliasM));        // SYMBOL_RUNNING
     cacheM.Append(bmSlowForward.Scaled(yFactorM, yFactorM, antiAliasM));    // SYMBOL_SFWD
     cacheM.Append(bmSlowForward1.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD1
     cacheM.Append(bmSlowForward2.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD2
     cacheM.Append(bmSlowForward3.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SFWD3
     cacheM.Append(bmSlowReverse.Scaled(yFactorM, yFactorM, antiAliasM));    // SYMBOL_SREW
     cacheM.Append(bmSlowReverse1.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW1
     cacheM.Append(bmSlowReverse2.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW2
     cacheM.Append(bmSlowReverse3.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_SREW3
     cacheM.Append(bmTeletext.Scaled(yFactorM, yFactorM, antiAliasM));       // SYMBOL_TELETEXT
     cacheM.Append(bmVPS.Scaled(yFactorM, yFactorM, antiAliasM));            // SYMBOL_VPS
     cacheM.Append(bmEventPartTimer.Scaled(yFactorM, yFactorM, antiAliasM)); // SYMBOL_EVENT_PARTTIMER
     cacheM.Append(bmEventTimer.Scaled(yFactorM, yFactorM, antiAliasM));     // SYMBOL_EVENT_TIMER
     cacheM.Append(bmEventVPS.Scaled(yFactorM, yFactorM, antiAliasM));       // SYMBOL_EVENT_VPS
     cacheM.Append(bmEventRunning.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_EVENT_RUNNING
     cacheM.Append(bmEventRecording.Scaled(yFactorM, yFactorM, antiAliasM)); // SYMBOL_EVENT_RECORDING
     cacheM.Append(bmRecordingNew.Scaled(yFactorM, yFactorM, antiAliasM));   // SYMBOL_RECORDING_NEW

     return true;
     }

  return false;
}

bool cSoppalusikkaSymbolCache::Flush(void)
{
  debug("%s()", __PRETTY_FUNCTION__);

  for (int i = 0; i < cacheM.Size(); ++i) {
      cBitmap *bmp = cacheM[i];
      DELETENULL(bmp);
      }
  cacheM.Clear();

  return true;
}

cBitmap& cSoppalusikkaSymbolCache::Get(eSymbols symbolP)
{
  cBitmap *bitmapM = NULL;

  if (symbolP < cacheM.Size())
     bitmapM = cacheM[symbolP];
  else
     error("%s(): Invalid symbol %d", __PRETTY_FUNCTION__, symbolP);

  return *bitmapM;
}
