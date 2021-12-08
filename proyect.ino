#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int timer1;                                                                         //variable para captar el tiempo de los sensores IR
int timer2;                                                                         //variable para captar el tiempo de los sensores IR

float Time;                                                                         //variable Tiempo de registro resultante

int flag1 = 0;                                                                      //variable interruptor de los sensores
int flag2 = 0;                                                                      //variable interruptor de los sensores

float distance = 5.0;                                                               //distacia a la que se colocara los sensores
float speed;                                                                        //variable para manejo de la velocidad

int ir_s1 = A0;                                                                     //sensor IR conectado a arduino
int ir_s2 = A1;                                                                     //sensor IR conectado a arduino 

int buzzer = 13;                                                                    //Conexion del puerto arduino al Buzzer

void setup(){
  pinMode(ir_s1, INPUT);                                                            //periferico de entrada
  pinMode(ir_s2, INPUT);                                                            //periferico de entrada 
  pinMode(buzzer, OUTPUT);                                                          //periferico de salida
  
  lcd.begin(16,2);                                                                  //Display lcd
  lcd.clear();                                                                      //Limpiar pantalla
  lcd.setCursor(0,0);                                                               //Iniciar cursor para la escritura
  lcd.print("     Bienvenido   ");                                                  //Mensaje para la pantalla en fila 1
  lcd.setCursor(0,1);
  lcd.print("Iniciando...         ");                                              //Mensaje para la pantalla en fila 2
  delay(2000);                                                                      //con 2 seg de tiempo para Mensaje
  lcd.clear();                                                                      //Limpiar pantalla
}

void loop() {
  if(digitalRead (ir_s1) == LOW && flag1==0)                                        //si sensor IR 1 detecta una variacion de voltaje 
  {
    timer1 = millis();                                                              //tomar el tiempo que se dio
    flag1=1;                                                                        //mandar 1 como resivido
  }

  if(digitalRead (ir_s2) == LOW && flag2==0)                                        //si sensor IR 2 detecta una variacion de voltaje 
  {
    timer2 = millis();                                                              //tomar el tiempo que se dio
    flag2=1;                                                                        //mandar 1 como resivido
  }

  if (flag1==1 && flag2==1)                                                         //condicionante detector de sensor IR
  {                                                                                 //si variable tiene valor 1 a detectado movimiento
    if(timer1 > timer2)                                                             //si timer1 es el mayor, es desir el primer sensor que detecto movimiento fue IR1    
    {
      Time = timer1 - timer2;                                                       //variable time toma la resta de ambos tiempo, para luego calcular la velocidad
    }
    else if(timer2 > timer1)                                                        //sino, la variable timer 2 sera el mayor
    {
      Time = timer2 - timer1;
    }
   
   Time=Time/1000;                                                                  //convertir milisegundos en segundos de la variable resultante de ambos tiempo 
   speed=(distance/Time);                                                           //formula de velocidad v=d/t
   speed=speed*3600;                                                                //miltiplica los segundos y convertir a hr
   speed=speed/1000;                                                                //division de metros a Km
  }

  if(speed==0)                                                                      //si la variable velocidad es igual cero, No a detectado movimientos los IR
  { 
    lcd.setCursor(0, 1); 
    if(flag1==0 && flag2==0)                                                        //se comprueba si las variables de los sensores tienen datos
    {                                                                               //si los sensores no detecta movimiento aser lo siguiente
      lcd.print("Sin detectar          ");                                          //mensaje de variable del IR sensor.  no detectado
    }
    else
    {                                                                               //caso contrario
      lcd.print("Registrando...        ");                                          //mensaje en espera del segundo sensor
    } 
  }
  else
  {
    lcd.clear();                                                                     //limpiar pantalla 
    lcd.setCursor(0, 0); 
    lcd.print("Speed:");
    lcd.print(speed,1);                                                              //mostrar el dato de velocidad en la pantalla
    lcd.print("Km/Hr  ");
    lcd.setCursor(0, 1); 
    
    if(speed > 50)                                                                   //si detecta speed mayor a 50
    {
      lcd.print("Velocidad Alta  ");                                                 //Mensaje de velocidad excedida 
      digitalWrite(buzzer, HIGH);                                                    //si registra velocidad alta el buzzer emitira sonido
      
    }      
    else                                                                            //caso contrario
    {
      lcd.print("Velocidad Normal  ");                                              //volicidad normal
    }  
              
    delay(3000);                                                                    //tiempo de 3seg para mensaje
    digitalWrite(buzzer, LOW);                                                      //reset de buzzer
    speed = 0;                                                                      //reset de speed
    flag1 = 0;
    flag2 = 0;   
     
  }
}
