function mapa_cerrado(mapa) {
    let filas = mapa.length;
    let columnas = mapa[0].length;
    
    // Verificar bordes del mapa
    for (let i = 0; i < filas; i++) {
      if (mapa[i][0] === 32) {
        if (!hay_camino(mapa, i, 0)) {
          return false;
        }
      }
      if (mapa[i][columnas-1] === 32) {
        if (!hay_camino(mapa, i, columnas-1)) {
          return false;
        }
      }
    }
    
    for (let j = 0; j < columnas; j++) {
      if (mapa[0][j] === 32) {
        if (!hay_camino(mapa, 0, j)) {
          return false;
        }
      }
      if (mapa[filas-1][j] === 32) {
        if (!hay_camino(mapa, filas-1, j)) {
          return false;
        }
      }
    }
    
    // Mapa está cerrado
    return true;
  }
  
  function hay_camino(mapa, i, j) {
    let filas = mapa.length;
    let columnas = mapa[0].length;
    
    let visitado = new Array(filas).fill().map(() => new Array(columnas).fill(false));
    let queue = [[i, j]];
    
    while (queue.length > 0) {
      let [x, y] = queue.shift();
      if (x === 0 || x === filas-1 || y === 0 || y === columnas-1) {
        return false;  // Se llegó al borde del mapa
      }
      
      if (visitado[x][y]) {
        continue;
      }
      visitado[x][y] = true;
      
      if (mapa[x-1][y] === 32) {
        queue.push([x-1, y]);
      }
      if (mapa[x+1][y] === 32) {
        queue.push([x+1, y]);
      }
      if (mapa[x][y-1] === 32) {
        queue.push([x, y-1]);
      }
      if (mapa[x][y+1] === 32) {
        queue.push([x, y+1]);
      }
    }
    
    return true;  // No se llegó al borde del mapa, hay un camino hacia el exterior
  }
  
  // Matriz de enteros correspondiente al nuevo mapa
  let mapa_nuevo =
                [
                    [32, 32, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 32, 32, 32, 32],
                    [32, 49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 32, 32],
                    [32, 49, 49, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 32],
                    [32, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 32, 32],
                    [32, 49, 49, 32, 49, 32, 49, 32, 49, 49, 49, 49, 49, 32, 32, 32]
                ]

if (mapa_cerrado(mapa_nuevo))
    console.log("El mapa está cerrado correctamente por 1");
else
    console.log("El mapa no está cerrado correctamente por 1");