/*
 *     UNIVERSIDAD TECNICA DEL NORTE
 * SISTEMAS EMBEBIDOS 
 * PROYECTO PRIMER BIMESTRE 
 * Integrantes: Carlos Guerrón, Edwin Solano
 * Docente: ING. Paul Rosero
 * Fecha: 14/12/2020
 * bjetivo: Convolucion, suavizado Media, metrica SNR de la señal ECG
 * 
 */
 
 #define tam_sig 69 // declaramos el tamaño de la señal ecg
 #define tam_fil 7 // declaramos el tamaño de la señal del filtro realizado en Tfilter

 extern double ecg_100Hz[tam_sig];  //llamamos a la señal de neustra pestaña signals
 extern double filter_taps[tam_fil]; 
 double output[tam_sig+tam_fil];  // vectores de salida 
 double output_sig[tam_sig];

 void convolution(double *sig_in,double *sig_out, double *imp, int sig_tam, int impt_tam); //definimos funcion para convolucion
 void media_filter(double *sig_in, double *output_sig, int sig_tam, int filer); //definimos la funcion para el suavizado de la señal 
 void plot_signal(void);  // definimos la fucnion de grafica

 double promOri; //guaradar promedio de la señal original
double promFilt; //guardar promedio de la seña filtrada
void setup() {
  Serial.begin(9600);
}

void loop() {
 convolution((double *)&ecg_100Hz, (double *)&output[0], (double *)&filter_taps[0],
              (int) tam_sig, (int) tam_fil); // funcion de la convulcion de las señales
              
 media_filter((double *)&ecg_100Hz, (double *)&output_sig[0], (int) tam_sig,5); //funcion de algoritmo media
 plot_signal();  // graficar las señales
 SNR();   // metrica señal-ruido
 delay(100);
}

// FILTRO FIR
void convolution (double *sig_in,double *sig_out, double *imp, int sig_tam, int fil_tam){  // convulucion
  int i,j; // declaramos variables para hacer dos ciclos
  //poner ceros a vector de salida
  for(i=0; i<(sig_tam+fil_tam); i++){
    sig_out[i]=0;
    }
    for(i=0; i<sig_tam; i++){
      for(j=0; j<fil_tam; j++){
        sig_out[i+j]=sig_out[i+j] + sig_in[i]*imp[j];
        }
      }
  }
// suavizado Media 
void media_filter(double *sig_in, double *output_sig, int sig_tam, int filter){
  int k,l;   // declaramos varibles 
  k=floor(filter/2);  // decaramos la cariable k
  while(k<sig_tam-floor(filter/2)-1){ //inciiamos ciclo while 
    k++;
    output_sig[k]=0;
    l=-floor(filter/2);
    while(l<floor(filter/2)){
      l++;
      output_sig[k]=output_sig[k]+sig_in[k+l];
      }
      output_sig[k]=output_sig[k]/((filter*2)+1);
    }
  }
//Grafica de la señal 
void plot_signal(void){   // graficar resultado
  int i;
  for(i=0; i<tam_sig; i++){
    Serial.print(ecg_100Hz[i]);
    Serial.print(",");
    Serial.print(output_sig[i]);
    Serial.print(",");
    Serial.println(output[i]);
    delay(5);
    }
  }
//métrica SNR
void SNR(){//metodo snr
  int i;//variable
  for(i=0;i<tam_sig;i++){//ciclo reccorre segun el numero de datos de la señal
    promOri=promOri+ecg_100Hz[i];//guarda los valores del promedio en cada punto 
    }
   for(i=0;i<tam_sig;i++){//reccorrico del numero de datos de la señal filtrada
    promFilt=promFilt+output[i];
    }
   double promFilt1 = promOri/tam_sig;//lo divide para el numero de datos de la señal filtrada
   double promFilt2 = promFilt/tam_sig; 
   double vout = (promFilt1*5)/1023;//hace el cambio de datos de hasta 1023 en la señal original para el voltaje de salida
   double vfilt = (promFilt2*5)/1023;//hace el cambio de datos de hasta 1023 en la señalfiltrada para el voltaje de filtrado
   double snr = 20*log(vfilt/vout);//calculo de la metrica
  Serial.println("");//salto de linea
  Serial.println(String("promedio señal ingresada: ")+String(promFilt1));//imprime el valor promedio
  Serial.println(String("promedio señal filtrada: ")+String(promFilt2));   //imprime el valor promedio
  Serial.println(String("Voltaje de salida señal ingresada: ")+String(vout));//imprime el valor promedio de voltaje de la señal ingresada
  Serial.println(String("Voltaje de salida señal filtrada: ")+String(vfilt)); //imprime el valor promedio de voltaje de la señal filtrada
  Serial.println(String("SNR: ")+String(snr)+String(" decibeles"));   //imprime el valor de la metrica snr
  }
