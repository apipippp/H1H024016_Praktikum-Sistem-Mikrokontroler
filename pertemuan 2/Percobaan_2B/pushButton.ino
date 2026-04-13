
// 7-Segment Common Anode
// Pin mapping segment: a b c d e f g dp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

const int btnNext = 3;
int currentDigit = 0;
bool lastBtnState = HIGH;

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, //0
  {0,1,1,0,0,0,0,0}, //1
  {1,1,0,1,1,0,1,0}, //2
  {1,1,1,1,0,0,1,0}, //3 
  {0,1,1,0,0,1,1,0}, //4
  {1,0,1,1,0,1,1,0}, //5
  {1,0,1,1,1,1,1,0}, //6
  {1,1,1,0,0,0,0,0}, //7
  {1,1,1,1,1,1,1,0}, //8
  {1,1,1,1,0,1,1,0}, //9
  {1,1,1,0,1,1,1,0}, //A
  {0,0,1,1,1,1,1,0}, //b
  {1,0,0,1,1,1,0,0}, //C
  {0,1,1,1,1,0,1,0}, //d
  {1,0,0,1,1,1,1,0}, //E
  {1,0,0,0,1,1,1,0}  //F
};

// Fungsi tampil digit (dibalik untuk CA)
void displayDigit(int num)
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup()
{
  for(int i = 0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnNext, INPUT_PULLUP);

  displayDigit(currentDigit);
}

void loop()
{
  bool btnState = digitalRead(btnNext);

  // deteksi tombol ditekan
  if(lastBtnState == HIGH && btnState == LOW)
  {
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0;

    displayDigit(currentDigit);
    delay(200); // debounce sederhana
  }

  lastBtnState = btnState;
}