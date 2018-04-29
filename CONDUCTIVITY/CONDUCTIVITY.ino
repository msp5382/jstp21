int sensorPin = 12; // ขาที่ต่อเซ็นเซอร์ อาจจะเป็น 14 26 หรือ 27 ก็ได้
int conductive = 0;

void setup() {
   Serial.begin(9600);
}

void loop() {
    conductive = analogRead(sensorPin);
    Serial.println(conductive);

    delay(50); 
    // ระยะเวลาในหน่วย millisecond หรือ 1/1000 ของ 1 วินาที เป็นระยะห่างของการแสดงผลแต่ละครั้ง
}