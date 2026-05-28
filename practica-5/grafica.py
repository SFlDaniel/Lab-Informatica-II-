import matplotlib.pyplot as plt

# Guardar datos de trayectorias
trayectorias = {}

# Abrir archivo generado por la simulacion
with open("trayectoria.txt", "r") as archivo:

    for linea in archivo:

        # Ignorar comentarios
        if linea.startswith("#"):
            continue

        datos = linea.split()

        tiempo = float(datos[0])
        pid    = int(datos[1])
        x      = float(datos[2])
        y      = float(datos[3])

        # Crear estructura si no existe
        if pid not in trayectorias:
            trayectorias[pid] = {
                "x": [],
                "y": []
            }

        trayectorias[pid]["x"].append(x)
        trayectorias[pid]["y"].append(y)

# Dibujar cada particula
for pid in trayectorias:

    plt.plot(
        trayectorias[pid]["x"],
        trayectorias[pid]["y"],
        label=f"Particula {pid}"
    )

# Configuracion de la grafica
plt.title("Trayectoria de Particulas")
plt.xlabel("Posicion X")
plt.ylabel("Posicion Y")

plt.legend()
plt.grid(True)

# Invertir eje Y para parecerse a Qt
plt.gca().invert_yaxis()

# Mostrar grafica
plt.show()