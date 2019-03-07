#include <Servo.h> 
// Declare the Servo pin 
int servoPin   = 4; 
int inputLeft  = A0; //blue
int inputMid   = A3; //green
int inputRight = A5; // yellow
int angle = 0;
int tolerance = 100;
double valLeft  = 0;
double valMid   = 0;
double valRight = 0;
double speed = 0;
String spin = "optimized";
int ambient = 0;
int find = 5;

// Create a servo object 
Servo servo; 
void setup() { 
   // We need to attach the servo to the used pin number 
   servo.attach(servoPin);
   Serial.begin(9600);           //  setup serial
   update();
   
 
   ambient = (valLeft + valMid + valRight)/3;
   servo.write(angle);

   
} 

void status() {
  Serial.print(valLeft);
  Serial.print("\t");
  Serial.print(valMid);
  Serial.print("\t");
  Serial.print(valRight);
  Serial.print("\t");
  Serial.print(": Angle: ");
  Serial.print(angle);
  Serial.print("\t");
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(": Rotating ");
  Serial.print(spin);
  Serial.print("\t");
  Serial.print("Ambient: ");
  Serial.print(ambient);
  Serial.print("\n");
//  delay(10);
}

void update() {
  valLeft = analogRead(inputLeft);
  valMid = analogRead(inputMid);
  valRight = analogRead(inputRight);

  
}
void loop(){ 

  

  status();
  update();
  while ((valLeft+valMid+valRight)/3 < ambient+100) {
    status();
    update();
    angle+=find;
    if (angle == 0 || angle == 180) find *=-1;
    servo.write(angle);
  }

  
  while (valLeft >= valMid + tolerance) {
    update(); 
    status();
    speed = (valLeft)/(valMid);
    if (angle+(int)speed < 180) angle+=(int)speed;
    spin = "cw";
    servo.write(angle);

  }
  while (valRight >= valMid + tolerance) {
    update();
    status();
    speed = (valRight/valMid);
    if (angle-(int)speed > 0) angle-= (int)speed;
    spin = "ccw";
    servo.write(angle);
  }

}
