//単発　三点
int val=0;
void setup() {
  pinMode(A4,INPUT);　//セレクタ１　単発
  pinMode(A5,INPUT);　//セレクタ２　３点
  pinMode(A3,OUTPUT);　//出力
  Serial.begin(9600);  //シリアルモニタ
}

void loop(){
    val=digitalRead(A4);
    Serial.println(val);
    if(digitalRead(A4)==HIGH)　//単発
    {
      for(int i=0;i<3;i++)
      {
       digitalWrite(A3,HIGH);
       delay(50);
       digitalWrite(A3,LOW);
       delay(500);　　　//分かりやすくするため、無くもいい
      }
    }
    else if(digitalRead(A5)==HIGH) //三点
    {
       digitalWrite(A3,HIGH);
       delay(20);
       digitalWrite(A3,LOW);
     }
    else　　　　　　　　　　　　　　　//セーフティ
    {
        digitalWrite(A3,LOW);
    }
}
