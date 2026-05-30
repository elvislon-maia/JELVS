// Definição dos pinos dos 5 sensores do HW-871
const int sensores[5] = {3, 4, 5, 6, 7};
const int MEF = 8, MET = 9; // Motor da esquerda
const int MDF = 10, MDT = 11; // Motor da direita

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
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void moverTras(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void moverEsquerda(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, HIGH);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDT, LOW);
}

void moverDireita(){
  digitalWrite(MEF, HIGH);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, HIGH);
}

void pararMotor(){
  digitalWrite(MEF, LOW);
  digitalWrite(MET, LOW);

  digitalWrite(MDF, LOW);
  digitalWrite(MDT, LOW);
}

void loop() {
  moverFrente();
  delay(1000);
  moverDireita();
  delay(1000);
  moverEsquerda();
  delay(1000);
  moverTras();
  delay(1000);
  pararMotor();
  delay(1000);
}
