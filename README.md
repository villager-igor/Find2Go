# Projeto Find2Go
## Introdução

Este projeto utiliza um ESP32, um botão, uma fita de LED e um módulo nRF24L01 como antena para coletar dados, calcular e enviar a distância calculada entre um microcontrolador e aos roteadores de WiFi para uma aplicação web contendo um mapa. A aplicação, desenvolvida no WordPress, apresenta uma interface intuitiva, composta por uma página inicial, uma página de login e uma página dedicada ao mapa. O sistema permite que, ao pressionar o botão, o sistema detecte quais carrinhos estão disponíveis, indicado por um LED.
&nbsp;

## Desenvolvimento
Este projeto utiliza uma arquitetura de Internet das Coisas (IoT) com o objetivo de localizar um carrinho, empregando um ESP32 como dispositivo principal. A seguir, são descritos os principais elementos da arquitetura, suas funcionalidades, tecnologias envolvidas e os resultados esperados.
### Arquitetura e Funcionamento
A solução IoT é composta por um ESP32 Dev Kit v1, conectado a um botão, uma fita de LED e um módulo nRF24L01, que atua como antena para comunicação. O ESP32 é responsável por rastrear e localizar a plataforma utilizando a rede Wi-Fi e o módulo de comunicação via rádio. Quando o botão é pressionado, o LED mudará de cor e notificará o ESP32 a disponibilidade do carrinho em questão, sendo o ESP32 responsável pela coleta dos dados de localização e o envio dessas informações para uma aplicação web.

A aplicação web, desenvolvida em WordPress, exibe um mapa que facilita a visualização da localização do carrinho plataforma em tempo real. Esse mapa foi montado utilizando os plugins Astra e Elementor, o que permite uma interface intuitiva e responsiva. A comunicação entre o ESP32 e a aplicação web é feita por meio de requisições HTTP, enviando dados ao servidor PHP, que interage com o banco de dados MySQL.

![arquitetura_do_projeto](./.img/arquitetura_do_projeto.png)
&nbsp;

### Tecnologias Envolvidas
-Softwares: Arduino IDE foi utilizado para a programação do ESP32, enquanto o Tinkercad auxiliou no design e simulação do hardware. A interface web foi desenvolvida no WordPress, com o uso de phpMyAdmin para a gestão do banco de dados MySQL
&nbsp;

-Linguagens: O desenvolvimento utiliza PHP para interagir com o banco de dados, C++ para programar o ESP32 e SQL para manipulação de dados.
&nbsp;

-Bibliotecas: O projeto faz uso das bibliotecas nRF24L01 e RF24 para comunicação sem fio, WiFi para conectar o ESP32 à rede, Adafruit NeoPixel para controle da fita de LED e HTTPClient para gerenciar as requisições HTTP.
&nbsp;

-Addons do WordPress: O tema Astra e o construtor de páginas Elementor foram usados para criar e estilizar o site.
&nbsp;

-Hardware: Além do ESP32 Dev Kit v1, o projeto conta com uma fita de LED, um botão de controle e o módulo de comunicação nRF24L01.
&nbsp;

## Resultados
A aplicação desenvolvida oferece uma solução para a localização de um carrinho, devolvendo informações visuais e técnicas que comprovam seu funcionamento. O site exibe um mapa, onde o objeto rastreado pode ser visualizado em tempo real. 
### Imagem do protótipo
![Esp32](./.img/esp32_prototipo.jpg)
&nbsp;

### Visualização da Página
![pagina_inicial](./assets/pag_inicial.jpg.jpg)
&nbsp;

### Visualização da Página
![pagina_login](./assets/pag_login,jpg.jpg)
&nbsp;

### Visualização da Página
![pagina_mapa](./assets/pag_mapa.jpg.jpg)
&nbsp;

### Dificuldades enfrentadas ao longo do projeto
Durante o desenvolvimento do projeto, enfrentamos diversos desafios técnicos. O primeiro deles foi a comunicação entre a função do ESP32 e a tabela no banco de dados no WordPress. Houve dificuldades no envio correto dos dados via requisições HTTP, o que impedia a inserção dos dados de localização no banco.

Além disso, a montagem da matriz para o mapa representou um obstáculo significativo. Criar uma grade precisa que pudesse representar a posição do carrinho no mapa de forma confiável demanda mais tempo e diversos refinamentos, tanto no layout da aplicação quanto no código que gerencia a interpretação dos dados.

Por fim, o processo de triangulação e roteirização também apresentou desafios. Implementar algoritmos capazes de calcular com precisão a posição do carrinho sem os dados de posição ou grade tornou impossível prosseguir até esta etapa do projeto.