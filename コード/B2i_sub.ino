//単発　三点
int val=0;
void setup() {
  pinMode(A4,INPUT); //3点
  pinMode(A5,INPUT);//単発
  pinMode(A3,OUTPUT);
  Serial.begin(9600);  
  }

void loop(){
    val=digitalRead(A3);
    Serial.println(val);
    if(digitalRead(A4)==HIGH){//3点バースト
      for(int i=0;i<3;i++)
      {
       digitalWrite(A3,HIGH);
       delay(50);
       digitalWrite(A3,LOW);
       delay(50);
       }
    }
    else if(digitalRead(A5)==HIGH)//単発
    {
       digitalWrite(A3,HIGH);
       delay(50);
       digitalWrite(A3,LOW);
     }
    

    else{//セーフティ
      digitalWrite(A3,LOW);
    }
    
}
