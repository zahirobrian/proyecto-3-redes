import math  # Importamos la librería math para usar log2 y ceil

def calcular_vlsm():
    print("\n=== CALCULADORA VLSM ===")
    
    # --- BLOQUE DE ENTRADA DE DATOS ---
    # Solicitamos la IP base y el prefijo actual
    ip = input("Ingrese la red principal (ej: 192.168.1.0): ")
    prefijo = int(input("Ingrese el prefijo de red (ej: 24): "))
    num_subredes = int(input("Ingrese el número de subredes: "))
    
    # Lista para almacenar los requisitos de hosts de cada subred
    hosts_por_subred = []
    for i in range(num_subredes):
        hosts = int(input(f"Número de hosts para la subred {i+1}: "))
        hosts_por_subred.append(hosts)
    
    # --- LOGICA VLSM: ORDENAMIENTO ---
    # VLSM requiere asignar primero las subredes más grandes.
    # Ordenamos la lista de hosts de mayor a menor (descendente).
    hosts_por_subred.sort(reverse=True)
    
    # --- VALIDACIÓN DE CAPACIDAD ---
    # Calculamos si la red base tiene suficiente espacio para todos los hosts solicitados
    hosts_totales = sum(hosts_por_subred)
    # Fórmula de hosts disponibles: 2^(32 - prefijo) - 2 (red y broadcast)
    hosts_disponibles = (2 ** (32 - prefijo)) - 2
    
    if hosts_totales > hosts_disponibles:
        print(f"\n¡Error! La red {ip}/{prefijo} solo soporta {hosts_disponibles} hosts.")
        return
    
    # --- PROCESO DE CÁLCULO DE SUBREDES ---
    subredes = []
    # Convertimos la IP string "192.168.1.0" a una lista de enteros [192, 168, 1, 0]
    ip_actual = list(map(int, ip.split('.')))
    
    # Iteramos sobre cada solicitud de hosts (ya ordenadas)
    for i, hosts in enumerate(hosts_por_subred):
        # 1. Calcular bits de host (n) necesarios
        # Fórmula: n = log2(hosts + 2). El +2 es por la dirección de Red y Broadcast.
        # Usamos ceil para redondear al entero superior más cercano.
        n = math.ceil(math.log2(hosts + 2))
        
        # 2. Calcular nueva máscara
        # R = Bits prestados (no usado explícitamente en la máscara final pero parte de la lógica)
        # Nueva máscara (M) = 32 - bits de host (n)
        R = (32 - prefijo) - n  
        M = prefijo + R  # Simplificado: M = 32 - n
        
        # 3. Calcular el salto (tamaño del bloque) en el último octeto
        # Esto determina cuánto sumar para llegar a la siguiente subred.
        bits_ultimo_octeto = max(0, M - 24)
        salto = 2 ** (8 - bits_ultimo_octeto) # Cantidad de IPs en el bloque
        
        # --- ASIGNACIÓN DE DIRECCIONES ---
        # Convertimos la lista de octetos actual a string para guardar la IP de Red
        ip_subred = ".".join(map(str, ip_actual))
        
        # Primer Host utilizable: IP de Red + 1 en el último octeto
        primer_host = ip_actual.copy()
        primer_host[3] += 1
        
        # Último Host utilizable: IP de Red + (Tamaño Bloque - 2)
        ultimo_host = ip_actual.copy()
        ultimo_host[3] += (2 ** (8 - bits_ultimo_octeto)) - 2
        
        # Broadcast: IP de Red + (Tamaño Bloque - 1)
        broadcast = ip_actual.copy()
        broadcast[3] += (2 ** (8 - bits_ultimo_octeto)) - 1
        
        # Guardamos los datos calculados en un diccionario
        subredes.append({
            "Subred": i + 1,
            "Hosts": hosts,
            "IP Subred": ip_subred,
            # Cálculo visual de la máscara decimal (ej: 255.255.255.192)
            "Máscara": f"/{M} (255.255.255.{256 - (2 ** (8 - bits_ultimo_octeto))})",
            "Primer Host": ".".join(map(str, primer_host)),
            "Último Host": ".".join(map(str, ultimo_host)),
            "Broadcast": ".".join(map(str, broadcast))
        })
        
        # --- PREPARAR SIGUIENTE ITERACIÓN ---
        # Actualizamos la IP base sumando el tamaño del bloque actual
        # Nota: Esta lógica asume subneteo en el 4to octeto principalmente.
        ip_actual[3] += (2 ** (8 - bits_ultimo_octeto))
    
    # --- IMPRESIÓN DE RESULTADOS ---
    print("\nRESULTADOS:")
    print("-" * 100)
    # Formato de tabla con espaciado fijo
    print(f"{'Subred':<8} {'Hosts':<8} {'IP Subred':<15} {'Máscara':<25} {'Primer Host':<15} {'Último Host':<15} {'Broadcast':<15}")
    print("-" * 100)
    for subred in subredes:
        print(f"{subred['Subred']:<8} {subred['Hosts']:<8} {subred['IP Subred']:<15} {subred['Máscara']:<25} {subred['Primer Host']:<15} {subred['Último Host']:<15} {subred['Broadcast']:<15}")

# Punto de entrada del script
calcular_vlsm()