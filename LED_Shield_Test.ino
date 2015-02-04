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
