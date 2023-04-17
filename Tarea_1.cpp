/*TAREA 1 PARADIGMAS DE LA PROGRAMACION*/
/*AUTHOR : VICENTE ROA*/
/* FECHA: 15/04/2023*/
/*
*/
/*PRINCIPALES LIBRERIAS*/
#include <iostream>
#include <string>//Nos permite trabajar con cadenas de texto
#include <thread>
#include <fstream>//Nos permite trabajar con archivos externos
#include <vector> // Nos permite generar una lista dinamica
#include <sstream>//Nos permite operar con flujos de texto

using namespace std;

// CLASE ASIGNATURA
class Asignatura //Creamos la clase asignatura 
{ 
public:
    string nombre; 

    Asignatura(string nombre) //Constructor de la clase 
    { 
        this->nombre = nombre;
    }

    void obtener_asig() //Funcion principal de la clase asignatura 
    {
        cout << "Nombre de la asignatura: " << nombre << endl;
    }
};

// CLASE PRUEBA
class Prueba  //Creamos la clase prueba
{
public:
    int anio;
    float ponderaciones;

    Prueba(int anio, float ponderaciones) //Constructor de la clase prueba
    {
        this->anio = anio;
        this->ponderaciones = ponderaciones;
    }

    int tiempo() //Funcion principal de la clase prueba 
    {
        cout<< "\nTienes 10 min para realizar la prueba"<<endl;
        return 0;
   }
 };     


// CLASE PREGUNTA
class Pregunta {
private:
    string taxonomia;
    string tipo;

public:
    string texto;
    string respuesta;

    // Constructor de la clase
    Pregunta(string texto, string taxonomia, string tipo, string respuesta) {
        this->texto = texto;
        this->taxonomia = taxonomia;
        this->tipo = tipo;
        this->respuesta = respuesta;
    }

    // Función para establecer la respuesta
    void establecer_preguntas(vector<string> campos) 
    {
        /*ACA ATRIBUIMOS CADA CAMPO DEL ARCHIVO A LOS ATRIBUTOS*/
        this->texto = campos[0];
        this->taxonomia = campos[2];
        this->tipo = campos[1];
        this->respuesta = campos[3];
    }
    void mostrar_pregunta() {
        cout<< texto <<"" << endl;
    }
};

//nuestro contador de ID
int cont_persona = 0;
// CLASE PERSONA
class Persona  //Creamos la clase persona
{  
private:
    string nombre;
    int id;
 public:
    Persona(string nombre, int id) //Constructor de persona 
    {
        this->nombre = nombre;
        this->id = cont_persona + 1; //se sumara 1 al id para poder indentificarlos
        cont_persona++;
    }

    void solicitar_nombre() //Funcion para solicitar el nombre 
    {
        cout<<"\nIngresa el nombre de tu Profesor: ";
    	cin >> nombre;
        cout << "El nombre de tu profesor a sido ingresado correctamente " <<endl;
    }

	int obtener_id() //Funcion para obtener la id 
	{
        cout<<"id del profesor:"<<id<<endl;
    	return id;
	}
};

// CLASE PROFESOR
class Profesor : public Persona {
public:

    Profesor(string nombre, int id) : Persona(nombre, id) {} //Aca profesor heradará todo lo que persona tiene como atributo


void leer_prueba(string taxonomia) 
{
    vector<Pregunta> preguntas_seleccionadas; //Creamos un vector que va almacenar lo que tenga nuestra clase Pregunta
    string linea;
    ifstream archivo("prueba.csv");

    if (archivo.is_open()) { //Abrimos el archivo
        bool primera_linea = true; 
        /*CREAMOS UN CICLO QUE NOS INSERTE LO QUE HAY EN ARCHIVO EN LINEA*/
        while (getline(archivo, linea)) {
            if (primera_linea) {
                primera_linea = false; //Aca lo que hacemos es que la primera fila la omitimos de la lectura
                continue;// Aca le decimos que pase desde la siguente linea a trabajar
            }

            stringstream linea_stream(linea); //creamos una variable stringstream que va adjunto a la linea donde contiene las lineas del archivo
            string campo; //Declara una variable string 
            vector<string> campos; //Declaramos una lista dinamica (vector) llamada campos
            while (getline(linea_stream, campo, ';')) { //Quitamos los ; en el archivo
                campos.push_back(campo); //Esta funcion agrega cada linea a campo
            }
            if (campos[2] == taxonomia)//Verificamos que la taxonomia es igual a la que ingresamos
             {
                Pregunta pregunta(campos[0], campos[2], campos[1], campos[3]); //Creamos pregunta con todos los campos
                preguntas_seleccionadas.push_back(pregunta); //Agregaremos al vector de preguntas
            }
        }
        archivo.close(); //Cierra el archivo

        

        if (!preguntas_seleccionadas.size())
        //creamos esta condicional que nos verifica si las preguntas existen
        {
            cout << "No se encontraron preguntas para la taxonomia seleccionada" << endl;
        } 
        else 
        {
            srand(time(NULL)); // Esto incializa el numero aleatorio, lo que hara que nos genere numeros diferentes al ejecutar el programa
            int indice_aleatorio = rand() % preguntas_seleccionadas.size(); //Generamos una variable que genera un numero aleatorio entre 0 y el tamaño del vector que creamos
            /*ES IMPORTANTE ESTA PARTE YA QUE NOS ASEGURAMOS DE QUE LA GENERACION DEL NUMERO SE REALIZE UNA VEZ EN EL PROGRAMA Y NO CADA VEZ*/
            preguntas_seleccionadas[indice_aleatorio].mostrar_pregunta(); //Muestra las preguntas con el indice aleatoriamente
        }
    } else {
        cout << "No se pudo abrir el archivo" << endl; //Condicional si es que no es posible leer el archivo
    }
}
};

//FUNCION PARA GENERAR EL MENU
void menu() 
{
    cout<< "| MIDE TUS CONOCIMIENTOS |";
    cout<< "\n| -----------------------|";

}

int main() 
{
    //CREAMOS LAS VARIABLES
    string respuesta, seleccion;
    int seleccion_preguntas;
    int contador=0;

    menu();
    Prueba Solemne(2023,0);
    Solemne.tiempo();
    Profesor profe("", 0); //Aca no lo ponemos nada ya que este despues cambiara al solicitarle el nombre
    Asignatura introudccion_programacion("Programacion"); //Asignamos la asignatura de la prueba

    profe.solicitar_nombre(); //Solicitamos el nombre
    cout<<"\n\n"; 
    system("pause"); //Generamos un pause en el sistema
    system("cls"); //Eliminamos la informacion en la pantalla para que empieze la prueba

    /*PREGUNTAMOS LA CANTIDAD DE PREGUNTAS QUE QUIERE EL USUARIO*/
    cout<<"\nIngrese la cantidad de preguntas: ";
    cin>>seleccion_preguntas;

    while (seleccion_preguntas>0) //Si seleccion de preguntas es mayor a 0 se ejecutura el bucle 
    { 
        cout << "-------------------------\n";
        while (contador<seleccion_preguntas) {
            fflush(stdin); //Nos servira para limpiar el caracter enter
            cout << "Ingrese taxonomia: ";
            cin >> seleccion;
            profe.leer_prueba(seleccion);
            fflush(stdin);
            cout<<"\n";
            cout << "Ingrese respuesta: ";
            cin >> respuesta;
            cout << "-------------------------\n";
            contador++; //Sumamos 1 al contador
        } 
        seleccion_preguntas--; //Se le resta 1 a la seleccion de preguntas para que no siga avanzando el ciclo
    }
    return 0;
}