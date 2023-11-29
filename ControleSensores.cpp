#ifndef NOVABIBLIOTECA_H
#define NOVABIBLIOTECA_H

#ifndef CONTROLEMOTORES_H
  #include <ControleMotores.h>
#endif

#include <ControleSensores.h>
#include <Arduino.h>

ControleSensores::ControleSensores(const byte *portasSensores, const byte quantidadeSensores, const short corteSensores)
  : QUANTIDADE_SENSORES(quantidadeSensores), PORTAS_SENSORES(portasSensores),
    menorValoresSensores((short *)malloc(this->QUANTIDADE_SENSORES * sizeof(short))), maiorValoresSensores((short *)malloc(this->QUANTIDADE_SENSORES * sizeof(short))), CORTE_SENSORES(corteSensores) {

  for (byte i = 0; i < this->QUANTIDADE_SENSORES; i++) {
    pinMode(this->PORTAS_SENSORES[i], INPUT);
    this->menorValoresSensores[i] = 2000;
    this->maiorValoresSensores[i] = 0;
  }
}
void ControleSensores::calibrar(const byte botaoCalibrar) {
  while (!digitalRead(botaoCalibrar)) {
    for (byte i = 0; i < this->QUANTIDADE_SENSORES; i++) {
      short valorSensor = analogRead(this->PORTAS_SENSORES[i]);
      if (valorSensor < this->menorValoresSensores[i]) {
        this->menorValoresSensores[i] = valorSensor;
      } else if (valorSensor > this->maiorValoresSensores[i]) {
        this->maiorValoresSensores[i] = valorSensor;
      }
    }
  }
}
void ControleSensores::autoCalibrar(ControleMotores motores, short tempoEspera) {
  motores.acionar(-255,255);
  long time = millis();
  while (millis() - time <= tempoEspera) {
    for (byte i = 0; i < this->QUANTIDADE_SENSORES; i++) {
      short valorSensor = analogRead(this->PORTAS_SENSORES[i]);
      if (valorSensor < this->menorValoresSensores[i]) {
        this->menorValoresSensores[i] = valorSensor;
      } else if (valorSensor > this->maiorValoresSensores[i]) {
        this->maiorValoresSensores[i] = valorSensor;
      }
    }
  }
  motores.parado();
}
short ControleSensores::leitura(byte indice) {
  return constrain(map(analogRead(this->PORTAS_SENSORES[indice]), this->menorValoresSensores[indice], this->maiorValoresSensores[indice], 200, 800), 200, 800);
}

short ControleSensores::leitura(byte indice, short valorMinimo, short valorMaximo) {
  return constrain(map(analogRead(this->PORTAS_SENSORES[indice]), this->menorValoresSensores[indice], this->maiorValoresSensores[indice], valorMinimo, valorMaximo), valorMinimo, valorMaximo);
}
short ControleSensores::calcularErro(){
  if       (ControleSensores::leitura(0) <= this->CORTE_SENSORES && ControleSensores::leitura(1) >= this->CORTE_SENSORES){          // 1 0 0 0 0 0 0     -6                                                                       // POSIÇÃO = 1 0 0 0 0 0 0
    return -6;
  } else if(ControleSensores::leitura(6) <= this->CORTE_SENSORES && ControleSensores::leitura(5) >= this->CORTE_SENSORES){          // 0 0 0 0 0 0 1      6                                                                     // POSIÇÃO = 1 0 0 0 0 0 0
    return 6;
  } else if(ControleSensores::leitura(0) <= this->CORTE_SENSORES && ControleSensores::leitura(1) <= this->CORTE_SENSORES){          // 1 1 0 0 0 0 0     -5                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return -5;
  } else if(ControleSensores::leitura(6) <= this->CORTE_SENSORES && ControleSensores::leitura(5) <= this->CORTE_SENSORES){          // 0 0 0 0 0 1 1      5                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return 5;
  } else if(ControleSensores::leitura(1) <= this->CORTE_SENSORES && ControleSensores::leitura(2) >= this->CORTE_SENSORES){          // 0 1 0 0 0 0 0     -4                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return -4;
  } else if(ControleSensores::leitura(5) <= this->CORTE_SENSORES && ControleSensores::leitura(4) >= this->CORTE_SENSORES){          // 0 0 0 0 0 1 0      4                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return 4;
  } else if(ControleSensores::leitura(1) <= this->CORTE_SENSORES && ControleSensores::leitura(2) <= this->CORTE_SENSORES){          // 0 1 1 0 0 0 0     -3                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return -3;
  } else if(ControleSensores::leitura(5) <= this->CORTE_SENSORES && ControleSensores::leitura(4) <= this->CORTE_SENSORES){          // 0 0 0 0 1 1 0      3                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return 3;
  } else if(ControleSensores::leitura(2) <= this->CORTE_SENSORES && ControleSensores::leitura(3) >= this->CORTE_SENSORES){          // 0 0 1 0 0 0 0     -2                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return -2;
  } else if(ControleSensores::leitura(4) <= this->CORTE_SENSORES && ControleSensores::leitura(3) >= this->CORTE_SENSORES){          // 0 0 0 0 1 0 0      2                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return 2;
  } else if(ControleSensores::leitura(2) <= this->CORTE_SENSORES && ControleSensores::leitura(3) <= this->CORTE_SENSORES){          // 0 0 1 1 0 0 0     -1                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return -1;
  } else if(ControleSensores::leitura(4) <= this->CORTE_SENSORES && ControleSensores::leitura(3) <= this->CORTE_SENSORES){          // 0 0 0 1 1 0 0      1                                                                      // POSIÇÃO = 1 0 0 0 0 0 0
    return 1;
  }
  return 0;
}
short ControleSensores::calcularPID(byte Kp, byte Ki, byte Kd){
  short erro = calcularErro();
  this->P = erro;
  this->I += erro;
  if (erro == 0) this->I = 0;
  this->D = erro - erroAnterior;
  erroAnterior = erro;
  return (Kp * this->P) + (Kp * this->I) + (Kd * this->D);
}
#endif