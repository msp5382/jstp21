#include <thermistor.h>
#include <HardwareSerial.h>

int thermistorPin = A0; // ขาที่ต่อเซ็นเซอร์ อาจจะเป็น A2 A4 หรือ A15 ก็ได้ 

THERMISTOR thermistor(thermistorPin,        
                      10000,          // ความต้านทานของ thermistor ที่ 25องศา
                      3950,           // ค่า beta coefficient ของ thermistor
                      10000);         // ค่าของตัวต้านทานที่ต่ออยู่ด้วย

uint16_t temp;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  temp = thermistor.read();
  Serial.print("Temp in ºC : ");
  Serial.println(temp);

  delay(50); 
  // ระยะเวลาในหน่วย millisecond หรือ 1/1000 ของ 1 วินาที เป็นระยะห่างของการแสดงผลแต่ละครั้ง

}
