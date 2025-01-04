#include "Adafruit_VS1053_Wav.h"

Adafruit_VS1053_Wav_FilePlayer::Adafruit_VS1053_Wav_FilePlayer(int8_t rst, int8_t cs,
                                                       int8_t dcs, int8_t dreq,
                                                       int8_t cardcs)
    : Adafruit_VS1053_FilePlayer(rst, cs, dcs, dreq, cardcs) {

  playingMusic = false;
}

void Adafruit_VS1053_Wav_FilePlayer::startRecordWav(boolean mic, uint16_t samplerate) {
  softReset();
  while (!readyForData())
    ;

  sciWrite(VS1053_SCI_AICTRL0, samplerate); // Sample rate between 8000 and
                                            // 48000
//  sciWrite(VS1053_SCI_AICTRL1, 0);    // Recording gain : 1024 : 1.If 0, use AGC
  sciWrite(VS1053_SCI_AICTRL1, 200);    // Recording gain : 1024 : 1.If 0, use AGC
    sciWrite(VS1053_SCI_AICTRL2, 500); // Maximum AGC level: 1024 = 1. Only used
// sciWrite(VS1053_SCI_AICTRL2, 4096); // Maximum AGC level: 1024 = 1. Only used
                                      // if SCI_AICTRL1 is set to 0.
  // Miscellaneous bits that also must be set before recording.
  // sciWrite(VS1053_SCI_AICTRL3, 0); //joint stereo AGC + IMA ADPCM
  sciWrite(VS1053_SCI_AICTRL3, 2); // LEFT only
  // sciWrite(VS1053_SCI_AICTRL3, 3); //RIGHT only
  // sciWrite(VS1053_SCI_AICTRL3, 4); //joint stereo AGC + LINEAR PCM

  while (!readyForData())
    ;

  if (mic) {
    sciWrite(VS1053_REG_MODE, VS1053_MODE_SM_RESET | VS1053_MODE_SM_ADPCM |
                                  VS1053_MODE_SM_SDINEW);
  } else {
    sciWrite(VS1053_REG_MODE, VS1053_MODE_SM_RESET | VS1053_MODE_SM_LINE1 |
                                  VS1053_MODE_SM_ADPCM | VS1053_MODE_SM_SDINEW);
  }

  while (!readyForData())
    ;

  // IMA fix patch
  sciWrite(VS1053_REG_WRAMADDR, 0x8010);
  sciWrite(VS1053_REG_WRAM, 0x3e12);
  sciWrite(VS1053_REG_WRAM, 0xb817);
  sciWrite(VS1053_REG_WRAM, 0x3e14);
  sciWrite(VS1053_REG_WRAM, 0xf812);
  sciWrite(VS1053_REG_WRAM, 0x3e01);
  sciWrite(VS1053_REG_WRAM, 0xb811);
  sciWrite(VS1053_REG_WRAM, 0x0007);
  sciWrite(VS1053_REG_WRAM, 0x9717);
  sciWrite(VS1053_REG_WRAM, 0x0020);
  sciWrite(VS1053_REG_WRAM, 0xffd2);
  sciWrite(VS1053_REG_WRAM, 0x0030);
  sciWrite(VS1053_REG_WRAM, 0x11d1);
  sciWrite(VS1053_REG_WRAM, 0x3111);
  sciWrite(VS1053_REG_WRAM, 0x8024);
  sciWrite(VS1053_REG_WRAM, 0x3704);
  sciWrite(VS1053_REG_WRAM, 0xc024);
  sciWrite(VS1053_REG_WRAM, 0x3b81);
  sciWrite(VS1053_REG_WRAM, 0x8024);
  sciWrite(VS1053_REG_WRAM, 0x3101);
  sciWrite(VS1053_REG_WRAM, 0x8024);
  sciWrite(VS1053_REG_WRAM, 0x3b81);
  sciWrite(VS1053_REG_WRAM, 0x8024);
  sciWrite(VS1053_REG_WRAM, 0x3f04);
  sciWrite(VS1053_REG_WRAM, 0xc024);
  sciWrite(VS1053_REG_WRAM, 0x2808);
  sciWrite(VS1053_REG_WRAM, 0x4800);
  sciWrite(VS1053_REG_WRAM, 0x36f1);
  sciWrite(VS1053_REG_WRAM, 0x9811);
  sciWrite(VS1053_REG_WRAMADDR, 0x8028);
  sciWrite(VS1053_REG_WRAM, 0x2a00);
  sciWrite(VS1053_REG_WRAM, 0x040e);
}

void Adafruit_VS1053_Wav_FilePlayer::stopRecordWav(void) { sciWrite(VS1053_SCI_AICTRL3, 1); }
