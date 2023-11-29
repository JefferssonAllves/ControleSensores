
#ifndef CONTROLESENSORES_H
#define CONTROLESENSORES_H

#include <Arduino.h>
class ControleSensores {
public:
  ControleSensores(const byte* portasSensores, const byte quantidadeSensores, const short corteSensores);
  void calibrar(byte botaoCalibrar);
  void autoCalibrar(ControleMotores motores, short time);
  short leitura(byte indice);
  short leitura(byte indice, short valorMinimo, short valorMaximo);
  short calcularPID(byte Kp, byte Ki, byte Kd);

private:
  const byte* PORTAS_SENSORES;
  const byte QUANTIDADE_SENSORES;
  const short CORTE_SENSORES;
  short* menorValoresSensores;
  short* maiorValoresSensores;
  short P, I, D, erroAnterior;
  short calcularErro();
};

#endif





