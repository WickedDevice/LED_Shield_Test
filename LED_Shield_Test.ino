/* * * * * * * * * * * * * * * * * * * * */
/* Demo sketch for MAKE: SMD LED Shield  */
/* Authored by Victor Aprea              */
/* (c) 2015    Wicked Device LLC         */
/* * * * * * * * * * * * * * * * * * * * */

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

uint8_t rowstate = 0;
uint8_t colstate = 0;

void setup() {
  // put your setup code here, to run once:
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("reset");
}

void loop(void){
  slowScanRows();
  rasterize();  
  renderRandomImage();
  renderRectangle();
  renderDownRightSlash();
  renderBarGraph();
  renderAllOn();
  scrollFonts();
  scrollRandom(); 
}

void setRowColValues(uint8_t row, uint8_t col){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, col);
  shiftOut(dataPin, clockPin, MSBFIRST, row);  
  digitalWrite(latchPin, HIGH);
}

void slowScanRows(){
  clearImage();
  for(uint8_t row = 0; row < 8; row++){
     setRowColValues(_BV(row), B11111111);
     delay(100);
  }
}

void rasterize(){
  clearImage();
  for(int row = 0; row < 8; row++){
    for(int col = 7; col >= 0; col--){
       setRowColValues(_BV(row), _BV(col));     
       delay(40);
    } 
  }
}

void renderRandomImage(){
  uint8_t randomImage[8] = {
    B00100110,
    B10110101,
    B11010110,
    B01101011,
    B00011010,
    B10010001,
    B01101011,
    B11110010
  };  
  
  renderImage(randomImage, 1000);
}


void renderRectangle(){
  uint8_t rectangle[8] = {
    B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111
  };  
  
  renderImage(rectangle, 1000);
}

void renderDownRightSlash(){
  uint8_t downRightSlash[8] = {
    B11111111,
    B11000001,
    B10100001,
    B10010001,
    B10001001,
    B10000101,
    B10000011,
    B11111111
  };  
  
  renderImage(downRightSlash, 1000);  
}

void renderBarGraph(){
  uint8_t barGraph[8] = {
    B10000000,
    B11000000,
    B11100000,
    B11110000,
    B11111000,
    B11111100,
    B11111110,
    B11111111
  };  
  
  renderImage(barGraph, 1000);    
}

void renderAllOn(){
  uint8_t allOn[8] = {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111
  };  
  
  renderImage(allOn, 1000);    
}

void clearImage(void){
  setRowColValues(0,0);
}

void renderImage(uint8_t image[8], uint16_t display_duration){
  uint32_t current_time = millis();
  uint32_t end_time = millis() + display_duration;
  while(current_time > end_time){
    current_time = millis();
    end_time = millis() + display_duration;
  }
  clearImage();
  
  while(millis() < end_time){
    for(int row = 0; row < 8; row++){
      setRowColValues(_BV(row), image[row]);
      
      //uncomment delay to see what's really going on in slow motion
      //delay(100);
    }  
  }
}


// a font set borrowed/adapted from 
// http://www.instructables.com/id/LED-Scolling-Dot-Matrix-Font-Graphics-Generator-/step6/Predefined-5x8-Font-Data-and-Awesome-Patterns/
const uint8_t font[] = {
  0x7F, 0x88, 0x88, 0x88, 0x7F, //  A
  0xFF, 0x91, 0x91, 0x91, 0x6E, //  B
  0x7E, 0x81, 0x81, 0x81, 0x42, //  C
  0xFF, 0x81, 0x81, 0x42, 0x3C, //  D
  0xFF, 0x91, 0x91, 0x91, 0x81, //  E
  0xFF, 0x90, 0x90, 0x90, 0x80, //  F
  0x7E, 0x81, 0x89, 0x89, 0x4E, //  G
  0xFF, 0x10, 0x10, 0x10, 0xFF, //  H
  0x81, 0x81, 0xFF, 0x81, 0x81, //  I
  0x06, 0x01, 0x01, 0x01, 0xFE, //  J
  0xFF, 0x18, 0x24, 0x42, 0x81, //  K
  0xFF, 0x01, 0x01, 0x01, 0x01, //  L
  0xFF, 0x40, 0x30, 0x40, 0xFF, //  M
  0xFF, 0x40, 0x30, 0x08, 0xFF, //  N
  0x7E, 0x81, 0x81, 0x81, 0x7E, //  O
  0xFF, 0x88, 0x88, 0x88, 0x70, //  P
  0x7E, 0x81, 0x85, 0x82, 0x7D, //  Q
  0xFF, 0x88, 0x8C, 0x8A, 0x71, //  R
  0x61, 0x91, 0x91, 0x91, 0x8E, //  S
  0x80, 0x80, 0xFF, 0x80, 0x80, //  T
  0xFE, 0x01, 0x01, 0x01, 0xFE, //  U
  0xF0, 0x0C, 0x03, 0x0C, 0xF0, //  V
  0xFF, 0x02, 0x0C, 0x02, 0xFF, //  W
  0xC3, 0x24, 0x18, 0x24, 0xC3, //  X
  0xE0, 0x10, 0x0F, 0x10, 0xE0, //  Y
  0x83, 0x85, 0x99, 0xA1, 0xC1, //  Z
  0x06, 0x29, 0x29, 0x29, 0x1F, //  a
  0xFF, 0x09, 0x11, 0x11, 0x0E, //  b
  0x1E, 0x21, 0x21, 0x21, 0x12, //  c
  0x0E, 0x11, 0x11, 0x09, 0xFF, //  d
  0x0E, 0x15, 0x15, 0x15, 0x0C, //  e
  0x08, 0x7F, 0x88, 0x80, 0x40, //  f
  0x30, 0x49, 0x49, 0x49, 0x7E, //  g
  0xFF, 0x08, 0x10, 0x10, 0x0F, //  h
  0x00, 0x00, 0x5F, 0x00, 0x00, //  i
  0x02, 0x01, 0x21, 0xBE, 0x00, //  j
  0xFF, 0x04, 0x0A, 0x11, 0x00, //  k
  0x00, 0x81, 0xFF, 0x01, 0x00, //  l
  0x3F, 0x20, 0x18, 0x20, 0x1F, //  m
  0x3F, 0x10, 0x20, 0x20, 0x1F, //  n
  0x0E, 0x11, 0x11, 0x11, 0x0E, //  o
  0x3F, 0x24, 0x24, 0x24, 0x18, //  p
  0x10, 0x28, 0x28, 0x18, 0x3F, //  q
  0x1F, 0x08, 0x10, 0x10, 0x08, //  r
  0x09, 0x15, 0x15, 0x15, 0x02, //  s
  0x20, 0xFE, 0x21, 0x01, 0x02, //  t
  0x1E, 0x01, 0x01, 0x02, 0x1F, //  u
  0x1C, 0x02, 0x01, 0x02, 0x1C, //  v
  0x1E, 0x01, 0x0E, 0x01, 0x1E, //  w
  0x11, 0x0A, 0x04, 0x0A, 0x11, //  x
  0x00, 0x39, 0x05, 0x05, 0x3E, //  y
  0x11, 0x13, 0x15, 0x19, 0x11, //  z
  0x00, 0x41, 0xFF, 0x01, 0x00, //  1
  0x43, 0x85, 0x89, 0x91, 0x61, //  2
  0x42, 0x81, 0x91, 0x91, 0x6E, //  3
  0x18, 0x28, 0x48, 0xFF, 0x08, //  4
  0xF2, 0x91, 0x91, 0x91, 0x8E, //  5
  0x1E, 0x29, 0x49, 0x89, 0x86, //  6
  0x80, 0x8F, 0x90, 0xA0, 0xC0, //  7
  0x6E, 0x91, 0x91, 0x91, 0x6E, //  8
  0x70, 0x89, 0x89, 0x8A, 0x7C, //  9
  0x60, 0x80, 0x8D, 0x90, 0x60, //  ?
  0x00, 0x00, 0xFD, 0x00, 0x00, //  !
  0x7E, 0x89, 0x91, 0xA1, 0x7E, //  0
  0x66, 0x89, 0x8F, 0x81, 0x7E, //  @
  0x24, 0xFF, 0x24, 0xFF, 0x24, //  #
  0x76, 0x89, 0x95, 0x62, 0x05, //  &
  0x00, 0x3C, 0x42, 0x81, 0x00, //  (
  0x00, 0x81, 0x42, 0x3C, 0x00, //  )
  0x08, 0x08, 0x3E, 0x08, 0x08, //  "+"
  0x08, 0x08, 0x08, 0x08, 0x08, //  -
  0x14, 0x14, 0x14, 0x14, 0x14, //  =
  0x10, 0x10, 0x54, 0x38, 0x10, //  R arrow
  0x08, 0x1C, 0x2A, 0x08, 0x08, //  L arrow
  0x12, 0x2A, 0x7F, 0x2A, 0x24, //  $
  0x44, 0x02, 0x12, 0x02, 0x44, //  smile
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //  5x8 block  
};

void scrollFonts(){

  uint8_t fontImage[8] = {0};
  uint8_t displayImage[8] = {0};
  
  const uint16_t scrollLag = 90;
  
  for(uint8_t fontIndex = 0; fontIndex < 52 + 25; fontIndex++){
    getFontImage(fontIndex, fontImage);  
    for(uint8_t columnNumber = 0; columnNumber < 5; columnNumber++){
      slideDisplayLeft(displayImage);                  
      addSliceToDisplay(fontImage, columnNumber, displayImage);      
      renderImage(displayImage, scrollLag);  
    }
    slideDisplayLeft(displayImage);   
    renderImage(displayImage, scrollLag);
  }
  
  // scroll out the last font
  for(uint8_t ii = 0; ii < 8; ii++){
    slideDisplayLeft(displayImage);
    renderImage(displayImage, scrollLag);
  }     
    
}

void scrollRandom(void){
  uint8_t fontImage[8] = {0};
  uint8_t displayImage[8] = {0};
  
  const uint16_t scrollLag = 90;
  
  for(uint8_t fontIndex = 0; fontIndex < 20; fontIndex++){
    // generate random image
    for(uint8_t ii = 0; ii < 8; ii++){
      fontImage[ii] = random() % 256; 
    }
    
    for(uint8_t columnNumber = 0; columnNumber < 5; columnNumber++){
      slideDisplayLeft(displayImage);                  
      addSliceToDisplay(fontImage, columnNumber, displayImage);      
      renderImage(displayImage, scrollLag);  
    }
    slideDisplayLeft(displayImage);   
    renderImage(displayImage, scrollLag);
  }
  
  for(uint8_t ii = 0; ii < 8; ii++){
    slideDisplayLeft(displayImage);
    renderImage(displayImage, scrollLag);
  }    
}

void getFontImage(uint8_t fontIndex, uint8_t * fontImage){
    memset(fontImage, 0, 8);
    // transpose and rotate the font  
    for(uint8_t columnNumber = 0; columnNumber < 5; columnNumber++){
      uint8_t columnBits =  font[fontIndex*5 + columnNumber];
      for(uint8_t rowNumber = 0; rowNumber < 8; rowNumber++){      
        if(columnBits & _BV(rowNumber)){                 // if the row is set in this column
          fontImage[7-rowNumber] |= _BV(7-columnNumber); // set the column in this row of the transposed image
        }
      }
    } 
}

void slideDisplayLeft(uint8_t * displayImage){
  for(uint8_t row = 0; row < 8; row++){
    displayImage[row] <<= 1; 
  }
}

void addSliceToDisplay(uint8_t * fontImage, uint8_t columnNumber, uint8_t * displayImage){
  for(uint8_t row = 0; row < 8; row++){
    if(fontImage[row] & _BV(7 - columnNumber)){ // if a bit is set in the font in this row at the requested column
      displayImage[row] |= 1;               // set the right most column in the image in this row
    }    
  }
}
