#include <TFT_eSPI.h>
#include <arduinoFFT.h>

#define SAMPLE_RATE 44100 // Sample rate of the microphone (adjust if needed)
#define MIC_PIN A0         // Analog input pin connected to the microphone (GP26)

#define FFT_SIZE 256      // Size of the FFT buffer (adjust if needed)

TFT_eSPI tft = TFT_eSPI();
arduinoFFT FFT = arduinoFFT();

double microphoneData[FFT_SIZE];

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Other setup code, if any
}

void loop() {
  // Read the analog value from the microphone
  for (int i = 0; i < FFT_SIZE; i++) {
    microphoneData[i] = analogRead(MIC_PIN);
  }

  // Perform FFT analysis
  FFT.Windowing(microphoneData, FFT_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Display the spectrogram on the TFT
  displaySpectrogram();

  // Other loop code, if any
}

void displaySpectrogram() {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < FFT_SIZE / 2; i++) {
    // Map FFT data to pixel height
    int pixelHeight = map(microphoneData[i], 0, 5000, 0, TFT_HEIGHT);

    // Draw a vertical line to represent the spectrogram
    tft.drawFastVLine(i, TFT_HEIGHT - pixelHeight, pixelHeight, TFT_WHITE);
  }
}
