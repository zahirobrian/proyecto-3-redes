#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// --- PROTOTIPOS DE FUNCIONES ---
// Convierte string "192.168.1.1" a un unsigned long para facilitar cálculos matemáticos
int convertirIPaDecimal(const char *ipString, unsigned long *ipDecimal);
// Convierte el valor numérico de vuelta a string con formato IP
void convertirDecimalaIP(unsigned long ip, char *buffer);
// Genera los 4 octetos de la máscara basándose en los bits CIDR (ej: /24 -> 255.255.255.0)
void obtenerMascaraSubred(int bits, int mascara[4]);

int main(int argc, char const *argv[])
{
    // Buffers para almacenar las cadenas de texto de las IPs
    char ipString[16], redString[16], broadcastString[16], hostMinString[16], hostMaxString[16];
    // Variables para manejo numérico de las direcciones (unsigned long garantiza 32 bits positivos)
    unsigned long ipDecimal=0, red, broadcast, hostMin, hostMax, ipTotales=1;
    int mask=-1, mascara[4];

    // --- ENTRADA DE DATOS: IP ---
    // Bucle infinito hasta que el usuario ingrese una IP con formato válido
    while(1){
        printf("\nIntroduce una direccion IP: ");
        scanf("%15s", ipString);
        // La función retorna 1 si la conversión es exitosa
        if(convertirIPaDecimal(ipString, &ipDecimal))
            break;
        else
            printf("Formato de IP invalido, intenta nuevamente.\n");
    }

    // --- ENTRADA DE DATOS: MÁSCARA ---
    // Validación de rango CIDR (0-32)
    while(1){
        printf("Introduce la cantidad de bits de la mascara de subred: ");
        scanf("%d", &mask);
        if(mask>=0 && mask<=32)
            break;
        else{
            printf("Mascara Invalida. Itroduzca un numero entre 0 y 32.\n");
            // Limpieza del buffer de entrada en caso de error
            while(getchar()!='\n');
        }
    }

    // --- CÁLCULOS DE RED ---
    // 1. Calcular total de direcciones en el bloque: 2^(32 - máscara)
    ipTotales=(unsigned long)pow(2, 32-mask);

    // 2. Calcular ID de Red
    // Truco matemático entero: Al dividir y multiplicar por el tamaño del bloque,
    // se eliminan los "restos" (bits de host), dejando la base de la red.
    red=(ipDecimal/ipTotales)*ipTotales;

    // 3. Calcular Broadcast: Dirección de red + total de IPs - 1
    broadcast=red+ipTotales-1;

    // 4. Calcular rango de hosts (validando si es una red punto a punto /31 o /32)
    hostMin=(ipTotales>2)?(red+1):red;
    hostMax=(ipTotales>2)?(broadcast-1):broadcast;

    // --- CONVERSIÓN A FORMATO LEGIBLE ---
    convertirDecimalaIP(red, redString);
    convertirDecimalaIP(broadcast, broadcastString);
    convertirDecimalaIP(hostMin, hostMinString);
    convertirDecimalaIP(hostMax, hostMaxString);
    obtenerMascaraSubred(mask, mascara);

    // --- SALIDA DE RESULTADOS ---
    printf("\nIngresaste la IP %s", ipString);
    printf("\nHost asignables: %lu", ipTotales-2); // Se resta red y broadcast
    printf("\nDireccion de red: %s/%d", redString, mask);
    printf("\nDireccion de broadcast: %s", broadcastString);
    printf("\nRango de host validos: %s - %s", hostMinString, hostMaxString);
    printf("\nMascara de subred: %d.%d.%d.%d\n", mascara[0], mascara[1], mascara[2], mascara[3]);
    
    printf("\nPresiona Enter para salir...");
    getchar();
    getchar();
    return 0;
}

// Implementación: Parsea "X.X.X.X" y calcula el valor decimal total
int convertirIPaDecimal(const char *ipString, unsigned long *ipDecimal){
    unsigned long oct1, oct2, oct3, oct4;
    // sscanf devuelve el número de items asignados correctamente (deben ser 4)
    if(sscanf(ipString, "%u.%u.%u.%u", &oct1, &oct2, &oct3, &oct4)!=4)
        return 0;
    // Validación básica de rango de octetos (0-255)
    if(oct1>255 || oct2>255 || oct3>255 || oct4>255)
        return 0;
    // Suma ponderada: Octeto1 * 256^3 + Octeto2 * 256^2...
    *ipDecimal=(oct1*256*256*256)+(oct2*256*256)+(oct3*256)+(oct4);
    return 1;
}

// Implementación: Descompone el unsigned long en 4 octetos mediante división y módulo
void convertirDecimalaIP(unsigned long ip, char *buffer){
    int oct1=(ip/(256*256*256))%256;
    int oct2=(ip/(256*256))%256;
    int oct3=(ip/(256))%256;
    int oct4=ip%256;
    sprintf(buffer, "%d.%d.%d.%d", oct1, oct2, oct3, oct4);
}

// Implementación: Llena un array con los valores decimales de la máscara
void obtenerMascaraSubred(int bits, int mascara[4]){
    for(int i=0; i<4; i++){
        if(bits>=8){
            // Si quedan 8 o más bits, el octeto es 255
            mascara[i]=255;
            bits-=8;
        }
        else if(bits<8){
            // Si quedan menos de 8 bits, calculamos el valor decimal sumando potencias de 2
            int valor=0;
            for(int j=0; j<bits; j++){
                valor+=(int)pow(2, 7-j);
            }
            mascara[i]=valor;
            bits=0;
        }
        else if(bits==0)
            // Si no quedan bits, el octeto es 0
            mascara[i]=0;
    }
}