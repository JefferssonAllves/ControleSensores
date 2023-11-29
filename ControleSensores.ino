#include <ControleSensores.h>

#define botaoCalibrar 26
//Instancia sensores de linha usando a biblioteca 'ControleSensores':
const byte PORTAS_ANALOGICOS[] = {A1,A2,A3,A4,A5};
ControleSensores sensores(PORTAS_ANALOGICOS, 5, botaoCalibrar);
void setup(){

}
void loop(){
  Serial.println("Tes");
}