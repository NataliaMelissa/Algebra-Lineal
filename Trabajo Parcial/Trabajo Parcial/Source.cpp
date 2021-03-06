#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Punto {
	//Atributos
	int x; //eje x
	int y; //eje y
	int z; //eje z

	//M?todos
public:
	//Constructor sin par?metros
	Punto() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	//Destructor
	~Punto() {}

	//Obtener datos
	int GetX() { return this->x; }
	int GetY() { return this->y; }
	int GetZ() { return this->z; }

	//Modificar Datos
	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }
	void SetZ(int z) { this->z = z; }

};

class Menu {
	//Atributos: no hay por ahora
	int n = 0; //N?mero de puntos
	int k = 7; //Elementos que hay en las ecuaciones
	Punto* puntos; //Vector de puntos
	int* Ecuacion1 = new int[k]; //Ecuacion de y = ax + bz +cn
	int* Ecuacion2 = new int[k]; //Ecuacion de xy = ax^2 + bxz + cx
	int* Ecuacion3 = new int[k]; //Ecuacion de yz = axz + bz^2 + cz
	float* EcuacionCurva = new float[3]; //Ecuacion de la curva y = ax + bz + cn
	int** MatrizA = new int* [k];
	int* MatrizB = new int[3];
	int** MatrizB1 = new int* [3]; //Matriz A reemplazando la primera columna de A con B
	int** MatrizB2 = new int* [3]; //Matriz A reemplazando la segunda columna de A con B
	int** MatrizB3 = new int* [3]; //Matriz A reemplazando la tercera columna de A con B

	//M?todos
	void InicializarVector(Punto*& puntos, int n) {
		//Se inicializa cada componente del punto (x,y,z) con 0
		for (short i = 0; i < n; i++) {
			puntos[i].SetX(0);
			puntos[i].SetY(0);
			puntos[i].SetZ(0);
		}
	}

	void InicializarEcuacion(int*& Ecuacion, int k) {
		for (short i = 0; i < k; i++) {
			Ecuacion[i] = 0;
		}
	}

	void InicializarEcCurva(float*& EcuacionCurva, int k) {
		for (short i = 0; i < k; i++) {
			EcuacionCurva[i] = 0;
		}
	}

	void InicializarMatrices(int**& Matriz, int n) {
		for (int i = 0; i < n; i++) {
			Matriz[i] = new int[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				Matriz[i][j] = 0;
			}
		}
	}

	void GenerarPuntos(Punto*& puntos, int n) {
		int k = 0; //Variable que tendr? los valores generados aleatoriamente

		for (short i = 0; i < n; i++) {
			//Generar valor en x
			k = -20 + rand() % 40;
			puntos[i].SetX(k);

			//Generar valor en y
			k = -20 + rand() % 40;
			puntos[i].SetY(k);

			//Generar valor en z
			k = -20 + rand() % 40;
			puntos[i].SetZ(k);
		}
	}

	void ValoresMatrizB(int* &MatrizB, int SumaY, int SumaXY, int SumaYZ) {
		MatrizB[0] = SumaY;
		MatrizB[1] = SumaXY;
		MatrizB[2] = SumaYZ;
	}

	void ValorMatrizA(int**& MatrizA, int* Ecuacion1, int* Ecuacion2, int* Ecuacion3) {
		//Fila 1:
		MatrizA[0][0] = Ecuacion1[2];
		MatrizA[0][1] = Ecuacion1[4];
		MatrizA[0][2] = Ecuacion1[6];

		//Fila 2:
		MatrizA[1][0] = Ecuacion2[2];
		MatrizA[1][1] = Ecuacion2[4];
		MatrizA[1][2] = Ecuacion2[6];

		//Fila 3:
		MatrizA[2][0] = Ecuacion3[2];
		MatrizA[2][1] = Ecuacion3[4];
		MatrizA[2][2] = Ecuacion3[6];
	}

	void ValoresMatricesB(int** &MatrizB1, int** &MatrizB2, int** &MatrizB3, int** MatrizA, int* MatrizB) {
		for (short i = 0; i < 3; i++) {
			for (short j = 0; j < 3; j++) {
				if (j != 0)
					MatrizB1[i][j] = MatrizA[i][j];

				if (j != 1)
					MatrizB2[i][j] = MatrizA[i][j];

				if (j != 2)
					MatrizB3[i][j] = MatrizA[i][j];

				else {
					MatrizB1[i][0] = MatrizB[i];
					MatrizB2[i][1] = MatrizB[i];
					MatrizB3[i][2] = MatrizB[i];
				}
			}
			
		}
	}

public:
	//Constructor sin par?metros
	Menu() {
		n = IngresarDatos(); //Ingresar el valor de n
		puntos = new Punto[n]; //El vector puntos tiene el tama?o de n

		//Inicializar Vectores
		InicializarVector(puntos, n);
		InicializarEcuacion(Ecuacion1, k);
		InicializarEcuacion(Ecuacion2, k);
		InicializarEcuacion(Ecuacion3, k);
		InicializarEcCurva(EcuacionCurva, 3);
		InicializarEcuacion(MatrizB, 3);
		InicializarMatrices(MatrizA, 3);
		InicializarMatrices(MatrizB1, 3);
		InicializarMatrices(MatrizB2, 3);
		InicializarMatrices(MatrizB3, 3);

		//Generar puntos
		GenerarPuntos(puntos, n);
	}

	//Destructor
	~Menu() {
		delete[] puntos;
		delete[] Ecuacion1;
		delete[] Ecuacion2;
		delete[] Ecuacion3;
		delete[] EcuacionCurva;
		delete[] MatrizB;

		for (short i = 0; i < 3; i++) {
			delete MatrizA[i];
			delete MatrizB1[i];
			delete MatrizB2[i];
			delete MatrizB3[i];
		}
		delete[] MatrizA;
		delete[] MatrizB1;
		delete[] MatrizB2;
		delete[] MatrizB3;
	}

	//Obtener Datos:
	int GetN() { return this->n; }
	int GetK() { return this->k; }
	int* GetEcuacion1() { return this->Ecuacion1; }
	int* GetEcuacion2() { return this->Ecuacion2; }
	int* GetEcuacion3() { return this->Ecuacion3; }

	//Funciones
	int IngresarDatos() {
		int m;

		cout << "Ingrese la cantidad de puntos a generar entre 12 y 20: " << endl;
		cin >> m;

		if (m < 12 || m > 20) {
			do {
				cout << "El numero no esta en el rango, ingresar el valor nuevamente" << endl;
				cin >> m;
			} while (m < 12 || m > 20);
		}

		return m;
	}

	//Funciones Mostrar Valores
	void MostrarPuntos(Punto* puntos, int n) {
		cout << "Los puntos generados son: " << endl;

		for (short i = 0; i < n; i++) {
			cout << "El punto " << i + 1 << " es: (" << puntos[i].GetX() << "," << puntos[i].GetY() << "," << puntos[i].GetZ() << ")" << endl;
		}

		cout << endl;
	}

	void MostrarSumatorias(int SumaX, int SumaY, int SumaZ, int SumaXZ, int SumaXY, int SumaYZ, int SumaX2, int SumaZ2) {
		cout << "Sumatoria de x:" << SumaX << endl;
		cout << "Sumatoria de y:" << SumaY << endl;
		cout << "Sumatoria de z:" << SumaZ << endl;
		cout << "Sumatoria de xy:" << SumaXY << endl;
		cout << "Sumatoria de xz:" << SumaXZ << endl;
		cout << "Sumatoria de yz:" << SumaYZ << endl;
		cout << "Sumatoria de x al cuadrado:" << SumaX2 << endl;
		cout << "Sumatoria de z al cuadrado:" << SumaZ2 << endl;
	}

	void MostrarEcuaciones(int* Ecuacion, int k) {
		cout << Ecuacion[0] << "=" << Ecuacion[1] << Ecuacion[2] << "+" << Ecuacion[3] << Ecuacion[4] << "+" << Ecuacion[5] << Ecuacion[6] << endl;
	}

	void MostrarEcuacionCurva(float* EcuacionCurva) {
		if (EcuacionCurva[0] != 0.0 && EcuacionCurva[1] != 0.0 && EcuacionCurva[2] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[0] << " x + " << EcuacionCurva[1] << "z + " << EcuacionCurva[2] << endl;

		else if (EcuacionCurva[0] == 0.0 && EcuacionCurva[1] != 0.0 && EcuacionCurva[2] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[1] << "z + " << EcuacionCurva[2] << endl;

		else if (EcuacionCurva[1] == 0.0 && EcuacionCurva[0] != 0.0 && EcuacionCurva[2] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[0] << " x + " << EcuacionCurva[2] << endl;

		else if (EcuacionCurva[2] == 0.0 && EcuacionCurva[0] != 0.0 && EcuacionCurva[1] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[0] << " x + " << EcuacionCurva[1] << "z" << endl;

		else if (EcuacionCurva[0] == 0.0 && EcuacionCurva[1] == 0.0 && EcuacionCurva[2] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[2] << endl;

		else if (EcuacionCurva[0] == 0.0 && EcuacionCurva[2] == 0.0 && EcuacionCurva[1] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[1] << endl;

		else if (EcuacionCurva[1] == 0.0 && EcuacionCurva[2] == 0.0 && EcuacionCurva[0] != 0.0)
			cout << "La ecuacion de la curva es: y = " << EcuacionCurva[0] << endl;

		else
			cout << "La ecuacion de la curva es: y = 0" << endl;
	}

	void MostrarDeterminantes(int detA, int detB1, int detB2, int detB3) {
		cout << "Los determinantes obtenidos son los siguientes: " << endl;
		cout << "El determinante de la matriz A: " << detA << endl;
		cout << "El determinante de la matriz B1: " << detB1 << endl;
		cout << "El determinante de la matriz B2: " << detB2 << endl;
		cout << "El determinante de la matriz B3: " << detB3 << endl << endl;
	}

	void MostrarValores(float a, float b, float c) {
		cout << "Los valores obtenidos para a, b, c son los siguientes: " << endl;
		cout << "El valor de a es: " << a << endl;
		cout << "El valor de b es: " << b << endl;
		cout << "El valor de c es: " << c << endl;
	}

	void MostrarMatrices(int** matriz, int n) {
		for (short i = 0; i < n; i++) {
			for (short j = 0; j < n; j++) {
				cout << matriz[i][j] << " " ;
			}
			cout << endl;
		}
	}

	//Funciones para los valores:
	void SumatoriaPuntos(Punto* puntos, int n, int &SumaX, int &SumaY, int &SumaZ, int &SumaXZ, int &SumaXY, int &SumaYZ, int &SumaX2, int &SumaZ2) {
		for (short i = 0; i < n; i++) {
			SumaX += puntos[i].GetX();
			SumaY += puntos[i].GetY();
			SumaZ += puntos[i].GetZ();
			SumaXY += (puntos[i].GetX() * puntos[i].GetY());
			SumaXZ += (puntos[i].GetX() * puntos[i].GetZ());
			SumaYZ += (puntos[i].GetY() * puntos[i].GetZ());
			SumaX2 += (pow(puntos[i].GetX(), 2));
			SumaZ2 += (pow(puntos[i].GetZ(), 2));
		}
	}

	void ValoresEcuaciones(int*& Ecuacion1, int*& Ecuacion2, int*& Ecuacion3, int k, int SumaX, int SumaY, int SumaZ, int SumaXZ, int SumaXY, int SumaYZ, int SumaX2, int SumaZ2, int n, int a, int b, int c) {
		//Valores de la ecuacion1: y = ax + bz +cn
		Ecuacion1[0] = SumaY;
		Ecuacion1[1] = a;
		Ecuacion1[2] = SumaX;
		Ecuacion1[3] = b;
		Ecuacion1[4] = SumaZ;
		Ecuacion1[5] = c;
		Ecuacion1[6] = n;

		//Valores de la ecuacion2: xy = ax^2 + bxz + cx
		Ecuacion2[0] = SumaXY;
		Ecuacion2[1] = a;
		Ecuacion2[2] = SumaX2;
		Ecuacion2[3] = b;
		Ecuacion2[4] = SumaXZ;
		Ecuacion2[5] = c;
		Ecuacion2[6] = SumaX;

		//Valores de la ecuacion3: yz = axz + bz^2 + cz
		Ecuacion3[0] = SumaYZ;
		Ecuacion3[1] = a;
		Ecuacion3[2] = SumaXZ;
		Ecuacion3[3] = b;
		Ecuacion3[4] = SumaZ2;
		Ecuacion3[5] = c;
		Ecuacion3[6] = SumaZ;
	}

	float Determinante(int** Matriz) {
		//Se utilizar? la regla de Sarrus porque es una matriz 3x3
		float det = 0;

		//Suma de la diagonal principal (DP) y las diagonales que van en su misma direcci?n
		float SumaDP = 0; //Diagonal Principal
		float SumaD1 = 0; //Diagonal que va en su misma direcci?n
		float SumaD2 = 0; //Diagonal que va en su misma direcci?n

		//Suma de la diagonal menor (DM) y las diagonales que van en su misma direcci?n
		float SumaDM = 0; //Diagonal Menor  
		float SumaD3 = 0; //Diagonal que va en su misma direcci?n
		float SumaD4 = 0; //Diagonal que va en su misma direcci?n

		SumaDP = Matriz[0][0] * Matriz[1][1] * Matriz[2][2];
		SumaD1 = Matriz[1][0] * Matriz[2][1] * Matriz[0][2];
		SumaD2 = Matriz[2][0] * Matriz[0][1] * Matriz[1][2];

		SumaDM = Matriz[2][0] * Matriz[1][1] * Matriz[0][2];
		SumaD3 = Matriz[0][0] * Matriz[2][1] * Matriz[1][2];
		SumaD4 = Matriz[1][0] * Matriz[0][1] * Matriz[2][2];

		det = ((SumaDP + SumaD1 + SumaD2) - (SumaDM + SumaD3 + SumaD4));
		return det;
	}

	float ReglaDeCramer(float detA, float detB) {
		float x = 0.0;
		x = detB / detA;
		return x;
	}

	void EcuacionesCurva(float* &EcuacionCurva, float a, float b, float c) {
		EcuacionCurva[0] = a;
		EcuacionCurva[1] = b;
		EcuacionCurva[2] = c;
	}

	void Programa() {
		int SumaX = 0; //Sumatoria Puntos en X
		int SumaY = 0; //Sumatoria Puntos en Y
		int SumaZ = 0; //Sumatoria Puntos en Z
		int SumaXZ = 0; //Sumatoria Puntos en X y Z
		int SumaXY = 0; //Sumatoria Puntos en X y Y
		int SumaYZ = 0; //Sumatoria Puntos en Y y Z
		int SumaX2 = 0; //Sumatoria Puntos en X al cuadrado
		int SumaZ2 = 0; //Sumatoria Puntos en Z al cuadrado

		float detA = 0.0; //Determinante matriz A
		float detB1 = 0.0; //Determinante matriz A reemplazando la primera columna de A con B
		float detB2 = 0.0; //Determinante matriz A reemplazando la segunda columna de A con B
		float detB3 = 0.0; //Determinante matriz A reemplazando la tercera columna de A con B

		int m = GetN();
		float a = 0.0;
		float b = 0.0;
		float c = 0.0;

		MostrarPuntos(puntos, n);

		SumatoriaPuntos(puntos, n, SumaX, SumaY, SumaZ, SumaXZ, SumaXY, SumaYZ, SumaX2, SumaZ2);
		MostrarSumatorias(SumaX, SumaY, SumaZ, SumaXZ, SumaXY, SumaYZ, SumaX2, SumaZ2);
		ValoresEcuaciones(Ecuacion1, Ecuacion2, Ecuacion3, k, SumaX, SumaY, SumaZ, SumaXZ, SumaXY, SumaYZ, SumaX2, SumaZ2, n, a, b, c);
		
		cout << "Se obtienen las siguientes ecuaciones: " << endl;
		MostrarEcuaciones(Ecuacion1, k);
		MostrarEcuaciones(Ecuacion2, k);
		MostrarEcuaciones(Ecuacion3, k);
		cout << "Los valores en 0 son los valores de a,b,c porque aun no se han hallado" << endl;

		//Valores de los determinantes
		ValoresMatrizB(MatrizB, SumaY, SumaXY, SumaYZ);
		ValorMatrizA(MatrizA, Ecuacion1, Ecuacion2, Ecuacion3);
		ValoresMatricesB(MatrizB1, MatrizB2, MatrizB3, MatrizA, MatrizB);

		cout << "Valores matriz A:" << endl;
		MostrarMatrices(MatrizA, 3);

		cout << "Valores matriz B1" << endl;
		MostrarMatrices(MatrizB1, 3);
		
		cout << "Valores matriz B2" << endl;
		MostrarMatrices(MatrizB2, 3);
		
		cout << "Valores matriz B3" << endl;
		MostrarMatrices(MatrizB3, 3);

		detA = Determinante(MatrizA);
		detB1 = Determinante(MatrizB1);
		detB2 = Determinante(MatrizB2);
		detB3 = Determinante(MatrizB3);
		cout << "Utilizando la regla de sarrus se obtienen los determinantes..." << endl << endl;
		MostrarDeterminantes(detA, detB1, detB2, detB3);

		cout << "Utilizando la regla de Cramer se obtienen los valores de a, b, c:" << endl;
		a = ReglaDeCramer(detA, detB1);
		b = ReglaDeCramer(detA, detB2);
		c = ReglaDeCramer(detA, detB3);
		MostrarValores(a, b, c);

		cout << "Una vez obtenidos los valores de a, b, c, se puede obtener la ecuacion de la curva: " << endl;
		EcuacionesCurva(EcuacionCurva, a, b, c);
		MostrarEcuacionCurva(EcuacionCurva);
	}
};

int main() {
	srand(time(NULL)); 
	Menu menu = Menu();
	menu.Programa();
	return 0;
}