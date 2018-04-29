int sensorPin = 34; // ขาที่ต่อเซ็นเซอร์ อาจจะเป็น 35 36 หรือ 39 ก็ได้
int heart = 0;

void setup() {
   Serial.begin(9600);
}

void loop() {
    heart = analogRead(sensorPin);
    Serial.println(heart);

    delay(50); 
    // ระยะเวลาในหน่วย millisecond หรือ 1/1000 ของ 1 วินาที เป็นระยะห่างของการแสดงผลแต่ละครั้ง
}