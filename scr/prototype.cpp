#include <WiFi.h>
#include <HTTPClient.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Adafruit_NeoPixel.h>

#define PIN 14
#define NUMPIXELS 1
#define BUTTON_PIN 12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool buttonState = HIGH; // Estado inicial do botão
bool lastButtonState = HIGH; // Armazena o último estado do botão
unsigned long lastDebounceTime = 0; // Tempo do último estado estável
unsigned long debounceDelay = 50;   // Debounce delay em milissegundos
bool isRed = false; // Estado inicial do LED (inicia em verde)

// Substitua pelos dados da sua rede Wi-Fi
const char* ssid = "sua_rede";
const char* password = "senha_da_rede";

// URL do script PHP que irá inserir os dados no MySQL
const char* serverName = "endereço_da_função";

RF24 radio(4, 5);  // CE, CSN

// Fator de atenuação (Path Loss Exponent) ajustável
float pathLossExponent = 20.3;

// Credenciais do banco de dados
const char* db_user = "root";
const char* db_password = "";

// Variáveis de controle
unsigned long previousMillis = 0;
const long interval = 2000; // Intervalo de 2 segundos


void setup() {
  Serial.begin(115200);
  
  pixels.begin();  // Inicializa o NeoPixel
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o pino do botão como entrada

  radio.begin();
  radio.setChannel(76); // Canal 76
  radio.setDataRate(RF24_1MBPS); // Taxa de dados de 1Mbps

  // Conectando ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado");
}

void loop() {
  unsigned long currentMillis = millis();

  // Lê o estado do botão (HIGH quando pressionado, LOW quando não)
  int buttonState = digitalRead(BUTTON_PIN);

  // Controla o LED RGB com base no estado do botão
  if (buttonState == HIGH) {
    // Acende o NeoPixel em vermelho (botão pressionado)
    setColor(255, 0, 0); // Vermelho
  } else {
    // Acende o NeoPixel em verde (botão não pressionado)
    setColor(0, 255, 0); // Verde
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Escaneando redes Wi-Fi
    int n = WiFi.scanNetworks();
    if (n == 0) {
      Serial.println("Nenhuma rede encontrada");
    } else {
      Serial.println("Redes encontradas:");
      for (int i = 0; i < (n > 3 ? 3 : n); i++) {
        String networkName = WiFi.SSID(i);
        int P_r = WiFi.RSSI(i); // RSSI retorna int

        // Calculando a distância
        float distance = calculateDistance(P_r);
       
        Serial.printf("Rede: %s, Sinal: %d dBm, Distância: %.2f metros\n", networkName.c_str(), P_r, distance);

        // Enviando para o servidor MySQL
        if (sendToServer(networkName, distance, buttonState)) {
          Serial.println("Dados enviados com sucesso.");
        } else {
          Serial.println("Falha ao enviar dados.");
        }
      }
    }
  }
}

bool sendToServer(String networkName, float distance, int buttonState) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Iniciar a conexão com o servidor
    http.begin(serverName);
   
    // Definir cabeçalho do tipo de conteúdo
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Formatar os dados e credenciais para serem enviados no corpo da requisição
    String httpRequestData = "network_name=" + networkName
                            + "&distance=" + String(distance)
                            + "&button_state=" + String(buttonState)
                            + "&db_user=" + db_user
                            + "&db_password=" + db_password;

    // Enviar a solicitação POST com os dados
    int httpResponseCode = http.POST(httpRequestData);

    // Verificar o código de resposta HTTP
    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.println("Resposta do servidor: " + payload);
      http.end();
      return true;
    } else {
      Serial.print("Erro HTTP: ");
      Serial.println(httpResponseCode);
      http.end();
      return false;
    }
  } else {
    Serial.println("Falha na conexão Wi-Fi");
    return false;
  }
}

// Função para calcular a distância com base no RSSI
float calculateDistance(int rssi) {
  float freq = 2.4;  // Frequência em GHz (para Wi-Fi 2.4GHz)
  float exponent = (27.55 - (20 * log10(freq)) + abs(rssi)) / (10 * pathLossExponent);
  float distance = pow(10.0, exponent);
  return distance;
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  pixels.setPixelColor(0, pixels.Color(red, green, blue));  
  pixels.show(); // Envia os dados ao LED
}
