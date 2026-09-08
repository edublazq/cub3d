# cub3d — errores conocidos (sin corregir)

Listado de bugs identificados por revisión de código (no se ha tocado nada del código fuente). Todos, salvo que se indique lo contrario, se disparan **dentro de `check_arg()` / `get_data_for_map()`, antes de abrir la ventana MLX42**, así que se pueden reproducir sin pantalla.

## Críticos (segfault / heap overflow)

### 1. `open_map()` usa el ANCHO del mapa como límite de filas
**`src/map_checkers.c`, función `open_map()`**
```c
while (y < max)          // max = "longest" = ANCHO del mapa, no el alto
{
    while (x < max) { ... map[y - 1][x] ... map[y + 1][x] ... }
    y++;
}
```
`map` solo tiene `altura + 1` punteros de fila reservados. Si el ancho es mayor que el alto (muy habitual, `resources/maps/first_map.cub` ya lo cumple: ancho ~34, alto ~14), el bucle acaba leyendo `map[y]` mucho más allá del array de punteros → lectura fuera de rango → segfault casi seguro.
Además, sin depender de eso: `map[y-1]` cuando `y==0` y `map[y+1]` cuando `y` es la última fila leen una posición fuera del array aunque el mapa sea cuadrado — cualquier tile transitable en la primera o última fila del mapa lo dispara.

**Repro:** `./cub3d resources/maps/first_map.cub` (ya está en el repo, sin tocarlo).

### 2. Underflow de `size_t` en el cálculo de `longest` → heap-buffer-overflow de escritura
**`src/map_checkers.c`, líneas ~100-113**
```c
if (ft_strlen(content[i]) > longest)
    longest = ft_strlen(content[i]) - 2;
```
Si la primera línea del mapa (justo después de la cabecera de 8 líneas) está vacía (`strlen == 1`), `longest = 1 - 2` desborda `size_t` a ~`SIZE_MAX`. El `malloc(longest + 3)` que sigue **no comprueba NULL** y, por el propio desborde, en realidad envuelve de vuelta a `malloc(2)` (2 bytes). Las filas de mapa normales que vienen después se copian con `map_rectangulizer()` sobre ese buffer de 2 bytes → **escritura fuera de los límites del heap**, no un simple NULL-deref.

**Repro:** cabecera válida + una línea de mapa vacía justo tras el separador, seguida de filas normales.

### 3. `map->grid[0]` desreferenciado sin comprobar que haya alguna fila
**`src/data/get_data_for_map.c:53`**
```c
map->width = ft_strlen(map->grid[0]);
```
Si `get_map()` devuelve un grid con 0 filas (`grid[0] == NULL`), esto llama a `ft_strlen(NULL)` → segfault. En el flujo normal está protegido por `check_arg`, pero como hay **dos parsers independientes que releen el fichero por separado** (ver punto siguiente), un fichero que cambie entre la primera y la segunda lectura (p. ej. un FIFO) puede hacer que el segundo parser vea un cuerpo de mapa vacío aunque el primero validara uno completo.

### 4. Dos parsers de mapa completamente independientes y divergentes
- `check_arg()` → `map_checkers.c`: valida y construye su propio grid temporal.
- `get_data_for_map()` → `data/map_grid.c`: **vuelve a abrir y leer el fichero desde cero** y construye el grid real con lógica distinta (`strlen(x)-1` en vez de `strlen(x)-2`, su propio `get_map`/`longest_line`).

Pasar la validación del primero no garantiza que el segundo sea seguro (y viceversa). Es la causa raíz de los puntos 1-3 y de que ambos tengan bugs de índices distintos entre sí.

### 5. `content[8]` accedido sin comprobar cuántas líneas tiene el fichero (nuevo, "H")
**`src/map_checkers.c`, `check_map()` y `count_players()`**
Ambas funciones empiezan a leer en `i = 8` asumiendo que la cabecera siempre mide 8 líneas exactas. Si el fichero tiene 0, 1 o exactamente 8 líneas, `content` se reservó con menos de 9 huecos → lectura fuera de rango del array de punteros.

**Repro:** fichero vacío, fichero de 1 línea, fichero con exactamente las 8 líneas de cabecera y ningún mapa.

### 6. Fila de mapa sin `\n` final → escritura sin límite (nuevo, "I")
**`map_rectangulizer()`, duplicada en `src/map_checkers.c` y `src/data/map_grid.c`**
```c
while (line[i] != '\n')
{
    map[i] = line[i];
    i++;
}
```
Nunca comprueba `'\0'`. Si la última fila del `.cub` no termina en salto de línea (fichero guardado sin línea en blanco final, algo muy común), este bucle sigue leyendo memoria del heap más allá del string hasta encontrar por casualidad un byte `'\n'`, copiando basura sin límite en un buffer pequeño. Probablemente el crash más fácil de reproducir de todos los de esta lista.

## Validación rota (no crashea, pero acepta entradas inválidas)

### 7. `check_textures()` — lectura fuera de rango en líneas de textura muy cortas
**`src/file_checkers.c`**, `&line[len - 5]` sin comprobar que `len >= 5`. Una línea `NO\n` o similar hace que `len - 5` sea negativo → lectura antes del buffer.

### 8. `check_colors()` — el filtro de dígitos es un no-op
**`src/file_checkers.c`**
```c
if ((line[i] < '0' && line[i] > '9') && line[i] != ',')
```
Ningún carácter puede ser a la vez menor que `'0'` Y mayor que `'9'` — la condición es siempre falsa (debería ser `||`). Colores basura como `F abc,xyz,123` pasan la validación sin problema porque `ft_atoi` de tokens no numéricos devuelve `0`, que cae dentro de 0-255.

### 9. `extract_texture_path()` — underflow teórico, probablemente inalcanzable
**`src/data/map_header.c`**: `ft_substr(line, 3, ft_strlen(line) - 4)` desborda si la línea mide menos de 4 caracteres, pero `ft_substr` de libft clampa internamente y el bug #7 ya rechaza esas líneas antes de llegar aquí. Se deja anotado por si `check_textures` se corrige en el futuro y deja de servir de escudo.

### 10. `longest` mal recalculado → última fila y última columna nunca se comprueban
**`src/map_checkers.c`**: por cómo se recalcula `longest` (comparando contra un valor ya `-2`), converge a `L-1` en vez de `L`. `open_map(map, longest)` entonces nunca inspecciona la fila ni la columna finales del mapa → un mapa abierto exactamente por el borde inferior o derecho pasa la validación como si estuviera cerrado.

## Memory leaks

### 11. Textura ya cargada no se libera si falla una posterior
**`src/data/map_header.c` / `src/data/get_data_for_map.c:47-51`**: si la textura `NO` carga bien pero `SO` (o cualquiera de las siguientes) falla, `get_data_for_map` libera `content`/`aux` pero **no** la `mlx_texture_t*` de `NO` que ya se había cargado con `mlx_load_png`. `main.c` solo llama a `free_textures()` en el camino de éxito total.

### 12. (Menor) fd sin cerrar si `malloc` falla entre dos `open()`
**`src/check.c`, `read_file()`**: abre el fichero dos veces (una para contar líneas, otra para leer). Si el `malloc` de `content` falla justo después del primer `open`, ese fd nunca se cierra. Poco relevante en la práctica (solo ocurre ya en un estado de casi-OOM).

## Código muerto / inconsistencias menores (no crashean)

- **`config_player()`** declarada en `include/cub3d.h` pero **sin implementación en ningún `.c`** y sin ninguna llamada — declaración huérfana.
- **`draw_map`/`draw_player`/`draw_square`/`draw_line`/`draw_direction`** (`src/render/draw_minimap.c`) están completos pero **no se llaman desde ningún sitio** del bucle principal — minimapa muerto, no forma parte del render actual.
- **`map_rectangulizer` duplicada** con implementaciones ligeramente distintas en `src/map_checkers.c` y `src/data/map_grid.c` — mismo nombre, comportamiento distinto, riesgo de que diverjan aún más si se edita una sin la otra.
- **Orientación E/W posiblemente intercambiada** en `src/data/get_data_for_player.c`: con `x` creciendo hacia la derecha, `'E'` debería dar `orientation.x = +1` y `'W'` debería dar `orientation.x = -1`; el código hace lo contrario. No rompe el juego (es internamente consistente), pero si alguien coloca una `E` en su mapa esperando mirar al este, en realidad mirará al oeste.

---
*Generado por revisión estática de código (lectura del código fuente, sin ejecutar el binario ni modificar nada). No incluye confirmación en vivo con gdb/valgrind/ASan — eso quedaría como siguiente paso si se quiere verificar cada uno antes de arreglarlo.*
