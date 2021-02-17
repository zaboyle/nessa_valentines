// grid display
const int rows[5]  = { 11, 10, 9, 8, 7 };
const int cols[5]  = { 2, 6, 4, 5, 3 };

// mode of operation. changes on button press
enum mode_t {
  pulse,
  normal,
  message
};
mode_t mode = pulse;

// buttons to change mode
const int PULSE_PIN   = A0;
const int NORMAL_PIN  = A2;
const int MESSAGE_PIN = A4;

void setup()
{
  // grid
  for (int i = 0; i < 5; ++i)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }

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
  // read buttons to update mode
  if (digitalRead(PULSE_PIN)) { mode = pulse; }
  else if (digitalRead(NORMAL_PIN)) { mode = normal; }
  else if (digitalRead(MESSAGE_PIN)) { mode = message; }
}

void refreshLEDs()
{
  if (mode == pulse) { pulseLEDs(); }
  else if (mode == normal) { normalLEDs(); }
  else if (mode == message) { messageLEDs(); }

}

void pulseLEDs()
{
  // pulse from origin (LED #12)
  int ring1[1] = {12};
  lightLEDs(ring1, 1);
  delay(100);

  int ring2[8] = {6, 7, 8, 11, 13, 16, 17, 18};
  lightLEDs(ring2, 8);
  delay(100);

  int ring3[16] = {0, 1, 2, 3, 4, 5, 9, 10, 14, 15, 19, 20, 21, 22, 23, 24};
  lightLEDs(ring3, 16);
  delay(100);
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
  for (int i = 0; i < msg.length(); i++)
  {
    writeLetter(msg[i]);
    delay(250);
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

  // repeat to display letter for 1 sec
  for(int i = millis(); millis() - i < 1000;)
  {

    // light each individual LED in list
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
      delay(1);
      digitalWrite(rows[row], LOW);
      for (int j = 0; j < 5; j++)
      {
        // reset all cols
        digitalWrite(cols[j], HIGH);
      }
    }
  }
}

// made for 5x5 grid numbered as
// 0  1  2  3  4
// 5  6  7  8  9
// 10 11 12 13 14
// 15 16 17 18 19
// 20 21 22 23 24
void writeLetter(char letter)
{
    if (letter == 'I') {
      int i_lights[9] = {1, 2, 3, 7, 12, 17, 21, 22, 23};
      lightLEDs(i_lights, 9);
    }
    else if (letter == 'L') {
      int l_lights[7] = {1, 6, 11, 16, 21, 22, 23};
      lightLEDs(l_lights, 7);
    }
    else if (letter == 'O') {
      int o_lights[12] = {1, 2, 3, 6, 8, 11, 13, 16, 18, 21, 22, 23};
      lightLEDs(o_lights, 12);
    }
    else if (letter == 'V') {
      int v_lights[9] = {0, 4, 5, 9, 10, 14, 16, 18, 22};
      lightLEDs(v_lights, 9);
    }
    else if (letter == 'E') {
      int e_lights[11] = {1, 2, 3, 6, 11, 12, 13, 16, 21, 22, 23};
      lightLEDs(e_lights, 11);
    }
    else if (letter == 'Y') {
      int y_lights[7] = {0, 4, 6, 8, 12, 17, 22};
      lightLEDs(y_lights, 7);
    }
    else if (letter == 'U') {
      int u_lights[11] = {1, 3, 6, 8, 11, 13, 16, 18, 21, 22, 23};
      lightLEDs(u_lights, 11);
    }
    else if (letter == ' ') {
      int lights[0] = {};
      lightLEDs(lights, 0);
    }
    else if (letter == '~') {
      int smile_lights[7] = {6, 8, 15, 19, 21, 22, 23};
      lightLEDs(smile_lights, 7);
    }
}
