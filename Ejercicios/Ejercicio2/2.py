class Evento:
    def __init__(self, nom, fec):
        self.nombre = nom
        self.fecha = fec
        self.asistentes = []

    def agregarAsistente(self, asistente):
        self.asistentes.append(asistente)
        self.asistentes.sort()

    def mostrarAsistentes(self):
        for asistente in self.asistentes:
            print(asistente)

class Organizador:
    def __init__(self):
        self.eventos = []

    def agregarEvento(self, nombre, fecha):
        if any(evento.nombre == nombre for evento in self.eventos):
            print(f"Evento con el nombre {nombre} ya existe.")
            return
        self.eventos.append(Evento(nombre, fecha))
        print("Evento agregado exitosamente.")

    def agregarAsistente(self, nombreEvento, asistente):
        for evento in self.eventos:
            if evento.nombre == nombreEvento:
                evento.agregarAsistente(asistente)
                print("Asistente agregado exitosamente.")
                return
        print("Evento no encontrado.")

    def mostrarAsistentes(self, nombreEvento):
        for evento in self.eventos:
            if evento.nombre == nombreEvento:
                evento.mostrarAsistentes()
                return
        print("Evento no encontrado.")

    def buscarEventosPorFecha(self, fecha):
        encontrados = False
        for evento in self.eventos:
            if evento.fecha == fecha:
                print(f"Evento: {evento.nombre}")
                encontrados = True
        if not encontrados:
            print(f"No se encontraron eventos en la fecha {fecha}")

def mostrarMenu():
    print("Menu de Gestion de Eventos")
    print("1. Agregar evento")
    print("2. Agregar asistente a evento")
    print("3. Mostrar asistentes de un evento")
    print("4. Buscar eventos por fecha")
    print("5. Salir")

    organizador = Organizador()
    opcion = 0

    while opcion != 5:
        mostrarMenu()
        opcion = int(input("Seleccione una opcion: "))

        if opcion == 1:
            nombre = input("Ingrese nombre del evento: ")
            fecha = input("Ingrese fecha del evento: ")
            organizador.agregarEvento(nombre, fecha)
        elif opcion == 2:
            nombre = input("Ingrese nombre del evento: ")
            asistente = input("Ingrese nombre del asistente: ")
            organizador.agregarAsistente(nombre, asistente)
        elif opcion == 3:
            nombre = input("Ingrese nombre del evento: ")
            organizador.mostrarAsistentes(nombre)
        elif opcion == 4:
            fecha = input("Ingrese fecha del evento (YYYY-MM-DD): ")
            organizador.buscarEventosPorFecha(fecha)
        elif opcion == 5:
            print("Saliendo...")
        else:
            print("Opcion no valida. Intente nuevamente.")
