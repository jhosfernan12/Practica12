class Producto:
    def __init__(self, cod, desc, cant):
        self.codigo = cod
        self.descripcion = desc
        self.cantidad = cant

class Inventario:
    def __init__(self):
        self.productos = {}

    def agregarProducto(self, codigo, descripcion, cantidad):
        if codigo in self.productos:
            print(f"Producto con el codigo {codigo} ya existe.")
        else:
            self.productos[codigo] = Producto(codigo, descripcion, cantidad)
            print("Producto agregado exitosamente.")

    def actualizarCantidad(self, codigo, cantidad):
        if codigo in self.productos:
            self.productos[codigo].cantidad = cantidad
            print("Cantidad actualizada exitosamente.")
        else:
            print("Producto no encontrado.")

    def buscarProducto(self, codigo):
        if codigo in self.productos:
            prod = self.productos[codigo]
            print(f"Codigo: {prod.codigo}, Descripcion: {prod.descripcion}, Cantidad: {prod.cantidad}")
        else:
            print("Producto no encontrado.")

    def mostrarProductosOrdenados(self):
        listaProductos = sorted(self.productos.values(), key=lambda x: x.descripcion)

        for prod in listaProductos:
            print(f"Codigo: {prod.codigo}, Descripcion: {prod.descripcion}, Cantidad: {prod.cantidad}")

def mostrarMenu():
    print("Menu de Gestion de Inventario")
    print("1. Agregar producto")
    print("2. Actualizar cantidad")
    print("3. Buscar producto")
    print("4. Mostrar productos ordenados por descripcion")
    print("5. Salir")

    inventario = Inventario()
    opcion = 0

    while opcion != 5:
        mostrarMenu()
        opcion = int(input("Seleccione una opcion: "))

        if opcion == 1:
            codigo = input("Ingrese codigo: ")
            descripcion = input("Ingrese descripcion: ")
            cantidad = int(input("Ingrese cantidad: "))
            inventario.agregarProducto(codigo, descripcion, cantidad)
        elif opcion == 2:
            codigo = input("Ingrese codigo: ")
            cantidad = int(input("Ingrese nueva cantidad: "))
            inventario.actualizarCantidad(codigo, cantidad)
        elif opcion == 3:
            codigo = input("Ingrese codigo: ")
            inventario.buscarProducto(codigo)
        elif opcion == 4:
            inventario.mostrarProductosOrdenados()
        elif opcion == 5:
            print("Saliendo...")
        else:
            print("Opcion no valida. Intente nuevamente.")
