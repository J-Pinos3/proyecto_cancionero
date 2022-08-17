#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <array>
using namespace std;

const int MAX_MUSIC = 100;

struct CANCION{
    int id_cancion;
    string autor;
    string album;
    string titulo_obra;
    string genero;
};

struct LISTA{
    array <CANCION, MAX_MUSIC> arrCanciones;
    int contador = 0;
};

//PROTOTIPOS DE FUNCIONES
int Menu();
void Cargar(LISTA& lista, bool& funciona);
void Guardar(const LISTA& lista);
void LeerCancion(CANCION& cancion, const LISTA& lista);
void InsertarCancion(LISTA& lista, CANCION cancion, bool& funciona);
void EliminarCancion(LISTA& lista, bool& funciona);
void BuscarCancion(const LISTA& lista);
void ListarCanciones(const LISTA& lista);

int main()
{
    int opcion = 1;
    bool funciona;
    CANCION cancion;
    LISTA lista;
    Cargar(lista, funciona);

    if(!funciona){
        cout <<"No se pudo cargar el archivo o este no existe"<<endl<<endl;

    }else{

        while(opcion != 0){
            opcion = Menu();
            system("cls");

            switch(opcion){


            case 1:{
                    LeerCancion(cancion, lista);
                    InsertarCancion(lista, cancion, funciona);
                    if(!funciona){
                        cout <<"El cancionero est"<<char(160)<<" lleno"<<endl<<endl;
                    }
            }
            break;

            case 2:{
                    EliminarCancion(lista, funciona);

                    if(!funciona){
                        cout <<"Canci"<<char(162)<<" inexistente"<<endl;
                    }
            }
            break;

            case 3:{
                    BuscarCancion(lista);
            }
            break;

            case 4:{
                    ListarCanciones(lista);
            }
            break;

            case 0:{
                    cout <<"Vuelva pronto"<<endl;

            }
            break;

            default:{
                    cout <<"Algo ha salido muy mal"<<endl;
            }
            break;

            }//FIN DEL SWITCH

            system("pause");
            system("cls");

        }//FIN DEL WHILE PRINCIPAL

        Guardar(lista);
    }//FIN DEL ELSE PRINCIPAL


    return 0;
}///FIN DE MAIN


int Menu(){
    int opcion;
    cout <<"\t\tMEN"<<char(233)<<" DEL GESTOR DE CANCIONES"<<endl;
    cout <<"1) A"<<char(164)<<"dir canci"<<char(162)<<"n"<<endl;
    cout <<"2) Eliminar canci"<<char(162)<<"n"<<endl;
    cout <<"3) Buscar canci"<<char(162)<<"n"<<endl;
    cout <<"4) Listar canciones"<<endl;
    cout <<"0) Salir"<<endl;
    cout <<">";
    cin >> opcion;

    cout <<endl;
    while(opcion < 0 || opcion > 4){
        cout <<"Error, int"<<char(130)<<"ntelo de nuevo"<<endl;
        cout <<">";
        cin >> opcion;
        cout <<endl;
    }

    return opcion;
}//FIN DE LA FUNCIÓN MENÚ

void Cargar(LISTA& lista, bool& funciona){

    string nombre_Archivo;
    int op_archi;

    cout <<"1) Crear un nuevo archivo"<<endl;
    cout <<"2) Cargar un archivo existente"<<endl;
    cout <<">";
    cin >> op_archi;

    cout<<endl;
    while( op_archi < 1 || op_archi > 2){
        cout <<"1) Crear un nuevo archivo"<<endl;
        cout <<"2) Cargar un archivo existente"<<endl;
        cout <<">";
        cin >> op_archi;
        cout <<endl;
    }

        cin.ignore();


    if(op_archi == 1){
        cout <<endl<<"Ingrese el nombre del archivo y su extensi"<<char(162)<<"n: ";
        getline(cin, nombre_Archivo);

        ofstream archivo_esc(nombre_Archivo.c_str(),ios::out);
            archivo_esc <<"XXX";
        archivo_esc.close();

        op_archi = 2;//para ingresar a la opción de cargar el archivo
    }


    if(op_archi == 2){
        cout <<endl<<"CARGAR ARCHIVO"<<endl;
        cout <<"Ingrese el nombre y extensi"<<char(162)<<"n del archivo a abrir: ";
        getline(cin, nombre_Archivo);


        CANCION cancion;
        ifstream archivo_lec;
        char aux = ' ';
        lista.contador =0;

        archivo_lec.open(nombre_Archivo.c_str(), ios::in);

        if( !archivo_lec.is_open() ){
            funciona = false;
        }else{

            funciona = true;

            getline(archivo_lec, cancion.autor);
            while( (cancion.autor != "XXX")&&(lista.contador < MAX_MUSIC) ){

                getline(archivo_lec, cancion.album);
                getline(archivo_lec, cancion.titulo_obra);
                getline(archivo_lec, cancion.genero);
                archivo_lec >> cancion.id_cancion;

                archivo_lec.get(aux);

                lista.arrCanciones[lista.contador] = cancion;
                lista.contador++;

                getline(archivo_lec, cancion.autor);
            }

            archivo_lec.close();
        }


    }

}//FIN DE LA FUNCIÓN CARGAR CANCIONES

void Guardar(const LISTA& lista){

    string nombre_Archivo;
    cin.ignore();

    cout <<endl<<"GUARDAR ARCHIVO"<<endl;
    cout <<"Ingrese el nombre y extensi"<<char(162)<<"n del archivo a guardar: ";
    getline(cin, nombre_Archivo);

    ofstream archivo_esc;
    archivo_esc.open( nombre_Archivo.c_str(), ios::out);

    for(int i = 0; i < lista.contador; i++){
        archivo_esc << lista.arrCanciones[i].autor<<endl;
        archivo_esc << lista.arrCanciones[i].album<<endl;
        archivo_esc << lista.arrCanciones[i].titulo_obra<<endl;
        archivo_esc << lista.arrCanciones[i].genero<<endl;
        archivo_esc << lista.arrCanciones[i].id_cancion<<endl;
    }

    archivo_esc <<"XXX"<<endl;
    archivo_esc.close();

}//FIN DE LA FUNCIÓN GUARDAR CANCIONES

void LeerCancion(CANCION& cancion, const LISTA& lista){
    cin.ignore();

    cout <<"Ingrese el autor/es de la canci"<<char(162)<<"n: ";
    getline(cin, cancion.autor);

    cout <<"Ingrese a que "<<char(160)<<"lbum pertenece la canci"<<char(162)<<"n: ";
    getline(cin, cancion.album);

    cout <<"Ingrese el nombre de la canci"<<char(162)<<"n: ";
    getline(cin, cancion.titulo_obra);

    cout <<"Ingrese el g"<<char(130)<<"nero de la canci"<<char(162)<<"n: ";
    getline(cin, cancion.genero);

    cout <<"Ingrese el ID de la canci"<<char(162)<<"n: ";
    cin >> cancion.id_cancion;

    for(int i = 0; i <lista.contador; i++){

        if(cancion.id_cancion == lista.arrCanciones[i].id_cancion){
            cout <<"Ingrese el ID de la canci"<<char(162)<<"n: ";
            cin >> cancion.id_cancion;
        }

    }


    cin.sync();

}//FIN DE LA FUNCIÓN LEER CANCIÓN

void InsertarCancion(LISTA& lista, CANCION cancion, bool& funciona){
    funciona = true;

    if(lista.contador == MAX_MUSIC){
        funciona = false;

    }else{
        lista.arrCanciones[lista.contador] = cancion;
        lista.contador++;
    }


}//FIN DE LA FUNCIÓN INSERTAR CANCIÓN

void EliminarCancion(LISTA& lista, bool& funciona){

    int pos;
    cout <<"Ingrese la posici"<<char(162)<<"n de la canci"
        <<char(162)<<"n a eliminar"<<endl;
    cin >>pos;

    pos--;

    if(pos < 0 || pos > lista.contador-1){
        funciona = false;
    }else{

        funciona = true;

        for(int i = pos; i < lista.contador-1; i++){
            lista.arrCanciones[i] = lista.arrCanciones[i+1];
        }

        lista.contador--;
    }


}//FIN DE LA FUNCIÓN ELIMINAR CANCIÓN

void BuscarCancion(const LISTA& lista){

    int id;
    int index = 0;
    bool encontrado = false;

    cout <<"Ingrese el ID de la canci"<<char(162)<<"n a buscar: ";
    cin >> id;

    for(int i = 0; i < lista.contador && encontrado == false; i++){
        if(id == lista.arrCanciones[i].id_cancion){
            index = i;
            encontrado = true;
        }
    }


    if(encontrado){
        cout <<"La canci"<<char(162)<<"n "
            <<lista.arrCanciones[index].titulo_obra<<" est"<<char(160)
           <<" en la posici"<<char(162)<<"n "<<index+1<<endl<<endl;

    }else{
        cout <<"No se pudo encontrar una canci"<<char(162)<<" con ese ID"<<endl<<endl;
    }



}//FIN DE LA FUNCIÓN BUSCAR CANCIÓN

void ListarCanciones(const LISTA& lista){

    string linea(60, '-');
    cout <<"LISTA DE CANCIONES"<<endl<<endl;
    cout <<linea<<endl<<endl;

    for(int i = 0; i < lista.contador; i++){
        cout <<"CANCI"<<char(224)<<"N "<<i+1<<endl;

        cout <<"ID: "<<lista.arrCanciones[i].id_cancion<<endl;
        cout <<"Autor: "<<lista.arrCanciones[i].autor<<endl;
        cout <<char(181)<<"lbum: "<<lista.arrCanciones[i].album<<endl;
        cout <<"T"<<char(161)<<"tulo: "<<lista.arrCanciones[i].titulo_obra<<endl;
        cout <<"G"<<char(130)<<"nero: "<<lista.arrCanciones[i].genero<<endl<<endl;

        cout <<linea<<endl<<endl;
    }

}//FIN DE LA FUNCIÓN LISTAR CANCIONES









