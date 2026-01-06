============================================================
 HERRAMIENTAS DE CÁLCULO DE REDES (IP Y VLSM)
============================================================

Este archivo contiene las instrucciones para ejecutar las dos herramientas de red incluidas en este proyecto: una calculadora VLSM en Python y una calculadora IP en C.

------------------------------------------------------------
 1. CALCULADORA VLSM (PYTHON)
------------------------------------------------------------
Archivo: CalculadoraVLSM.py
Descripción: Script para dividir una red utilizando Máscara de Subred de Longitud Variable (VLSM).

REQUISITOS PREVIOS:
- Tener instalado Python 3.x.
- Verificar instalación: escriba "python --version" en su terminal.

INSTRUCCIONES DE EJECUCIÓN:
1. Abra su terminal o línea de comandos (CMD/PowerShell).
2. Navegue hasta la carpeta donde guardó el archivo.
3. Ejecute el siguiente comando:

   python CalculadoraVLSM.py

   (Nota: En Linux/Mac puede requerir: python3 CalculadoraVLSM.py)

EJEMPLO DE USO:
El programa solicitará:
- Red principal (ej: 192.168.1.0)
- Prefijo (ej: 24)
- Número de subredes
- Cantidad de hosts para cada subred

------------------------------------------------------------
 2. CALCULADORA DE IP (LENGUAJE C)
------------------------------------------------------------
Archivo: calculadoraIP.c
Descripción: Programa para obtener dirección de red, broadcast, rango de hosts y máscara decimal a partir de una IP y un CIDR.

REQUISITOS PREVIOS:
- Un compilador de C (GCC recomendado).
  * Windows: MinGW.
  * Linux: build-essential.
  * macOS: Xcode Command Line Tools.

INSTRUCCIONES DE COMPILACIÓN:
Debido al uso de la librería matemática <math.h>, use el flag "-lm" (especialmente en Linux).

1. Abra su terminal.
2. Navegue a la carpeta del archivo.
3. Ejecute:

   gcc calculadoraIP.c -o calculadoraIP -lm

INSTRUCCIONES DE EJECUCIÓN:
Una vez compilado, ejecute el archivo generado.

- En Windows:
  calculadoraIP.exe

- En Linux / macOS:
  ./calculadoraIP

EJEMPLO DE USO:
El programa solicitará:
- Dirección IP (ej: 10.0.0.55)
- Bits de máscara (ej: 8)

------------------------------------------------------------
 SOLUCIÓN DE PROBLEMAS COMUNES
------------------------------------------------------------
* Si "python" no se reconoce: Asegúrese de agregar Python al PATH durante la instalación.
* Error "undefined reference to pow" en C: No olvide agregar "-lm" al final del comando de compilación gcc.
* Permisos denegados (Linux/Mac): Ejecute "chmod +x calculadoraIP" para dar permisos de ejecución.
