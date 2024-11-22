Sistema de Monitoramento e Controle IoT com ESP32

![image](https://github.com/user-attachments/assets/58e58ab2-8e76-44d8-9b47-02e4f9b8263c)

Este projeto utiliza o ESP32 para monitorar condições ambientais (temperatura e umidade), medir consumo de energia elétrica, e realizar controles automatizados com base nos dados coletados. Os dados são enviados para o ThingSpeak para visualização e armazenamento.
 
Descrição do Projeto
Funcionalidades Principais
Monitoramento de Temperatura e Umidade:
Sensor DHT22 para coleta de dados ambientais.
Monitoramento de Consumo de Energia:
Sensor de corrente (como ACS712) e EmonLib para medição da corrente e cálculo da potência em watts.
Ativação de Jatos Simulados:
Controle de LEDs que representam:
Jato de Água (ativado quando a temperatura excede 35 °C).
Jato de Ar (ativado quando a umidade está abaixo de 30%).
Envio de Dados para ThingSpeak:
Os dados de temperatura, umidade, corrente e potência são enviados via HTTP para o ThingSpeak para monitoramento remoto.

Componentes Utilizados
Hardware
ESP32: Microcontrolador principal.
DHT22: Sensor de temperatura e umidade.
Sensor de corrente (ACS712): Para medir a corrente elétrica.
Resistores e LEDs:
LED azul para "jato de ar".
LED ciano para "jato de água".

Dependências do Projeto
Bibliotecas Utilizadas
WiFi.h: Para conectar à rede Wi-Fi.
HTTPClient.h: Para enviar dados ao ThingSpeak via HTTP.
DHT.h: Para ler dados do sensor DHT22.
EmonLib.h: Para medir corrente e potência elétrica.

Fluxo do Código
Inicialização:
Configuração dos sensores, LEDs e conexão Wi-Fi.
Loop Principal:
Lê os dados dos sensores.
Calcula os valores derivados (corrente e potência).
Controla os LEDs com base nas condições definidas.
Envia os dados ao ThingSpeak.
Controle e Erros:
Exibe os dados no monitor serial.
Trata falhas na leitura dos sensores ou na conexão com o Wi-Fi/ThingSpeak.
tem menu de contexto
