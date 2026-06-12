// Definição dos pinos dos 5 sensores do HW-871
const int sensores[5] = {3, 4, 5, 6, 7};

// Motores
const int MEF = 8, MET = 9;
const int MDF = 10, MDT = 11;

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

ULTIMA_DIRECAO ultimaDirecao = RETO;

void setup() {
  Serial.begin(9600);

  pinMode(MEF, OUTPUT);
  pinMode(MET, OUTPUT);
  pinMode(MDF, OUTPUT);
  pinMode(MDT, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT);
  }
}

//====================
// Controle dos motores
//====================

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

//====================
// Teste dos sensores
//====================

void testarSensores() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

//====================
// Loop principal
//====================

void loop() {

  int esquerda1 = digitalRead(sensores[ESQUERDA1]);
  int esquerda2 = digitalRead(sensores[ESQUERDA2]);
  int frente    = digitalRead(sensores[FRENTE]);
  int direita1  = digitalRead(sensores[DIREITA1]);
  int direita2  = digitalRead(sensores[DIREITA2]);

  if (frente == LOW) {
    moverFrente();
    ultimaDirecao = RETO;
  }
  else if((esquerda1 == LOW || esquerda2 == LOW) && (direita1 == HIGH || direita2 == HIGH)){
    moverEsquerda();
    ultimaDirecao = ESQUERDA;
  }
  else if((direita1 == LOW || direita2 == LOW) && (esquerda1 == HIGH || esquerda2 == HIGH)){
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
