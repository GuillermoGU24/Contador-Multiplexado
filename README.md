# Contador Doble de 2 Dígitos con Arduino (7 Segmentos Multiplexados)

Proyecto electrónico basado en Arduino que implementa **dos contadores independientes (00–99)** usando **4 displays de 7 segmentos construidos con LEDs individuales**, controlados mediante multiplexado.

El sistema funciona con **batería 18650 recargable**, incluye regulación de voltaje y control por botones.

---

## Características

- Dos contadores independientes (00–99)
- Displays de 7 segmentos hechos con LEDs individuales
- Multiplexado para reducir pines
- Control mediante dos pulsadores
- Alimentación portátil con batería 18650
- Regulador Step-Up a 5V
- Bajo consumo energético
- Código optimizado para evitar ghosting

---

## Funcionamiento

El sistema usa **multiplexado de displays**, lo que permite controlar 4 dígitos usando:

- 7 pines para segmentos
- 4 pines para selección de dígitos

Cada botón incrementa un contador independiente:

- Botón A → contador izquierdo
- Botón B → contador derecho

---

## Distribución de pines

### Segmentos

| Segmento | Pin Arduino |
|----------|-------------|
| A        |     D7      |
| B 	   | 	 D4      |
| C        |     D2      |
| D        |     D6      |
| E        |     D8      |
| F        |     D3      |
| G        |     D5 	 |

---

### Dígitos

| Dígito | Pin Arduino |
|--------|-------------|
| D1     |     D12     |
| D2     |     D11     |
| D3     |     D10     |
| D4     |     D9      |

---

### Botones

| Botón |  Pin |
| ----- |------|
|   A   |  A4  |
|   B   |  A2  |

---

## Alimentación

El sistema funciona con:

1. Batería 18650 (3.7V)
2. TP4056 para carga
3. MT3608 ajustado a 5V
4. Salida regulada al Arduino Nano

---

## Estructura del código

- Lectura de botones con antirrebote
- Tabla de números 7 segmentos
- Mapeo de segmentos configurable
- Multiplexado optimizado
- Corrección de ghosting

---

## Mejoras futuras

- Control de brillo por PWM
- Guardado de contadores en EEPROM
- Pantalla OLED opcional
- Indicador de batería digital

---


<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<title>Esquema Completo Alimentación</title>
<style>
body {
  background-color: #111;
  color: #fff;
  font-family: monospace;
}
.container {
  display: flex;
  align-items: center;
  flex-wrap: wrap;
}
.box {
  border: 2px solid #00ff88;
  padding: 15px;
  margin: 10px;
  text-align: center;
  min-width: 140px;
}
.red { color: #ff4444; }
.black { color: #aaaaaa; }
.green { color: #00ff88; }
.arrow {
  font-size: 22px;
  margin: 0 10px;
}
.section {
  margin-top: 40px;
}
</style>
</head>
<body>

<h2>ESQUEMA COMPLETO DE ALIMENTACIÓN</h2>

<div class="container">

<div class="box">
🔋 BATERÍA 18650<br><br>
<span class="red">(+)</span> → TP4056 B+<br>
<span class="black">(-)</span> → TP4056 B-
</div>

<div class="arrow">→</div>

<div class="box">
TP4056<br><br>
B+ / B- → batería<br>
<span class="red">OUT+</span> → DIODO (ÁNODO)<br>
<span class="black">OUT-</span> → GND general
</div>

<div class="arrow">→</div>

<div class="box">
DIODO 1N5819<br><br>
ÁNODO (sin raya) ← OUT+<br>
CÁTODO (con raya) → Interruptor<br><br>
Dirección:<br>
OUT+ ----|>|---- Interruptor
</div>

<div class="arrow">→</div>

<div class="box">
INTERRUPTOR<br><br>
Entrada → desde diodo<br>
Salida → Fusible
</div>

<div class="arrow">→</div>

<div class="box">
FUSIBLE PTC 1A<br><br>
Entrada → Interruptor<br>
Salida → MT3608 VIN+
</div>

<div class="arrow">→</div>

<div class="box">
MT3608 STEP-UP<br><br>
VIN+ ← Fusible<br>
VIN- ← GND<br><br>
VOUT+ → +5V<br>
VOUT- → GND
</div>

<div class="arrow">→</div>

<div class="box">
CONDENSADORES<br><br>
1000µF:<br>
+ → 5V<br>
- → GND<br><br>
100nF:<br>
Entre 5V y GND
</div>

<div class="arrow">→</div>

<div class="box">
ARDUINO NANO<br><br>
5V ← MT3608 VOUT+<br>
GND ← MT3608 VOUT-<br><br>
Desde aquí alimenta:<br>
Display + Transistores + Botones
</div>

</div>

<div class="section">
<h3>CONEXIONES DE TIERRA (GND)</h3>
<span class="black">
TP4056 OUT- → MT3608 VIN- → MT3608 VOUT- → Arduino GND → 
Transistores (emisor) → Botones (COM) → Todo GND común
</span>
</div>

<div class="section">
<h3>REGLAS IMPORTANTES</h3>
<ul>
<li>La rayita del diodo apunta hacia el interruptor.</li>
<li>El interruptor corta el positivo, nunca el negativo.</li>
<li>Todos los GND deben estar unidos.</li>
<li>No usar VIN del Arduino, usar pin 5V.</li>
<li>No conectar USB mientras esté alimentado por batería.</li>
</ul>
</div>

</body>
</html>



## Autor

Proyecto desarrollado por **GuillerGU24**
