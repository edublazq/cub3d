```
 ██████╗██╗   ██╗██████╗ ██████╗██████╗
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝  ▄███╔╝██║  ██║
██║     ██║   ██║██╔══██╗  ▀▀══╝ ██║  ██║
╚██████╗╚██████╔╝██████╔╝  ██╗   ██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝   ╚═╝   ╚═════╝
```

<div align="center">

![42 Badge](https://img.shields.io/badge/42-cub3D-00BABC?style=for-the-badge&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![MiniLibX](https://img.shields.io/badge/Graphics-MiniLibX-FF6B6B?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

*Un motor 3D por raycasting inspirado en el legendario Wolfenstein 3D*

</div>

---

## ¿Qué es cub3D?

**cub3D** es un proyecto del currículo de [42 School](https://www.42.fr/) que consiste en construir desde cero un motor de renderizado 3D en primera persona usando la técnica del **raycasting**. El objetivo es crear una experiencia similar a los primeros videojuegos de disparos en primera persona (FPS): un mundo en 3D generado a partir de un mapa 2D, con texturas en las paredes, movimiento del jugador e iluminación básica.

Todo ello implementado íntegramente en **C**, sin librerías 3D ni motores externos, solo matemáticas puras y píxeles.

---

## La historia detrás: de Wolf3D a cub3D

### El nacimiento del FPS: *Wolfenstein 3D* (1992)

<div align="center">

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│     id Software, 1992 — John Carmack, John Romero,         │
│     Adrian Carmack, Tom Hall y Jay Wilbur                   │
│                                                             │
│     "We can make a 3D game that runs on a PC!"             │
│                          — John Carmack                     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

</div>

En 1992, un equipo de cinco personas llamado **id Software** publicó *Wolfenstein 3D*, considerado el padre del género FPS. El juego era sorprendente para su época: corredores tridimensionales, enemigos que te perseguían, armas en primera persona... todo funcionando en un PC con apenas 8 MHz de procesador.

El secreto no era ninguna magia gráfica compleja. Era una técnica brillante e ingeniosa llamada **raycasting**.

### Antes de Wolfenstein: los antecedentes

La idea no surgió de la nada. Años antes, títulos como *Maze War* (1974) o *Battlezone* (1980) habían explorado perspectivas en primera persona, pero eran lentos o corrían en hardware especializado. El mérito de **John Carmack** fue adaptar y optimizar el raycasting para que funcionara en tiempo real en hardware doméstico.

Poco después, id Software llevaría la idea aún más lejos con *DOOM* (1993), que usaba una técnica más avanzada (BSP trees), y más tarde *Quake* (1996), el primer FPS completamente en 3D real.

---

## ¿Qué es el Raycasting?

### La idea central

El **raycasting** (proyección de rayos) es una técnica de renderizado que simula una vista en 3D a partir de un mundo 2D. La idea es deceptivamente simple:

> Desde la posición del jugador, para cada columna de píxeles de la pantalla, se lanza un rayo en la dirección que el jugador está mirando. Cuando ese rayo golpea una pared, calculamos a qué distancia está. Cuanto más cerca está la pared, más alta la dibujamos en pantalla.

```
         MAPA 2D (vista cenital)
         ┌─────────────────────────┐
         │ # # # # # # # # # # # # │
         │ #                     # │
         │ #   P→→→→→→→→[HIT]   # │
         │ #     ↗              # │
         │ #   P→               # │
         │ #                     # │
         │ # # # # # # # # # # # # │
         └─────────────────────────┘
              P = Jugador, # = Pared

         RESULTADO EN PANTALLA (3D)
         ┌─────────────────────────┐
         │ ░░░░░░░░ cielo ░░░░░░░░ │
         │▓▓▓▓▓███████████▓▓▓▓▓▓▓▓│
         │▓▓▓▓▓███████████▓▓▓▓▓▓▓▓│  ← pared
         │▓▓▓▓▓███████████▓▓▓▓▓▓▓▓│
         │ ▒▒▒▒▒▒▒▒ suelo ▒▒▒▒▒▒▒▒│
         └─────────────────────────┘
```

### El algoritmo DDA

El corazón del raycasting es el algoritmo **DDA** (*Digital Differential Analysis*). Este algoritmo traza un rayo en el mapa de cuadrícula y calcula exactamente en qué celda impacta, de forma extremadamente eficiente.

```
Para cada columna x de la pantalla:
  1. Calcular la dirección del rayo según el ángulo de cámara
  2. Usar DDA para avanzar celda a celda en el mapa 2D
  3. Detectar impacto con una pared (N/S/E/W)
  4. Calcular la distancia perpendicular (evita el "fish-eye")
  5. Proyectar la altura de la pared en pantalla
  6. Dibujar la franja vertical de textura correspondiente
```

### ¿Por qué "distancia perpendicular"?

Sin corrección, los rayos diagonales parecen más largos que los frontales, generando una distorsión llamada **efecto ojo de pez** (*fish-eye effect*). La solución es calcular no la distancia real al punto de impacto, sino la **distancia perpendicular al plano de la cámara**:

```
                 Plano de cámara
                 ─────────────────
                       │
  rayo izquierdo  ╲    │    ╱ rayo derecho
                   ╲   │   ╱
                    ╲  │  ╱
                     ╲ │ ╱
                      ╲│╱
                       P  (jugador)

  distancia real ≠ distancia perpendicular  →  fish-eye
  distancia perpendicular = corrección necesaria
```

### Raycasting vs Raytracing: ¿cuál es la diferencia?

| Característica | Raycasting | Raytracing |
|:---|:---:|:---:|
| Año de popularización | 1992 | 2018+ (tiempo real) |
| Complejidad | Baja | Muy alta |
| Coste computacional | Muy bajo | Altísimo |
| Reflejos y sombras | No | Sí |
| Mundo representable | 2.5D (pseudo-3D) | 3D completo |
| Ejemplos | Wolfenstein 3D, DOOM | Metro Exodus, Cyberpunk 2077 |

> El **raycasting** es una simplificación que asume paredes verticales y suelo plano, lo que lo hace enormemente eficiente. El **raytracing** es la técnica "real" que simula el comportamiento físico de la luz, rebotando por la escena, calculando reflejos, refracciones y sombras con precisión fotorrealista — pero requiere GPUs de última generación.

---

## Características del proyecto

- **Motor 3D por raycasting** con algoritmo DDA
- **Texturas en las 4 caras** de las paredes (Norte, Sur, Este, Oeste)
- **Suelo y techo** con colores personalizables
- **Movimiento del jugador**: avanzar, retroceder, rotar izquierda/derecha
- **Rotación con el ratón** *(bonus)*
- **Minimapa** en pantalla *(bonus)*
- **Puertas** interactivas *(bonus)*
- **Sprites** animados *(bonus)*
- **Cielo y suelo texturizados** *(bonus)*
- Lectura de mapas desde ficheros `.cub`

---

## Formato del mapa `.cub`

Los mapas se definen en ficheros de texto con extensión `.cub`:

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Donde:
- `NO/SO/WE/EA` → rutas a las texturas de cada pared
- `F` → color RGB del suelo (*floor*)
- `C` → color RGB del techo (*ceiling*)
- `1` → pared, `0` → espacio libre
- `N/S/E/W` → posición inicial del jugador y orientación

---

## Compilación y uso

### Requisitos

- GCC o Clang
- MiniLibX (incluida en el proyecto)
- X11 / XOrg (Linux) o AppKit/OpenGL (macOS)

### Compilar

```bash
make
```

### Ejecutar

```bash
./cub3D maps/my_map.cub
```

### Controles

| Tecla | Acción |
|:---:|:---|
| `W` / `↑` | Avanzar |
| `S` / `↓` | Retroceder |
| `A` | Desplazarse a la izquierda (*strafe*) |
| `D` | Desplazarse a la derecha (*strafe*) |
| `←` | Rotar cámara izquierda |
| `→` | Rotar cámara derecha |
| `Ratón` | Rotar cámara *(bonus)* |
| `ESC` | Salir |

---

## Recursos y referencias

- 📖 [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — La referencia definitiva para entender el algoritmo
- 🎮 [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) — El código original de id Software
- 📚 [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Documentación de la librería gráfica de 42
- 🎥 [Making DOOM](https://www.youtube.com/watch?v=F-eCmFthedc) — El making-of del juego que llevó el raycasting al siguiente nivel

---

<div align="center">

Made with ❤️ and lots of `segfaults`

</div>
