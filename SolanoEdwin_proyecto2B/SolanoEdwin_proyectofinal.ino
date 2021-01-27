/*
 * UTN_FICA_CITEL
 * sitemas embebidos 
 * proyecto segundo bimestre
 * Nombre: Solano Edwin
 * 
 * objetivo: determinar la postura de una persona en silla de ruedas mediante el uso de sensores de presion y un sensor ultrasonico 
 *           filtrando la señal y aplicando los agoritmos de KNN y bayes y el algorimto de confusion para obtener un resultado, enviar
 *           ese dato al procesing y este muestre en pantalla la postura que se encuentra
 */
#include <SoftwareSerial.h>//libreria que permite la coneccion serial con otros pines del arduino
#define rxCOM 5//pin 5 para recibir datos
#define txCOM 3//pin 6 para evio de datos
SoftwareSerial cxSerial =  SoftwareSerial(rxCOM, txCOM);//conexion serial con otros pines del arduino

#define sensorpin A0// analog pin 0
#define sensorpin1 A1
#define sensorpin2 A2
#include <avr/wdt.h>
#include<MsTimer2.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

//***************************variables para ultrasonisco**************************
long tiempo=0; //Donde se va a guardar el tiempo de duración del pulso generado por el pin Echo
float distancia=0; //Donde se va a guardar la distancia calculada
int pinTrigger=7; 
int pinEcho=6;
//****************************variables para KNN**********************************
#include "datos.h"
 //datos de prueba
// float datos_prueba [4]={549.00,106.00,260.00,12.00};
 int col;
 int fil=0;
 float potencia;
 float raiz;
 float etiqueta; 
 float dist_menor=2500;//agregar un valor fuera del rango
 String tipo="";

 //*******************************************************************************

 //llamar a las señales 
 #define tam_sig 21  //tamaño de la señal de entrada
extern double flex_sensor[tam_sig];//llamar a la señal 
extern double flex_sensor1[tam_sig];//llamar a la señal 
//extern double flex_sensor2[tam_sig];//llamar a la señal 
//extern double flex_sensor3[tam_sig];//llamar a la señal 
int senal;//variable donde se guarda el resultado del filtro
double promOri; //guaradar promedio de la señal original
double promFilt; //guardar promedio de la seña filtrada
double output[tam_sig];//vector de salida
double vector[5]; //almacenar los datos de filtrado
void mediana_filtro (double *sen_in, double *salida_sen, int sen_tam, int filtro);//definir la funcion
void plot_signal(void); //metodo graficar la señal 

//*********************variables datos***************
 int force;
   int force1;
    int force2;
  float force_per=0;
  float force_per1=0;
  float force_per2=0;
 

//float datos_prueba [5]={};

int i=0;
int cont=0;
int on=0;
int btn1;
int reinicio;

//***************variables vayes**********************
#include <ListLib.h>
List<int> list;
char respuesta;
float sumatoria;
float distanciaB;
float distanciaMayor = 0.1;
float normalizador;
float p_x;
float aux = 0.0;
float resultado;
void bayes(int tags, int filas, int columnas, float r);
float datos_prueba1 [5]={};

//void bayesiano(int etiquetas, int columnas, int filas, float r);

int format;
 //float datos_prueba [5]={force_per,force_per1,force_per2,distancia,1.00};

 
void setup() {
  pinMode(rxCOM, INPUT);//entrada de datos
  pinMode(txCOM, OUTPUT);//salida de datos
  cxSerial.begin(9600);//conceccion con pin 5 y 6 para el puerto COM
  Serial.begin(9600); //CX
  pinMode(pinEcho,INPUT); // Configuración del pin 6 como entrada
  pinMode(pinTrigger,OUTPUT); //Configuración del pin 7 como salida
    lcd.begin(16,4);
    lcd.setCursor(0, 0);
    lcd.print("UTN_FICA");
    lcd.setCursor(0, 1);
    lcd.print("SENSORES");
    delay(300);
    lcd.clear();
     MsTimer2::set(100,reloj);//reloj cada segundo
     attachInterrupt(0,activacion,LOW);//interrupciones inico
}


void loop() {
  if(on==1){//interrupcion 2 hacer 
     lcd.clear();
     force=analogRead(sensorpin);
     force1=analogRead(sensorpin1);
     force2=analogRead(sensorpin2);
     force_per= map(force, 0, 305, 0,1023);
     force_per1= map(force1, 0, 305, 0, 1023);
     force_per2= map(force2, 0, 305,0, 1023);
     lcd.setCursor(4,0);
     lcd.print("Fuerza: ");
     lcd.setCursor(0,1);
     lcd.print(force_per);
     //Serial.println(force_per);
     format=(int)force_per;//guardar ese dato en la variable
     cxSerial.write(format);//escribir en la comunicacion serial
     delay(100);
     lcd.setCursor(7,1);
     lcd.print(force_per1);
     //Serial.println(force_per1);
     int format1=(int)force_per1;//guardar ese dato en la variable
     cxSerial.write(format1);//escribir en la comunicacion serial
     delay(100);
     lcd.setCursor(0,2);
     lcd.print(force_per2);
     //Serial.println(force_per2);
     int format2=(int)force_per2;//guardar ese dato en la variable
     cxSerial.write(format2);//escribir en la comunicacion serial
     delay(100);
     ultrasonico();
     Serial.println(String(force_per)+String(",")+String(force_per1)+String(",")+String(force_per2)+String(",")+String(distancia));
     bayes(4, 35, 5, 0.1);
     KNN();
}
 
 
//gauss_filtro ((double *)&flex_sensor[0], (double *)&output[0], (int) tam_sig,5); //llamar al metodo gauss
 //plot_signal(); //metodo para graficar la señal
 //delay(150);  //temporizador

}
void ultrasonico (){
digitalWrite(pinTrigger,LOW); //Se asegura un cero en el pin que se va a utilizar como Trigger
delayMicroseconds(5);//Restardo de 5 microsegundo
digitalWrite(pinTrigger,HIGH); //Se establece en alto el pin del trigger para comenzar el pulso de inicio del sensor
delayMicroseconds(10); //retardo de 10 microsegundos (tiempo minimo para inicializar el trigger del sensor)
digitalWrite(pinTrigger,LOW);//Se establece en bajo el pin del Trigger para terminar el pulso de inicio del sensor
tiempo=pulseIn(pinEcho,HIGH);//Se inicia la función pulseIn para que mida el tiempo del pulso generado por el Echo del sensor
distancia=tiempo*0.00343/2; //Calculo de distancia a la cual se encuentra el objeto
lcd.setCursor(0,3); // Se ubica el cursor en la columna 0 y fila 1 del LCD
lcd.print("dist= "); // Se imprime el texto Volt=
lcd.setCursor(6,3); // Se ubica el cursor en la columna 0 y fila 1 del LCD
lcd.print(distancia); // Se imprime el texto Volt=
//Serial.println(distancia);
delay(100);
lcd.setCursor(9,3); // Se ubica el cursor en la columna 0 y fila 1 del LCD
lcd.print("Cm"); // Se imprime el texto Volt=
delay(1000);
}

//Filtro gaussiano
void gauss_filtro (double *sig_in, double *output, int sig_tam, int filtrado){//metodo gausssiano
int i,j,k;//variables
  for(k=0;k<sig_tam;k++){ //ciclo para el metodo de gauss
    vector[0]=sig_in[k+0];//remplazo de la señal a la posicion del vector uno
    vector[1]=sig_in[k+1];//remplazo de la señal a la posicion del vector dos
    vector[2]=sig_in[k+2];//remplazo de la señal a la posicion del vector tres
    vector[3]=sig_in[k+3];//remplazo de la señal a la posicion del vector cuatro
    vector[4]=sig_in[k+4];//remplazo de la señal a la posicion del vector cinco
    i=0;//inicio de variable
    while(i<=3){//en la tercera posiicion
      i++;//aumento de valor
      j=i+1;//valor de i mas uno
      while(j<=4){
        j++;
        if(vector[j]<vector[i]){//si la posicion del vector es menor 
          senal=vector[j];//reemplaza el valor de la posiicon del vector en la variable senal
            vector[j]=vector[i];//si el vector es igual
            vector[i]=senal;//remplaza el valor de senal en vector[posicion]
        }
      }
    }
    output[k]=vector[1];//salida del resultado
  }
  }

  void plot_signal(void){ //metodo para graficar la señal
  int i; //variable 
  for(i=0;i<tam_sig;i++){//ciclo repetitivo para recorrer la señal
      Serial.print(flex_sensor[i]);//posiscion del dato
      Serial.print(",");
      Serial.print((output[i]));//salida del resultado señal metodo gauss
      Serial.println(",");
    delay(100);//temporizador
  }
}

//********************metodo KNN***************
void KNN(){

 float datos_prueba [5]={force_per,force_per1,force_per2,distancia,1.00};
   for(;fil<35;fil++){
    for(col=0;col<4;col++){
      potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2); 
    }
    raiz=sqrt(potencia);
    potencia=0;
    //almacenar la distancia menor
    if(raiz<dist_menor){
      dist_menor=raiz;//guardo distancia menor de la matriz
      etiqueta=matriz[fil][4];//almacenor valor de  etiqueta de la fila donde la distancia es menor 
    }
  }
  switch((int) etiqueta){
    case 1:
     Serial.print("prediccion KNN: ");
    Serial.println("");
    tipo="postura 1";
    break;
    case 2:
     Serial.print("prediccion KNN: ");
    Serial.println("");
    tipo="postura 2";
    break;
    case 3:
     Serial.print("prediccion KNN: ");
    Serial.println("");
    tipo="postura 3";
    break;
    case 4:
     Serial.print("prediccion KNN: ");
    Serial.println("");
    tipo="postura 4";
    break;
  }
    cxSerial.write(etiqueta);//escribir en la comunicacion serial
  Serial.println(tipo);
  if(etiqueta==datos_prueba[5]){
  Serial.println("asignasion correcta");
  }
 
}

//***************************************************bayesiano******************************************
 
void bayes(int tags, int filas, int columnas, float r) {

   //float datos_prueba[5] = {586.25,388.45,0.00,20.35,1.00};
  float sum1, sum2, sum3, sumatoria = 0, distancia_menor = 3000, distanciaB;
  int cont1 = 0, cont2 = 0, cont3 = 0, drain = 0, source = 0, tag;
  
float datos_prueba1 [5]={force_per,force_per1,force_per2,distancia,1.00};
  for(int g=0;g<6;g++){
  Serial.println(datos_prueba1[5]);
  }
  

  float prob[5][tags];
  //******************encerar matriz de probabilidades***************
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < tags; j++) {
      prob[i][j] = 0;
    }
  }
  //*******************asiganr etiquetas a matriz************
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < tags; j++) {
      prob[i][j] = 0;
      if (i == 0)
        prob[i][j] = j + 1;
    }
  }
  //********************valores a:  P(X/1),P(X/2),P(X/3),P(X/4)******************
  for (int t = 0; t < 5; t++) {
    for (int i = 0; i < filas; i++) {
      if (matriz[i][columnas - 1] == t + 1) {
        prob[1][t]++;
      }
    }
  }

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      sumatoria = sumatoria + pow(matriz[i][j] - datos_prueba1[j], 2);
    }
    distanciaB = sqrt(sumatoria);
    sumatoria = 0;
    if (distanciaB > distanciaMayor)
      distanciaMayor = distanciaB;
  }

  distanciaB = 0;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      sumatoria = sumatoria + pow(matriz[i][j] - datos_prueba1[j], 2);
    }
    distanciaB = sqrt(sumatoria);
    normalizador = distanciaB / distanciaMayor;
    sumatoria = 0;
    if (normalizador < r) {
      list.Add(i);
    }
  }

  for (int i = 0; i < list.Count(); i++) {
    for (int j = 0; j < tags; j++) {
      if (matriz[list[i]][columnas - 1] == prob[0][j])
        prob[2][j]++;
    }
  }
  p_x = list.Count() / float(filas);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < tags ; j++) {
      prob[4][j] = ((prob[1][j] / filas) * (prob[2][j] / prob[1][j])) / p_x;
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < tags ; j++) {
      if (prob[4][j] > aux) {
        resultado = int (prob[0][j]);
        aux = prob[4][j];
      }
    }
  }
  for (int i = 0; i < 5 - 4; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print("   ");
      Serial.print(prob[i][j], 0);
      Serial.print("     ");
    }
    Serial.println(" ");
  }
  for (int i = 1; i < 5 - 3; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print("  ");
      Serial.print(prob[i][j], 0);
      Serial.print("     ");
    }
    Serial.println(" ");
  }
  for (int i = 2; i < 5 - 2; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print("   ");
      Serial.print(prob[i][j], 0);
      Serial.print("     ");
    }
    Serial.println(" ");
  }
    for (int i = 3; i < 5 - 1; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print("   ");
      Serial.print(prob[i][j], 0);
      Serial.print("     ");
    }
    Serial.println(" ");
  }
  for (int i = 4; i < 5; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print(" ");
      Serial.print(prob[i][j], 5);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  Serial.println("prediccion Bayes: ");
    Serial.print("postura ");
  Serial.print(etiqueta,0);
    Serial.println(" ");
}



  void activacion(){//interrupciones
  switch(on){//menu
    case 0://caso 1
     Serial.println("UTN-FICA-CITEL");//mensaje en CX
      Serial.println("proyect");//mensaje en CX
      Serial.println("Solano Edwin");//mensaje en CX
      Serial.println("SELECCIONE EL MODO");//mensaje en CX
      Serial.println("Tiempo de reinicio: ");
        MsTimer2::start();//inicia el relog
      on++;//contador
    break;
    case 1:
      Serial.println("power OFF");
      on=0;//reinicio de variables
      MsTimer2::stop();//reinicio del reloj
      cont=0;//reincio de variables
      on=0;
      etiqueta=0;
      force_per=0.00;
      force_per1=0.00;
      force_per2=0.00;
      distancia=0.00;
      float datos_prueba [5]={force_per,force_per1,force_per2,distancia,1.00};
      Serial.println(String(force_per)+String(",")+String(force_per1)+String(",")+String(force_per2)+String(",")+String(distancia));
      Serial.println("");
    break;
  }
 }


void reloj() {
  cont++;//contador 
 Serial.println(String("reloj: ")+String(cont));//mensaje del reloj
  if (cont>=20){//cuando el tiempo de conteo sea igual que de reinicio hacer
  wdt_disable();//desactivar perro guardian
  wdt_enable(WDTO_500MS);//activar perro guardian en 4 segundos
  }
}
