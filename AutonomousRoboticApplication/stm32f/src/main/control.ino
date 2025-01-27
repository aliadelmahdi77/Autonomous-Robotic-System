#include <Wire.h>

#define I2C_ADDR        0x34

#define GET_LOW_BYTE(A) (uint8_t)((A))
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))

#define ADC_BAT_ADDR                  0
#define MOTOR_TYPE_ADDR               20 
#define MOTOR_ENCODER_POLARITY_ADDR   21 
#define MOTOR_FIXED_PWM_ADDR      31
//#define SERVOS_ADDR_CMD 40        
#define MOTOR_FIXED_SPEED_ADDR    51 
#define MOTOR_HIGH_SPEED    100 

#define MOTOR_ENCODER_TOTAL_ADDR  60 


#define MOTOR_TYPE_WITHOUT_ENCODER        0
#define MOTOR_TYPE_TT                     1
#define MOTOR_TYPE_N20                    2
#define MOTOR_TYPE_JGB37_520_12V_110RPM   3 
#define JOYSTICK_X A0  // Joystick X-axis connected to analog pin A0
#define JOYSTICK_Y A1  // Joystick Y-axis connected to analog pin A1
#define servopin PA2 
#define potpin PA3

int threshold = 50; // Dead zone threshold for joystick

int pulsewidth;  
void servo(int myangle)
{
  pulsewidth=map(myangle,0,180,500,2500);  
  digitalWrite(servopin,HIGH); 
  delayMicroseconds(pulsewidth);  
  digitalWrite(servopin,LOW);   
  delay(20-pulsewidth/1000);    
}

// u8 data[20];
bool WireWriteByte(uint8_t val)  
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }
    return true;
}
bool WireWriteDataArray(  uint8_t reg,uint8_t *val,unsigned int len) 
{
    unsigned int i;

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(reg);  
    for(i = 0; i < len; i++) {
        Wire.write(val[i]);  
    }
    if( Wire.endTransmission() != 0 ) {   
        return false;
    }

    return true;
}
uint8_t MotorType = MOTOR_TYPE_JGB37_520_12V_110RPM;  
uint8_t MotorEncoderPolarity = 0;     
int8_t car_back[4]={-30,0,30,0};   
int8_t car_forward[4]={30,0,-30,0};  


int8_t car_stop[4]={0,0,0,0};
bool flag;
void setup()
{
  Wire.begin();
  pinMode(servopin,OUTPUT);
  delay(200);
  WireWriteDataArray(MOTOR_TYPE_ADDR,&MotorType,1);
  delay(5);
  WireWriteDataArray(MOTOR_ENCODER_POLARITY_ADDR,&MotorEncoderPolarity,1);
  servo(90);
 pinMode(PC13, OUTPUT);
 digitalWrite(PC13, HIGH);
  delay(1000); // Wait for 1 second
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

 
}
  int joystickX ;
  int joystickY;
  int centeredX ;
  int centeredY ;
  int pot_raw;
    int pwmValue;
void loop()
{
   joystickX = analogRead(JOYSTICK_X); // Read joystick X-axis value
   joystickY = analogRead(JOYSTICK_Y); // Read joystick Y-axis value
   pot_raw = analogRead(potpin);
   // Step 2: Map the value to a PWM range (-100 to 100 or 0 to 255)
    pwmValue = map(pot_raw, 0, 1023, 0, 50);
   centeredX = joystickX - 512; // Center joystick around 0 (-512 to 512)
   centeredY = joystickY - 512; // Center joystick around 0 (-512 to 512)
  // Forward and backward control based on Y-axis
  // Apply dead zone for Y-axis
   if (abs(centeredY) <= threshold) {
       centeredY = 0; // Ignore small deviations
   }

   // Forward and backward control based on Y-axis
   if (centeredY > 400) {
      if (pwmValue > 0) {
        // Forward motion (positive speed)
        car_forward[0] = pwmValue;
        car_forward[1] = 0;
        car_forward[2] = -pwmValue;
        car_forward[3] = 0;
    } 
       WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR, (uint8_t*)car_forward, 4);
        digitalWrite(PC13, LOW);
   } 
   else if (centeredY < 0) {
          if (pwmValue > 0) {
        car_back[0] = -pwmValue;
        car_back[1] = 0;
        car_back[2] = pwmValue;
        car_back[3] = 0;
    } 

       WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR, (uint8_t*)car_back, 4);
        digitalWrite(PC13, HIGH);

   } 
   else {
       WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR, (uint8_t*)car_stop, 4);
         digitalWrite(PC13, HIGH);
   }

   if (centeredX > 400) {
       servo(150);
   } 
   else if (centeredX < 0) {
       servo(40);

   } 
   else {
       servo(90); 

   }

   delay(10);
}
