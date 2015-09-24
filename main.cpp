#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstring>
#include "tree.h"
#include "node.h"
#include "index.h"
#include <algorithm>//replace

using namespace std;

string GenerarId();
string GenerarIdCiudad();
string GenerarTelefono();
void CityToBinary();
void ClientToBinary();
void CallToBinary();
void NumberToBinary();
void IndexCity();
void IndexClient();
void IndexNumber();
int PosicionIngresoOrdenadoAlIndice(vector<string>,  int);
int PosicionIngresoOrdenadoAlIndiceLong(vector<string>, unsigned long );
void writeIndexCity( );
void writeIndexClient( );
void writeIndexNumber( );
void borrarCity( int );
void borrarClient( long );
void borrarNumber( int );
void agregarCity();
void agregarClient();
void agregarNumero();
void modificarCity();
void modificarClient();
void modificarNumber();
void buscarCityIndexado(int);
void buscarClientIndexado(unsigned long);
void buscarNumberIndexado(int);
void buscarCity(int);
void buscarClient(unsigned long);
void buscarNumber(int);
void ListCall();
void ListCity();//----
void ListClient();
void ListNumber();
void CrearArbolCity();
void CrearArbolClient();
void CrearArbolNumber();
void Tarifa(unsigned long );
int menu();
const int HeaderSize = sizeof(int) + sizeof(int) + sizeof(bool);
vector<string> indexCityRRN;
vector<string> indexCityKey;
vector<string> indexClientKey;
vector<string> indexClientRRN;
vector<string> indexNumberRRN;
vector<string> indexNumberKey;
vector<Index> IndexArbolCity;
int orden = 7;
Tree TreeCity(orden);
Tree TreeClient(orden);
Tree TreeNumber(orden);
void BuscarCityArbol(int);
void BuscarClientArbol(int);
void BuscarNumberArbol(int);
int PosicionBusquedaOrdenadaAlIndiceLong(vector<string>  , unsigned long );
void CompactarCity();
void CompactarClient();
void CompactarNumber();
void readIndexCity();
void readIndexClient();
void readIndexNumber();

int main(int argc, char* argv[]){
	srand(time(0));
	int opcion = 0,opcionAdd = 0,opcionEliminar = 0,opcionModificar = 0,opcionListar = 0, opcionBuscar =0, opcionReindexar = 0,opcionCompactar = 0;
	int opcionListarArbol = 0;
	CityToBinary();
	ClientToBinary();
	CallToBinary();
	NumberToBinary();
	IndexCity();
	IndexClient();
	IndexNumber();
	CrearArbolCity();
	CrearArbolClient();
	CrearArbolNumber();
	cout << "Archivos creados e indexados exitosamente"<<endl;
	bool continuar = true;
	while(continuar){
		cout << "1. Agregar\n2. Eliminar\n3. Modificar\n4. Listar\n5. Buscar\n6. Reindexar\n7. Visualizar Arbol\n8. Tarifa\n9. Compactar\n10. Salir"<<endl;
		cin >> opcion;
		switch(opcion){
			case 1:{//agregar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionAdd;
				switch(opcionAdd){
					case 1:{
						agregarCity();
					}break;
					case 2:{
						agregarClient();				
					}break;
					case 3:{
						agregarNumero();				
					}break;
				}
			}break;//fin agregar

			case 2:{//eliminar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionEliminar;
				switch(opcionEliminar){
					case 1:{
						int Id=0;
						while(Id != -1){
							cout << "Ingrese el Id de la ciudad que desea borrar: ";
							cin >> Id;
							if (Id != -1)
							{ 
								borrarCity(Id);
							}
							
						}
						
					}break;
					case 2:{
						long Id;
						cout << "Ingrese el Id del cliente que desea borrar: ";
						cin >> Id;
						borrarClient(Id);				
					}break;
					case 3:{
						int Id;
						cout << "Ingrese el numero que desea borrar: ";
						cin >> Id;
						borrarNumber(Id);			
					}break;
				}
			}break;//fin eliminar

			case 3:{//modificar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionModificar;
				switch(opcionModificar){
					case 1:{
						modificarCity();
					}break;
					case 2:{
						modificarClient();		
					}break;
					case 3:{
						modificarNumber();
					}break;
				}
			}break;//fin modificar

			case 4:{//listar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionListar;
				switch(opcionListar){
					case 1:{
						ListCity();
					}break;
					case 2:{
						ListClient();									
					}break;
					case 3:{
						ListNumber();				
					}break;
				}
			}break;//fin listar

			case 5:{//buscar
				int typeOfSearch = 0;
				cout << "1. Busqueda Indexada\n2. Busqueda secuencial\n3. Busqueda con arbol B"<<endl;
				cin >> typeOfSearch;
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionBuscar;
				switch(opcionBuscar){
					case 1:{
						cout << "Ingrese el Id de la ciudad que desea buscar: ";
						int key;
						cin >> key;
						if(typeOfSearch == 1)
							buscarCityIndexado(key);
						if(typeOfSearch == 2)
							buscarCity(key);
						if(typeOfSearch == 3){
							int rrn = TreeCity.Buscar((long)key);
							if(rrn != -1)
								BuscarCityArbol(TreeCity.Buscar((long)key));	
							else
								cout << "No se encontro el registro"<< endl;

						}
					}break;
					case 2:{
						cout << "Ingrese el Id del cliente que desea buscar: ";
						long key;
						cin >> key;
						if(typeOfSearch == 1)
							buscarClientIndexado(key);
						if(typeOfSearch == 2)
							buscarClient(key);
						if(typeOfSearch == 3){
							int rrn = TreeClient.Buscar((long)key);
							if(rrn != -1)
								BuscarClientArbol(TreeClient.Buscar((long)key));	
							else
								cout << "No se encontro el registro"<< endl;

						}	
					}break;
					case 3:{
						cout << "Ingrese el numero que desea buscar: ";
						int key;
						cin >> key;
						if(typeOfSearch == 1)
							buscarNumberIndexado(key);
						if(typeOfSearch == 2)
							buscarNumber(key);
						if(typeOfSearch == 3){
							int rrn = TreeNumber.Buscar((long)key);
							if(rrn != -1)
								BuscarNumberArbol(TreeNumber.Buscar((long)key));	
							else
								cout << "No se encontro el registro"<< endl;

						}			
					}break;
				}
			}break;//fin buscar

			case 6:{//reindexar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionAdd;
				int Id;
				switch(opcionAdd){
					case 1:{
						IndexCity();
					}break;
					case 2:{
						IndexClient();				
					}break;
					case 3:{
						IndexNumber();				
					}break;
				}
			}break;//fin reindexar
			case 7:{//Visualizar arbol
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionListarArbol;
				switch(opcionListarArbol){
					case 1:{
						TreeCity.Listar();
					}break;
					case 2:{
						TreeClient.Listar();								
					}break;
					case 3:{
						TreeNumber.Listar();			
					}break;
				}
			}break;//fin visualizar arbol
			case 8:{//tarifa de numero
				unsigned long Id;
				cout << "Ingrese el Id que desea consultar: ";
				cin >> Id;
				Tarifa(Id);
			}break;//tarifa
			case 9:{//compactar
				cout << "1. Ciudad\n2. Cliente\n3. Numero"<<endl;
				cin >> opcionCompactar;
				switch(opcionCompactar){
					case 1:{
						CompactarCity();
					}break;
					case 2:{
						CompactarClient();								
					}break;
					case 3:{
						CompactarNumber();			
					}break;
				}
			}break;//compactar
			
			default:{//salir
				writeIndexCity();
				writeIndexClient();
				writeIndexNumber();
				continuar =false;
			}break;
		}
	}
	return 0;
}//fin main
string GenerarId(){
	string id;
	srand(time(0));
	stringstream ss;
	ss << rand() % 2 << rand() % 10<< rand() % 9<< rand() % 10 << (rand() % 98 + 1900) << (rand() % 90000+10000);
	id  = ss.str();

	return id;
}
string GenerarIdCiudad(){
	string id;
	srand(time(0));
	stringstream ss;
	ss << rand() % 10 << rand() % 10<< rand() % 10<< rand() % 10 ;
	id  = ss.str();
	return id;
}
string GenerarTelefono(){
	string id;
	srand(time(0));
	stringstream ss;
	ss << rand() % 10 << rand() % 10<< rand() % 10<< rand() % 10<< rand() % 10 << rand() % 10<< rand() % 10<< rand() % 10 ;
	id  = ss.str();
	return id;
}
//Texto a binario
void CityToBinary(){
	ifstream file("Ciudad.txt");
	ofstream outputFile("Ciudades.bin");
	int rrn=-1, recordNumber = 0;
	bool indexindexFlag = 0;
	outputFile.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	char EndOfFile;
	while(file>>EndOfFile){
		/*if(file.eof())
			break;*/
		char IdCiudad[4];
		char NameCiudad[40];
		string temp = "", temp1 = "";
		getline(file, temp, ',');
		getline(file, temp1, ',');
		for (int i = 0; i < 4; i++){
			IdCiudad[i] = temp[i];
		}		
		for (int i = 0; i < 40; i++){
			NameCiudad[i] = temp1[i];
		}
		bool CadenaVacia = true;
		for (int i = 0; i < sizeof(IdCiudad); i++)
		{
			if(IdCiudad[i] != '\0' && IdCiudad[i] != ' ')
				CadenaVacia = false;
		}
		if(!CadenaVacia){			
			outputFile.write((char*)IdCiudad, sizeof(IdCiudad));
			outputFile.write((char*)NameCiudad, sizeof(NameCiudad));
			recordNumber++;
	  		outputFile.seekp (sizeof(rrn));
	  		outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(recordNumber));
	  		outputFile.seekp(sizeof(int)*2 +1 +(recordNumber*44));
		}
	}	
	file.close();
	outputFile.close();
	//ListCity();
}
void ClientToBinary(){
	ifstream file("Clientes.txt");
	ofstream outputFile("Clientes.bin");
	int rrn=-1, recordNumber = 0;
	bool indexindexFlag = 0;
	outputFile.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	char EndOfFile;
	while(file>>EndOfFile){
		/*if(file.eof())
			break;*/
		char IdClient[14];
		char NameClient[40];
		char Gender[2];
		char IdCiudad[4];
		string temp1 = "", temp2 = "",temp3 = "",temp4 = "";
		getline(file, temp1, ',');
		getline(file, temp2, ',');
		getline(file, temp3, ',');
		getline(file, temp4, ',');
		for (int i = 0; i < sizeof(IdClient); i++){
			IdClient[i] = temp1[i];
		}		
		for (int i = 0; i < sizeof(NameClient); i++){
			NameClient[i] = temp2[i];
		}
		for (int i = 0; i < sizeof(Gender); i++){
			Gender[i] = temp3[i];
		}		
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = temp4[i];
		}
		outputFile.write((char*)IdClient, sizeof(IdClient));
		outputFile.write((char*)NameClient, sizeof(NameClient));
		outputFile.write((char*)Gender, sizeof(Gender));
		outputFile.write((char*)IdCiudad, sizeof(IdCiudad));
		recordNumber++;
  		outputFile.seekp (sizeof(rrn));
  		outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(recordNumber));
  		outputFile.seekp(sizeof(int)*2 +1 +(recordNumber*60));
	}	
	file.close();
	outputFile.close();
	//ListClient();
}
void CallToBinary(){
	ifstream file("Llamadas.txt");
	ofstream outputFile("Llamadas.bin");
	int rrn=-1, recordNumber = 0;
	bool indexindexFlag = 0;
	outputFile.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	int Id;
	char Numero[9];
	char FechaInicio[20];
	char FechaFinal[20];
	char NumDestino[9];
	char EndOfFile;
	while(file>>EndOfFile){
		/*if (file.eof())
			break;*/
		string temp1 = "", temp2 = "",temp3 = "",temp4 = "",temp5 = "";
		getline(file, temp1, ',');
		getline(file, temp2, ',');
		getline(file, temp3, ',');
		getline(file, temp4, ',');
		getline(file, temp5, ',');
		stringstream ss;
		for (int i = 0; i < sizeof(temp1); i++){
			ss << temp1[i];
		}
		Id = atoi(ss.str().c_str());
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = temp2[i];
		}		
		for (int i = 0; i < sizeof(FechaInicio); i++){
			FechaInicio[i] = temp3[i];
		}
		for (int i = 0; i <  sizeof(FechaFinal); i++){
			FechaFinal[i] = temp4[i];
		}		
		for (int i = 0; i <  sizeof(NumDestino); i++){
			NumDestino[i] = temp5[i];
		}
		//cout << temp1 <<" | "<<Numero << " | " << FechaInicio << " | " << FechaFinal << " | " << NumDestino <<endl;
		outputFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
		outputFile.write((char*)Numero, sizeof(Numero));
		outputFile.write((char*)FechaInicio, sizeof(FechaInicio));
		outputFile.write((char*)FechaFinal, sizeof(FechaFinal));
		outputFile.write((char*)NumDestino, sizeof(NumDestino));
		recordNumber++;
  		outputFile.seekp (sizeof(rrn));
  		outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(recordNumber));
  		outputFile.seekp(sizeof(int)*2 +1 +(recordNumber*62));
	}	
	file.close();
	outputFile.close();
	//ListCall();
}
void NumberToBinary(){
	ifstream file("Numero.txt");
	ofstream outputFile("Numeros.bin");
	int rrn=-1, recordNumber = 0;
	bool indexindexFlag = 0;
	outputFile.write( reinterpret_cast<char*>(&rrn), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	outputFile.write( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	char EndOfFile;
	while(file>>EndOfFile){
		/*if(file.eof())
			break;*/
		char Numero[9];
		char Id[14];
		string temp = "", temp1 = "";
		getline(file, temp, ',');
		getline(file, temp1, ',');
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = temp[i];
		}		
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = temp1[i];
		}
		outputFile.write((char*)Numero, sizeof(Numero));
		outputFile.write((char*)Id, sizeof(Id));
		recordNumber++;
  		outputFile.seekp (sizeof(rrn));
  		outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(recordNumber));
  		outputFile.seekp(sizeof(int)*2 +1 +(recordNumber*23));
	}	
	file.close();
	outputFile.close();
	//ListNumber();
}
//Listar
void ListCity(){
	int rrn=-1, recordNumber = 0, endFile = 0;
	bool indexindexFlag = 0;
	char IdCiudad[4];
	char NameCiudad[40];
	ifstream readFile("Ciudades.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	//cout << rrn <<"||"<< recordNumber<<"||" << indexindexFlag <<endl;
 	while(endFile < recordNumber){

		/*if(readFile.eof())
			break;*/
		char IdCiudad[4];
		char NameCiudad[40];
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		readFile.read((char*)NameCiudad, sizeof(NameCiudad));
		if( IdCiudad[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Id Ciudad: "<<IdCiudad <<endl;
			cout << "Nombre de la ciudad: " <<NameCiudad<<endl;
		}
		endFile++;
	}
	readFile.close();
}
void ListClient(){
	int rrn=-1, recordNumber = 0,endFile = 0;
	bool indexindexFlag = 0;
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	ifstream readFile("Clientes.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		/*if(readFile.eof())
			break;*/
		readFile.read((char*)IdClient, sizeof(IdClient));
		readFile.read((char*)NameClient, sizeof(NameClient));
		readFile.read((char*)Gender, sizeof(Gender));
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		if( IdClient[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Id: " << IdClient << endl;
			cout << "Nombre: " << NameClient <<endl; 
			cout << "Genero: " << Gender << endl;
			cout << "Id Ciudad: " << IdCiudad <<endl;
		}
		endFile++;

	}
	readFile.close();
}
void ListNumber(){
	int rrn=-1, recordNumber = 0,endFile = 0;
	bool indexindexFlag = 0;
	char Numero[9];
	char Id[14];
	ifstream readFile("Numeros.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		/*if(readFile.eof())
			break;*/
		char Numero[9];
		char Id[14];
		readFile.read((char*)Numero, sizeof(Numero));
		readFile.read((char*)Id, sizeof(Id));
		if( Numero[0] != '*'){
			cout <<"----------------------------------------------------------------------------"<<endl;
			cout << "Numero: " << Numero << endl;
			cout << "Id Propietario: " << Id <<endl; 
		}
		endFile++;

	}
	readFile.close();
}
void ListCall(){
	int Id;
	char Numero[9];
	char FechaInicio[20];
	char FechaFinal[20];
	char NumDestino[9];
	ifstream readFile("Llamadas.bin",ios::binary);
	readFile.seekg(0);
	int rrn=-1, recordNumber = 0,endFile=0;
	bool indexindexFlag = 0;
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		/*if(readFile.eof())
			break;*/
		readFile.read(reinterpret_cast<char*>(&Id), sizeof(Id));
		readFile.read((char*)Numero, sizeof(Numero));
		readFile.read((char*)FechaInicio, sizeof(FechaInicio));
		readFile.read((char*)FechaFinal, sizeof(FechaFinal));
		readFile.read((char*)NumDestino, sizeof(NumDestino));
		cout <<"----------------------------------------------------------------------------"<<endl;
		cout << "Id: " << Id << endl;
		cout << "Numero: " << Numero <<endl; 
		cout << "Fecha Inicial: " << FechaInicio << endl;
		cout << "Fecha Final: " << FechaFinal <<endl;
		cout << "Destino: " << NumDestino <<endl;
		endFile++;
	}
	readFile.close();
}
void writeIndexCity(){
	ofstream markFile("Ciudades.bin");
	markFile.seekp(sizeof(int)+sizeof(int));

	bool indexFlag = true;
	markFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	markFile.close();
	ofstream outputFile("IndexCity.bin");
	for (int i = 0; i < indexCityRRN.size(); i++){	
		int llave = atoi(indexCityKey[i].c_str());
		unsigned long rrn = atol(indexCityRRN[i].c_str());	
  		outputFile.write( reinterpret_cast<char*>(&llave), sizeof(int) );
  		outputFile.write( reinterpret_cast<char*>(&rrn), sizeof(long) );
	}
	outputFile.close();
	ofstream remarkFile("Ciudades.bin");
	remarkFile.seekp(sizeof(int)+sizeof(int));
	indexFlag = false;
	remarkFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	remarkFile.close();
}
void writeIndexClient(){
	ofstream markFile("Clientes.bin");
	markFile.seekp(sizeof(int)+sizeof(int));

	bool indexFlag = true;
	markFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	markFile.close();
	ofstream outputFile("IndexClient.bin");
	for (int i = 0; i < indexClientRRN.size(); i++){		
  		outputFile.write( reinterpret_cast<char*>(&indexClientKey[i]), sizeof(indexClientKey[i]) );
  		outputFile.write( reinterpret_cast<char*>(&indexClientRRN[i]), sizeof(indexClientRRN[i]) );
	}
	outputFile.close();
	ofstream remarkFile("Clientes.bin");
	remarkFile.seekp(sizeof(int)+sizeof(int));
	indexFlag = false;
	remarkFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	remarkFile.close();
}
void writeIndexNumber(){
	ofstream markFile("Numeros.bin");
	markFile.seekp(sizeof(int)+sizeof(int));

	bool indexFlag = true;
	markFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	markFile.close();
	ofstream outputFile("IndexNumeros.bin");
	for (int i = 0; i < indexNumberRRN.size(); i++){		
  		outputFile.write( reinterpret_cast<char*>(&indexNumberKey[i]), sizeof(indexNumberKey[i]) );
  		outputFile.write( reinterpret_cast<char*>(&indexNumberRRN[i]), sizeof(indexNumberRRN[i]) );
	}
	outputFile.close();
	ofstream remarkFile("Numeros.bin");
	remarkFile.seekp(sizeof(int)+sizeof(int));
	indexFlag = false;
	remarkFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag) );
	remarkFile.close();
}
//Crear indice de cada uno
void IndexCity(){
	indexCityKey.clear();
	indexCityRRN.clear();
	ifstream readFile("Ciudades.bin",ios::binary);
	readFile.seekg(HeaderSize);
	int cont = 0;

 	while(true){
		stringstream rrn ;
		if(readFile.eof()){
			break;
		}
		char IdCiudad[4];
		char NameCiudad[40];
		readFile.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		readFile.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		bool iguales = false;
		for (int i = 0; i < sizeof(IdCiudad)-1; i++){
			if(IdCiudad[i] == '*'){
				iguales = true;	
				break;			
			}
		}
		if(!iguales){
			stringstream ss;
			for (int i = 0; i < sizeof(IdCiudad); i++){							
				ss<< IdCiudad[i];	
			}
			rrn<< cont;
			int key = atoi(ss.str().c_str());
			int position = PosicionIngresoOrdenadoAlIndice(indexCityKey, key);
			if (position == -1){
				indexCityKey.push_back(ss.str());
				indexCityRRN.push_back(rrn.str());
			}else{
				indexCityKey.insert(indexCityKey.begin() + position, ss.str());
				indexCityRRN.insert(indexCityRRN.begin() + position, rrn.str());
			}

		}
		cont++;

	}
	/*for (int i = 0; i < indexCityKey.size(); i++)
	{
		cout << "Key: " << indexCityKey.at(i) << " RRN: " << indexCityRRN.at(i)<< endl;
	}*/
	readFile.close();
	//writeIndexCity();
	//ListIndex("IndexCity.bin");
}
void IndexClient(){
	indexClientKey.clear();
	indexClientKey.clear();
	ifstream readFile("Clientes.bin",ios::binary);
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	int cont = 0;

 	while(true){
		stringstream rrn ;
		if(readFile.eof())
			break;
		char IdClient[14];
		char NameClient[40];
		char Gender[2];
		char IdCiudad[4];
		readFile.read((char*)IdClient, sizeof(IdClient));
		readFile.read((char*)NameClient, sizeof(NameClient));
		readFile.read((char*)Gender, sizeof(Gender));
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		bool iguales = false;
		for (int i = 0; i < sizeof(IdClient)-1; i++)
		{
			if(IdClient[i] == '*'){
				iguales = true;	
				break;			
			}
		}
		if(!iguales){
			stringstream ss;
			for (int i = 0; i < sizeof(IdClient); i++)
			{							
				ss<< IdClient[i];	
			}
			rrn<< cont;
			unsigned long key = atol(ss.str().c_str());
			int position = PosicionIngresoOrdenadoAlIndiceLong(indexClientKey, key);
			if (position == -1){
				indexClientKey.push_back(ss.str());
				indexClientRRN.push_back( rrn.str());
			}else{
				indexClientKey.insert(indexClientKey.begin() + position, ss.str());
				indexClientRRN.insert(indexClientRRN.begin() + position, rrn.str());
			}

		}
		cont++;

	}/*
	for (int i = 0; i < indexClientKey.size(); i++)
	{
		cout << "Key: " << indexClientKey.at(i) << " RRN: " << indexClientRRN.at(i)<< endl;
	}	*/
	readFile.close();
	//writeIndexClient();
}
void IndexNumber(){
	indexNumberKey.clear();
	indexNumberRRN.clear();
	ifstream readFile("Numeros.bin",ios::binary);
	readFile.seekg(HeaderSize);
	int cont = 0;

 	while(true){
		stringstream rrn ;
		if(readFile.eof())
			break;
		char Numero[9];
		char Id[14];
		readFile.read(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		readFile.read((char*)Id, sizeof(Id));
		bool iguales = false;
		for (int i = 0; i < sizeof(Numero)-1; i++){
			if(Numero[i] == '*'){
				iguales = true;	
				break;			
			}
		}
		if(!iguales){
			stringstream ss;
			for (int i = 0; i < sizeof(Numero); i++){							
				ss<< Numero[i];	
			}
			//cout << ss.str()<<endl;
			rrn<< cont;
			//cout << rrn.str() << "|||"<< endl;
			int key = atoi(ss.str().c_str());
			int position = PosicionIngresoOrdenadoAlIndice(indexNumberKey, key);
			if (position == -1){
				indexNumberKey.push_back(ss.str());
				indexNumberRRN.push_back( rrn.str());
			}else{
				indexNumberKey.insert(indexNumberKey.begin() + position, ss.str());
				indexNumberRRN.insert(indexNumberRRN.begin() + position, rrn.str());
			}

		}
		cont++;

	}
	/*for (int i = 0; i < indexNumberKey.size(); i++)
	{
		cout << "Key: " << indexNumberKey.at(i) << " RRN: " << indexNumberRRN.at(i)<< endl;
	}	*/
	readFile.close();
	//writeIndexNumber();
}
//Eliminar
void borrarCity( int key ){
	char IdCiudad[4];
	char NameCiudad[40];
	int position = PosicionIngresoOrdenadoAlIndice(indexCityKey, key);
	string rrn = indexCityRRN.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	stringstream ss;
	ifstream readFile("Ciudades.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader;
	int recordNumber;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.close();
	ofstream writeFile("Ciudades.bin", ios::out | ios::in);
	if (position != -1){
		IdCiudad[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			NameCiudad[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recordNumber){
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}else{
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad) );
		writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad) );// se escribe el rrn en el header
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
	}
	indexCityKey.erase(indexCityKey.begin() +position);
	indexCityRRN.erase(indexCityRRN.begin() +position);
	TreeCity.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	writeFile.close();	
}
void borrarClient( long key ){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	int position = PosicionBusquedaOrdenadaAlIndiceLong(indexClientKey, key);
	string rrn = indexClientRRN.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	ifstream readFile("Clientes.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader,recordNumber;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.close();
	ofstream writeFile("Clientes.bin", ios::out | ios::in);
	if (position != -1){
		IdClient[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			NameClient[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recordNumber){
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}else{
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}
		//writeFile.seekp(HeaderSize + atoi((rrn).c_str())*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		writeFile.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient) );
		writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient) );// se escribe el rrn en el header
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
	}
	indexClientKey.erase(indexClientKey.begin() +position);
	indexClientRRN.erase(indexClientRRN.begin() +position);
	TreeClient.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	writeFile.close();
}
void borrarNumber( int key ){
	char Numero[9];
	char Id[14];
	
	int position = PosicionBusquedaOrdenadaAlIndiceLong(indexNumberKey, (long)key);
	string rrn = indexNumberRRN.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	ifstream readFile("Numeros.bin", ios::binary);
	readFile.seekg(0);
	int rrnHeader,recordNumber;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.close();
	ofstream writeFile("Numeros.bin", ios::out | ios::in);
	if (position != -1){
		Numero[0] ='*';
		rrnToString<< rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			Id[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recordNumber){
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*( sizeof(Numero) + sizeof(Id))  );
		}else{
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) )*( sizeof(Numero) + sizeof(Id))  );
		}
		//writeFile.seekp(HeaderSize + atoi((rrn).c_str())*( sizeof(Numero) + sizeof(Id) )  );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero) );
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id) );// se escribe el rrn en el header
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
	}
	indexNumberKey.erase(indexNumberKey.begin() +position);
	indexNumberRRN.erase(indexNumberRRN.begin() +position);
	TreeNumber.Eliminar(Index( (unsigned long)key , atoi(rrn.c_str())));
	writeFile.close();
}
//Busqueda binaria para localizar la posicion a ingresar
int PosicionIngresoOrdenadoAlIndice(vector<string> indexKey  , int key){
    int low = 0;
    int high = indexKey.size() - 1;
    int mid;
    bool avoidInfiniteCicle = false;
    
    while(true){
    	if(low > high)
    		break;    	
    	mid = (low + high)/2;
    	if(key == atoi((indexKey.at(mid)).c_str()) )
    		return mid;
    	if(key > atoi((indexKey.at(mid)).c_str())){
    		if(mid != indexKey.size() - 1){
    			if(key < atoi((indexKey.at(mid+1)).c_str())){
    				return mid+1;
    			}else{
    				if(avoidInfiniteCicle && mid == indexKey.size()-2)
    					return -1;
    				low = mid;
    				avoidInfiniteCicle = true;
    			}
    		}else{
    			if(key < atoi((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(mid != 0){
    			if(key > atoi((indexKey.at(mid-1)).c_str())){

    				return mid;
    			}else{
    				high = mid;
    			}
    		}else{
    			if(key < atoi((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return mid+1;
    			}

    		}
    	}
    }
    return -1;
}

int PosicionIngresoOrdenadoAlIndiceLong(vector<string> indexKey  , unsigned long key){
    int low = 0;
    int high = indexKey.size() - 1;
    int mid;
    bool avoidInfiniteCicle = false;
    
    while(true){
    	if(low > high)
    		break;    	
    	mid = (low + high)/2;
    	if(key == atol((indexKey.at(mid)).c_str()) )
    		return mid;
    	if(key > atol((indexKey.at(mid)).c_str())){
    		if(mid != indexKey.size() - 1){
    			if(key < atol((indexKey.at(mid+1)).c_str())){
    				return mid+1;
    			}else{
    				if(avoidInfiniteCicle && mid == indexKey.size()-2)
    					return -1;
    				low = mid;
    				avoidInfiniteCicle = true;
    			}
    		}else{
    			if(key < atol((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(mid != 0){
    			if(key > atol((indexKey.at(mid-1)).c_str())){

    				return mid;
    			}else{
    				high = mid;
    			}
    		}else{
    			if(key < atol((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return mid+1;
    			}

    		}
    	}
    }
    return -1;
}
//Agregar de todos
void agregarCity(){
	ifstream readFile("Ciudades.bin", ios::binary);
	char IdCiudad[4];
	char NameCiudad[40];
	readFile.seekg(0);
	int rrnHeader, recordNumber,cont = 0;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.seekg(HeaderSize + rrnHeader*( sizeof(IdCiudad) + sizeof(NameCiudad) )+ sizeof(IdCiudad) );
	readFile.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(NameCiudad); i++){
		streamNombre << NameCiudad[i];
	}
	int newRRNHeader = atoi(streamNombre.str().c_str());
	readFile.close();
	string leerId = "", leerDato = "";
	if(rrnHeader != -1){
		cout << "Ingrese el Id de la ciudad: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerId[i];
			ss<< leerId[i];
		}
		cout << "Ingrese el nombre de la ciudad: ";
		cin >> leerDato;
		for (int i = 0; i < sizeof(NameCiudad); i++){
			NameCiudad[i] = leerDato[i];
		}
		ofstream writeFile("Ciudades.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&newRRNHeader), sizeof(newRRNHeader));
		writeFile.close();
		int position = PosicionIngresoOrdenadoAlIndice( indexCityKey  , atoi(ss.str().c_str()) );
		indexCityKey.insert(indexCityKey.begin()+ position, ss.str());
		TreeCity.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el Id de la ciudad: ";
		cin >> leerId;
		stringstream streamId;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerId[i];
			streamId<< leerId[i];
		}

		cout << "Ingrese el nombre de la ciudad: ";
		cin >> leerDato;
		for (int i = 0; i < sizeof(NameCiudad); i++){
			NameCiudad[i] = leerDato[i];
		}
		ofstream writeFile("Ciudades.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recordNumber -1)*( sizeof(IdCiudad) + sizeof(NameCiudad) )  );
		}else{
			writeFile.seekp(HeaderSize + recordNumber*( sizeof(IdCiudad) + sizeof(NameCiudad)) );
		}
		
		writeFile.seekp(HeaderSize + recordNumber*( sizeof(IdCiudad) + sizeof(NameCiudad)) );
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		recordNumber++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		writeFile.close();
		TreeCity.Agregar(Index(atol(streamId.str().c_str()) , recordNumber-1));
	}
}
void agregarClient(){
	ifstream readFile("Clientes.bin", ios::binary);
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	readFile.seekg(0);
	int rrnHeader, recordNumber,cont = 0;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.seekg(HeaderSize + rrnHeader*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))+ sizeof(IdClient) );
	readFile.read(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(NameClient); i++){
		streamNombre << NameClient[i];
	}
	int newRRNHeader = atoi(streamNombre.str().c_str());
	cout << newRRNHeader << "°|°" << endl;
	readFile.close();
	string leerName = "",leerId = "", leerGender = "",leerCiudad = "";
	if(rrnHeader != -1){
		cout << "Ingrese el Id del cliente: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){
			IdClient[i] = leerId[i];
			ss<< leerId[i];
		}
		
		cout << "Ingrese el nombre del cliente: ";
		cin >> leerName;
		for (int i = 0; i < sizeof(NameClient); i++){
			NameClient[i] = leerName[i];
		}

		cout << "Ingrese el genero del cliente: ";
		cin >> leerGender;
		for (int i = 0; i < sizeof(Gender); i++){
			Gender[i] = leerGender[i];
		}

		cout << "Ingrese la ciudad en la que el cliente vive: ";
		cin >> leerCiudad;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerCiudad[i];
		}

		ofstream writeFile("Clientes.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		writeFile.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient));
		writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
		writeFile.write(reinterpret_cast<char*>(&Gender), sizeof(Gender));
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&newRRNHeader), sizeof(newRRNHeader));
		writeFile.close();
		int position = PosicionIngresoOrdenadoAlIndice( indexClientKey  , atoi(ss.str().c_str()) );
		indexClientKey.insert(indexClientKey.begin()+ position, ss.str());
		TreeClient.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el Id del cliente: ";
		cin >> leerId;
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){
			IdClient[i] = leerId[i];
			ss<< leerId[i];
		}
		
		cout << "Ingrese el nombre del cliente: ";
		cin >> leerName;
		for (int i = 0; i < sizeof(NameClient); i++){
			NameClient[i] = leerName[i];
		}

		cout << "Ingrese el genero del cliente: ";
		cin >> leerGender;
		for (int i = 0; i < sizeof(Gender); i++){
			Gender[i] = leerGender[i];
		}

		cout << "Ingrese la ciudad en la que el cliente vive: ";
		cin >> leerCiudad;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			IdCiudad[i] = leerCiudad[i];
		}
		ofstream writeFile("Clientes.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recordNumber-1)*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}else{
			writeFile.seekp(HeaderSize + (recordNumber )*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad))  );
		}
		writeFile.seekp(HeaderSize + recordNumber*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad)) );
		writeFile.write(reinterpret_cast<char*>(&IdClient), sizeof(IdClient));
		writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
		writeFile.write(reinterpret_cast<char*>(&Gender), sizeof(Gender));
		writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		recordNumber++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		writeFile.close();
		TreeClient.Agregar(Index(atol(ss.str().c_str()) , recordNumber-1));
	}
}
void agregarNumero(){
	ifstream readFile("Numeros.bin", ios::binary);
	char Numero[9];
	char Id[14];
	readFile.seekg(0);
	int rrnHeader, recordNumber,cont = 0;
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.seekg(HeaderSize + rrnHeader*( sizeof(Numero) + sizeof(Id) )+ sizeof(Numero) );
	readFile.read(reinterpret_cast<char*>(&Id), sizeof(Id));
	stringstream streamNombre;
	for (int i = 0; i < sizeof(Id); i++){
		streamNombre << Id[i];
	}
	int newRRNHeader = atoi(streamNombre.str().c_str());
	readFile.close();
	string leerId = "", leerDato = "";
	if(rrnHeader != -1){
		cout << "Ingrese el numero: ";
		cin >> leerDato;
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = leerDato[i];
			ss<< leerDato[i];
		}
		
		cout << "Ingrese id del cliente que posee este numero: ";
		cin >> leerId;
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = leerId[i];
		}
		ofstream writeFile("Numeros.bin", ofstream::in | ofstream :: out);
		writeFile.seekp(HeaderSize + rrnHeader*( sizeof(Numero) + sizeof(Id) )  );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
		writeFile.seekp(0);
		writeFile.write(reinterpret_cast<char*>(&newRRNHeader), sizeof(newRRNHeader));
		writeFile.close();
		int position = PosicionIngresoOrdenadoAlIndice( indexNumberKey  , atoi(ss.str().c_str()) );
		indexNumberKey.insert(indexNumberKey.begin()+ position, ss.str());
		TreeNumber.Agregar(Index(atol(ss.str().c_str()) , rrnHeader));
	}else{
		cout << "Ingrese el numero: ";
		cin >> leerDato;
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++){
			Numero[i] = leerDato[i];
			ss<< leerDato[i];
		}
		
		cout << "Ingrese id del cliente que posee este numero: ";
		cin >> leerId;
		for (int i = 0; i < sizeof(Id); i++){
			Id[i] = leerId[i];
		}
		ofstream writeFile("Numeros.bin", ofstream::in | ofstream::out);
		if(rrnHeader == -1){
			writeFile.seekp(HeaderSize + (recordNumber-1)*( sizeof(Numero) + sizeof(Id))  );
		}else{
			writeFile.seekp(HeaderSize + (recordNumber)*( sizeof(Numero) + sizeof(Id))  );
		}
		writeFile.seekp(HeaderSize + recordNumber*( sizeof(Numero) + sizeof(Id)) );
		writeFile.write(reinterpret_cast<char*>(&Numero), sizeof(Numero));
		writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
		recordNumber++;
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		writeFile.close();
		TreeNumber.Agregar(Index(atol(ss.str().c_str()) , recordNumber-1));
	}
}
//Modificar de todos
void modificarCity(){
	char IdCiudad[4];
	char NameCiudad[40];
	string leerId = "", leerDato = "",key = "";
	cout << "Ingrese la llave de la ciudad que desea modificar"<<endl;
	cin >>key;
	int position = PosicionIngresoOrdenadoAlIndice(indexCityKey, atoi(key.c_str()));

	cout << "Nuevo nombre de la ciudad: ";
	cin >> leerDato;
	for (int i = 0; i < sizeof(NameCiudad); i++){
		NameCiudad[i] = leerDato[i];
	}
	ofstream writeFile("Ciudades.bin", ofstream::in | ofstream :: out);
	int rrnModificar = atoi(indexCityRRN.at(position).c_str());
	writeFile.seekp(HeaderSize + rrnModificar*( sizeof(IdCiudad) + sizeof(NameCiudad) ) + sizeof(IdCiudad)  );
	//writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
	writeFile.write(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
	writeFile.close();
	/*int position2 = PosicionIngresoOrdenadoAlIndice( indexCityKey  , atoi(ss.str().c_str()) );
	indexCityKey.insert(indexCityKey.begin()+ position2, ss.str());*/
}
void modificarClient(){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	string leerName = "",leerId = "", leerGender = "",leerCiudad = "",key = "";
	cout << "Ingrese la llave del cliente que desea modificar"<<endl;
	cin >>key;
	int position = PosicionIngresoOrdenadoAlIndiceLong(indexClientKey, atol(key.c_str()));
	
	cout << "Nuevo nombre del cliente: ";
	cin >> leerName;
	for (int i = 0; i < sizeof(NameClient); i++){
		NameClient[i] = leerName[i];
	}

	cout << "Nuevo genero del cliente: ";
	cin >> leerGender;
	for (int i = 0; i < sizeof(Gender); i++){
		Gender[i] = leerGender[i];
	}

	cout << "Nuevo ciudad en la que el cliente vive: ";
	cin >> leerCiudad;
	for (int i = 0; i < sizeof(IdCiudad); i++){
		IdCiudad[i] = leerCiudad[i];
	}
	ofstream writeFile("Clientes.bin", ofstream::in | ofstream :: out);
	int rrnModificar = atoi(indexClientRRN.at(position).c_str());
	writeFile.seekp(HeaderSize + rrnModificar*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad)) + sizeof(IdClient)  );
	writeFile.write(reinterpret_cast<char*>(&NameClient), sizeof(NameClient));
	writeFile.write(reinterpret_cast<char*>(&Gender), sizeof(Gender));
	writeFile.write(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
	writeFile.close();
	/*int position = PosicionIngresoOrdenadoAlIndice( indexClientKey  , atoi(ss.str().c_str()) );
	indexClientKey.insert(indexClientKey.begin()+ position, ss.str());*/
}
void modificarNumber(){
	char Numero[9];
	char Id[14];
	int cont = 0;
	string leerId = "", leerDato = "",key = "";
	cout << "Ingrese el numero que desea modificar"<<endl;
	cin >>key;
	int position = PosicionIngresoOrdenadoAlIndice(indexNumberKey, atoi(key.c_str()));
	cout << "Nuevo id del cliente que posee este numero: ";
	cin >> leerId;
	for (int i = 0; i < sizeof(Id); i++){
		Id[i] = leerId[i];
	}
	
	ofstream writeFile("Numeros.bin", ofstream::in | ofstream :: out);
	int rrnModificar = atoi(indexNumberRRN.at(position).c_str());
	writeFile.seekp(HeaderSize + rrnModificar*( sizeof(Numero) + sizeof(Id) )+ sizeof(Numero)  );
	writeFile.write(reinterpret_cast<char*>(&Id), sizeof(Id));
	writeFile.close();
	/*int position2 = PosicionIngresoOrdenadoAlIndice( indexCityKey  , atoi(ss.str().c_str()) );
	indexCityKey.insert(indexCityKey.begin()+ position2, ss.str());*/
}
//busqueda directa con index
void buscarCityIndexado(int key){
	char IdCiudad[4];
	char NameCiudad[40];
	
	int position = PosicionBusquedaOrdenadaAlIndiceLong(indexCityKey, (long)key);
	ifstream readFile("Ciudades.bin", ios::binary);

	if (position != -1){
		string rrn = indexCityRRN.at(position);
		readFile.seekg(HeaderSize + atoi((rrn).c_str())*( sizeof(IdCiudad) + sizeof(NameCiudad) ));
		readFile.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad) );
		readFile.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad) );		
		cout << "Id Ciudad : " << IdCiudad <<endl;
		cout << "Nombre de la ciudad: " << NameCiudad << endl;	
	}else
		cout << "El registro no se encuentra entre los datos."<<endl;
	
	readFile.close();
}
void buscarClientIndexado(unsigned long key){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	int position = PosicionBusquedaOrdenadaAlIndiceLong(indexClientKey, key);
	ifstream readFile("Clientes.bin", ios::binary);
	if (position != -1){
		string rrn = indexClientRRN.at(position);
		readFile.seekg(HeaderSize + atoi((rrn).c_str())*( sizeof(IdClient) + sizeof(NameClient) + sizeof(Gender) + sizeof(IdCiudad) ));
		readFile.read(reinterpret_cast<char*>(&IdClient), sizeof(IdClient) );
		readFile.read(reinterpret_cast<char*>(&NameClient), sizeof(NameClient) );		
		readFile.read(reinterpret_cast<char*>(&Gender), sizeof(Gender) );
		readFile.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad) );		
		cout << "Id Cliente : " << IdClient <<endl;
		cout << "Nombre del cliente: " << NameClient << endl;	
		cout << "Genero: " << Gender <<endl;
		cout << "ID Ciudad: " << IdCiudad << endl;	
	}else
		cout << "El registro no se encuentra entre los datos."<< endl;
	
	readFile.close();
}
void buscarNumberIndexado( int key){
	char Numero[9];
	char IdNumber[14];
	int position = PosicionBusquedaOrdenadaAlIndiceLong(indexNumberKey, (long)key);
	ifstream readFile("Numeros.bin", ios::binary);
	if (position != -1){		
		string rrn = indexNumberRRN.at(position);
		readFile.seekg(HeaderSize + atoi((rrn).c_str())*( sizeof(Numero) + sizeof(IdNumber) ));
		readFile.read(reinterpret_cast<char*>(&Numero), sizeof(Numero) );
		readFile.read(reinterpret_cast<char*>(&IdNumber), sizeof(IdNumber) );		
		cout << "Numero: " << Numero <<endl;
		cout << "Id del cliente: " << IdNumber << endl;	
	}else
		cout << "El registro no se encuentra entre los datos."<< endl;
	
	readFile.close();
}
//busqueda secuenial sin index.
void buscarCity(int key){
	cout<< "entro" << endl;
	char IdCiudad[4];
	char NameCiudad[40];	
	ifstream readFile("Ciudades.bin",ios::binary);
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	//cout << rrn <<"||"<< recordNumber<<"||" << indexindexFlag <<endl;
	bool encontrado = false;
 	while(true){

		if(readFile.eof())
			break;
		readFile.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad));
		readFile.read(reinterpret_cast<char*>(&NameCiudad), sizeof(NameCiudad));
		stringstream ss;
		for (int i = 0; i < sizeof(IdCiudad); i++){							
			ss<< IdCiudad[i];	
		}
		int keyLeida = atoi(ss.str().c_str());	
		if(keyLeida == key){
			encontrado = true;
			cout << "Id Ciudad : " << IdCiudad <<endl;
			cout << "Nombre de la ciudad: " << NameCiudad << endl;	
			break;
		}

	}
	if(!encontrado)
		cout << "El registro no se encuentra entre los datos."<< endl;
	
	readFile.close();
}
void buscarClient(unsigned long key){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	bool encontrado = false;
	ifstream readFile("Clientes.bin",ios::binary);
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
 	while(true){
		if(readFile.eof())
			break;
		readFile.read(reinterpret_cast<char*>(&IdClient), sizeof(IdClient) );
		readFile.read(reinterpret_cast<char*>(&NameClient), sizeof(NameClient) );		
		readFile.read(reinterpret_cast<char*>(&Gender), sizeof(Gender) );
		readFile.read(reinterpret_cast<char*>(&IdCiudad), sizeof(IdCiudad) );		
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){							
			ss<< IdClient[i];	
		}
		unsigned long keyLeida = atol(ss.str().c_str());		
		if(keyLeida == key){
			encontrado = true;
			cout << "Id Cliente : " << IdClient <<endl;
			cout << "Nombre del cliente: " << NameClient << endl;	
			cout << "Genero: " << Gender <<endl;
			cout << "ID Ciudad: " << IdCiudad << endl;	
			break;
		}

	}
	if(!encontrado)
		cout << "El registro no se encuentra entre los datos."<< endl;
	
	readFile.close();
}
void buscarNumber( int key){
	char Numero[9];
	char IdNumber[14];	
	ifstream readFile("Numeros.bin",ios::binary);
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	//cout << rrn <<"||"<< recordNumber<<"||" << indexindexFlag <<endl;
	bool encontrado = false;
 	while(true){
		if(readFile.eof())
			break;
		
		readFile.read(reinterpret_cast<char*>(&Numero), sizeof(Numero) );
		readFile.read(reinterpret_cast<char*>(&IdNumber), sizeof(IdNumber) );				
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++)					
			ss<< Numero[i];	

		int keyLeida = atoi(ss.str().c_str());	
		if(keyLeida == key){
			encontrado = true;
			cout << "Numero: " << Numero <<endl;
			cout << "Id del cliente: " << IdNumber << endl;	
			break;
		}

	}
	if(!encontrado)
		cout << "El registro no se encuentra entre los datos."<< endl;
	
	readFile.close();
}
void CrearArbolCity(){
	int rrn=-1, recordNumber = 0, endFile = 0,cont = 0;
	unsigned long agregado = 0;
	bool indexindexFlag = 0;
	
	ifstream readFile("Ciudades.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
 	while(endFile < recordNumber){
 		char IdCiudad[4];
		char NameCiudad[40];
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		readFile.read((char*)NameCiudad, sizeof(NameCiudad));
		stringstream ss;
		for (int i = 0; i < sizeof(IdCiudad); i++){
			ss << IdCiudad[i];
		}
		if( IdCiudad[0] != '*'){
			agregado = atol(ss.str().c_str());
			Index ingresado(agregado,cont);
			TreeCity.Agregar(ingresado);
		}
		endFile++;
		cont++;

	}
	readFile.close();
	//TreeCity.Listar();
}
void CrearArbolClient(){
	int rrn=-1, recordNumber = 0, endFile = 0;
	unsigned long agregado = 0;
	bool indexindexFlag = 0;
	int cont = 0;
	
	ifstream readFile("Clientes.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		char IdClient[14];
		char NameClient[40];
		char Gender[2];
		char IdCiudad[4];
		readFile.read((char*)IdClient, sizeof(IdClient));
		readFile.read((char*)NameClient, sizeof(NameClient));
		readFile.read((char*)Gender, sizeof(Gender));
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		stringstream ss;
		for (int i = 0; i < sizeof(IdClient); i++){
			ss << IdClient[i];
		}
		
		if( IdClient[0] != '*'){
			agregado = atol(ss.str().c_str());
			Index ingresado(agregado,cont);
			TreeClient.Agregar(ingresado);
		}
		//cout << agregado<<"|||||||"<<endFile<<endl;
		endFile++;
		cont ++;

	}
	readFile.close();
	//TreeClient.Listar();
}
void CrearArbolNumber(){
	int rrn=-1, recordNumber = 0, endFile = 0;
	unsigned long agregado = 0;
	bool indexindexFlag = 0;
	int cont = 0;
	
	ifstream readFile("Numeros.bin",ios::binary);
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		char Numero[9];
		char Id[14];
		readFile.read((char*)Numero, sizeof(Numero));
		readFile.read((char*)Id, sizeof(Id));
		stringstream ss;
		for (int i = 0; i < sizeof(Numero); i++){
			ss << Numero[i];
		}
		if( Numero[0] != '*'){
			agregado = atol(ss.str().c_str());
			Index ingresado(agregado,cont);
			TreeNumber.Agregar(ingresado);
		}
		endFile++;
		cont++;

	}
	readFile.close();
	//TreeNumber.Listar();
}
void Tarifa(unsigned long key){
	
	vector<int> vectorNumero;
	int rrn=-1, recordNumber = 0,endFile = 0;
	bool indexindexFlag = 0;
	ifstream readFileNumber("Numeros.bin",ios::binary);
	readFileNumber.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFileNumber.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFileNumber.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFileNumber.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	while(endFile < recordNumber){
		char Numero[9];
		char Id[14];
		char IdTemporal[14];
		readFileNumber.read((char*)Numero, sizeof(Numero));
		readFileNumber.read((char*)Id, sizeof(Id));
		if( Numero[0] != '*'){
			stringstream ss,ssNumber,ssKey;
			for (int i = 0; i < sizeof(Id); ++i){
				ss<<Id[i];
			}
			for (int i = 0; i < sizeof(Numero); ++i){
				ssNumber<<Numero[i];
			}
			ssKey<<key;
			for (int i = 0; i < sizeof(Id); ++i)
			{
				IdTemporal[i] = ssKey.str()[i];
			}
			if(strcmp(Id,IdTemporal) == 0){
				vectorNumero.push_back(atoi(ssNumber.str().c_str()));
			}
		}
		endFile++;

	}
	if(vectorNumero.size() == 0){
		cout << "No se encontro el cliente o no tiene registrado un numero"<< endl;
		return;
	}

	readFileNumber.close();
	ifstream readFile("Llamadas.bin",ios::binary);
	readFile.seekg(0);
	rrn=-1;
	recordNumber = 0;
	endFile=0;
	indexindexFlag = 0;
	int Id;
	double TarifaTotal = 0;
	unsigned long SegundosTiempoTotal=0;
	char Numero[9];
	char FechaInicio[20];
	char FechaFinal[20];
	char NumDestino[9];
	readFile.read( reinterpret_cast<char*>(&rrn), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&recordNumber), sizeof(int) );
	readFile.read( reinterpret_cast<char*>(&indexindexFlag), sizeof(bool)  );
	readFile.seekg(sizeof(int)+sizeof(int)+sizeof(bool));
	for (int i = 0; i < vectorNumero.size(); i++){
		while(endFile < recordNumber){
		char NumeroTemporal[9];
		readFile.read(reinterpret_cast<char*>(&Id), sizeof(Id));
		readFile.read((char*)Numero, sizeof(Numero));
		readFile.read((char*)FechaInicio, sizeof(FechaInicio));
		readFile.read((char*)FechaFinal, sizeof(FechaFinal));
		readFile.read((char*)NumDestino, sizeof(NumDestino));
		stringstream ss, TiempoInicio, TiempoFinal,ssNumeroTemporal;
		//cout << Numero << "||" << FechaInicio << "||"<< FechaFinal << "||" <<NumDestino;
		unsigned long SegundosTiempoInicio=0, SegundosTiempoFinal=0;
		int DiferenciaTiempo = 0;
		for (int j = 0; j < sizeof(FechaInicio); ++j){
			TiempoInicio << FechaInicio[j];
		}
		for (int k = 0; k < sizeof(FechaFinal); ++k){
			TiempoFinal << FechaFinal[k];
		}
		ssNumeroTemporal << vectorNumero.at(i);
		for (int j = 0; j < sizeof(Numero); ++j)
		{			
			NumeroTemporal[j] = ssNumeroTemporal.str()[j];
		}
		
		if ( strcmp(Numero, NumeroTemporal) == 0){
			SegundosTiempoInicio += atol(TiempoInicio.str().substr(0,4).c_str())* 31536000;
			SegundosTiempoInicio += atol(TiempoInicio.str().substr(5,2).c_str())* 2419200;
			SegundosTiempoInicio += atol(TiempoInicio.str().substr(8,2).c_str())* 86400;
			SegundosTiempoInicio += atol(TiempoInicio.str().substr(11,2).c_str())* 3600;
			SegundosTiempoInicio += atol(TiempoInicio.str().substr(14,2).c_str())* 60 + atol(TiempoInicio.str().substr(17,2).c_str());

			SegundosTiempoFinal += atol(TiempoFinal.str().substr(0,4).c_str())* 31536000;
			SegundosTiempoFinal += atol(TiempoFinal.str().substr(5,2).c_str())* 2419200;
			SegundosTiempoFinal += atol(TiempoFinal.str().substr(8,2).c_str())* 86400;
			SegundosTiempoFinal += atol(TiempoFinal.str().substr(11,2).c_str())* 3600;
			SegundosTiempoFinal += atol(TiempoFinal.str().substr(14,2).c_str())* 60 + atol(TiempoFinal.str().substr(17,2).c_str());

			DiferenciaTiempo = SegundosTiempoFinal - SegundosTiempoInicio;
			SegundosTiempoTotal += (SegundosTiempoFinal - SegundosTiempoInicio);

			if(atoi(TiempoInicio.str().substr(11,2).c_str())>= 0 && atoi(TiempoFinal.str().substr(11,2).c_str())< 8){
				TarifaTotal += ((DiferenciaTiempo/60) * 0.01);
			}else if(atoi(TiempoInicio.str().substr(11,2).c_str())>= 8 && atoi(TiempoFinal.str().substr(11,2).c_str())< 16){
				TarifaTotal += ((DiferenciaTiempo/60) * 0.04);
			}else if(atoi(TiempoInicio.str().substr(11,2).c_str())>= 16 && atoi(TiempoFinal.str().substr(11,2).c_str())< 24){
				TarifaTotal += ((DiferenciaTiempo/60) * 0.05);
			}
		
		}
		endFile++;
	}
	readFile.close();
	}
	if(vectorNumero.size() != 0){
		cout << "Los numeros que el cliente posee son: "<<endl;

		for (int i = 0; i < vectorNumero.size(); ++i)
			cout << "\t* " << vectorNumero.at(i) << endl;

		cout << "El cliente hablo " << SegundosTiempoTotal << " segundos en total." << endl;
		cout << "La tarifa total del numero " << key << " es de $"<< TarifaTotal<<endl;

	}	
}
void BuscarCityArbol(int rrn){
	char IdCiudad[4];
	char NameCiudad[40];
	ifstream readFile("Ciudades.bin",ios::binary);	
	readFile.seekg(HeaderSize + (sizeof(IdCiudad) + sizeof(NameCiudad)) * rrn );
	readFile.read((char*)IdCiudad, sizeof(IdCiudad));
	readFile.read((char*)NameCiudad, sizeof(NameCiudad));
	cout <<"----------------------------------------------------------------------------"<<endl;
	cout << "Id Ciudad: "<<IdCiudad <<endl;
	cout << "Nombre de la ciudad: " <<NameCiudad<<endl;	
	readFile.close();
}
void BuscarClientArbol(int rrn){
	char IdClient[14];
	char NameClient[40];
	char Gender[2];
	char IdCiudad[4];
	ifstream readFile("Clientes.bin",ios::binary);
	readFile.seekg(HeaderSize + (sizeof(IdClient) + sizeof(NameClient)+ sizeof(Gender)+ sizeof(IdCiudad)) * rrn );
	readFile.read((char*)IdClient, sizeof(IdClient));
	readFile.read((char*)NameClient, sizeof(NameClient));
	readFile.read((char*)Gender, sizeof(Gender));
	readFile.read((char*)IdCiudad, sizeof(IdCiudad));
	cout <<"----------------------------------------------------------------------------"<<endl;
	cout << "Id: " << IdClient << endl;
	cout << "Nombre: " << NameClient <<endl; 
	cout << "Genero: " << Gender << endl;
	cout << "Id Ciudad: " << IdCiudad <<endl;
	readFile.close();
}
void BuscarNumberArbol(int rrn){
	char Numero[9];
	char Id[14];
	ifstream readFile("Numeros.bin",ios::binary);
	cout << rrn<< endl;
	readFile.seekg(HeaderSize + ( sizeof(Numero) + sizeof(Id)) * rrn );
	readFile.read((char*)Numero, sizeof(Numero));
	readFile.read((char*)Id, sizeof(Id));
	cout <<"----------------------------------------------------------------------------"<<endl;
	cout << "Numero: " << Numero << endl;
	cout << "Id Propietario: " << Id <<endl; 
	readFile.close();
}
int PosicionBusquedaOrdenadaAlIndiceLong(vector<string> indexKey  , unsigned long key){
    int low = 0;
    int high = indexKey.size() - 1;
    int mid;
    bool avoidInfiniteCicle = false;
    
    while(true){
    	if(low > high)
    		break;    	
    	mid = (low + high)/2;
    	if(key == atol((indexKey.at(mid)).c_str()) )
    		return mid;
    	if(key > atol((indexKey.at(mid)).c_str())){
    		if(mid != indexKey.size() - 1){
    			if(key < atol((indexKey.at(mid+1)).c_str())){
    				return -1;
    			}else{
    				if(avoidInfiniteCicle && mid == indexKey.size()-2)
    					return -1;
    				low = mid;
    				avoidInfiniteCicle = true;
    			}
    		}else{
    			if(key < atol((indexKey.at(mid)).c_str())){
    				return -1;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(mid != 0){
    			if(key > atol((indexKey.at(mid-1)).c_str())){

    				return -1;
    			}else{
    				high = mid;
    			}
    		}else{
    			if(key < atol((indexKey.at(mid)).c_str())){
    				return -1;
    			}else{
    				return -1;
    			}

    		}
    	}
    }
    return -1;
}
void CompactarCity(){
	ifstream readFile("Ciudades.bin");
	ofstream writeFile("Tmp.bin");
	int rrn;
	int recordNumber;
	bool indexFlag;
	readFile.read((char*)&rrn, sizeof(int));
	readFile.read((char*)&recordNumber, sizeof(int));
	readFile.read((char*)&indexFlag, sizeof(bool));
	rrn=-1;
	writeFile.write((char*)&rrn, sizeof(rrn));
	writeFile.write((char*)&recordNumber, sizeof(recordNumber));
	writeFile.write((char*)&indexFlag, sizeof(indexFlag));
	int cont=0;
	int recordNumberTmp=0;
	while(cont<recordNumber){
		char IdCiudad[4];
		char NombreCiudad[40];
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		readFile.read((char*)NombreCiudad, sizeof(NombreCiudad));
		if (IdCiudad[0]!='*'){
			writeFile.write((char*)IdCiudad, sizeof(IdCiudad));
			writeFile.write((char*)NombreCiudad, sizeof(NombreCiudad));
			recordNumberTmp++;
		}
		cont++;
	}
	readFile.close();
	writeFile.seekp( sizeof(int));
	writeFile.write((char*)&recordNumberTmp, sizeof(int));
	writeFile.close();
	Tree newTree(orden);
	TreeCity = newTree;
	CrearArbolCity();
	remove("Ciudades.bin");
	rename("Tmp.bin","Ciudades.bin");
	IndexCity();
}
void CompactarClient(){
	ifstream readFile("Clientes.bin");
	ofstream writeFile("Tmp.bin");
	int rrn;
	int recordNumber;
	bool indexFlag;
	readFile.read((char*)&rrn, sizeof(int));
	readFile.read((char*)&recordNumber, sizeof(int));
	readFile.read((char*)&indexFlag, sizeof(bool));
	rrn=-1;
	writeFile.write((char*)&rrn, sizeof(rrn));
	writeFile.write((char*)&recordNumber, sizeof(recordNumber));
	writeFile.write((char*)&indexFlag, sizeof(indexFlag));
	int cont=0;
	int recordNumberTmp=0;
	while(cont<recordNumber){
		char IdClient[14];
		char NameClient[40];
		char Gender[2];
		char IdCiudad[4];
		readFile.read((char*)IdClient, sizeof(IdClient));
		readFile.read((char*)NameClient, sizeof(NameClient));
		readFile.read((char*)Gender, sizeof(Gender));
		readFile.read((char*)IdCiudad, sizeof(IdCiudad));
		if (IdClient[0]!='*'){
			writeFile.write((char*)IdClient, sizeof(IdClient));
			writeFile.write((char*)NameClient, sizeof(NameClient));
			writeFile.write((char*)Gender, sizeof(Gender));
			writeFile.write((char*)IdCiudad, sizeof(IdCiudad));
			recordNumberTmp++;
		}
		cont++;
	}
	readFile.close();
	writeFile.seekp( sizeof(int));
	writeFile.write((char*)&recordNumberTmp, sizeof(int));
	writeFile.close();
	Tree newTree(orden);
	TreeCity = newTree;
	CrearArbolClient();
	remove("Clientes.bin");
	rename("Tmp.bin","Clientes.bin");
	IndexClient();
}
void CompactarNumber(){
	ifstream readFile("Numeros.bin");
	ofstream writeFile("Tmp.bin");
	int rrn;
	int recordNumber;
	bool indexFlag;
	readFile.read((char*)&rrn, sizeof(int));
	readFile.read((char*)&recordNumber, sizeof(int));
	readFile.read((char*)&indexFlag, sizeof(bool));
	rrn=-1;
	writeFile.write((char*)&rrn, sizeof(rrn));
	writeFile.write((char*)&recordNumber, sizeof(recordNumber));
	writeFile.write((char*)&indexFlag, sizeof(indexFlag));
	int cont=0;
	int recordNumberTmp=0;
	while(cont<recordNumber){
		char Numero[9];
		char Id[14];
		readFile.read((char*)Numero, sizeof(Numero));
		readFile.read((char*)Id, sizeof(Id));
		if (Numero[0]!='*'){
			writeFile.write((char*)&Numero, sizeof(Numero));
			writeFile.write((char*)&Id, sizeof(Id));
			recordNumberTmp++;
		}
		cont++;
	}
	readFile.close();
	writeFile.seekp( sizeof(int));
	writeFile.write((char*)&recordNumberTmp, sizeof(int));
	writeFile.close();
	Tree newTree(orden);
	TreeCity = newTree;
	CrearArbolCity();
	remove("Numeros.bin");
	rename("Tmp.bin","Numeros.bin");
	IndexCity();
}
void readIndexCity(){
	indexCityKey.clear();
	indexCityRRN.clear();
	ifstream readFile("IndexCity.bin",ios::binary);
	readFile.seekg(HeaderSize);
	int cont = 0;
	while(true){
		if(readFile.eof()){
			break;
		}

		int IndexLlaveCity;
		unsigned long IndexLlaveRRN;
		stringstream ss,ssRRN;
		readFile.read( reinterpret_cast<char*>(&IndexLlaveCity), sizeof(IndexLlaveCity) );
  		readFile.read( reinterpret_cast<char*>(&IndexLlaveRRN), sizeof(IndexLlaveRRN) );
		ss << IndexLlaveCity;
		ssRRN << IndexLlaveRRN;
  		indexCityKey.push_back(ss.str());
  		indexCityRRN.push_back(ssRRN.str());
		
	}
	readFile.close();
}
void readIndexClient(){
	indexClientKey.clear();
	indexClientRRN.clear();
	ifstream readFile("IndexClient.bin",ios::binary);
	readFile.seekg(HeaderSize);
	int cont = 0;
	while(true){
		if(readFile.eof()){
			break;
		}

		int IndexLlaveClient;
		unsigned long IndexLlaveRRN;
		stringstream ss,ssRRN;
		readFile.read( reinterpret_cast<char*>(&IndexLlaveClient), sizeof(IndexLlaveClient) );
  		readFile.read( reinterpret_cast<char*>(&IndexLlaveRRN), sizeof(IndexLlaveRRN) );
		ss << IndexLlaveClient;
		ssRRN << IndexLlaveRRN;
  		indexClientKey.push_back(ss.str());
  		indexClientRRN.push_back(ssRRN.str());
		
	}
	readFile.close();
}
void readIndexNumber(){
	indexNumberKey.clear();
	indexNumberRRN.clear();
	ifstream readFile("IndexCity.bin",ios::binary);
	readFile.seekg(HeaderSize);
	int cont = 0;
	while(true){
		if(readFile.eof()){
			break;
		}

		int IndexLlaveNumeros;
		unsigned long IndexLlaveRRN;
		stringstream ss,ssRRN;
		readFile.read( reinterpret_cast<char*>(&IndexLlaveNumeros), sizeof(IndexLlaveNumeros) );
  		readFile.read( reinterpret_cast<char*>(&IndexLlaveRRN), sizeof(IndexLlaveRRN) );
		ss << IndexLlaveNumeros;
		ssRRN << IndexLlaveRRN;
  		indexNumberKey.push_back(ss.str());
  		indexNumberRRN.push_back(ssRRN.str());
		
	}
	readFile.close();
}