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

import processing.serial.*;
PImage img;//variable para ingresar imagen
Serial port;
float valor=0;
float datoSerial;
float mapeo;
int aux=0;
void setup (){
  port= new Serial(this, "COM10",9600);//comunicacion con el puerto COM virtual
  size(700,600); // tamaño cuadro
  background(#A528FA); //color de fondo

}

void serialEvent(Serial port){
datoSerial=port.read();
valor=int(datoSerial);
println(valor);
}

void draw(){  
loop();
  }
  
  void loop(){
    if(valor==1.0){
      redraw();
      size(700,600); // tamaño cuadro
      background(#E2F238); //color de fondo
      textSize(20);
      fill(0);
      text("Su postura es CORRECTA, mantenga esa posición.",25,25);
      img=loadImage("posCorrecta.PNG");//cargamos la imagen
      image(img,30,80);//posicion de la imagen
      text("UTN-FICA-CITEl",25,550);
      text("SISTEMAS EMBEBIDOS",200,550);
      text("Solano Edwin",25,575);
   
   }
   if(valor==2.0){
     redraw();
     size(700,600); // tamaño cuadro
     background(#19F78D); //color de fondo
     textSize(20);
     fill(0);
     text("Su postura es INCORRECTA, debe acercar la espalda al espaldar.",25,25);
     img=loadImage("espaCurva.PNG");//cargamos la imagen
     image(img,30,80);//posicion de la imagen
     text("UTN-FICA-CITEl",25,550);
     text("SISTEMAS EMBEBIDOS",200,550);
     text("Solano Edwin",25,575);
   }
   if(valor==3.0){
     redraw();
     size(700,600); // tamaño cuadro
     background(#32C3FA); //color de fondo
     textSize(20);
     fill(0);
     text("Su postura es INCORRECTA, apoyado del lado derecho.",25,25);
     img=loadImage("derecho.PNG");//cargamos la imagen
     image(img,30,80);//posicion de la imagen
     text("UTN-FICA-CITEl",25,550);
     text("SISTEMAS EMBEBIDOS",200,550);
     text("Solano Edwin",25,575);
   }
   if(valor==4.0){
     redraw();
     size(700,600); // tamaño cuadro
     background(#FA3286); //color de fondo
     textSize(20);
     fill(0);
     text("Su postura es INCORRECTA, apoyado del lado izquierdo.",25,25);
     img=loadImage("izquierdo.PNG");//cargamos la imagen
     image(img,30,80);//posicion de la imagen
     text("UTN-FICA-CITEl",25,550);
     text("SISTEMAS EMBEBIDOS",200,550);
     text("Solano Edwin",25,575);
   }
  }
