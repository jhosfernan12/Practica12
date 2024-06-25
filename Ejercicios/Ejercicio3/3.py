class Contacto:
    def __init__(self, nom, tel, em):
        self.nombre = nom
        self.telefono = tel
        self.email = em

    def mostrarContacto(self):
        print("Nombre:", self.nombre)
        print("Telefono:", self.telefono)
        print("Email:", self.email)

class Agenda:
    def __init__(self):
        self.contactos = []

    def agregarContacto(self, nombre, telefono, email):
        self.contactos.append(Contacto(nombre, telefono, email))
        print("Contacto agregado exitosamente.")

    def buscarContacto(self, nombre):
        encontrado = False
        for contacto in self.contactos:
            if contacto.nombre == nombre:
                contacto.mostrarContacto()
                encontrado = True
                break
        if not encontrado:
            print("Contacto no encontrado.")

    def actualizarContacto(self, nombre, nuevoTelefono, nuevoEmail):
        encontrado = False
        for contacto in self.contactos:
            if contacto.nombre == nombre:
                contacto.telefono = nuevoTelefono
                contacto.email = nuevoEmail
                print("Contacto actualizado exitosamente.")
                encontrado = True
                break
        if not encontrado:
            print("Contacto no encontrado.")

    def mostrarContactosOrdenados(self):
        contactos_ordenados = sorted(self.contactos, key=lambda c: c.nombre)
        for contacto in contactos_ordenados:
            contacto.mostrarContacto()
            print("---------------------")

def mostrarMenu():
    print("Menu de Gestion de Contactos")
    print("1. Agregar contacto")
    print("2. Buscar contacto por nombre")
    print("3. Actualizar contacto")
    print("4. Mostrar contactos ordenados alfabeticamente")
    print("5. Salir")

    agenda = Agenda()
    opcion = 0

    while opcion != 5:
        mostrarMenu()
        opcion = int(input("Seleccione una opcion: "))

        if opcion == 1:
            nombre = input("Ingrese nombre del contacto: ")
            telefono = input("Ingrese numero de telefono: ")
            email = input("Ingrese direccion de correo electronico: ")
            agenda.agregarContacto(nombre, telefono, email)
        elif opcion == 2:
            nombre = input("Ingrese nombre del contacto a buscar: ")
            agenda.buscarContacto(nombre)
        elif opcion == 3:
            nombre = input("Ingrese nombre del contacto a actualizar: ")
            nuevoTelefono = input("Ingrese nuevo numero de telefono: ")
            nuevoEmail = input("Ingrese nuevo correo electronico: ")
            agenda.actualizarContacto(nombre, nuevoTelefono, nuevoEmail)
        elif opcion == 4:
            print("Listado de contactos ordenados alfabeticamente:")
            agenda.mostrarContactosOrdenados()
        elif opcion == 5:
            print("Saliendo...")
        else:
            print("Opcion no valida. Intente nuevamente.")
