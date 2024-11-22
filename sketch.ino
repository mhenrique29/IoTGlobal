#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Inclua a biblioteca para o sensor de energia
#include <EmonLib.h> // Biblioteca para medição de energia (usando EmonLib)

// Configuração do DHT
#define DHTPIN 4           // Pino conectado ao DHT
#define DHTTYPE DHT22      // Tipo de sensor (DHT22 ou DHT11)
#define LED_WATER 15       // LED simulando o jato de água
#define LED_AIR 16         // LED simulando o jato de ar

DHT dht(DHTPIN, DHTTYPE);  // Instância do sensor DHT

// Configuração do sensor de energia
EnergyMonitor emon;       // Instância do EmonLib
#define CURRENT_SENSOR_PIN A0 // Pino do sensor de corrente (ex: ACS712)
#define VOLTAGE_CAL 234.26    // Fator de calibração para o sensor de tensão

// Credenciais WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Credenciais ThingSpeak
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "C6636YWTHVS2MAZO";

void setup() {
  Serial.begin(115200);

  // Configuração de LEDs
  pinMode(LED_WATER, OUTPUT);
  pinMode(LED_AIR, OUTPUT);
  digitalWrite(LED_WATER, LOW);
  digitalWrite(LED_AIR, LOW);

  // Inicializa o sensor DHT
  dht.begin();

  // Inicializa o sensor de energia
  emon.current(CURRENT_SENSOR_PIN, 111.1); // Configure o sensor de corrente
                                           // O valor 111.1 depende do sensor usado
                                           // Consulte a documentação do sensor

  // Conexão WiFi
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi.");
  Serial.println("Sistema iniciado.");
}

void loop() {
  // Leitura dos sensores
  float temp = dht.readTemperature(); // Temperatura em °C
  float hum = dht.readHumidity();     // Umidade em %

  // Leitura do sensor de energia
  float current = emon.calcIrms(1480); // Mede a corrente RMS (1480 amostras)
  float voltage = VOLTAGE_CAL;         // Simulação de tensão fixa, ajustar se necessário
  float power = voltage * current;     // Calcula potência em Watts

  // Verifica se os valores são válidos
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Erro ao ler o sensor DHT!");
    delay(2000);
    return;
  }

  // Exibe os dados no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C, Umidade: ");
  Serial.print(hum);
  Serial.print(" %, Corrente: ");
  Serial.print(current);
  Serial.print(" A, Potência: ");
  Serial.print(power);
  Serial.println(" W");

  // Controle do jato de água
  if (temp > 35) {
    digitalWrite(LED_WATER, HIGH);
    Serial.println("Jato de água ativado.");
  } else {
    digitalWrite(LED_WATER, LOW);
  }

  // Controle do jato de ar
  if (hum < 30) {
    digitalWrite(LED_AIR, HIGH);
    Serial.println("Jato de ar ativado.");
  } else {
    digitalWrite(LED_AIR, LOW);
  }

  // Envia os dados ao ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(temp) +
                 "&field2=" + String(hum) +
                 "&field3=" + String(current) +
                 "&field4=" + String(power);
    http.begin(url);
    int httpCode = http.GET(); // Envia a requisição HTTP GET

    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak!");
    } else {
      Serial.println("Falha ao enviar dados ao ThingSpeak.");
    }
    http.end(); // Finaliza a conexão HTTP
  } else {
    Serial.println("Conexão WiFi perdida.");
  }

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
