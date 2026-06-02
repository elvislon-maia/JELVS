// Definição dos pinos dos 5 sensores do HW-871
const int sensores[5] = {3, 4, 5, 6, 7};
const int MEF = 8, MET = 9; // Motor da esquerda
const int MDF = 10, MDT = 11; // Motor da direita

int ultimaDirecao = 0;

enum DIRECOES{
  ESQUERDA1,
  ESQUERDA2,
  FRENTE,
  DIREITA1,
  DIREITA2
};

enum ULTIMA_DIRECAO{
  ESQUERDA = 1,
  RETO = 2,
  DIREITA = 3
};

void setup() {
  // Inicializa a comunicação serial para exibir os dados no computador
  Serial.begin(9600);

  // Configurar os pinos dos motores como SAIDA
  pinMode(MEF, OUTPUT);
  pinMode(MET, OUTPUT);
  pinMode(MDF, OUTPUT);
  pinMode(MDT, OUTPUT);
  
  // Configura os pinos dos sensores como ENTRADA
  for(int i = 0; i < 5; i++){
    pinMode(sensores[i], INPUT);
  }
}

void testarSensores(){
  Serial.println("--- Teste dos sensores do robô seguidor de linha JELVS iniciado---");
  Serial.println("Formatacao: [S1] [S2] [S3] [S4] [S5]"); 
  delay(2000);
  // Leitura digital de cada um dos sensores
  for(int i = 0; i < 5; i++){
    if(i == 4){
      Serial.print("["); Serial.print(digitalRead(sensores[i])); Serial.println("] ");
    }
    else{
      Serial.print("["); Serial.print(digitalRead(sensores[i])); Serial.print("] ");
    }
  }
  delay(250);
}

void moverFrente(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void moverTras(){
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void moverEsquerda(){
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void moverDireita(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void pararMotor(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, LOW);
}

void loop() {
  int frente = digitalRead(sensores[DIRECOES(FRENTE)]);
  int esquerda1 = digitalRead(sensores[DIRECOES(ESQUERDA1)]);
  int esquerda2 = digitalRead(sensores[DIRECOES(ESQUERDA2)]);
  int direita1 = digitalRead(sensores[DIRECOES(DIREITA1)]); 
  int direita2 = digitalRead(sensores[DIRECOES(DIREITA2)]);

  if(frente == HIGH && esquerda1 == LOW && esquerda2 == LOW && direita1 == LOW && direita2 == LOW){
    moverFrente();
    ultimaDirecao = ULTIMA_DIRECAO(RETO);
  }
  else if(esquerda1 == HIGH || esquerda2 == HIGH){
    moverEsquerda();
    ultimaDirecao = ULTIMA_DIRECAO(ESQUERDA);
  }
  else if(direita1 == HIGH || direita2 == HIGH){
    moverDireita();
    ultimaDirecao = ULTIMA_DIRECAO(DIREITA);
  }
  else{
    if(ultimaDirecao = ULTIMA_DIRECAO(RETO)){
      moverTras();
      delay(120);
    }
    else if(ultimaDirecao = ULTIMA_DIRECAO(ESQUERDA)){
      moverEsquerda();
      delay(120);
    }
    else if(ultimaDirecao = ULTIMA_DIRECAO(DIREITA)){
      moverDireita();
      delay(120);
    }
    pararMotor();
  }
}
