// Definição dos pinos dos 5 sensores do HW-871
const int sensores[5] = {3, 4, 5, 6, 7};

// Motores esquerdo Frente e Tras
const int MEF = 8, MET = 9;
// Motores direito Frente e Tras
const int MDF = 12, MDT = 13;
// Controle de velocidade dos motores;
const int MEV = 10, MDV = 11;

// Enumerador para facilitar a escrita do código
enum DIRECOES {
  ESQUERDA1,
  ESQUERDA2,
  FRENTE,
  DIREITA1,
  DIREITA2
};

enum ULTIMA_DIRECAO {
  ESQUERDA,
  RETO,
  DIREITA
};

// Variável que guarda a ultima direção usando os valores do enumerador "ULTIMA_DIRECAO"
ULTIMA_DIRECAO ultimaDirecao = RETO;

// Variável para controlar em qual estado o robô deve andar, LOW = linha preta; HIGH = linha branca
int leitura = LOW;
// Variável que controla a velocidade do robô;
int velocidade = 150;

void setup() {
  // Serial.begin(9600);

  // Definindo os motores como saída
  pinMode(MEF, OUTPUT);
  pinMode(MET, OUTPUT);
  pinMode(MDF, OUTPUT);
  pinMode(MDT, OUTPUT);
  pinMode(MEV, OUTPUT);
  pinMode(MDV, OUTPUT);

  // Controle da velocidade do motor 0 = parado; 255 = velocidade máxima
  analogWrite(MEV, 0);
  analogWrite(MDV, 0);

  // Definindo os sensor como entrada
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT);
  }
}

// Funções para movimentar o motor em cada uma das direções
void moverFrente() {
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void moverTras() {
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void moverEsquerda() {
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void moverDireita() {
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void pararMotor() {
  digitalWrite(MEF, LOW);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, LOW);
}

// Função para teste individual dos sensores
void testarSensores() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

void loop() {
  // Variáveis para facilitar a escrita no código
  int esquerda1 = digitalRead(sensores[ESQUERDA1]);
  int esquerda2 = digitalRead(sensores[ESQUERDA2]);
  int frente    = digitalRead(sensores[FRENTE]);
  int direita1  = digitalRead(sensores[DIREITA1]);
  int direita2  = digitalRead(sensores[DIREITA2]);

  analogWrite(MEV, velocidade);
  analogWrite(MDV, velocidade);

  if (frente == leitura) {
    moverFrente();
    ultimaDirecao = RETO;
  }
  else if((esquerda1 == leitura || esquerda2 == leitura) && (direita1 == !leitura || direita2 == !leitura)){
    moverEsquerda();
    ultimaDirecao = ESQUERDA;
  }
  else if((direita1 == leitura || direita2 == leitura) && (esquerda1 == !leitura || esquerda2 == !leitura)){
    moverDireita();
    ultimaDirecao = DIREITA;
  }
  // Linha perdida
  else {
    if (ultimaDirecao == ESQUERDA) {
      moverEsquerda();
      return;
    }
    else if (ultimaDirecao == DIREITA) {
      moverDireita();
      return;
    }
  }
}
