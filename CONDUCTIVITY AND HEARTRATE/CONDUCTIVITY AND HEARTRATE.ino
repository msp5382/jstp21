int ConductiveSensorPin = 12; // ขาที่ต่อเซ็นเซอร์วัดความชื้น อาจจะเป็น 14 26 หรือ 27 ก็ได้
int HeartRateSensorPin = 34; // ขาที่ต่อเซ็นเซอร์ อาจจะเป็น 35 36 หรือ 39 ก็ได้

int conductive = 0;
int heart = 0;

void setup() {
   Serial.begin(9600);
}

void loop() {
    conductive = analogRead(ConductiveSensorPin);
    heart = analogRead(HeartRateSensorPin);
    Serial.print("ค่าความชื้น : ");
    Serial.println(conductive);
    Serial.print("อัตราการเต้นของหัวใจ : ");
    Serial.prontln(heart);
    Serial.println();
    
    delay(50); 
    // ระยะเวลาในหน่วย millisecond หรือ 1/1000 ของ 1 วินาที เป็นระยะห่างของการแสดงผลแต่ละครั้ง
}