#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

void setup()
{
  DDRB = 255; // Set all pins on PORTB to output
  DDRD = 255; // Set all pins on PORTD to output
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  // Serial.begin(115200);
}

void writey(uint8_t coord)
{
  PORTD = coord;
}

void writex(uint8_t coord)
{
  // Step 1: Convert to binary
  String binary = String(coord, BIN);

  // Step 2: Pad with zeros if necessary
  int bitAsInt[8]; // Declare the variable bitAsInt

  while (binary.length() < 8)
  {
    binary = "0" + binary;
  }

  // Step 3: Split into 8 numbers
  for (int i = 0; i < 8; ++i)
  {
    char bit = binary.charAt(i);
    // Convert char to int and do something with it
    bitAsInt[i] = bit - '0';                     // Assign the value to bitAsInt array
    bitAsInt[i] = bitAsInt[i] == 1 ? HIGH : LOW; // Convert 1 to HIGH and 0 to LOW
  }
  Serial.println();
  digitalWrite(8, bitAsInt[0]);
  digitalWrite(9, bitAsInt[1]);
  digitalWrite(10, bitAsInt[2]);
  digitalWrite(11, bitAsInt[3]);
  digitalWrite(12, bitAsInt[4]);
  digitalWrite(13, bitAsInt[5]);
  digitalWrite(A2, bitAsInt[6]);
  digitalWrite(A3, bitAsInt[7]);
}

unsigned char sinTab[] = {128, 130, 132, 134, 136, 139, 141, 143, 145, 148, 150, 152, 154, 156, 158, 161, 163, 165, 167, 169, 171, 173, 175, 178, 180, 182, 184, 186, 188, 190, 192, 193, 195, 197, 199, 201, 203, 205, 206, 208, 210, 211, 213, 215, 216, 218, 220, 221, 223, 224, 226, 227, 228, 230, 231, 232, 234, 235, 236, 237, 238, 239, 241, 242, 243, 244, 244, 245, 246, 247, 248, 249, 249, 250, 251, 251, 252, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 256, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 252, 251, 251, 250, 249, 249, 248, 247, 246, 245, 244, 244, 243, 242, 241, 239, 238, 237, 236, 235, 234, 232, 231, 230, 228, 227, 226, 224, 223, 221, 220, 218, 216, 215, 213, 211, 210, 208, 206, 205, 203, 201, 199, 197, 195, 193, 192, 190, 188, 186, 184, 182, 180, 178, 175, 173, 171, 169, 167, 165, 163, 161, 158, 156, 154, 152, 150, 148, 145, 143, 141, 139, 136, 134, 132, 130, 128, 125, 123, 121, 119, 116, 114, 112, 110, 107, 105, 103, 101, 99, 97, 94, 92, 90, 88, 86, 84, 82, 80, 77, 75, 73, 71, 69, 67, 65, 63, 62, 60, 58, 56, 54, 52, 50, 49, 47, 45, 44, 42, 40, 39, 37, 35, 34, 32, 31, 29, 28, 27, 25, 24, 23, 21, 20, 19, 18, 17, 16, 14, 13, 12, 11, 11, 10, 9, 8, 7, 6, 6, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 23, 24, 25, 27, 28, 29, 31, 32, 34, 35, 37, 39, 40, 42, 44, 45, 47, 49, 50, 52, 54, 56, 58, 60, 62, 63, 65, 67, 69, 71, 73, 75, 77, 80, 82, 84, 86, 88, 90, 92, 94, 97, 99, 101, 103, 105, 107, 110, 112, 114, 116, 119, 121, 123, 125};
unsigned char cosTab[] = {256, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 252, 251, 251, 250, 249, 249, 248, 247, 246, 245, 244, 244, 243, 242, 241, 239, 238, 237, 236, 235, 234, 232, 231, 230, 228, 227, 226, 224, 223, 221, 220, 218, 216, 215, 213, 211, 210, 208, 206, 205, 203, 201, 199, 197, 195, 193, 192, 190, 188, 186, 184, 182, 180, 178, 175, 173, 171, 169, 167, 165, 163, 161, 158, 156, 154, 152, 150, 148, 145, 143, 141, 139, 136, 134, 132, 130, 128, 125, 123, 121, 119, 116, 114, 112, 110, 107, 105, 103, 101, 99, 97, 94, 92, 90, 88, 86, 84, 82, 80, 77, 75, 73, 71, 69, 67, 65, 64, 62, 60, 58, 56, 54, 52, 50, 49, 47, 45, 44, 42, 40, 39, 37, 35, 34, 32, 31, 29, 28, 27, 25, 24, 23, 21, 20, 19, 18, 17, 16, 14, 13, 12, 11, 11, 10, 9, 8, 7, 6, 6, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 23, 24, 25, 27, 28, 29, 31, 32, 34, 35, 37, 39, 40, 42, 44, 45, 47, 49, 50, 52, 54, 56, 58, 60, 62, 63, 65, 67, 69, 71, 73, 75, 77, 80, 82, 84, 86, 88, 90, 92, 94, 97, 99, 101, 103, 105, 107, 110, 112, 114, 116, 119, 121, 123, 125, 127, 130, 132, 134, 136, 139, 141, 143, 145, 148, 150, 152, 154, 156, 158, 161, 163, 165, 167, 169, 171, 173, 175, 178, 180, 182, 184, 186, 188, 190, 192, 193, 195, 197, 199, 201, 203, 205, 206, 208, 210, 211, 213, 215, 216, 218, 220, 221, 223, 224, 226, 227, 228, 230, 231, 232, 234, 235, 236, 237, 238, 239, 241, 242, 243, 244, 244, 245, 246, 247, 248, 249, 249, 250, 251, 251, 252, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255};

unsigned char i = 0;
int b = 0;

unsigned char r = 128;

void loop()
{
  // writey(sinTab[i++]);
  // writex(cosTab[i++]);

  // 畫出拋物線
  for (int x = 0; x < SCREEN_WIDTH; x++)
  {
    // 使用拋物線公式計算 y 值
    int y = 0.01 * pow(x - SCREEN_WIDTH / 2, 2) + 10;
    // 確保 y 值在顯示器的範圍內
    y = constrain(y, 0, SCREEN_HEIGHT - 1);
    // 在顯示器上畫點
    writex(x);
    writey(SCREEN_HEIGHT - y);
    // display.drawPixel(x, SCREEN_HEIGHT - y, WHITE);
  }

  // writex(0);
  // writey(0);
  // writex(127);
  // writey(0);
  // writex(255);
  // writey(0);
  // writex(0);
  // writey(127);
  // writex(127);
  // writey(127);
  // writex(255);
  // writey(127);
  // writex(0);
  // writey(255);
  // writex(127);
  // writey(255);
  // writex(255);
  // writey(255);
}
