#include <ControleMotores.h>
#include <ControleSensores.h>
#include <LiquidCrystal_I2C.h>

const byte PORTAS_MOTORES[4] = { 1, 4, 2, 3};
ControleMotores motores(PORTAS_MOTORES);

#define velocidadePadrao 180

#define ledVerde1 44
#define ledVerde2 45
#define ledVermelho2 46
#define ledVermelho1 47

#define corteSensoresLinha 500
#define quantidadeSensores 7
#define botaoCalibrar 6

#define Kp 20
#define Ki 0
#define Kd 20

#define QUANTIDADE_SENSORES 7
#define CORTE_SENSORES 500

const byte PORTAS_SENSORES[quantidadeSensores] = { A5, A6, A4, A3, A2, A1, A7 };
ControleSensores sensores(PORTAS_SENSORES, QUANTIDADE_SENSORES, CORTE_SENSORES);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(">>> PROGRAMA INICIADO <<<");

  lcd.init();       
  lcd.backlight();
  lcd.clear();  

  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVermelho2, OUTPUT);

  digitalWrite(ledVermelho1, 1);
  digitalWrite(ledVermelho2, 1);

  Serial.print(">>> CALIBRANDO <<<");
  lcd.print(">> CALIBRANDO <<");
  sensores.autoCalibrar(motores, 6000);
  lcd.clear();
  lcd.print(">> CALIBRADO <<");
  Serial.print(">>> CALIBRADO <<<");
}

void loop() {
  short PID = sensores.calcularPID(Kp, Ki, Kd);
  motores.acionarPID(velocidadePadrao + PID, velocidadePadrao - PID);
}
