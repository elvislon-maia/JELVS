// Definição dos pinos dos 5 sensores do HW-871
const int sensores[5] = {3, 4, 5, 6, 7};

void setup() {
  // Inicializa a comunicação serial para exibir os dados no computador
  Serial.begin(9600);
  
  // Configura os pinos dos sensores como ENTRADA
  for(int i = 0; i < 5; i++){
    pinMode(sensores[i], INPUT);
  }
  Serial.println("--- Teste dos sensores do robô seguidor de linha JELVS iniciado---");
  Serial.println("Formatacao: [S1] [S2] [S3] [S4] [S5]"); 
  delay(2000);
}

void loop() {
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
