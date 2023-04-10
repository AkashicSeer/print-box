#include <U8g2lib.h>

//U8G2_SSD1309_128X64_NONAME2_1_4W_SW_SPI u8g2(U8G2_R0, D5, D2, D8, D1);
//[page buffer, size = 256 bytes]
U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D1, D2);
void screenSetup() {
  u8g2.begin();
  pinMode(D1, OUTPUT);
}

void sendToScreen(String ipAddress) {
  u8g2.firstPage();
  char char_array[ipAddress.length()];
  ipAddress.toCharArray(char_array, ipAddress.length() + 1);
  do {
    //keep this the same as it pages through the data generating the screen
    u8g2.setFont(u8g2_font_helvB12_tr);
    u8g2.drawStr(0, 20, "Ip Address is");
    u8g2.drawStr(0, 40,  char_array);
    //u8g2.drawStr(0,60,"Last line!");
  } while (u8g2.nextPage());
}

void serialOutput(String lines[]) {
  Serial.print("Line printed \n");
  Serial.println(lines[0]);
  Serial.println(lines[1]);
}
