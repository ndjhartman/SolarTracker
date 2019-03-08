#include <Servo.h> 
int servoPin   = 4; 
int inputLeft  = A5; //blue
int inputMid   = A3; //green
int inputRight = A0; // yellow
int angle = 55;
int tolerance = 25;
double valLeft  = 0;
double valMid   = 0;
double valRight = 0;
double speed = 0;
String spin = "optimized";
int ambient = 0;
int find = 4;

Servo servo; // Create a servo object 


void setup() { 
   servo.attach(servoPin);
   Serial.begin(9600);            //  setup serial
   log();                         //  updateDiodes sensors   
 
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

void updateDiodes() { //Reads diodes
  valLeft = analogRead(inputLeft);
  valMid = analogRead(inputMid);
  valRight = analogRead(inputRight);
}

void loop(){ 
  
  log();
  updateDiodes();

//  if (valLeft < ambient + 25 && valMid < ambient +25 && valRight < ambient + 25) {
//    if (spin == "cw" && find < 0)
//      find*=-1;
//    if (spin == "ccw" && find > 0)
//      find*=-1;   
//  }
//    
  while (valLeft < ambient + 25 && valMid < ambient +25 && valRight < ambient + 25) { //Initial search for source
    log();
    updateDiodes();
//
//    
//    if ((angle += find >= 0) && (angle += find <= 90)) angle+=find;
    angle+= find;
    if (angle <= 0 || angle >= 110) find *=-1;
    servo.write(angle);
  }

  
  while (valLeft-valMid > valRight-valMid ) { //Rotate cw
    log();
    updateDiodes(); 
    spin = "searching";
    speed = ((valLeft)/(valMid+1)/4)+2;
    if (angle-(int)speed > 0) angle-=(int)speed;
    spin = "ccw";
    servo.write(angle);

  }
  while (valRight-valMid > valLeft-valMid + tolerance) { //Rotate ccw
    log();
    updateDiodes();
    speed = ((valRight/valMid+1)/4)+2;
    if (angle+(int)speed < 220) angle+= (int)speed;
    spin = "cw";
    servo.write(angle);
  }

}
