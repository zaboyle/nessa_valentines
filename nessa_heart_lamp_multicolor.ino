// grid display. rows are connected to gate on transistors
const int rows[5]   = { 0, 4, 8, 13, 12 };
const int cols[5]   = { 6, 2, 3, 5, 1 };
// color channels to lights
const int R_PIN_OUT = 9;
const int G_PIN_OUT = 10;
const int B_PIN_OUT = 11;
// color channels from potentiometers
const int R_PIN_IN = A0;
const int G_PIN_IN = A1;
const int B_PIN_IN = A2;
// color values
int r_val = 0;
int g_val = 0;
int b_val = 0;

// mode of operation. changes on button press
enum mode_t {
  pulse,
  normal,
  message
};
mode_t mode = normal;

// buttons to change mode
const int PULSE_PIN   = A3;
const int NORMAL_PIN  = A4;
const int MESSAGE_PIN = A5;

void setup()
{
  // grid
  for (int i = 0; i < 5; ++i)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }

  // color channels
  pinMode(R_PIN_IN, INPUT);
  pinMode(G_PIN_IN, INPUT);
  pinMode(B_PIN_IN, INPUT);
  pinMode(R_PIN_OUT, OUTPUT);
  pinMode(G_PIN_OUT, OUTPUT);
  pinMode(B_PIN_OUT, OUTPUT);

  // modes
  pinMode(PULSE_PIN, INPUT);
  pinMode(NORMAL_PIN, INPUT);
  pinMode(MESSAGE_PIN, INPUT);
}

void loop()
{
  readSensors();
  refreshLEDs();
}

void readSensors()
{
  // read potentiometers to update color
  r_val = map(analogRead(R_PIN_IN), 0, 1023, 0, 255);
  g_val = map(analogRead(G_PIN_IN), 0, 1023, 0, 255);
  b_val = map(analogRead(B_PIN_IN), 0, 1023, 0, 255);

  // read buttons to update mode
  if (digitalRead(PULSE_PIN)) { mode = pulse; }
  else if (digitalRead(NORMAL_PIN)) { mode = normal; }
  else if (digitalRead(MESSAGE_PIN)) { mode = message; }
}

void refreshLEDs()
{
  // change color
  analogWrite(R_PIN_OUT, r_val);
  analogWrite(G_PIN_OUT, g_val);
  analogWrite(B_PIN_OUT, b_val);

  // change mode
  if (mode == pulse) { pulseLEDs(); }
  else if (mode == normal) { normalLEDs(); }
  else if (mode == message) { messageLEDs(); }

}

void pulseLEDs()
{
  // pulse from origin (LED #12)
  int ring1[1] = {12};
  lightLEDs(ring1, 1);
  delay(250);

  int ring2[8] = {6, 7, 8, 11, 13, 16, 17, 18};
  lightLEDs(ring2, 8);
  delay(250);

  int ring3[16] = {0, 1, 2, 3, 4, 5, 9, 10, 14, 15, 19, 20, 21, 22, 23, 24};
  lightLEDs(ring3, 16);
  delay(250);
}

void normalLEDs()
{
  // turn on all lights
  for (int r = 0; r < 5; r++)
  {
    digitalWrite(rows[r], HIGH);
  }

  for (int c = 0; c < 5; c++)
  {
    digitalWrite(cols[c], LOW);
  }
}

void messageLEDs()
{
  // '~' = smiley face
  String msg = "I LOVE YOU~";
  for (int i = 0; i < msg.length(); ++i)
  {
    writeLetter(msg[i]);
    delay(500);
  }
  delay(1000);
}

// made for 5x5 grid numbered as
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
void writeLetter(char letter)
{
  switch(letter)
  {
    case 'I':
      int i_lights[7] = {1, 2, 3, 7, 12, 17, 22};
      lightLEDs(i_lights, 7);
      break;
    case 'L':
      int l_lights[7] = {1, 6, 11, 16, 21, 22, 23};
      lightLEDs(l_lights, 7);
      break;
    case 'O':
      int o_lights[12] = {1, 2, 3, 6, 8, 11, 13, 16, 18, 21, 22, 23};
      lightLEDs(o_lights, 12);
      break;
    case 'V':
      int v_lights[7] = {0, 4, 5, 9, 16, 18, 22};
      lightLEDs(v_lights, 7);
      break;
    case 'E':
      int e_lights[11] = {1, 2, 3, 6, 11, 12, 13, 16, 21, 22, 23};
      lightLEDs(e_lights, 11);
      break;
    case 'Y':
      int y_lights[7] = {0, 4, 6, 8, 12, 17, 22};
      lightLEDs(y_lights, 7);
      break;
    case 'U':
      int u_lights[11] = {1, 3, 6, 8, 11, 13, 16, 18, 21, 22, 23};
      lightLEDs(u_lights, 11);
      break;
    case ' ':
      int lights[0] = {};
      lightLEDs(lights, 0);
      break;
    case '~':
      int smile_lights[7] = {6, 8, 15, 19, 21, 22, 23};
      lightLEDs(smile_lights, 7);
    default:
      break;
  }
}

// made for 5x5 grid numbered as
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
void lightLEDs(int nums[], int len)
{
  // light each individual LED in list
  for(int start = millis(); millis() < start + 2000;)
  {
  
    for (int i = 0; i < len; i++)
    {
      int row = nums[i] / 5;
      int col = nums[i] % 5;
  
      digitalWrite(rows[row], HIGH);
      for (int j = 0; j < 5; j++)
      {
        // LOW for col we want, HIGH otherwise
        digitalWrite(cols[j], j != col);
      }
      delay(5);
      digitalWrite(rows[row], LOW);
    }
  }
}
