def mapa_cerrado(mapa):
    filas = len(mapa)
    columnas = len(mapa[0])
    
    # Verificar bordes del mapa
    for i in range(filas):
        if mapa[i][0] == ' ':
            if not hay_camino(mapa, i, 0):
                return False
        if mapa[i][columnas-1] == ' ':
            if not hay_camino(mapa, i, columnas-1):
                return False
    
    for j in range(columnas):
        if mapa[0][j] == ' ':
            if not hay_camino(mapa, 0, j):
                return False
        if mapa[filas-1][j] == ' ':
            if not hay_camino(mapa, filas-1, j):
                return False
    
    # Mapa está cerrado
    return True

def hay_camino(mapa, i, j):
    filas = len(mapa)
    columnas = len(mapa[0])
    
    visitado = [[False for _ in range(columnas)] for _ in range(filas)]
    queue = [(i, j)]
    
    while queue:
        x, y = queue.pop(0)
        if x == 0 or x == filas-1 or y == 0 or y == columnas-1:
            return False  # Se llegó al borde del mapa
        
        if visitado[x][y]:
            continue
        visitado[x][y] = True
        
        if mapa[x-1][y] == ' ':
            queue.append((x-1, y))
        if mapa[x+1][y] == ' ':
            queue.append((x+1, y))
        if mapa[x][y-1] == ' ':
            queue.append((x, y-1))
        if mapa[x][y+1] == ' ':
            queue.append((x, y+1))
    
    return True  # No se llegó al borde del mapa, hay un camino hacia el exterior

# Matriz de enteros correspondiente al nuevo mapa
mapa_nuevo = [  [32, 32, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 32, 32, 32, 32],
                [32, 49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 32, 32],
                [32, 49, 49, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 32],
                [32, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 32, 32],
                [32, 49, 49, 32, 49, 32, 49, 32, 49, 32, 49, 49, 49, 32, 32, 32]
]

if mapa_cerrado(mapa_nuevo):
    print("El mapa está cerrado correctamente por 1")
else:
    print("El mapa no está cerrado correctamente por 1")