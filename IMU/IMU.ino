#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

////////////////////////////
// เรียกใช้ library LSM9DS1 //
///////////////////////////
// สร้าง ออบเจ็ก ชื่อ imu จาก library LSM9DS1
// ตั้งชื่อว่าอะไรก็ได้ ไม่จำเป็นต้อง imu
LSM9DS1 imu;

///////////////////////
// Example I2C Setup //
///////////////////////
#define LSM9DS1_M	0x1C
#define LSM9DS1_AG	0x6A

///////////////////////////////
// ตั้งค่าการแสดงผลข้อมูลจาก imu //
//////////////////////////////
#define PRINT_CALCULATED
#define PRINT_SPEED 250 // เขียนข้อมูลทุกๆ 250 ms.

// ค่า DECLINATION เป็นค่าสนามแม่เหล็กโลกแตกต่างกันตามสถานที่
// การใช้ค่าที่ตรงสถานที่จะให้ความแม่นยำมากกว่า
// ดูค่าได้ที่
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

void setup() 
{
  
  Serial.begin(115200);
  
  // ก่อนจะเริ่มใช้งาน IMU เราจะมาตั้งค่าอะไรกัน
  // ตั้งโหมดการเชื่อมต่อ และที่อยู่การเชื่อมต่อ
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // ข้อมูลด้านบนจะถูกเรียกใช้ก็ต่อเมื่อมีคำสั่ง imu.begin()
  // ถ้าพร้อมแล้ว เราจะเริ่ม IMU เลย!!
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1)
      ;
  }
}

void loop()
{
  printGyro();  // Print "G: gx, gy, gz" แสดงข้อมูลจาก Gyro
  printAccel(); // Print "A: ax, ay, az" แสดงข้อมูลจาก Accelero Meter
  printMag();   // Print "M: mx, my, mz" แสดงข้อมูลจาก Magnetometer
  
  // แสดงการหันทิศทาง
  printAttitude(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);
  Serial.println();
  
  delay(PRINT_SPEED); //หน่วงเวลาตามที่กำหนดไว้
}

void printGyro()
{
  // เวลาเราจะอ่านข้อมูลจาก Gyro เนี่ย เราจะต้องใช้คำสั่ง readGyro()
  imu.readGyro();
  
  // ข้อมูลจาก Gyro จะอยู่ในตัวแปร gx, gy, และ gz 
  // สามารถแสดงผลข้อมูลได้สองแบบ คือแบบข้อมูลดิบ(ADC) หรือบแบบที่คำนวณแล้ว(DPS)
  Serial.print("G: ");
#ifdef PRINT_CALCULATED
  // ถ้ากำหนดไว้ว่าให้แสดงผลแบบคำนวณแล้ว จะใช้คำสั่ง calcGyro
  // ในการช่วยคำนวณค่า
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
#endif
}

void printAccel()
{
  // เวลาเราจะอ่านข้อมูลจาก Accelero Meter เนี่ย เราจะต้องใช้คำสั่ง readAccel()
  imu.readAccel();

  // ข้อมูลจาก Accelero Meter จะอยู่ในตัวแปร ax, ay, และ az
  // สามารถแสดงผลข้อมูลได้สองแบบ คือแบบข้อมูลดิบ(ADC) หรือบแบบที่คำนวณแล้ว(g's)
  Serial.print("A: ");
#ifdef PRINT_CALCULATED
  // ถ้ากำหนดไว้ว่าให้แสดงผลแบบคำนวณแล้ว จะใช้คำสั่ง calcAccel
  // ในการช่วยคำนวณค่า
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
#elif defined PRINT_RAW 
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
#endif

}

void printMag()
{
  // เวลาเราจะอ่านข้อมูลจาก Magnetometer เนี่ย เราจะต้องใช้คำสั่ง readMag()
  imu.readMag();

  // ข้อมูลจะถูกเก็บในตัวแปร mx, my, และ mz
  // สามารถแสดงผลข้อมูลได้สองแบบ คือแบบข้อมูลดิบ(ADC) หรือบแบบที่คำนวณแล้ว(gauss)
  Serial.print("M: ");
#ifdef PRINT_CALCULATED
  // ถ้ากำหนดไว้ว่าให้แสดงผลแบบคำนวณแล้ว จะใช้คำสั่ง calcMag
  // ในการช่วยคำนวณค่า
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}

// คำนวณทิศทางการหันหัว หันข้าง
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(
float ax, float ay, float az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  
  float heading;
  if (my == 0)
    heading = (mx < 0) ? 180.0 : 0;
  else
    heading = atan2(mx, my);
    
  heading -= DECLINATION * PI / 180;
  
  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
  else if (heading < 0) heading += 2 * PI;
  
  // เปลี่ยนหน่วย จาก radius เป็น degree
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
  
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);
}