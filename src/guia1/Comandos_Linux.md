# Guia de ejercicios N1.2 Linea de comandos de Linux

## Ejercicio 2 
---
Man sirve para consultar el manual de un comando

## Ejercicio 3
---
Estoy usando zsh

## Ejercicio 5
--- 

Podes exportar asi
```bash
export FOO='BAR'
```

## Ejercicio 6
--- 
El prompt es el texto que muestra la consola para indicarte que está lista para recibir un comando. No es un comando en sí, ni una herramienta, sino una señal visual del sistema.

## Ejercicio 7
Podes modificar el prompt exportandolo como variable en el sistema o simplemente, si lo tenes instalado, cambiar de prompt escribiendo el prompt que queres usar en la terminal.
```bash
zsh # Cambia a ZSH
```

## Ejercicio 8
Se puede mover utilizando ambas

```bash
cd /home/foo
```
o si esas en home
```bash
cd foo
```

## Ejercicio 9

ls sirve para listar los archivos en una carpeta
puede ser en la actual o en otra ruta.

¡Vamos con todo! Te explico cada punto paso a paso, bien claro y directo.

---

## a. Ejecutar `ls -l` y analizar su salida

El comando `ls -l` **muestra los archivos en formato largo** ("long format").

### Ejemplo de salida:

```bash
-rw-r--r--  1 nahuel users   1042 Jul  2 18:22 archivo.txt
```

### Significado de cada columna:

| Columna       | Significado                                 |
| ------------- | ------------------------------------------- |
| `-rw-r--r--`  | **Permisos** del archivo                    |
| `1`           | **Número de enlaces** duros (hard links)    |
| `nahuel`      | **Propietario** (usuario dueño del archivo) |
| `users`       | **Grupo** al que pertenece el archivo       |
| `1042`        | **Tamaño** del archivo en bytes             |
| `Jul 2 18:22` | **Fecha y hora** de la última modificación  |
| `archivo.txt` | **Nombre** del archivo                      |

---

## b. ¿Qué son `.` y `..` en cada directorio?

* `.`  → Representa el **directorio actual**.
* `..` → Representa el **directorio padre** (el que lo contiene).

### Ejemplo:

Si estás en `/home/nahuel/Documentos`, entonces:

* `.`  → `/home/nahuel/Documentos`
* `..` → `/home/nahuel`

Sirven para navegar con `cd .` (te quedás en el mismo lugar) o `cd ..` (subís un nivel).

---

## c. Diferencias entre variantes del comando `ls`

### i. `ls -t`

Ordena los archivos por **fecha de modificación**, del más **reciente al más viejo**.

---

### ii. `ls -lt`

Muestra el listado en **formato largo (`-l`)** y lo **ordena por fecha (`-t`)**.

> Combina ambos: te da detalles + los más recientes primero.


### iii. `ls -la`

* `-l`: formato largo
* `-a`: muestra **todos los archivos**, incluyendo los **ocultos** (los que empiezan con `.`)

> Verás cosas como `.bashrc`, `..`, `.` que normalmente están ocultos.


### iv. `ls -lh`

* `-l`: formato largo
* `-h`: **"human-readable"** — muestra los tamaños en **KB, MB, GB**, etc.

> Ejemplo: `1048576` se verá como `1.0M`


### v. `ls -s`

Muestra el tamaño en **bloques** (no en bytes), al principio de cada línea.

> Similar a `du`, útil para ver cuánto espacio en disco ocupa un archivo, no solo su contenido.


### vi. `ls -i`

Muestra el **número de inodo** de cada archivo.

> Cada archivo en Linux tiene un inodo, que es su "número de identidad" en el sistema de archivos.



### vii. `ls -F`

Agrega un **símbolo al final** del nombre de cada archivo para identificar su tipo:

| Símbolo | Significa                  |             |
| ------- | -------------------------- | ----------- |
| `/`     | Directorio                 |             |
| `*`     | Ejecutable                 |             |
| `@`     | Enlace simbólico (symlink) |             |
| \`      | \`                         | FIFO (pipe) |

> Ejemplo: `script.sh*` te indica que es un archivo ejecutable.

---

¿Querés que te lo arme todo junto en una tabla resumen para imprimir o estudiar? Te lo preparo en un toque.
