/* ----------------------------------------------------------------------
Double-buffering (smooth animation) Protomatter library example.
PLEASE SEE THE "simple" EXAMPLE FOR AN INTRODUCTORY SKETCH.
Comments here pare down many of the basics and focus on the new concepts.

This example is written for a 64x32 matrix but can be adapted to others.
------------------------------------------------------------------------- */

#include <Adafruit_Protomatter.h>
#include <Fonts/FreeSansBold18pt7b.h> // Large friendly font

/* ----------------------------------------------------------------------
The RGB matrix must be wired to VERY SPECIFIC pins, different for each
microcontroller board. This first section sets that up for a number of
supported boards.
------------------------------------------------------------------------- */

  uint8_t rgbPins[]  = {6, 5, 9, 11, 10, 12};
  uint8_t addrPins[] = {A5, A4, A3, A2};
  uint8_t clockPin   = 13; // Must be on same port as rgbPins
  uint8_t latchPin   = RX;
  uint8_t oePin      = TX;

/* ----------------------------------------------------------------------
Matrix initialization is explained EXTENSIVELY in "simple" example sketch!
It's very similar here, but we're passing "true" for the last argument,
enabling double-buffering -- this permits smooth animation by having us
draw in a second "off screen" buffer while the other is being shown.
------------------------------------------------------------------------- */

Adafruit_Protomatter matrix(
  128,          // Matrix width in pixels
  6,           // Bit depth -- 6 here provides maximum color options
  1, rgbPins,  // # of matrix chains, array of 6 RGB pins for each
  4, addrPins, // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin, // Other matrix control pins
  true);       // HERE IS THE MAGIC FOR DOUBLE-BUFFERING!

// Sundry globals used for animation ---------------------------------------

int16_t  textX;        // Current text position (X)
int16_t  textY;        // Current text position (Y)
int16_t  textMin;      // Text pos. (X) when scrolled off left edge
char     str[42];      // Buffer to hold scrolling message text
int16_t  ball[3][4] = {
  {  3,  0,  1,  1 },  // Initial X,Y pos+velocity of 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
uint16_t ballcolor[3]; // Colors for bouncy balls (init in setup())

// SETUP - RUNS ONCE AT PROGRAM START --------------------------------------

void setup(void) {
  Serial.begin(9600);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for(;;);
  }

  // Unlike the "simple" example, we don't do any drawing in setup().
  // But we DO initialize some things we plan to animate...

  // Set up the scrolling message...
  // sprintf(str, "Adafruit %dx%d RGB LED Matrix",
  //   matrix.width(), matrix.height());
  sprintf(str,"YOU ARE A VICTIM OF THE RULES YOU LIVE BY");
  matrix.setFont(&FreeSansBold18pt7b); // Use nice bitmap font
  matrix.setTextWrap(false);           // Allow text off edge
  matrix.setTextColor(0xFFFF);         // White
  int16_t  x1, y1;
  uint16_t w, h;
  matrix.getTextBounds(str, 0, 0, &x1, &y1, &w, &h); // How big is it?
  textMin = -w; // All text is off left edge when it reaches this point
  textX = matrix.width(); // Start off right edge
  textY = matrix.height() / 2 - (y1 + h / 2); // Center text vertically
  // Note: when making scrolling text like this, the setTextWrap(false)
  // call is REQUIRED (to allow text to go off the edge of the matrix),
  // AND it must be BEFORE the getTextBounds() call (or else that will
  // return the bounds of "wrapped" text).

  // Set up the colors of the bouncy balls.
  ballcolor[0] = matrix.color565(0, 20, 0); // Dark green
  ballcolor[1] = matrix.color565(0, 0, 20); // Dark blue
  ballcolor[2] = matrix.color565(20, 0, 0); // Dark red
}

// LOOP - RUNS REPEATEDLY AFTER SETUP --------------------------------------

void loop(void) {
  // Every frame, we clear the background and draw everything anew.
  // This happens "in the background" with double buffering, that's
  // why you don't see everything flicker. It requires double the RAM,
  // so it's not practical for every situation.

  matrix.fillScreen(0); // Fill background black

  // Draw the big scrolly text
  matrix.setCursor(textX, textY);
  matrix.print(str);

  // Update text position for next frame. If text goes off the
  // left edge, reset its position to be off the right edge.
  if((--textX) < textMin) textX = matrix.width();



  // AFTER DRAWING, A show() CALL IS REQUIRED TO UPDATE THE MATRIX!

  matrix.show();

  delay(20); // 20 milliseconds = ~50 frames/second
}
