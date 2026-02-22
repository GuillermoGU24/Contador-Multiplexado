// ================= SEGMENTOS =================
int segmentos[7] = {2,3,4,5,6,7,8};

// ================= DIGITOS =================
int digitos[4] = {12,11,10,9};

// ================= BOTONES =================
int botonA = A4;
int botonB = A2;

// ================= CONTADORES =================
int contadorA = 0;
int contadorB = 0;

// ================= MAPEO =================
// ORDEN LOGICO: A B C D E F G
int mapSeg[7] = {
  5, // A
  2, // B
  0, // C
  4, // D
  6, // E
  1, // F
  3  // G
};

// ================= NUMEROS =================
const byte numeros[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {

  for (int i = 0; i < 7; i++) {
    pinMode(segmentos[i], OUTPUT);
    digitalWrite(segmentos[i], LOW);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(digitos[i], OUTPUT);
    digitalWrite(digitos[i], LOW);
  }

  pinMode(botonA, INPUT_PULLUP);
  pinMode(botonB, INPUT_PULLUP);
}

void loop() {
  leerBotones();
  multiplexar();
}

// ================= BOTONES =================

void leerBotones() {

  static bool estadoA = HIGH;
  static bool estadoB = HIGH;

  bool lecturaA = digitalRead(botonA);
  bool lecturaB = digitalRead(botonB);

  if (estadoA == HIGH && lecturaA == LOW) {
    contadorA++;
    if (contadorA > 99) contadorA = 0;
    delay(200);
  }

  if (estadoB == HIGH && lecturaB == LOW) {
    contadorB++;
    if (contadorB > 99) contadorB = 0;
    delay(200);
  }

  estadoA = lecturaA;
  estadoB = lecturaB;
}

// ================= MULTIPLEXADO MEJORADO =================

void multiplexar() {

  int valores[4] = {
    contadorA / 10,
    contadorA % 10,
    contadorB / 10,
    contadorB % 10
  };

  for (int d = 0; d < 4; d++) {

    apagarTodo();  
    delayMicroseconds(200); 

    mostrarNumero(valores[d]);

    digitalWrite(digitos[d], HIGH); // activar digito

    delay(5); 
  }
}

// ================= APAGADO TOTAL =================

void apagarTodo() {

  // apagar digitos
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitos[i], LOW);
  }

  // apagar segmentos
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], LOW);
  }
}

// ================= MOSTRAR NUMERO =================

void mostrarNumero(int num) {

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[ mapSeg[i] ], numeros[num][i]);
  }
}
