#include <iostream>
#include <cstring>
using namespace std;

class Empleado {
public:
    int ClavEmpleado;
    char Nombre[50];
    char Domicilio[100];
    float Sueldo;
    char ReportaA[50];

    Empleado() {}

    Empleado(int clave, const char* nombre, const char* domicilio, float sueldo, const char* reportaA) {
        ClavEmpleado = clave;
        strcpy(Nombre, nombre);
        strcpy(Domicilio, domicilio);
        Sueldo = sueldo;
        strcpy(ReportaA, reportaA);
    }

    // Sobrecargas de operadores
    bool operator==(const Empleado& other) const {
        return ClavEmpleado == other.ClavEmpleado;
    }

    bool operator!=(const Empleado& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Empleado& emp) {
        os << "Clave: " << emp.ClavEmpleado << ", Nombre: " << emp.Nombre
           << ", Domicilio: " << emp.Domicilio << ", Sueldo: " << emp.Sueldo
           << ", Reporta A: " << emp.ReportaA;
        return os;
    }

    friend istream& operator>>(istream& is, Empleado& emp) {
        cout << "Clave: ";
        is >> emp.ClavEmpleado;
        is.ignore();
        cout << "Nombre: ";
        is.getline(emp.Nombre, 50);
        cout << "Domicilio: ";
        is.getline(emp.Domicilio, 100);
        cout << "Sueldo: ";
        is >> emp.Sueldo;
        is.ignore();
        cout << "Reporta A: ";
        is.getline(emp.ReportaA, 50);
        return is;
    }
};

template <typename T, int size>
class ListaEstatica {
private:
    T data[size];
    int count;

public:
    ListaEstatica() : count(0) {}

    int Inserta(T element, int pos) {
        if (Llena()) return -1;
        if (pos < 0 || pos > count) return -2;
        for (int i = count; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = element;
        count++;
        return 0;
    }

    int Agrega(T element) {
        if (Llena()) return -1;
        data[count++] = element;
        return 0;
    }

    int Busca(T element) {
        for (int i = 0; i < count; ++i) {
            if (data[i] == element) return i;
        }
        return -1;
    }

    int Elimina(int pos) {
        if (Vacia()) return -1;
        if (pos < 0 || pos >= count) return -2;
        for (int i = pos; i < count - 1; ++i) {
            data[i] = data[i + 1];
        }
        count--;
        return 0;
    }

    int Vacia() {
        return count == 0;
    }

    int Llena() {
        return count == size;
    }

    int Muestra() {
        if (Vacia()) return -1;
        for (int i = 0; i < count; ++i) {
            cout << data[i] << endl;
        }
        return 0;
    }
};

int main() {
    ListaEstatica<Empleado, 10> lista;
    int opcion;
    do {
        cout << "Menu de opciones:" << endl;
        cout << "1. Agrega" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Elimina" << endl;
        cout << "4. Inserta" << endl;
        cout << "5. Muestra" << endl;
        cout << "6. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                Empleado emp;
                cin >> emp;
                int result = lista.Agrega(emp);
                if (result == -1) {
                    cout << "No se pudo agregar el empleado. La lista est� llena." << endl;
                }
                break;
            }
            case 2: {
                Empleado emp;
                cin >> emp;
                int pos = lista.Busca(emp);
                if (pos == -1 && !lista.Vacia()) {
                    cout << "No hubo resultados en la b�squeda." << endl;
                } else if (lista.Vacia()) {
                    cout << "La lista no tiene elementos guardados aun." << endl;
                } else {
                    cout << "Empleado encontrado en la posici�n: " << pos << endl;
                }
                break;
            }
            case 3: {
                Empleado emp;
                cout << "Dame el Empleado a eliminar" << endl;
                cin >> emp;
                int pos = lista.Busca(emp);
                if (pos == -1 && !lista.Vacia()) {
                    cout << "El Empleado ingresado no existe." << endl;
                } else if (lista.Vacia()) {
                    cout << "La lista no tiene elementos guardados aun." << endl;
                } else {
                    lista.Elimina(pos);
                    cout << "Empleado eliminado." << endl;
                }
                break;
            }
            case 4: {
                Empleado emp;
                cout << "Dame el Empleado a insertar" << endl;
                cin >> emp;
                int pos;
                cout << "Dame la posicion donde se debe insertar el Empleado: ";
                cin >> pos;
                int result = lista.Inserta(emp, pos);
                if (result == -1) {
                    cout << "No se pudo insertar. La lista est� llena." << endl;
                } else if (result == -2) {
                    cout << "No se puede insertar el objeto en esa posicion." << endl;
                } else {
                    cout << "Empleado insertado en la posici�n " << pos << endl;
                }
                break;
            }
            case 5: {
                int result = lista.Muestra();
                if (result == -1) {
                    cout << "La lista est� vac�a." << endl;
                }
                break;
            }
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opci�n no v�lida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}
