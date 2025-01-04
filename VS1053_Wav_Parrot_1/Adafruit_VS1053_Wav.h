#include <Adafruit_VS1053.h>

class Adafruit_VS1053_Wav_FilePlayer: public Adafruit_VS1053_FilePlayer {

  public:

   /*!
   * @brief Hardware SPI constructor. Uses Hardware SPI and assumes the default
   * SPI pins
   * @param rst Reset pin
   * @param cs SCI Chip Select pin
   * @param dcs SDI Chip Select pin
   * @param dreq Data Request pin
   * @param cardCS CS pin for the SD card on the SPI bus
   */
  Adafruit_VS1053_Wav_FilePlayer(int8_t rst, int8_t cs, int8_t dcs, int8_t dreq,
                             int8_t cardCS);

  /*!
    * @brief Start recording
    * @param mic mic=true for microphone input
    * @param samplerate sample rate in hz (8000 - 48000)
    */
  void startRecordWav(boolean mic, uint16_t samplerate);

  /*!
    * @brief Stop the recording
    */
  void stopRecordWav(void);

};
