
#import "datosKnnBayes.h"
#import "datosPrueba.h"

int col=5;
int fil=35;
  int verPos = 0;
  int falNeg = 0;
  int falPos = 0;
  int verNeg = 0;
#include <ListLib.h>
List <int> list;

void setup() {
  Serial.begin(9600);
}

void loop() {
  algorConfusion();
}

void algorConfusion() {

   for (int i = 0; i <= fil; i++) {
    for(int j=0;j<col;j++){
  if (matrizPruebas[i][j] == datosKnn[i][j] &&  matrizPruebas[i][j] == 1) {
      verPos++;
    }
    if (matrizPruebas[i][j] != datosKnn[i][j] == 1) {
      falNeg++;
    }
    if (matrizPruebas[i][j] == datosKnn[i][2] && matrizPruebas[i][j] == 2) {
      verNeg++;
    }
    if (matrizPruebas[i][j] !=datosKnn[i][j] == 2) {
      falPos++;
    }
      if (matrizPruebas[i][j] ==datosKnn[i][j] &&  matrizPruebas[i][j] == 3) {
    verPos++;
    }
    if (matrizPruebas[i][j] != datosKnn[i][j] == 3) {
      falNeg++;
    }
    if (matrizPruebas[i][j] == datosKnn[i][2] && matrizPruebas[i][j] == 4) {
        verNeg++;
    }
    if (matrizPruebas[i][j] != datosKnn[i][j] == 4) {
       falPos++;
    }
  }
  }
  Serial.println("algoritmo confusion a lgoritmo Knn");
  Serial.println(String(" VP = ") + String(verPos) + String(" FN = ") + String(falNeg) + String(" VN = ") + String(verNeg) + String(" FP = ") + String(falPos));
  verPos = 0;
  falNeg = 0;
  falPos = 0;
  verNeg = 0;
  for (int i = 0; i <= fil; i++) {
    for(int j=0;j<col;j++){
  if (matrizPruebas[i][j] == datosBayes[i][j] &&  matrizPruebas[i][j] == 1) {
 verPos++;
    }
    if (matrizPruebas[i][j] != datosBayes[i][j] == 1) {
       falNeg++;
    }
    if (matrizPruebas[i][j] == datosBayes[i][2] && matrizPruebas[i][j] == 2) {
    verNeg++;
    }
    if (matrizPruebas[i][j] != datosBayes[i][j] == 2) {
     falPos++;
    }
      if (matrizPruebas[i][j] == datosBayes[i][j] &&  matrizPruebas[i][j] == 3) {
     verPos++;
    }
    if (matrizPruebas[i][j] != datosBayes[i][j] == 3) {
       falNeg++;
    }
    if (matrizPruebas[i][j] == datosBayes[i][2] && matrizPruebas[i][j] == 4) {
      verNeg++;
    }
    if (matrizPruebas[i][j] != datosBayes[i][j] == 4) {
     falPos++;
    }
  }
  }
  Serial.println("algorimto confusion a algoritmo de bayes");
  Serial.println(String(" VP = ") + String(verPos) + String(" FN = ") + String(falNeg) + String(" VN = ") + String(verNeg) + String(" FP = ") + String(falPos));
  verPos = 0;
  falNeg = 0;
  falPos = 0;
  verNeg = 0;
}
