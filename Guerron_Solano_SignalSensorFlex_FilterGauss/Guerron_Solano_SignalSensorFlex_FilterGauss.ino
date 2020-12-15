/*
 *     UIVERSIDAD TECNICA DEL NORTE
 * SISTEMAS EMBEBIDOS 
 * PROYECTO PRIMER BIMESTRE 
 * Docente: ING. Paul Rosero
 * Integrantes: Guerron Carlos, Solano Edwin
 * Fecha: 14/12/2020
 * objetivos: realizar un filtrado de la señal de un sensor flex mediante el metodo gausssiano
 * 
 */
#define tam_sig 100  //tamaño de la señal de entrada
extern double flex_sensor[tam_sig];//llamar a la señal 
int senal;//variable donde se guarda el resultado del filtro
double promOri; //guaradar promedio de la señal original
double promFilt; //guardar promedio de la seña filtrada
double output[tam_sig];//vector de salida
double vector[5]; //almacenar los datos de filtrado
void mediana_filtro (double *sen_in, double *salida_sen, int sen_tam, int filtro);//definir la funcion
void plot_signal(void); //metodo graficar la señal 
void setup() {
  Serial.begin(9600); //CX
}
void loop() {
  gauss_filtro ((double *)&flex_sensor[0], (double *)&output[0], (int) tam_sig,5); //llamar al metodo gauss
  plot_signal(); //metodo para graficar la señal
  SNR(); //Metodo SNR
  delay(150);  //temporizador
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
    delay(10);//temporizador
  }
}
//métrica SNR
void SNR(){//metodo snr
  int i;//variable
  for(i=0;i<100;i++){//ciclo reccorre segun el numero de datos de la señal
    promOri=promOri+flex_sensor[i];//guarda los valores del promedio en cada punto 
    }
   double promOri1 = promOri/100;//lo divide para el numero de datos de la señal
   for(i=0;i<100;i++){//reccorrico del numero de datos de la señal filtrada
    promFilt=promFilt+output[i];
    }
   double promFilt2 = promFilt/100;//lo divide para el numero de datos de la señal filtrada
   double vout = (promOri1*5)/1023;//hace el cambio de datos de hasta 1023 en la señal original para el voltaje de salida
   double vfilt = (promFilt2*5)/1023;//hace el cambio de datos de hasta 1023 en la señalfiltrada para el voltaje de filtrado
   double snr = 20*log(vfilt/vout);//calculo de la metrica
  Serial.println("");//salto de linea
  Serial.println(String("promedio señal ingresada: ")+String(promOri1));//imprime el valor promedio
  Serial.println(String("promedio señal filtrada: ")+String(promFilt2));   //imprime el valor promedio
  Serial.println(String("Voltaje de salida señal ingresada: ")+String(vout));//imprime el valor promedio de voltaje de la señal ingresada
  Serial.println(String("Voltaje de salida señal filtrada: ")+String(vfilt)); //imprime el valor promedio de voltaje de la señal filtrada
  Serial.println(String("SNR: ")+String(snr)+String(" decibeles"));   //imprime el valor de la metrica snr
  }
