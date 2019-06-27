
int pin = 30; // 17 = rx, 30=tx led

enum { // l293 pin-match
   E12 = 5,  I1 = 7,  I2 = 6, // left
   E34=9,   I4=4,   I3=8 // right
  };

 #include <IRremote.h>

int RECV_PIN = 16;

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup() {
  pinMode(pin,OUTPUT);
  pinMode(E12,OUTPUT); pinMode(I1,OUTPUT);pinMode(I2,OUTPUT);
  pinMode(E34,OUTPUT); pinMode(I3,OUTPUT);pinMode(I4,OUTPUT);
    irrecv.enableIRIn(); // Start the receiver
}

void motor(int l, int r) {
if (l==0) digitalWrite(E12,LOW); else {
   digitalWrite(I1,l>0); digitalWrite(I2,l<0);
   digitalWrite(E12,HIGH);
   }
 if (r==0) digitalWrite(E34,LOW); else {
   digitalWrite(I3,r>0); digitalWrite(I4,r<0);
   digitalWrite(E34,HIGH);
   }
  
}




void loop() {
 if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
case 0xFFA05F:  // up
    motor(1,1);
    break;
case 0xFF7887 : // left
    motor(1,-1);
    break;
case 0xFF50AF : // right
    motor(-1,1);
    break;
case 0xFF40BF: // down
    motor(-1,-1);
    break;
case 0xFF02FD :// stop
    motor(0,0);
    break;
    }
    irrecv.resume(); // Receive the next value
}
  delay(100);
//  motor(0,0);
 //motor(0,1);
 //digitalWrite(pin,HIGH);
// delay(1000);
// digitalWrite(pin,LOW);
 //motor(0,-1);
// delay(1000);
}
