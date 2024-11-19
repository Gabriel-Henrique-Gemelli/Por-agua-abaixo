#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal.h>

// Instância do sensor BMP180
Adafruit_BMP085 bmp;

// Configuração do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Limites de pressão em hPa
const float LIMITE_INFERIOR = 500.0; // Limite inferior da pressão (buraco)
const float LIMITE_SUPERIOR = 1000.0; // Limite superior da pressão (bloqueio)

void setup() {
  lcd.begin(16, 2);
  lcd.print("Inicializando...");

  // Inicializa o sensor BMP180
  if (!bmp.begin()) {
    lcd.clear();
    lcd.print("BMP180 erro!");
    while (1) {} // Trava aqui se o sensor não for encontrado
  }

  delay(2000);
  lcd.clear();
}

void loop() {
  // Lê a pressão absoluta medida pelo sensor
  float pressao_atual = bmp.readPressure() / 100.0; // Convertendo para hPa

  lcd.setCursor(0, 0);
  if (pressao_atual < LIMITE_INFERIOR) {
    // Pressão abaixo do limite inferior
    lcd.print("Buraco detectado!");
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(pressao_atual, 2); // Mostra a pressão com 2 casas decimais
    lcd.print(" hPa   ");
  } else if (pressao_atual > LIMITE_SUPERIOR) {
    // Pressão acima do limite superior
    lcd.print("Cano bloqueado!");
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(pressao_atual, 2);
    lcd.print(" hPa   ");
  } else {
    // Pressão dentro do intervalo aceitável
    lcd.print("Cano OK         "); // Espaços extras para apagar caracteres antigos
    lcd.setCursor(0, 1);
    lcd.print("Pressao: ");
    lcd.print(pressao_atual, 2);
    lcd.print(" hPa   ");
  }

  // Breve atraso para evitar atualizações excessivas
  delay(200);
}