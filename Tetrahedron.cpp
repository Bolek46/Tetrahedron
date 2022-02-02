// Tetrahedron.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <graphics.h>
#include <cmath>

struct point2D {
	int x, y;
};

int X_SCALE = 1;
int Y_SCALE = 1;
double Z_SCALE = 1.5;
int szerokosc_ekranu = 1500;
int wysokosc_ekranu = 1000;

struct point3D;

int angle(point3D X);

struct point3D {
	int x, y, z;

	point2D CastTo2D(point3D A) {
		point2D ret;
		ret.x = (int)((A.x*X_SCALE*pow(Z_SCALE, A.z/100)));
		ret.y = (int)((A.y*Y_SCALE*pow(Z_SCALE, A.z/100)));
		return ret;
	}
};

point3D center = { szerokosc_ekranu / 2, wysokosc_ekranu / 2,0 };
void tetrahedron(point3D A, point3D B, point3D C, point3D D);
int length(point3D A, point3D B);
point3D rotateOX(point3D,int angle);
void podzial();

point3D skalowanie(point3D X,int scale);


int main()
{
	//Tworzenie obaszaru
	initwindow(szerokosc_ekranu, wysokosc_ekranu);

	//Linie współrzednych
	line(center.x, 0, center.x, wysokosc_ekranu);
	line(0, center.y, szerokosc_ekranu, center.y);

	podzial();

	point3D A = { 200,-100,-100};
	point3D B = { -100,-100,300 };
	point3D C = { -300,-100,-100};
	point3D D = {-100,200,200};

	point3D D1,A1,B1,C1;
	A1 = A;
	B1 = B;
	C1 = C;
	D1 = D;

	//int angleA = angle(A);
	//int angleB = angle(B);
	//int angleC = angle(C);
	//int angleD = angle(D);
	
	int rozmiar = -1;


	for (double i = -3; i < 3; i++)
	{
		//lol = A1.x;
		//A1.x = A1.x *cos((i)*(M_PI / 180)) - A1.z*sin((i)*(M_PI / 180));
		//A1.z = lol * sin((i)*(M_PI / 180)) + A1.z*cos((i)*(M_PI / 180));

	/*	rotateOX(A1, i);
		B1.x = (int)(sqrt(pow(B.x, 2) + pow(B.z, 2))*(cos((i+angleB)*(M_PI / 180))));
		C1.x = (int)(sqrt(pow(C.x, 2) + pow(C.z, 2))*(cos((i+angleC)*(M_PI / 180))));
		D1.x = (int)(sqrt(pow(D.x, 2) + pow(D.z, 2))*(cos((i+angleD)*(M_PI / 180))));*/


			std::cout << rozmiar;
			std::cout << A.z;
			if (i == 0) rozmiar = rozmiar * (-1);
			A = skalowanie(A, rozmiar);
			B = skalowanie(B, rozmiar);
			C = skalowanie(C, rozmiar);
			D = skalowanie(D, rozmiar);

			A1.x = A.CastTo2D(A).x;
			B1.x = B.CastTo2D(B).x;
			C1.x = C.CastTo2D(C).x;
			D1.x = D.CastTo2D(D).x;

			A1.y = A.CastTo2D(A).y;
			B1.y = B.CastTo2D(B).y;
			C1.y = C.CastTo2D(C).y;
			D1.y = D.CastTo2D(D).y;
			//tetrahedron(rotateOX(A1, 0), rotateOX(B1, 0), rotateOX(C1, 0), rotateOX(D1, 0));
			//tetrahedron(A1, B1, C1, D1);
			//getch();
			
		



			for (int j = 0; j < 360; j=j+3) {
				tetrahedron(rotateOX(A1, j), rotateOX(B1, j), rotateOX(C1, j), rotateOX(D1, j));
				//tetrahedron(A1,B1,C1,D1);

				podzial();
				Sleep(40);
				//getch();
				cleardevice();
			}
		
	}




	getch();
	closegraph();

}

//// obrót w ogół osi Y, o podany kat
//point3D rotateOX(point3D A, int angle1) {
//
//	if (A.x < 0) {
//		A.x = -(int)(sqrt(pow(A.x, 2) + pow(A.z, 2))*(cos((angle1 + angle(A))*(M_PI / 180))));
//	}
//	else {
//		A.x = (int)(sqrt(pow(A.x, 2) + pow(A.z, 2))*(cos((angle1 + angle(A))*(M_PI / 180))));
//	}
//	return A;
//}


point3D rotateOX(point3D A, int angle1) {

		A.x =A.x*(cos(((angle1 + angle(A))*(M_PI / 180))));

	return A;
}

//wartośc scale okresla o jaką wartość wyskalowac punkt, wartość dodatnia przybliża, ujemna oddala
point3D skalowanie(point3D X, int scale) {

	X.z = X.z+(scale*100);
	return X;
}


//Funkcja Czworościanu, łączy liniami kolejne punkty i centruje obraz w środku obszaru
void tetrahedron(point3D A, point3D B, point3D C, point3D D)
{
	A.x = center.x + A.x;
	B.x = center.x + B.x;
	C.x = center.x + C.x;
	D.x = center.x + D.x;

	A.y = center.y - A.y;
	B.y = center.y - B.y;
	C.y = center.y - C.y;
	D.y = center.y - D.y;
	
	line(A.x, A.y, B.x, B.y);
	line(A.x, A.y, C.x, C.y);
	line(C.x, C.y, B.x, B.y);
	line(A.x, A.y, D.x, D.y);
	line(D.x, D.y, C.x, C.y);
	line(D.x, D.y, B.x, B.y);
}

//Funkcja obliczająca długość wektora
//Nieużywana
int length(point3D A, point3D B) {
	int liczba;
	//std::cout << pow((B.x - A.x),2);
	//std::cout << "  ";
	//std::cout << pow((B.y - A.y),2);
	liczba = pow((B.x - A.x), 2) + pow((B.y - A.y), 2);

	return sqrt(liczba);
	//return sqrt(((B.x - A.x),2) + (B.y - A.y) ^ 2);

}

//Funkcja obliczająca kąt na jakim znajduje się punkt pomiedzy osiami X i Z
int angle(point3D A)
{	
	float pom1,pom2;
	pom1 = A.x;
	pom2 = A.z;
	pom1 = atan(pom2/pom1)*180/M_PI;
	return pom1;
}

//Prowizoryczna podziałka osi
void podzial() {

	for (int j = 1; j < 10; j++)
	{
		outtextxy(center.x, center.y + 100 * j, "-");
		outtextxy(center.x, center.y - 100 * j, "-");
		outtextxy(center.x + 100 * j, center.y + 1, "|");
		outtextxy(center.x - 100 * j, center.y + 1, "|");

		//Linie współrzednych
		line(center.x, 0, center.x, wysokosc_ekranu);
		line(0, center.y, szerokosc_ekranu, center.y);
	}
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
