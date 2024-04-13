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
    plt.figure(figsize=(10, 5))
    plt.plot(mejores, label='Mejores Aptitudes',marker='o',linestyle='-' )
    plt.plot(promedios, label='Aptitud Promedio',marker='o', linestyle='-')
    plt.plot(peores, label='Peores Aptitudes',marker='o', linestyle='-')


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
