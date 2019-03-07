#include <Servo.h> 
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

Servo servo; // Create a servo object 


void setup() { 
   servo.attach(servoPin);
   Serial.begin(9600);            //  setup serial
   log();                         //  updates sensors   
 
   ambient = (valLeft + valMid + valRight)/3; //Reads ambient light level
   servo.write(angle);                        //Sets motor to default angle

   
} 

void log() {  //Logs info
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
}

void update() { //Reads diodes
  valLeft = analogRead(inputLeft);
  valMid = analogRead(inputMid);
  valRight = analogRead(inputRight);

  
}

void loop(){ 
  
  log();
  update();
  
  while ((valLeft+valMid+valRight)/3 < ambient+100) { //Initial search for source
    log();
    update();
    angle+=find;
    if (angle == 0 || angle == 180) find *=-1;
    servo.write(angle);
  }

  
  while (valLeft >= valMid + tolerance) { //Rotate cw
    log();
    update(); 
    speed = (valLeft)/(valMid);
    if (angle+(int)speed < 180) angle+=(int)speed;
    spin = "cw";
    servo.write(angle);

  }
  while (valRight >= valMid + tolerance) { //Rotate ccw
    log();
    update();
    speed = (valRight/valMid);
    if (angle-(int)speed > 0) angle-= (int)speed;
    spin = "ccw";
    servo.write(angle);
  }

}
