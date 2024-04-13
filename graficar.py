import matplotlib.pyplot as plt

def leer_datos(filename):
    mejores = []
    promedios = []
    peores = []

    with open(filename, 'r') as file:
        lines = file.readlines()
        mejores = [int(x.strip()) for x in lines[0].split(':')[1].split(',') if x.strip().isdigit()]
        promedios = [float(x.strip()) for x in lines[1].split(':')[1].split(',') if x.strip()]
        peores = [int(x.strip()) for x in lines[2].split(':')[1].split(',') if x.strip().isdigit()]

    return mejores, promedios, peores

def graficar(mejores, promedios, peores):
    generaciones = list(range(1, len(mejores) + 1))
    
    plt.figure(figsize=(10, 5))
    plt.plot(generaciones, mejores, label='Mejores Aptitudes')
    plt.plot(generaciones, promedios, label='Aptitud Promedio', linestyle='--')
    plt.plot(generaciones, peores, label='Peores Aptitudes', linestyle=':')
    
    plt.xlabel('Generación')
    plt.ylabel('Aptitud')
    plt.title('Evolución de las Aptitudes a lo Largo de las Generaciones')
    plt.legend()
    plt.grid(True)
    plt.show()

# Ruta al archivo de texto con los datos
filename = 'estadisticas.txt'

# Leer datos del archivo
mejores, promedios, peores = leer_datos(filename)

# Graficar los datos
graficar(mejores, promedios, peores)
