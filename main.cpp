#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <bitset>
#include <fstream>
#include <string.h>
#include <cmath>
#include <cstring>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <locale.h>
#include <iomanip>
#include "windows.h"
#include "conio.h"

using namespace std;
//Wersja programu WPP Hellion 1.02
const string wersja_programu="1.02";


//----------------------------------------------------------- zmienne
int x,y;
int znak;
int rodzaj_uruchamiania=0; //rodzaj uruchamiania programu 1=trzymanie klawisza / 2=wl/wyl klikanie
int zabezpieczenie=1; //rodzaj zabezpieczenia programu przed wykryciem
int auto_bot_loop_onoff_klawisz; // klawisz do wlaczenia zapetlania auto bota
int milisekundy=0;
unsigned int ile_plikow_wektorow_licznik=0;
unsigned short klikniecia=0;
string data, z_jakiego_pliku_brac_dane;
vector <string> wszystkie_pliki_tab;
const string pliki_wektorow_myszy="nazwy_plikow_z_zapisanymi_wektorami.txt";
string jaki_jezyk_programu="2";
bool pierwsze_wczytanie_jezyka_z_plikow=true;
const unsigned int language_ilosc_wierszy_pliku=231; // ile jest wierszy w plikach z tlumaczeniem programu
const short ile_programow=7; //ile w hellionie jest wszystkich programow (WPL, auto clicker, kalkulator czasu + OGOLNE,main,obliczanie walut)
string language_PL[ile_programow][language_ilosc_wierszy_pliku], language_ENG[ile_programow][language_ilosc_wierszy_pliku];
//-----------------------------------------------------------

string wyswietl_tekst(unsigned int ktory_program ,unsigned int ktory_wiersz)  //  wyswietl_tekst(,)
{
string linia;
// wczytanie tekstow z plikow do tablic i sprawdzenie czy pliki istnieja w glownym folderze z programem
ktory_wiersz-=1;
if(pierwsze_wczytanie_jezyka_z_plikow==true)
{fstream pl_plik_tekstu, eng_plik_tekstu;
pl_plik_tekstu.open("l_PL.lang"); eng_plik_tekstu.open("l_ENG.lang");
if(pl_plik_tekstu.fail()){system("0C");cout<<"Brak pliku [l_PL.lang] nalezy go pobrac w peciwnym razie program nie bedzie mial tekstu."; getchar();}
else if(eng_plik_tekstu.fail()){system("0C");cout<<"File [l_ENG.lang] is missing, it needs to be downloaded, otherwise the program will lack text."; getchar();}
else
{short do_ktorego_programu=-1;
bool zapisywac_dane=false;
string do_zapisu;
unsigned int numer_tekstu=0;


// zapis do tablicy z polskim tekstem
    for(int i=0;i<language_ilosc_wierszy_pliku;i++)
    {
        getline(pl_plik_tekstu,linia);
        if(linia=="<ogolne>"||linia=="<ustawienia>"||linia=="<WPL>"||linia=="<obliczanie_walut>"||linia=="<AUTO_CLICKER>"||linia=="<Kal_czasu>"||linia=="<main>"){do_ktorego_programu++;numer_tekstu=0;}
        // o = ogolne / 1 = ustawienia / 2 = wpl / 3 = obliczanie walut / 4 = auto clicker / 5 = kal czasu / 6 = main
        else{
                for(int j=0;j<linia.length();j++)
                {
                    if(linia[j]=='>'){zapisywac_dane=true;}   //zapisywac_dane==true
                    if(zapisywac_dane==true && linia[j]!='>'){do_zapisu+=linia[j];}
                }


           language_PL[do_ktorego_programu][numer_tekstu]=do_zapisu;do_zapisu.clear();numer_tekstu++;
           zapisywac_dane=false;
        }
    }


// zapis do tablicy z angielskim tekstem
    do_ktorego_programu=-1; numer_tekstu=0; linia.clear();
    for(int i=0;i<language_ilosc_wierszy_pliku;i++)
    {
        getline(eng_plik_tekstu,linia);
        if(linia=="<ogolne>"||linia=="<ustawienia>"||linia=="<WPL>"||linia=="<obliczanie_walut>"||linia=="<AUTO_CLICKER>"||linia=="<Kal_czasu>"||linia=="<main>"){do_ktorego_programu++;numer_tekstu=0;}
        // o = ogolne / 1 = ustawienia / 2 = wpl / 3 = obliczanie walut / 4 = auto clicker / 5 = kal czasu / 6 = main
        else{
                for(int j=0;j<linia.length();j++)
                {
                    if(linia[j]=='>'){zapisywac_dane=true;}   //zapisywac_dane==true
                    if(zapisywac_dane==true && linia[j]!='>'){do_zapisu+=linia[j];}
                }


           language_ENG[do_ktorego_programu][numer_tekstu]=do_zapisu;do_zapisu.clear();numer_tekstu++;
           zapisywac_dane=false;
        }
    }
}

pl_plik_tekstu.close(); eng_plik_tekstu.close();
pierwsze_wczytanie_jezyka_z_plikow=false;
}

// zwrocenie przez funkcje tekstu w odpowiednim jezyku  (tekst zwraca przez to w jakim wierszu w pliku jest poprzez podanie w funkcji)
if(jaki_jezyk_programu=="1"){return language_PL[ktory_program][ktory_wiersz];}
else if(jaki_jezyk_programu=="2"){return language_ENG[ktory_program][ktory_wiersz];}
}

void wymiary_okna_szer_wys(int szerokosc_okna, int wysokosc_okna)
{
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // potrzebujesz uchwytu
HANDLE hOut; // to wklejac w przypadu gdy wymiary okna nie sa zmieniane za pomoca funkcji tylko recznie
SMALL_RECT sr;
 // Wymiary okna
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // potrzebujesz uchwytu
    //SMALL_RECT sr;

    sr.Left = 0;
    sr.Top = 0;
    sr.Right = szerokosc_okna; // szerokość
    sr.Bottom = wysokosc_okna; // wysokość
    SetConsoleWindowInfo(handle,true,&sr);
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo(handle, &sbi);
}

class USTAWIENIA  //wyswietl_tekst(1,)
{
private:
HANDLE hOut;
const string plik_ustawien_name="Ustawienia.set";
unsigned short kolor;
string wersja_programu_odczyt="";
unsigned int wielkosc_tablicy=0;

public:




void kolor_tekstu_z_ustawien()
{
  hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    switch(kolor)
    {
         case 0://Ten napis jest srebny
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
         break;
         case 1://Ten napis jest czerwony
         SetConsoleTextAttribute( hOut, FOREGROUND_RED );
         break;
         case 2://Ten napis jest zielony
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
         break;
         case 3://Ten napis jest niebieski
         SetConsoleTextAttribute( hOut, FOREGROUND_BLUE );
         break;
         case 4://Ten napis jest intensywnie czerwony
         SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_INTENSITY );
         break;
         case 5://Ten napis jest intensywnie zielony
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
         break;
         case 6://Ten napis jest intensywnie niebieski
         SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
         break;
         case 7://fioletowy
         SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED );
         break;
         case 8://Ten napis jest rozowy
         SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
         break;
         case 9://Ten napis jest ala zloty
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED );
         break;
         case 10://Ten napis jest seledynowy
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
         break;
         case 11://Ten napis jest jasno niebieski
         SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE );
         break;
    }
}
//----------------------------------------------------------------------------------------
void zczytanie_nazw_plikow_do_ustawiania_myszy()
{
    fstream nazwy_plikow;
    string linia;
    nazwy_plikow.open(pliki_wektorow_myszy);
    wszystkie_pliki_tab.clear();
    if(nazwy_plikow.fail())
    {
        system("COLOR 0C");
        cout<<wyswietl_tekst(1,1)<<pliki_wektorow_myszy<<wyswietl_tekst(1,2)<<endl;
        cout<<endl<<wyswietl_tekst(1,3);
        getchar(); system("cls");
        nazwy_plikow.close();
        ofstream tworzenie_pliku; tworzenie_pliku.open(pliki_wektorow_myszy);tworzenie_pliku<<"0"; tworzenie_pliku.close();
        system("COLOR 0A");
        cout<<wyswietl_tekst(1,4)<<endl;
        cout<<wyswietl_tekst(0,2)<<endl;
        getchar();
        nazwy_plikow.open(pliki_wektorow_myszy);
    }

    do{
            getline(nazwy_plikow,linia);
            if(linia!="0"){wszystkie_pliki_tab.push_back(linia);ile_plikow_wektorow_licznik++;}
    }while(!nazwy_plikow.eof()); nazwy_plikow.close();
}
void z_jakiego_pliku_kozystac_zczytanie_pliku_tylko()
{
    const string name_fi="z_jakiego_pliku_kozystac.set";
    string linia;
    fstream plik;
    plik.open(name_fi);
    if(plik.fail()){plik.close(); ofstream plik_naprawa;plik_naprawa.open(name_fi);plik_naprawa<<"Nie uzyto jeszcze zadnego pliku.";plik_naprawa.close();plik.open(name_fi);}

    do{
            getline(plik,linia); z_jakiego_pliku_brac_dane=linia;
    }while(!plik.eof()); plik.close();
}







void start_programu_zczytanie_ustawien()
{
czytanie_ustawien_po_naprawie:
    string linia;
    fstream wczytanie_ustawien;
    wczytanie_ustawien.open(plik_ustawien_name);
    if(wczytanie_ustawien.fail())//aktywuje sie w momencie gdy nie ma pliku ustawien w folderze i automatycznie go stwarza
    {
        system("cls");
        system("COLOR 0C");
        cout<<wyswietl_tekst(1,5)<<endl;//Nie znaleziono pliku ustawien do zaladowania.
        cout<<wyswietl_tekst(1,6);//Plik ustawien zostanie automatycznie utworzony z zapisanymi podstawowymi ustawieniami.
        cout<<endl<<wyswietl_tekst(0,2);//"Naciśnij ENTER aby kontunuować.";
        getchar();
        system("cls");
        reset_do_ustawien_poczatkowych();
        wczytanie_ustawien.open(plik_ustawien_name);
    }

unsigned int wiersz_z_pliku_ustawien=0;
    do{
            getline(wczytanie_ustawien,linia);
            if(wiersz_z_pliku_ustawien==0){wersja_programu_odczyt=linia;}
    if(wersja_programu_odczyt!=wersja_programu)
    {system("cls");system("COLOR 0C");cout<<wyswietl_tekst(1,7); cout<<endl<<wyswietl_tekst(1,8)<<endl<<wyswietl_tekst(1,9); cout<<endl<<endl<<endl<<wyswietl_tekst(0,4);      //"Plik ustawieniń programu jest przestarzały."    "Program automatycznie naprawi problem. Spowoduje to utrate wcześniej zapisanych ustawień użytkownika."  "Program automatycznie załąduje się na nowo gdy zakończy proces."   Naciśnij ENTER aby kontynuować proces.";
    getchar();wczytanie_ustawien.close();reset_do_ustawien_poczatkowych();system("cls");system("COLOR 0A");cout<<wyswietl_tekst(1,10);goto czytanie_ustawien_po_naprawie;} //"SUKCES proces zakończony powodzeniem"
            if(wiersz_z_pliku_ustawien==1){znak=atoi(linia.c_str());}
            if(wiersz_z_pliku_ustawien==2){kolor=atoi(linia.c_str());}
            if(wiersz_z_pliku_ustawien==3){rodzaj_uruchamiania=atoi(linia.c_str());     rodzaj_uruchamiania-=48;}
            if(wiersz_z_pliku_ustawien==4){zabezpieczenie=atoi(linia.c_str());}
            if(wiersz_z_pliku_ustawien==5){auto_bot_loop_onoff_klawisz=atoi(linia.c_str());}
            if(wiersz_z_pliku_ustawien==6){jaki_jezyk_programu=linia;}
            wielkosc_tablicy++;
            wiersz_z_pliku_ustawien++;
    }while(!wczytanie_ustawien.eof());

}


void zapis_nowych_ustawien()
{
    system("cls");
    ofstream save_ustawienia;
    fstream wczytanie_ustawien;
    string linia;
    string nowe_dzialanie_programu;
    int wybor_uniwersalne_do_all_INT;
    int nowy_klawisz;
    double tablica[wielkosc_tablicy];
    wczytanie_ustawien.open(plik_ustawien_name);
    char co_zmienic;


    wymiary_okna_szer_wys(74,7);
    cout<<wyswietl_tekst(1,11);//"Wybierz co chcesz zmienic";
    cout<<endl<<wyswietl_tekst(1,12);//"1 - Zmiana klawisza uruchamiajacego auto klikanie";
    cout<<endl<<wyswietl_tekst(1,13);//"2 - Zmiana koloru tekstu";
    cout<<endl<<wyswietl_tekst(1,14);//"3 - Rodzaj działania programu (Auto Clicera klikanie/trzymanie klawisza)";
    cout<<endl<<wyswietl_tekst(1,15);//"4 - Zmiana klawisza włączającego pętlę Auto Bota";
    cout<<endl<<wyswietl_tekst(1,16);//"5 - Zmiana języka programu";
    cout<<endl;cin>>co_zmienic;


   for(int i=0;i<wielkosc_tablicy;i++){ // Zczytywanie pliku do tablicy jednoczesne zamienianie tekstu na liczby
        getline(wczytanie_ustawien,linia);
        tablica[i]=atoi(linia.c_str());
   }
    wczytanie_ustawien.close();
    save_ustawienia.open(plik_ustawien_name);


    if(co_zmienic=='1')
    {
        system("cls");
        cout<<wyswietl_tekst(1,17);//"--------------Podaj klawisz--------------"<<endl;
        cout<<endl<<wyswietl_tekst(1,18);//"Jesli chodzi o klawisze myszy to wpisz: ";
        cout<<endl<<wyswietl_tekst(1,19);//"; - lewy klawiszy myszy";
        cout<<endl<<wyswietl_tekst(1,20);//"[ - srodkowy klawiszy myszy";
        cout<<endl<<wyswietl_tekst(1,21);//"' - prawy klawiszy myszy";
        nowy_klawisz=getch();
        if(nowy_klawisz==59){tablica[1]=1;}
        if(nowy_klawisz==91){tablica[1]=4;}
        if(nowy_klawisz==39){tablica[1]=2;}
        if(nowy_klawisz!=59 && nowy_klawisz!=91 && nowy_klawisz!=39){nowy_klawisz-=32; tablica[1]=nowy_klawisz;}
    }

    if(co_zmienic=='2')
    {
        system("cls");
        int wybor_koloru;
        cout<<wyswietl_tekst(1,22)<<endl<<endl;//Wybierz kolor

    hOut = GetStdHandle( STD_OUTPUT_HANDLE );


    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,23)<<endl;//"0.Ten napis jest srebny"

    SetConsoleTextAttribute( hOut, FOREGROUND_RED );
    cout<<wyswietl_tekst(1,24)<<endl;//"1.Ten napis jest czerwony"

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
    cout<<wyswietl_tekst(1,25)<<endl;//"2.Ten napis jest zielony"

    SetConsoleTextAttribute( hOut, FOREGROUND_BLUE );
    cout<<wyswietl_tekst(1,26)<<endl;//"3.Ten napis jest niebieski"

    SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,27)<<endl;//"4.Ten napis jest intensywnie czerwony"

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,28)<<endl;//"5.Ten napis jest intensywnie zielony"

    SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,29)<<endl;//"6.Ten napis jest intensywnie niebieski"

    SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED );
    cout<<wyswietl_tekst(1,30)<< endl;//"7.Ten napis jest fioletowy"

    SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,31)<<endl;//"8.Ten napis jest rozowy"

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED );
    cout<<wyswietl_tekst(1,32)<<endl;//"9.Ten napis jest ala zloty"

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    cout<<wyswietl_tekst(1,33)<<endl;//"10.Ten napis jest seledynowy"

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE );
    cout<<wyswietl_tekst(1,34)<<endl;//"11.Ten napis jest jasno niebieski"


    cin>>wybor_koloru;
    tablica[2]=wybor_koloru;
    }

    if(co_zmienic=='3')
    {
        zmiana_ust_3:
        system("cls");
        cout<<wyswietl_tekst(1,35);//"1 - Trzymanie klawisza aby program działał.";
        cout<<endl<<wyswietl_tekst(1,36);//"2 - Wł / Wył automatyczne klikanie klawiszem.";
        cout<<endl<<endl<<wyswietl_tekst(1,37);//"Podaj cyfrę: ";
        tablica[3]=getch();
        if(tablica[3]!='1' && tablica[3]!='2'){system("cls");cout<<wyswietl_tekst(1,38);getchar();goto zmiana_ust_3;}//"Podana cyfra jest nie prawidłowa podaj ponownie!"
    }

    if(co_zmienic=='4')
    {
        system("cls");
        cout<<wyswietl_tekst(1,17);//"--------------Podaj klawisz--------------"<<endl;
        cout<<endl<<wyswietl_tekst(1,18);//"Jesli chodzi o klawisze myszy to wpisz: ";
        cout<<endl<<wyswietl_tekst(1,19);//"; - lewy klawiszy myszy";
        cout<<endl<<wyswietl_tekst(1,20);//"[ - srodkowy klawiszy myszy";
        cout<<endl<<wyswietl_tekst(1,21);//"' - prawy klawiszy myszy";
        nowy_klawisz=getch();
        if(nowy_klawisz==59){tablica[5]=1;}
        if(nowy_klawisz==91){tablica[5]=4;}
        if(nowy_klawisz==39){tablica[5]=2;}
        if(nowy_klawisz!=59 && nowy_klawisz!=91 && nowy_klawisz!=39){nowy_klawisz-=32; tablica[5]=nowy_klawisz;}
    }

    if(co_zmienic=='5')
    {
        system("cls");
        cout<<wyswietl_tekst(1,17)<<endl;//"--------------Podaj klawisz--------------"
        cout<<endl<<"1 - Polski";
        cout<<endl<<"2 - English";
        wybor_uniwersalne_do_all_INT=getch();
        tablica[6]=wybor_uniwersalne_do_all_INT;
    }



    save_ustawienia<<wersja_programu<<endl; //zapis nowych ustawien do pliku
    save_ustawienia<<tablica[1]<<endl;
    save_ustawienia<<tablica[2]<<endl;
    save_ustawienia<<tablica[3]<<endl;
    save_ustawienia<<tablica[4]<<endl;
    save_ustawienia<<tablica[5]<<endl;
    save_ustawienia<<tablica[6];

    save_ustawienia.close();
}


void reset_do_ustawien_poczatkowych()
{
    ofstream reset;
    reset.open(plik_ustawien_name);

    reset<<wersja_programu<<endl;
    reset<<"90"<<endl;
    reset<<"5"<<endl;
    reset<<"50"<<endl;
    reset<<"1"<<endl;
    reset<<"76"<<endl;
    reset<<"2";
    reset.close();
}
};



class WPL  //wyswietl_tekst(2,)
{
public:

void dodawanie()
{
vector <long long> liczby_cale;
vector <long double> liczby_niecale;
short ktora_liczba=1;
unsigned int dlugosc_tekstu=0;
long double suma_niecala=0,nc=0;
long long suma_cala=0,c=0;
string x;
string allliczby;
vector <string> allliczby_vect;
bool cala=true;
system("cls");


for(;;)
{
cout<<wyswietl_tekst(2,1)<<ktora_liczba<<wyswietl_tekst(2,2);//  "Podaj "<<ktora_liczba<<" liczbę (0-koniec podawania liczb): "
cin>>x;
system("cls");

if(x!="0")
{
allliczby_vect.push_back(x);
allliczby+=x;


ktora_liczba++;
}else{break;}
}


//----------------------------------------------------------------------------- sprawdzanie czy liczba jest z kropka czy bez i dopisanie do odpowiedniej tablicy
for(size_t i=0;i<allliczby_vect.size();i++){allliczby+=allliczby_vect[i];}
dlugosc_tekstu=allliczby.length();

for(int i=0;i<dlugosc_tekstu;i++){if(allliczby[i]=='.'){cala=false;}}

for(size_t i=0;i<allliczby_vect.size();i++)
{
    x=allliczby_vect[i];

    if(cala==true)
    {
       c=stoll(x.c_str());
       liczby_cale.push_back(c);
    }else
    {
        nc=stold(x.c_str());
        liczby_niecale.push_back(nc);
    }
}
//-----------------------------------------------------------------------------






//----------------------------------------------------------------------------- dodawanie i wyswietlanie wyniku
for(size_t i=0;i<liczby_cale.size();i++){cout<<liczby_cale[i]<<endl;}
for(size_t i=0;i<liczby_niecale.size();i++){cout<<liczby_niecale[i]<<endl;}

if(cala==true)
{
    suma_cala=liczby_cale[0];
    for(size_t i=1;i<liczby_cale.size();i++){suma_cala+=liczby_cale[i];}
    system("cls");
    cout<<wyswietl_tekst(2,3)<<"["<<suma_cala<<"]";//Wynik
}else
{
    suma_niecala=liczby_niecale[0];
    for(size_t i=1;i<liczby_niecale.size();i++){suma_niecala+=liczby_niecale[i];}
    system("cls");
    cout<<wyswietl_tekst(2,3)<<"["<<suma_niecala<<"]";//Wynik
}
//-----------------------------------------------------------------------------
}

void odejmowanie()
{
long double a,b;
long double suma=0;
int max=0;
int ile_liczb=1,x;
vector <long double> liczby;



cout<<wyswietl_tekst(2,4);//"Podaj 1 liczbę: ";
cin>>a;
system("cls");
cout<<wyswietl_tekst(2,5);//"Podaj 2 liczbę: ";
cin>>b;

system("cls");
cout<<wyswietl_tekst(2,6)<<"["<<a-b<<"]";//Wynik to
/*
//--------------------------------------------------------------------------------wpisanie liczb
for(;;)
{
cout<<"Podaj "<<ile_liczb<<" liczbe (0-koniec podawania liczb): ";
cin>>x;
system("cls");
if(x==0){break;}
liczby.push_back(x);
ile_liczb++;
}
//--------------------------------------------------------------------------------szukanie najwiekszej wartosci
for( size_t i=0;i<liczby.size();i++ ){if(max<tablica[i]){max=tablica[i];}}
for( size_t i=0;i<liczby.size();i++ ){if(max==tablica[i]){tablica[i]=0;}}
suma=max;
//--------------------------------------------------------------------------------sumowanie podanych liczb
for( size_t i=1;i<liczby.size(); i++ ){suma-=liczby[i];}
//--------------------------------------------------------------------------------wyswietlenie na ekran wyniku
system("cls");
cout<<"Wynik to ["<<suma<<"]";
*/
}

void mnozenie()
{
vector <long long> liczby_cale;
vector <long double> liczby_niecale;
short ktora_liczba=1;
unsigned int dlugosc_tekstu=0;
long double suma_niecala=0,nc=0;
long long suma_cala=0,c=0;
string x;
string allliczby;
vector <string> allliczby_vect;
bool cala=true;
system("cls");


for(;;)
{
cout<<wyswietl_tekst(2,1)<<ktora_liczba<<wyswietl_tekst(2,2);//  "Podaj "<<ktora_liczba<<" liczbę (0-koniec podawania liczb): "
cin>>x;
system("cls");

if(x!="0")
{
allliczby_vect.push_back(x);
allliczby+=x;


ktora_liczba++;
}else{break;}
}


//----------------------------------------------------------------------------- sprawdzanie czy liczba jest z kropka czy bez i dopisanie do odpowiedniej tablicy
for(size_t i=0;i<allliczby_vect.size();i++){allliczby+=allliczby_vect[i];}
dlugosc_tekstu=allliczby.length();

for(int i=0;i<dlugosc_tekstu;i++){if(allliczby[i]=='.'){cala=false;}}

for(size_t i=0;i<allliczby_vect.size();i++)
{
    x=allliczby_vect[i];

    if(cala==true)
    {
       c=stoll(x.c_str());
       liczby_cale.push_back(c);
    }else
    {
        nc=stold(x.c_str());
        liczby_niecale.push_back(nc);
    }
}
//-----------------------------------------------------------------------------






//----------------------------------------------------------------------------- mnozenie i wyswietlanie wyniku
for(size_t i=0;i<liczby_cale.size();i++){cout<<liczby_cale[i]<<endl;}
for(size_t i=0;i<liczby_niecale.size();i++){cout<<liczby_niecale[i]<<endl;}

if(cala==true)
{
    suma_cala=liczby_cale[0];
    for(size_t i=1;i<liczby_cale.size();i++){suma_cala*=liczby_cale[i];}
    system("cls");
    cout<<wyswietl_tekst(2,3)<<"["<<suma_cala<<"]";//Wynik
}else
{
    suma_niecala=liczby_niecale[0];
    for(size_t i=1;i<liczby_niecale.size();i++){suma_niecala*=liczby_niecale[i];}
    system("cls");
    cout<<wyswietl_tekst(2,3)<<"["<<suma_niecala<<"]";//Wynik
}
//-----------------------------------------------------------------------------
}

void dzielenie()
{
long double a,b;
cout<<wyswietl_tekst(2,4);//"Podaj liczbę 1: ";
cin>>a;
system("cls");
cout<<wyswietl_tekst(2,5);//"Podaj liczbę 2: ";
cin>>b;
system("cls");

if(a!=0 && b!=0){cout<<wyswietl_tekst(2,7)<<a<<"/"<<b<<"       "<<wyswietl_tekst(2,3)<<"["<<a/b<<"]"<<endl;}else{cout<<wyswietl_tekst(2,8);}//cout<<"Dziele: "<<a<<"/"<<b<<"       Wynik: ["<<a/b<<"]"<<endl;}else{cout<<"Nie dzielimy przez 0";}
}

void potegowanie()
{
string liczba_sprawdzic="";
long long podstawnik_caly=0;
long double podstawnik_niecaly=0;
int wykladnik=0;
bool cala=true;





system("cls");
cout<<wyswietl_tekst(2,9);//"Podaj podstawę potęgi: ";
cin>>liczba_sprawdzic;
system("cls");
cout<<wyswietl_tekst(2,10);//"Podaj wykładnik potęgi: ";
cin>>wykladnik;
system("cls");



//----------------------------------------------------------------------------- sprawdzanie czy liczba jest z kropka czy bez i przekonwertowanie liczby do odpowiedniej zmiennej

for(int i=0;i<liczba_sprawdzic.length();i++)
    {if(liczba_sprawdzic[i]=='.'){cala=false; break;}}

    if(cala==true)
    {podstawnik_caly=stoll(liczba_sprawdzic.c_str());} else{podstawnik_niecaly=stold(liczba_sprawdzic.c_str());}

//-----------------------------------------------------------------------------






//----------------------------------------------------------------------------- potegowanie i zwrocenie wyniku
if(cala==true)
{

long long wynik=podstawnik_caly;
    for(int i=1;i<wykladnik;i++){wynik*=podstawnik_caly;}
    cout<<liczba_sprawdzic<<wyswietl_tekst(2,11)<<wykladnik<<wyswietl_tekst(2,12)<<"["<<wynik<<"]"; //zwocenie przez funkcje wyniku
//  cout<<liczba_sprawdzic<<" do potęgi "<<wykladnik<<" wynosi: ["<<wynik<<"]";
}else{

long double wynik=podstawnik_niecaly;
    for(int i=1;i<wykladnik;i++){wynik*=podstawnik_niecaly;}
    cout<<liczba_sprawdzic<<wyswietl_tekst(2,11)<<wykladnik<<wyswietl_tekst(2,12)<<"["<<wynik<<"]"; //zwocenie przez funkcje wyniku
//  cout<<liczba_sprawdzic<<" do potęgi "<<wykladnik<<" wynosi: ["<<wynik<<"]";
}
//-----------------------------------------------------------------------------
}

void Pierwiastkowanie()
{
  cout<<wyswietl_tekst(2,13)<<endl;//"Funkcja jest aktualnie nie dostępna."
  cout<<wyswietl_tekst(2,14);//"Prace nad nią trwają, będzie aktywna jak najszybciej to możliwe."

    /*
long long a,b;
cout<<"Podaj liczbę: ";
cin>>a;
system("cls");
cout<<"Podaj jaki stopień pierwiastka: ";
cin>>b;

system("cls");
cout<<"Pierwiastek z "<<a<<" stopnia "<<b<<"       Wynik: ["<<pow(a, 1/b)<<"]"<<endl;
*/
}

void tekst_na_binarny()
{
char wybor;
short b;
string napis;

cout<<wyswietl_tekst(2,15);//"Podaj wyraz bez spacji: ";
cin>>napis;
system("cls");
b=napis.length();


cout<<wyswietl_tekst(2,16)<<endl;//"Wybierz rodzaj wyświetlenia"
cout<<wyswietl_tekst(2,17);//"Wypisać napis z [,]?  TAK[t] / NIE[n]: "
wybor=getch();


system("cls");
cout<<wyswietl_tekst(2,18);//"W kodzie binarnym: ";

if(wybor=='t'){for(int a=0;a<b;a++){cout<<bitset<CHAR_BIT>(napis[a])<<", ";}}
else{if(wybor=='n'){for(int a=0;a<b;a++){cout<<bitset<CHAR_BIT>(napis[a]);}}}
}

void zamiana_tekstu_z_kodami_ascii()
{
char wybor, ascii_kod2;
int ascii_kod=0;


cout<<wyswietl_tekst(2,19)<<endl;//"W którą stronę chcesz dokonać zamiany?"
cout<<wyswietl_tekst(2,20)<<char(26)<<wyswietl_tekst(2,21)<<endl;//"1-Tekst "<<char(26)<<" ASCII"<<endl;
cout<<wyswietl_tekst(2,22)<<char(26)<<wyswietl_tekst(2,23)<<endl;//"2-ASCII "<<char(26)<<" Tekst"<<endl;
cout<<wyswietl_tekst(2,24)<<endl;//"3-Wypisanie wszystkich znaków z tablicy"
wybor=getch();
system("cls");




if(wybor=='1')
{
cout<<wyswietl_tekst(2,25);//"Podaj znak: ";
cin>>ascii_kod2;
system("cls");
cout<<wyswietl_tekst(2,26)<<ascii_kod2<<wyswietl_tekst(2,27)<<int(ascii_kod2);//"Wyraz: "<<ascii_kod2<<"          W kodzie ASCII to liczba: "<<int(ascii_kod2);
}




if(wybor=='2')
{
cout<<wyswietl_tekst(2,28);//"Podaj liczbe w zakresie 0-255: ";
cin>>ascii_kod;
system("cls");
cout<<wyswietl_tekst(2,29)<<"["<<ascii_kod <<"]"<<wyswietl_tekst(2,30)<<char(ascii_kod);//"Liczba ["<<ascii_kod <<"] z kodu ASCII to znak: "<<char(ascii_kod);
}



short x=0;
int znaki[36][8];
if(wybor=='3')
{

for(int i=0;i<=255;i++)
    {
       if(i!=0 && i!=10 && i!=13 && i!=27 && i!=32){cout<<i<<" "<<char(26)<<" "<<char(i)<<endl;}
       if(i==10){cout<<i<<" "<<char(26)<<wyswietl_tekst(2,31)<<endl;}//" przesuniecie o jeden wiersz(enter)"
       else if(i==0){cout<<i<<" "<<char(26)<<wyswietl_tekst(2,32)<<endl;}//" Zero/Null"
       else if(i==13){cout<<i<<" "<<char(26)<<wyswietl_tekst(2,33)<<endl;}//" ENTER"
       else if(i==27){cout<<i<<" "<<char(26)<<wyswietl_tekst(2,34)<<endl;}//" BACKSPACE/strzałka zwrócona w lewo/Escape(ESC)"
       else if(i==32){cout<<i<<" "<<char(26)<<wyswietl_tekst(2,35)<<endl;}//" Spacja"
    }
}
}

void procenty()
{
string calosc,procent;
long double nc_calosc=0,nc_procent=0;
long long c_calosc=0,c_procent=0;
string x;
bool cala_calosc=true,cala_procent=true;
unsigned int dlugosc_calosc=0,dlugosc_procent=0;




poczatek:
system("cls");
cout<<wyswietl_tekst(2,36);//"Podaj całość: ";
cin>>calosc;
system("cls");
cout<<wyswietl_tekst(2,37);//"Podaj liczbę/procent: ";
cin>>procent;
system("cls");


dlugosc_calosc=calosc.length();
dlugosc_procent=procent.length();



//------------------------------------------------------------ sprawdzanie czy liczby sa calkowite
if(calosc!="0" && procent!="0")
{
    for(int i=0;i<dlugosc_calosc;i++)
    {
        x=calosc[i];
        if(x=="."){cala_calosc=false;break;}
    }

    for(int i=0;i<dlugosc_procent;i++)
    {
        x=procent[i];
        if(x=="."){cala_procent=false;break;}
    }
}else{goto poczatek;}
//------------------------------------------------------------ konwertowanie zmiennych tekstowych na liczbowe
c_calosc=stold(calosc.c_str());
c_procent=stoll(procent.c_str());   //stoll(procent.c_str());
nc_calosc=stold(calosc.c_str());
nc_procent=stold(procent.c_str());
//------------------------------------------------------------ wykonywanie dzialan obliczajacych

if(cala_calosc==true && cala_procent==true)
{
    cout<<procent<<wyswietl_tekst(2,38)<<calosc<<wyswietl_tekst(2,39)<<"["<<nc_procent/nc_calosc*100<<"]%"<<endl;// z   jest to
    cout<<procent<<"%"<<wyswietl_tekst(2,38)<<calosc<<wyswietl_tekst(2,39)<<"["<<c_procent*c_calosc/100<<"]"<<endl;// z    jest to

}else
{
    cout<<procent<<wyswietl_tekst(2,38)<<calosc<<wyswietl_tekst(2,39)<<"["<<nc_procent/nc_calosc*100<<"]%"<<endl;// z    jest to
    cout<<procent<<"%"<<wyswietl_tekst(2,38)<<calosc<<wyswietl_tekst(2,39)<<"["<<nc_procent*nc_calosc*0.01<<"]"<<endl;// z    jest to
}
//------------------------------------------------------------
}

void pomoc()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // potrzebujesz uchwytu
    SMALL_RECT sr;

    sr.Left = 0;
    sr.Top = 0;
    sr.Right = 100;
    sr.Bottom = 30;
    SetConsoleWindowInfo(handle,true,&sr); // ustawiasz szerokość okna na 50 x 50 (w szerokościach i wysokościach znaku pojedynczego a nie w pikselach)
    CONSOLE_SCREEN_BUFFER_INFO sbi; // struktura opisująca okno
    GetConsoleScreenBufferInfo(handle, &sbi); // pobieranie informacji o oknie



cout<<wyswietl_tekst(2,40)<<endl;//" W razie problemów z programem proszę o zgłaszanie ich."
cout<<endl<<endl<<wyswietl_tekst(2,41)<<endl;//" Kontakt:"
cout<<" Discord server: ==Legion==   on chanel: questions"<<endl;
cout<<" Email: miley.shimada@gmail.com"<<endl;

cout<<endl<<endl<<endl<<endl<<endl<<wyswietl_tekst(2,42)<<endl;//" Gdy kurs walut jest nieakualny przejdz do pliku (kurs_walut.txt) i popraw wartości na aktualne."
cout<<wyswietl_tekst(2,43)<<endl;//" Zalecane jest skorzystanie z linku zapisanym w pliku z walutami po skopiowaniu wartości kursów"
cout<<wyswietl_tekst(2,44)<<endl;//" należy zamienić ',' na '.' i zapisać plik."


cout<<endl<<endl<<wyswietl_tekst(2,45)<<endl;//" Instrukcja:"
cout<<" Dolar:  "<<char(26)<<wyswietl_tekst(2,46)<<endl;//" Dolar:  "<<char(26)<<"  tej wartości nie należy zmieniać"<<endl;
cout<<" 4.1147  "<<char(26)<<wyswietl_tekst(2,47)<<endl<<endl;//" 4.1147  "<<char(26)<<"  tą wartość należy poprawić"<<endl<<endl;
cout<<wyswietl_tekst(2,48)<<endl;//" Aby data kursu walut w Menu Głównym została zmieniona należy ją zmienić w pliku"<<endl;
cout<<wyswietl_tekst(2,49)<<endl;//" Data również zostanie zaktulizowana przy nastepniej aktulizacji programu WPL jak i"
cout<<wyswietl_tekst(2,50)<<endl;//" również kurs walut."



cout<<endl<<endl<<endl<<wyswietl_tekst(2,51)<<char(3)<<" :)";//" Miłego korzystania z programu "
}

void walut_create_file()
{
    ofstream plik;
    plik.open("kurs_walut.txt");

    plik<<"05.04.2022"<<endl;
    plik<<"Dolar:"<<endl;
    plik<<"4.2233"<<endl;
    plik<<"Euro:"<<endl;
    plik<<"4.6317"<<endl;
    plik<<"Funt GBP:"<<endl;
    plik<<"5.5410";
    plik<<endl<<endl<<endl<<endl;
    plik<<"Narodowy Bank Polski kursy walut: https://www.nbp.pl/";
    plik.close();

    system("cls");
    cout<<wyswietl_tekst(2,52);//"Plik został utworzony pomyślnie.";
}

};
class obliczanie_walut  //wyswietl_tekst(3,)
{
private:

    long double gotoweeuro=0, gotowydolar=0, gotowyfunt=0;
    long double ile_dolar=0,ile_euro=0,ile_funt=0;//po ile chodzi kazda waluta (wczytanie wartosci z pliku)
    long double suma=0;
    unsigned short wiersz_odczyt_pliku=0;
    WPL wpl;
    USTAWIENIA ustawienia;



public:
    void kurs_walut_odczyt()
    {
            string linia;
            vector <string> do_convertu;
            fstream wczytanie_cen;
            wczytanie_cen.open("kurs_walut.txt");
            bool pierwszy_raz=true;

            if(wczytanie_cen.fail())
            {
                system("COLOR 0C");
                cout<<wyswietl_tekst(3,1);//"Błąd w otwarciu pliku!!!   Plik o nazwie (kurs_walut.txt)";
                cout<<endl<<wyswietl_tekst(3,2)<<endl;//"Najprawdopodobniej nie ma pliku w folderze z programem."
                cout<<endl<<wyswietl_tekst(3,3);//"Plik zostanie utworzony automatycznie z podstawowymi danymi.";
                cout<<endl<<wyswietl_tekst(0,2);//"Naciśnij ENTER aby kontynuować.";
                getchar();
                wpl.walut_create_file();
                wczytanie_cen.open("kurs_walut.txt");
                cout<<endl<<wyswietl_tekst(3,4);//"Poprawne otwarcie pliku.";
                cout<<endl<<endl<<endl<<wyswietl_tekst(0,2);//"Naciśnij ENTER aby kontunuować.";
                getchar();
            }
            ustawienia.kolor_tekstu_z_ustawien();


          //zczytanie pliku i dodanie wartości do tablicy
          do{
                 getline(wczytanie_cen,linia);
                 if(pierwszy_raz!=true && wiersz_odczyt_pliku<7){do_convertu.push_back(linia);}
                 else if(pierwszy_raz==true){data=linia; pierwszy_raz=false;}
                 wiersz_odczyt_pliku++;

          }while(!wczytanie_cen.eof());
          wczytanie_cen.close();


          //zamiana wartości string z tablicy na long double wartości są a pozycjach zwiększających sie o 2 zaczynając od 0
          for(size_t i=0;i<do_convertu.size();i++)
          {
              if(i==1){ile_dolar=stold(do_convertu[i].c_str());}
              if(i==3){ile_euro=stold(do_convertu[i].c_str());}
              if(i==5){ile_funt=stold(do_convertu[i].c_str());}
          }
    }


    void wybor_dzialania()
    {
        char wybor='\0';
        system("cls");
        cout<<wyswietl_tekst(3,5)<<endl;//"Dokonaj wyboru w którą strone chcesz liczyć waluty"
        cout<<"1-PLN  --> EUR"<<endl;
        cout<<"2-PLN  --> USD"<<endl;
        cout<<"3-PLN --> Funt(GBP)"<<endl;
        cout<<"4-EUR --> PLN"<<endl;
        cout<<"5-USD --> PLN"<<endl;
        cout<<"6-Funt(GBP) --> PLN"<<endl;
        wybor=getch();
        system("cls");



        if(wybor== '1'){ZL_EUR();}
        if(wybor== '2'){ZL_USD();}
        if(wybor== '3'){ZL_FUNT();}





        if(wybor== '4'){EUR_ZL();}
        if(wybor== '5'){USD_ZL();}
        if(wybor== '6'){FUNT_ZL();}
    }









private:
    void ZL_EUR()
    {
        cout<<wyswietl_tekst(3,6);//"Podaj kowtę PLN: ";
        cin>>suma;
        system("cls");
        gotoweeuro=suma/ile_euro;
        cout<<wyswietl_tekst(3,7)<<"["<<gotoweeuro<<"] EUR"<<endl;//Wynik w Euro:
        gotoweeuro=0; suma=0;
    }

    void ZL_USD()
    {
        cout<<wyswietl_tekst(3,6);//"Podaj kowtę PLN: ";
        cin>>suma;
        system("cls");
        gotowydolar=suma/ile_dolar;
        cout<<wyswietl_tekst(3,8)<<"["<<gotowydolar<<"] $"<<endl;//Wynik w Dolarach:
        gotowydolar=0; suma=0;
    }

    void ZL_FUNT()
    {
        cout<<wyswietl_tekst(3,6);//"Podaj kowtę PLN: ";
        cin>>suma;
        system("cls");
        gotowyfunt=suma/ile_funt;
        cout<<wyswietl_tekst(3,9)<<"["<<gotowyfunt<<"] Funt"<<endl;//Wynik w Funtach:
        gotowyfunt=0; suma=0;
    }


//---------------------------------------------------------------------------------------- zl na walute


    void EUR_ZL()
    {
        cout<<wyswietl_tekst(3,10);//"Podaj kwotę EUR: ";
        cin>>suma;
        system("cls");
        gotoweeuro=suma*ile_euro;
        cout<<wyswietl_tekst(3,11)<<"["<<gotoweeuro<<"] PLN"<<endl;//Wynik PLN +- 2PLN:
        gotoweeuro=0; suma=0;
    }

    void USD_ZL()
    {
        cout<<wyswietl_tekst(3,12);//"Podaj kwotę $: ";
        cin>>suma;
        system("cls");
        gotowydolar=suma*ile_dolar;
        cout<<wyswietl_tekst(3,11)<<"["<<gotowydolar<<"] ZŁ"<<endl;//Wynik PLN +- 2PLN:
        gotowydolar=0; suma=0;
    }

    void FUNT_ZL()
    {
        cout<<wyswietl_tekst(3,13);//"Podaj kwotę Funtów: ";
        cin>>suma;
        system("cls");
        gotowyfunt=suma*ile_funt;
        cout<<wyswietl_tekst(3,11)<<"["<<gotowyfunt<<"] ZŁ"<<endl;//Wynik PLN +- 2PLN:
        gotowyfunt=0; suma=0;
    }
};



class AUTO_CLICKER  //wyswietl_tekst(4,)
{
private:
const short usp=1;
ofstream zapis_nowych_wektorow_myszy;
fstream wektory_ustawiania_myszy;
unsigned long long przerwa_miedzy_kliknieciami=0;
const short spoczynek=1;
bool auto_bot_loop=false;

public:

/*void test()
{
keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
}
*/

void jedno_klikniecie() //urzywane do procedur ponizej
{
mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
string zapis_nazwy_pliku_z_wektorami(string name_file)
{
unsigned int licznik_tymczasowy=0;
fstream zczytaj;
ofstream save;
string zczytanie_plikow_tab[ile_plikow_wektorow_licznik+1];
string linia;
zczytaj.open(pliki_wektorow_myszy);

do{
    getline(zczytaj,linia);
    zczytanie_plikow_tab[licznik_tymczasowy]=linia;
    licznik_tymczasowy++;
}while(!zczytaj.eof()); zczytaj.close();

save.open(pliki_wektorow_myszy);
for(int i=0;i<licznik_tymczasowy;i++)
{
    if(zczytanie_plikow_tab[0]!="0"){save<<zczytanie_plikow_tab[i]<<endl;}
}
save<<name_file;
save.close();
}


void tekst_klikniecia_milisekundy() //podawanie czasu pomiedzy kliknieciami
{
        cout<<wyswietl_tekst(4,1);//"Podaj ile czekac milisekund na nastepne klikniecie";
        cout<<endl<<wyswietl_tekst(4,2);//"(ms / 0=czestotliwosc klikniec do zegaru prosesora): ";
        cin>>milisekundy;
        system("cls");

        // skopiowane z MENU pokazuje informacje ktore sa pokazane na poczatku programu
        cout<<endl<<"     "<<wyswietl_tekst(4,3);//"*===========================================================================*";
        cout<<endl<<"     "<<wyswietl_tekst(4,4)<<(char)znak;//"|  Aktualny przycisk uruchamiajacy automatyczne klikanie myszy to: "
        cout<<endl<<"     "<<wyswietl_tekst(4,5);if(rodzaj_uruchamiania==1){cout<<wyswietl_tekst(4,6);}else{cout<<wyswietl_tekst(4,7);}//"|  Aktualny styl uruchamiania auto klikania to: " <"Trzymanie klawisza" "Włącz / Wyłącz klikanie"
        cout<<endl<<"     "<<wyswietl_tekst(4,8);if(zabezpieczenie==1){cout<<wyswietl_tekst(4,9);}else if(zabezpieczenie==2){cout<<wyswietl_tekst(4,10);}else if(zabezpieczenie==3){cout<<wyswietl_tekst(4,11);}//"|  Aktualny poziom zabezpieczenia: " "Brak" "Średni" "Zaawansowany"

        cout<<endl<<"     "<<wyswietl_tekst(4,12);//"|  Przycisk powrotu do menu głównego: x";

}
void tekst_klikniecia_w_milisekundzie() // podawanie ile klikniec w jednej milisekundzie (5 max)
{
        cout<<wyswietl_tekst(4,13);//"Podaj ilosc klikniec w 1 ms: ";
        cin>>klikniecia;
        system("cls");

        // skopiowane z MENU ukasuje informacje ktore sa pokazane na poczatku programu
        cout<<endl<<"     "<<wyswietl_tekst(4,3);//"*===========================================================================*";
        cout<<endl<<"     "<<wyswietl_tekst(4,4)<<(char)znak;//"|  Aktualny przycisk uruchamiajacy automatyczne klikanie myszy to: "
        cout<<endl<<"     "<<wyswietl_tekst(4,5);if(rodzaj_uruchamiania==1){cout<<wyswietl_tekst(4,6);}else{cout<<wyswietl_tekst(4,7);}//"|  Aktualny styl uruchamiania auto klikania to: " <"Trzymanie klawisza" "Włącz / Wyłącz klikanie"

        cout<<endl<<"     "<<wyswietl_tekst(4,12);//"|  Przycisk powrotu do menu głównego: x";
}




// trudnosc wykrycia 1 - brak
//------------------------------------------------------------------------------

    void Auto_klikanie_zab_1_klikniecie_na_milisekune_sekunde()
    {
        tekst_klikniecia_milisekundy(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                      Sleep(milisekundy);
		              if(GetAsyncKeyState(znak)){jedno_klikniecie();}
		              if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                     Sleep(milisekundy);
		             if(GetKeyState(znak)){jedno_klikniecie();}//wl/wyl
		             if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }

    void Auto_klikanie_zab_1_ilosc_klikniec_w_milisekundzie()
    {
        tekst_klikniecia_w_milisekundzie(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                        Sleep(usp);
                      if(GetAsyncKeyState(znak))//trzymanie klawisza
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                        Sleep(usp);
                      if(GetKeyState(znak))//wl/wyl
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }
//------------------------------------------------------------------------------


//zrobic !!!
// trudnosc wykrycia 2 - średni
//------------------------------------------------------------------------------

    void Auto_klikanie_zab_2_klikniecie_na_milisekune_sekunde()
    {
        tekst_klikniecia_milisekundy(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                      Sleep(milisekundy);
		              if(GetAsyncKeyState(znak)){jedno_klikniecie();}
		              if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                     Sleep(milisekundy);
		             if(GetKeyState(znak)){jedno_klikniecie();}//wl/wyl
		             if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }

    void Auto_klikanie_zab_2_ilosc_klikniec_w_milisekundzie()
    {
        tekst_klikniecia_w_milisekundzie(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                        Sleep(usp);
                      if(GetAsyncKeyState(znak))//trzymanie klawisza
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                        Sleep(usp);
                      if(GetKeyState(znak))//wl/wyl
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }
//------------------------------------------------------------------------------


//zrobic !!!
// trudnosc wykrycia 3 - zaawansowany
//------------------------------------------------------------------------------

    void Auto_klikanie_zab_3_klikniecie_na_milisekune_sekunde()
    {
        tekst_klikniecia_milisekundy(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                      Sleep(milisekundy);
		              if(GetAsyncKeyState(znak)){jedno_klikniecie();}
		              if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                     Sleep(milisekundy);
		             if(GetKeyState(znak)){jedno_klikniecie();}//wl/wyl
		             if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }

    void Auto_klikanie_zab_3_ilosc_klikniec_w_milisekundzie()
    {
        tekst_klikniecia_w_milisekundzie(); //pokaz menu informacyjnego


        if(rodzaj_uruchamiania==1) // klikanie gdy trzymany jest klawisz
        {
                    while (true)
                    {
                        Sleep(usp);
                      if(GetAsyncKeyState(znak))//trzymanie klawisza
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                    }
        }else if(rodzaj_uruchamiania==2) // wl/wyl auto klikanie
        {
                   while (true)
                   {
                        Sleep(usp);
                      if(GetKeyState(znak))//wl/wyl
                      {for(int i=0;i<klikniecia;i++){jedno_klikniecie();}}

                      if(GetAsyncKeyState(0x58)){break;} //x / powrot do menu
                   }
        }
    }
//------------------------------------------------------------------------------


//ustawianie kursora w danej pozycji na ekranie jak i zczytywanie pozycji
//--------------------------------------------------------------------------------------------------------------------wyswietl_tekst(,)  126 linia w pliku
void nagrywanie_pozycji_myszy()
{
    wymiary_okna_szer_wys(120,7);
    POINT cursorPos;
    char wybor_metody;
    string nazwa_pliku;

    cout<<wyswietl_tekst(4,14)<<endl<<endl;//"Wybierz metodę nagrywania ruchów pamiętaj, że w żadnej metodzie nie nagrywa się odstępów czasowych między kliknięciami."
    cout<<wyswietl_tekst(4,15)<<endl;//"1 - Rędzie ustawiaj punkty pozycji myszy oraz kliknięcia poprzez naciskanie klawiszy [g] i [n]."
    cout<<wyswietl_tekst(4,16)<<spoczynek<<wyswietl_tekst(4,46)<<endl<<wyswietl_tekst(4,17);//"2 - Automatycznie co "<<spoczynek<<" ms ustawia pozycję myszy natomiast naciśnij [n] aby w tym miejscu zostało wykonane kliknięcie."<<endl<<"Ale pamiętaj też czas nie jest w tej opcji zapisywany."
wybor_metody=getch();
nowa_nazwa:
system("cls");

    cout<<wyswietl_tekst(4,18); cin>>nazwa_pliku;//"Podaj nazwę pliku swoich wektorów: "
    if(nazwa_pliku.length()<2 || nazwa_pliku=="0"){cout<<wyswietl_tekst(4,19)<<endl<<wyswietl_tekst(4,20);getchar();getchar();goto nowa_nazwa;}//"Nazwa pliku jest za krótka lub ma w nazwie [0] jako pierwszą literę."<<endl<<"Naciśnij ENTER aby podać nazwę ponownie."
    system("cls"); zapis_nowych_wektorow_myszy.open(nazwa_pliku);
    zapis_nazwy_pliku_z_wektorami(nazwa_pliku);
    cout<<wyswietl_tekst(4,21)<<endl<<endl;//"Aby zakończyć nagrywanie wektorów naciśnij [x]."

    if(wybor_metody=='1')
        {
            cout<<wyswietl_tekst(4,22)<<endl;//"Naciśnij [g] aby postawić wektor gdzie myszka zostanie ustawiona na ekranie."
            cout<<wyswietl_tekst(4,23);//"Naciśnij [n] aby została wykonana akcja kliknięcia w tym momencie.";

            for(;;){Sleep(100);
            if(GetAsyncKeyState(0x47)){Sleep(50);GetCursorPos(&cursorPos);zapis_nowych_wektorow_myszy<<"X = <"<<cursorPos.x<<">"<<"Y = <"<<cursorPos.y<<">"<<endl;}
            if(GetAsyncKeyState(0x4E)){Sleep(50);zapis_nowych_wektorow_myszy<<"klikniecie"<<endl;}
            if(GetAsyncKeyState(0x58)){Sleep(50);zapis_nowych_wektorow_myszy.close();break;}
            }
        }
    if(wybor_metody=='2')
        {
            for(;;){
                Sleep(spoczynek);
            GetCursorPos(&cursorPos);zapis_nowych_wektorow_myszy<<"X = <"<<cursorPos.x<<">"<<"Y = <"<<cursorPos.y<<">"<<endl;
            if(GetAsyncKeyState(0x4E)){Sleep(50);zapis_nowych_wektorow_myszy<<"klikniecie"<<endl;}
            if(GetAsyncKeyState(0x58)){Sleep(50);zapis_nowych_wektorow_myszy.close();break;}
            }
        }
Sleep(50);
USTAWIENIA ustawienia;
ustawienia.zczytanie_nazw_plikow_do_ustawiania_myszy();
Sleep(50);
}
void Auto_Bot()
{
    char wybor_1;
    unsigned long long usp_bota=1, odstep_miedzy_loopem=1, usp_bota_klikniecie=1;
    string odczyt_1;
menu_AutoBot:
Sleep(100);
system("cls");

    cout<<wyswietl_tekst(4,24)<<endl;//"1 - Podaj odstępy czasowe i uruchom bota."
    cout<<wyswietl_tekst(4,25)<<endl<<endl<<endl;//"2 - Zmień plik z którego brane są wektory i moment kliknięcia."

    cout<<wyswietl_tekst(4,26)<<z_jakiego_pliku_brac_dane<<endl;//"Aktualnie/ostatnio wybrany/używany plik z zapisanymi wektorami myszy to: "
    cout<<wyswietl_tekst(4,27)<<endl;//"Lista dostępnych plików z zapisanymi wektorami:"
    for(int i=0;i<wszystkie_pliki_tab.size();i++)
        {odczyt_1=wszystkie_pliki_tab[i];
            if(odczyt_1=="0"){cout<<wyswietl_tekst(4,28);}else{cout<<i+1<<" - "<<odczyt_1<<endl;}//"!!!BRAK ZAPISANYCH WEKTORÓW!!!"
        }
    wybor_1=getch(); system("cls");

    if(wybor_1=='1')
    {
        fstream wektory_zczytanie_pliku;
        string linia;
        unsigned int ile_max_krokow_licznik=0, wiersz_tablica=0;
        //wczytywanie wektorów do tablicy
        wektory_zczytanie_pliku.open(z_jakiego_pliku_brac_dane);
        do{getline(wektory_zczytanie_pliku, linia);wiersz_tablica++;}while(!wektory_zczytanie_pliku.eof()); wektory_zczytanie_pliku.close();wiersz_tablica--;
        int auto_bot_wektory_kroki[2][wiersz_tablica+1]; // x y   układ tablicy pierwszy slot odpowiada za ilosć danych czyli mamy 2 (x i y) drugi slot za ilość kroków wielkość Y
        bool zapisywac_dane=false;
        unsigned short x_czy_y=0;
        string do_konwersji;
        wektory_zczytanie_pliku.open(z_jakiego_pliku_brac_dane);

        do{
            getline(wektory_zczytanie_pliku, linia);
            if(linia[0]=='k'){auto_bot_wektory_kroki[0][ile_max_krokow_licznik]=-1;}else{
                for(int i=0;i<=linia.length();i++)
                {
                    if(linia[i]=='<'){zapisywac_dane=true;}else if(linia[i]=='>'){auto_bot_wektory_kroki[x_czy_y][ile_max_krokow_licznik]=stoi(do_konwersji);zapisywac_dane=false; do_konwersji.clear();x_czy_y++; if(x_czy_y==2){x_czy_y=0;}}
                    if(zapisywac_dane==true && linia[i]!='<'){do_konwersji+=linia[i];}
                }
            }


            ile_max_krokow_licznik++;
        }while(!wektory_zczytanie_pliku.eof());
// koniec wczytywania tablica jest gotowa
system("cls");
for(int i=0;i<wiersz_tablica;i++){cout<<i<<" === "<<auto_bot_wektory_kroki[0][i]<<",  "<<auto_bot_wektory_kroki[1][i]<<endl;}

        cout<<wyswietl_tekst(4,29); cin>>usp_bota;//"Podaj prędkość działania bota (minimum 1 ms). "
        cout<<wyswietl_tekst(4,30); cin>>usp_bota_klikniecie;//"Podaj odstępny między klikaniem (minimum 1 ms). "
        cout<<wyswietl_tekst(4,31)<<endl;cin>>odstep_miedzy_loopem;//"Podaj odstępy między pętlami o ile daną pętlę uruchomisz (minimum 1 ms). "
        system("cls");

        cout<<wyswietl_tekst(4,32)<<char(znak)<<endl;//"Klawisz odpowiedzialny za uruchomienie bota: "
        cout<<wyswietl_tekst(4,33)<<char(auto_bot_loop_onoff_klawisz)<<endl;//"Klawisz odpowiedzialny za włączenie pętli: "
        cout<<endl<<endl<<wyswietl_tekst(4,34)<<endl;//"Koniec i powrót do menu: x"
        for(;;)
        {
            Sleep(10);
            if(GetAsyncKeyState(znak))
            {
                for(int i=0;i<wiersz_tablica;i++)
                {Sleep(2);
                    if(auto_bot_wektory_kroki[0][i]!=-1){Sleep(usp_bota); SetCursorPos(auto_bot_wektory_kroki[0][i], auto_bot_wektory_kroki[1][i]);}else {Sleep(usp_bota);jedno_klikniecie();Sleep(2);}
                }
            }
            if(GetKeyState(auto_bot_loop_onoff_klawisz))
            {Sleep(odstep_miedzy_loopem);
                for(int i=0;i<wiersz_tablica;i++)
                {Sleep(2);
                    if(auto_bot_wektory_kroki[0][i]!=-1){Sleep(usp_bota); SetCursorPos(auto_bot_wektory_kroki[0][i], auto_bot_wektory_kroki[1][i]);}else {Sleep(usp_bota);jedno_klikniecie();Sleep(2);}
                }
            }
            if(GetAsyncKeyState(0x58)){break;} //koniec i powrót do menu
        }

    }
    if(wybor_1=='2')
    {
        unsigned int jaki_plik_uzywany_bedzie;
        cout<<wyswietl_tekst(4,35)<<endl;//"Wybierz z którego pliku Bot ma brać dane."
        cout<<wyswietl_tekst(4,36)<<endl;//"Lista dostępnych plików z zapisanymi wektorami:"
        for(int i=0;i<wszystkie_pliki_tab.size();i++)
        {odczyt_1=wszystkie_pliki_tab[i];
            if(odczyt_1=="0"){cout<<wyswietl_tekst(4,28);}else{cout<<i+1<<" - "<<odczyt_1<<endl;}//"!!!BRAK ZAPISANYCH WEKTORÓW!!!"
        }
        cin>>jaki_plik_uzywany_bedzie;
        jaki_plik_uzywany_bedzie--;
        z_jakiego_pliku_brac_dane=wszystkie_pliki_tab[jaki_plik_uzywany_bedzie];
        ofstream uzywany_plik;
        uzywany_plik.open("z_jakiego_pliku_kozystac.set");
        uzywany_plik<<z_jakiego_pliku_brac_dane;
        uzywany_plik.close();
        goto menu_AutoBot;
    }
}
//--------------------------------------------------------------------------------------------------------------------wyswietl_tekst(4,50)








void MENU()
{
    system("cls");
    cout<<endl<<endl;
    cout<<"             "<<wyswietl_tekst(4,37)<<endl;//"------------------------Wybierz opcje------------------------"
    cout<<"             "<<wyswietl_tekst(4,38)<<endl;//"      1 - Kliknięcie na milisekundę/sekundę."
    cout<<"             "<<wyswietl_tekst(4,39)<<endl;//"      2 - Ilość kliknięć w 1 milisekundzie."
    cout<<"             "<<wyswietl_tekst(4,40)<<endl;//"      3 - Auto Bot klika w danych wektorach na ekranie."
    cout<<"             "<<wyswietl_tekst(4,41)<<endl;//"      4 - Ustawienia."
    cout<<"             "<<wyswietl_tekst(4,42)<<endl;//"      5 - Ustawianie wektorów kliknieć Bota na ekranie."
    cout<<"             "<<wyswietl_tekst(4,43)<<endl;//"      6 - Reset do ustawien początkowych."
    cout<<"             "<<wyswietl_tekst(4,44)<<endl;//"      7 - O co chodzi z zabezpieczeniami?."
    cout<<endl;
    cout<<"             "<<wyswietl_tekst(4,45)<<endl;//"         m - Strona Główna."



    cout<<endl<<endl<<endl<<endl;
	cout<<endl<<"     "<<wyswietl_tekst(4,47);//"*===========================================================================*";
    cout<<endl<<"     "<<wyswietl_tekst(4,4)<<(char)znak;//"|  Aktualny przycisk uruchamiajacy automatyczne klikanie myszy to: "
    cout<<endl<<"     "<<wyswietl_tekst(4,5);if(rodzaj_uruchamiania==1){cout<<wyswietl_tekst(4,6);}else{cout<<wyswietl_tekst(4,7);}//"|  Aktualny styl uruchamiania auto klikania to: " <"Trzymanie klawisza" "Włącz / Wyłącz klikanie"
    cout<<endl<<"     "<<wyswietl_tekst(4,8);if(zabezpieczenie==1){cout<<wyswietl_tekst(4,9);}else if(zabezpieczenie==2){cout<<wyswietl_tekst(4,10);}else if(zabezpieczenie==3){cout<<wyswietl_tekst(4,11);}//"|  Aktualny poziom zabezpieczenia: " "Brak" "Średni" "Zaawansowany"
    cout<<endl<<"     "<<wyswietl_tekst(4,48)<<char(auto_bot_loop_onoff_klawisz);//"|  Klawisz odpowiedzialny za włączenie pętli: "
    cout<<endl<<"     "<<wyswietl_tekst(4,49)<<z_jakiego_pliku_brac_dane;//"|  Ostatnio uzywany plik z zapisanymi wektorami: "
    cout<<endl<<"     "<<wyswietl_tekst(4,50);//"|  Nazwy wszystki zapisanych plików z wektorami:"
    cout<<endl; for(int i=0;i<wszystkie_pliki_tab.size();i++){cout<<"     "<<"|  "<<i+1<<": "<<wszystkie_pliki_tab[i]<<endl;}

}

void Informacje()
{
wymiary_okna_szer_wys(110,10);


cout<<wyswietl_tekst(4,51)<<endl;//"Zabezpieczenia chronią programu przed wykryciem przez programy Anti-Cheat."
cout<<wyswietl_tekst(4,52)<<endl<<endl;//"Ponieżej znajduje się wyjaśnienie jak dane zabezpieczenie dokładnie działa"

cout<<wyswietl_tekst(4,53)<<wyswietl_tekst(4,54)<<endl;//"BRAK: "<<"Nic nie zmienia klika w idealnych odstępach czasu co zwiększa szanse na wykrycie przez Anty-Cheat."
cout<<wyswietl_tekst(4,55)<<wyswietl_tekst(4,56)<<endl;//"ŚREDNIE: "
cout<<wyswietl_tekst(4,57)<<wyswietl_tekst(4,58)<<endl;//"ZAAWANSOWANE: "

cout<<endl<<endl<<wyswietl_tekst(0,3);
}
};


class Kal_czasu  //wyswietl_tekst(5,)
{
public:
    int liczba_lat, liczba_dni, liczba_godzin, liczba_minut, liczba_sekund;
    long long wyn_sek, sekundy;
    long long lpelne,dpelne,gpelne,mpelne,milisekundy;
    long long lnpelne,dnpelne,gnpelne,mnpelne;

    void wpisanie()
    {
        liczba_lat=0; liczba_dni=0; liczba_godzin=0; liczba_minut=0; liczba_sekund=0;

        system("cls");
        cout<<wyswietl_tekst(5,1);//"Podaj liczbe lat: ";
        cin>>liczba_lat;
        system("cls");

        cout<<wyswietl_tekst(5,2);//"Podaj liczbe dni: ";
        cin>>liczba_dni;
        system("cls");

        cout<<wyswietl_tekst(5,3);//"Podaj liczbe godzin: ";
        cin>>liczba_godzin;
        system("cls");

        cout<<wyswietl_tekst(5,4);//"Podaj liczbe minut: ";
        cin>>liczba_minut;
        system("cls");

        cout<<wyswietl_tekst(5,5);//"Podaj liczbe sekund: ";
        cin>>liczba_sekund;
        system("cls");
    }


    void pelen_czas()
    {
        const int sekunda=1000; //milisekund
        const int minuta=60; //s
        const int godzina=3600; //s
        const int dzien=86400; //s
        const int rok=31536000; //s

        long long suma=liczba_minut*minuta+liczba_godzin*godzina+liczba_dni*dzien+liczba_lat*rok;
        wyn_sek=liczba_sekund+suma;//sprowadzenie wszystkiego do sekund

        lpelne=wyn_sek/rok;
        dpelne=wyn_sek/dzien;
        gpelne=wyn_sek/godzina;
        mpelne=wyn_sek/minuta;
        milisekundy=wyn_sek*sekunda;
        sekundy=wyn_sek;
    }


    void niepelen_czas()
    {

        const int sekunda=1000; //milisekund
        const int minuta=60; //s
        const int godzina=3600; //s
        const int dzien=86400; //s
        const int rok=31536000; //s


     lnpelne=(wyn_sek%rok)/(24*60*60);
     dnpelne=(wyn_sek%dzien)/(60*60);
     gnpelne=(wyn_sek%godzina)/60;
     mnpelne=wyn_sek%minuta;
    }

    void wyswietlenie()
    {
      system("cls");
      cout<<wyswietl_tekst(2,3)<<endl;//"Wynik: "
      cout<<"--------------------------"<<endl;

      cout<<wyswietl_tekst(5,6)<<"["<<lpelne<<"."<<lnpelne<<"]"<<wyswietl_tekst(5,7)<<endl;//Liczba lat: [Lata.Dni]
      cout<<wyswietl_tekst(5,8)<<"["<<dpelne<<"."<<dnpelne<<"]"<<wyswietl_tekst(5,9)<<endl;//Liczba dni: [Dni.Godziny]
      cout<<wyswietl_tekst(5,10)<<"["<<gpelne<<"."<<gnpelne<<"]"<<wyswietl_tekst(5,11)<<endl;//Liczba godzin:  [Godziny.Minuty]
      cout<<wyswietl_tekst(5,12)<<"["<<mpelne<<"."<<mnpelne<<"]"<<wyswietl_tekst(5,13)<<endl;//Liczba minut:  [Minuty.Sekundy]
      cout<<wyswietl_tekst(5,14)<<"["<<wyn_sek<<"]"<<endl;//Liczba sekund:
      cout<<wyswietl_tekst(5,15)<<"["<<milisekundy<<"]"<<endl;//Liczba milisekund:

      cout<<endl<<endl<<wyswietl_tekst(5,16);//"Nacisnij ENTER aby liczyc ponownie || x-koniec programu";
    }
};

int main ()  //wyswietl_tekst(6,)
{
cout<<wyswietl_tekst(6,1)<<endl;//"Ładowanie..."
 USTAWIENIA ustawienia;
 cout<<wyswietl_tekst(6,2)<<endl;//"Ustawienia klasa przypisana"
 ustawienia.start_programu_zczytanie_ustawien();
 cout<<wyswietl_tekst(6,3)<<endl;//"Ustawienia programu załadowano"
 AUTO_CLICKER autoclicker;
 cout<<wyswietl_tekst(6,4)<<endl;//"Auto Clicker klasa przypisana"
 WPL wpl;
 cout<<wyswietl_tekst(6,5)<<endl;//"WPL klasa przypisana"
 obliczanie_walut waluta;
 cout<<wyswietl_tekst(6,6)<<endl;//"Kalkulator do walut załadowano"
 waluta.kurs_walut_odczyt();
 cout<<wyswietl_tekst(6,7)<<endl;//"Kursy walut załodowane"
 ustawienia.zczytanie_nazw_plikow_do_ustawiania_myszy();
 cout<<wyswietl_tekst(6,8)<<endl;//"Zczytane nazwy plików z wektorami poprawnie"
 ustawienia.z_jakiego_pliku_kozystac_zczytanie_pliku_tylko();
 cout<<wyswietl_tekst(6,9)<<endl;//"Jaki ostatni plik z wektorami był używany załadowano"
 Kal_czasu czas;
 cout<<wyswietl_tekst(6,10)<<endl;//"Kalkulator czasu załadowany"

 // ladowanie roznych ustawien klikania (przypisanie procedur jako funkcji wywolawczych)
cout<<endl<<endl<<wyswietl_tekst(6,11)<<endl;//"Ładowanie zakończone."
Sleep(1000);
char wybor_programu;





strona_glowna:
    wymiary_okna_szer_wys(68,16);
    ustawienia.kolor_tekstu_z_ustawien();
system("cls");
cout<<wyswietl_tekst(6,12)<<wersja_programu;
cout<<endl<<endl;
cout<<"          "<<wyswietl_tekst(6,13)<<endl;//"+================ Wybierz Program ==============+"
cout<<"          "<<wyswietl_tekst(6,37)<<endl;//"|                                               |"
cout<<"          "<<wyswietl_tekst(6,14)<<endl;//"|       1 - Wielofunkcyjny kalkulator           |"
cout<<"          "<<wyswietl_tekst(6,15)<<endl;//"|       2 - Auto Clicer                         |"
cout<<"          "<<wyswietl_tekst(6,16)<<endl;//"|       3 - Kalkulator jednostek czasu          |"
cout<<"          "<<wyswietl_tekst(6,17)<<endl;//"|       4 - Ustawienia                          |"
cout<<"          "<<wyswietl_tekst(6,37)<<endl;//"|                                               |"
cout<<"          "<<wyswietl_tekst(6,37)<<endl;//"|                                               |"
cout<<"          "<<wyswietl_tekst(6,18)<<endl;//"|       r - Reset do ustawień początkowych      |"
cout<<"          "<<wyswietl_tekst(6,37)<<endl;//"|                                               |"
cout<<"          "<<wyswietl_tekst(6,36)<<endl;//"+===============================================+"
cout<<endl;
cout<<"                         "<<wyswietl_tekst(6,19)<<endl;//"x - Zakończ program"
wybor_programu=getch();
system("cls");


//Wielofunkcyjny kalkulator
//==========================================================================================================================================================================
if(wybor_programu=='1')
{
    char wybor='/0';
    USTAWIENIA ustawienia;



for(;;)
{
wybor='\0';
Sleep(5);
wymiary_okna_szer_wys(68,20);
Sleep(5);
ustawienia.kolor_tekstu_z_ustawien();
Sleep(5);


system("cls");
cout<<endl<<wyswietl_tekst(6,20)<<endl;//MENU GŁÓWNE
cout<<"           "<<wyswietl_tekst(6,39)<<endl;//+==============================================+
cout<<"           "<<wyswietl_tekst(6,21)<<endl;//1 - Dodawanie
cout<<"           "<<wyswietl_tekst(6,22)<<endl;//2 - Odejmowanie
cout<<"           "<<wyswietl_tekst(6,23)<<endl;//3 - Mnożenie
cout<<"           "<<wyswietl_tekst(6,24)<<endl;//4 - Dzielenie
cout<<"           "<<wyswietl_tekst(6,25)<<endl;//5 - Potęgowanie
cout<<"           "<<wyswietl_tekst(6,26)<<endl;//6 - Pierwiastkowanie
cout<<"           "<<wyswietl_tekst(6,27)<<data<<wyswietl_tekst(6,38)<<endl;//7 - Waluty  (Kurs walut z: )        |
cout<<"           "<<wyswietl_tekst(6,28)<<endl;//8 - Zmiana tekstu na kod binarny
cout<<"           "<<wyswietl_tekst(6,29)<<endl;//9 - Tablica ASCII
cout<<"           "<<wyswietl_tekst(6,30)<<endl;//% - Działania procentowe
cout<<"           "<<wyswietl_tekst(6,31)<<endl;//? - Pomoc
cout<<"           "<<wyswietl_tekst(6,32)<<endl;//m - Strona Główna
cout<<"           "<<wyswietl_tekst(6,39)<<endl;//+==============================================+
cout<<"            "<<wyswietl_tekst(6,33);
wybor=getch();
system("cls");



switch(wybor)
{
//---------------------------------------------------------------------------------------- dodawanie
case '1':
system("cls");
wpl.dodawanie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- odejmowanie
case '2':
system("cls");
wpl.odejmowanie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- mnozenie
case '3':
system("cls");
wpl.mnozenie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- dzielenie
case '4':
system("cls");
wpl.dzielenie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- potegowanie
case '5':
system("cls");
wpl.potegowanie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- pierwiastkowanie
case '6':
system("cls");
wpl.Pierwiastkowanie();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- waluty wybor
case '7':
system("cls");
waluta.wybor_dzialania();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- Zmiana tekstu na kod binarny
case '8':
system("cls");
wpl.tekst_na_binarny();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- Zmiana tekstu na kod z tablicy ASCII
case '9':
system("cls");
wpl.zamiana_tekstu_z_kodami_ascii();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- obliczanie procentowe
case '%':
system("cls");
wpl.procenty();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//----------------------------------------------------------------------------------------










//---------------------------------------------------------------------------------------- pomoc
case '?':
system("cls");
wpl.pomoc();
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
//---------------------------------------------------------------------------------------- Koniec programu
case 'm':
goto strona_glowna;
break;
//----------------------------------------------------------------------------------------
default:
system("cls");
system("COLOR 0C");
cout<<endl<<endl<<wyswietl_tekst(6,34);//"----Kod działania jest nie poprawny!!! Dokonaj wyboru ponownie----";
cout<<endl<<endl<<wyswietl_tekst(0,1);
break;
}
getch();
wymiary_okna_szer_wys(68,20);
ustawienia.kolor_tekstu_z_ustawien();
}
}
//==========================================================================================================================================================================


//Auto Clicer
//==========================================================================================================================================================================
if(wybor_programu=='2')
{
char wybor;

menu:
Sleep(100);
wymiary_okna_szer_wys(85,27);

    Sleep(100);
    autoclicker.MENU(); // pokazuje poczatkowe menu programu wyboru

    wybor=getch();
    system("cls");





if(wybor=='1') //wybor nr 1    odstepy czasu miedzy kliknieciami
{
    wymiary_okna_szer_wys(85,8);
    if(zabezpieczenie==1){autoclicker.Auto_klikanie_zab_1_klikniecie_na_milisekune_sekunde();}//brak zabezpieczenia przed antywirusem
    if(zabezpieczenie==2){}//srednie zabezpieczenia przed antywirusem
    if(zabezpieczenie==3){}//zaawansowane zabezpieczenia przed antywirusem
}

if(wybor=='2') //wybor nr 2    ilosc klikniec w 1 milisekundzie
{
    wymiary_okna_szer_wys(85,8);
    if(zabezpieczenie==1){autoclicker.Auto_klikanie_zab_1_ilosc_klikniec_w_milisekundzie();}//brak zabezpieczenia przed antywirusem
    if(zabezpieczenie==2){}//srednie zabezpieczenia przed antywirusem
    if(zabezpieczenie==3){}//zaawansowane zabezpieczenia przed antywirusem
}

if(wybor=='3') //wybor nr 3    Auto Bot klika w wcześniej zapisanych wektorach w danych plikach
{
autoclicker.Auto_Bot();
}




if(wybor=='4') //wybor nr 4 (ustawienia zapis nowych oraz zaladowanie ich)
{
ustawienia.zapis_nowych_ustawien();
ustawienia.start_programu_zczytanie_ustawien();
}
if(wybor=='5'){autoclicker.nagrywanie_pozycji_myszy();} //wybor nr 5
if(wybor=='6'){ustawienia.reset_do_ustawien_poczatkowych(); ustawienia.start_programu_zczytanie_ustawien();} //wybor nr 6   reset do ustawien poczatkowych
if(wybor=='7'){autoclicker.Informacje();getchar();wymiary_okna_szer_wys(85,27);} //wybor nr 7   wyswietlenie informacji o zabezpieczeniach
if(wybor=='m'){goto strona_glowna;} //wybor nr 8/m koniec



goto menu;
}
//==========================================================================================================================================================================


//Kalkulator jednosek czasu
//==========================================================================================================================================================================
if(wybor_programu=='3')
{
    wymiary_okna_szer_wys(68,13);
for(;;)
{
    czas.wpisanie();
    czas.pelen_czas();
    czas.niepelen_czas();
    czas.wyswietlenie();
getch();
if (GetAsyncKeyState(0x58)){break;}
}
Sleep(10);
}
//==========================================================================================================================================================================


//Ustawienia
//==========================================================================================================================================================================
if(wybor_programu=='4')
{
   ustawienia.zapis_nowych_ustawien();
   ustawienia.start_programu_zczytanie_ustawien();
   goto strona_glowna;
}
if(wybor_programu=='r')
{
   ustawienia.reset_do_ustawien_poczatkowych();
   ustawienia.start_programu_zczytanie_ustawien();
   goto strona_glowna;
}
//==========================================================================================================================================================================


if(wybor_programu=='x'){exit(0);}
if(wybor_programu!='1'||wybor_programu!='2'||wybor_programu!='3'||wybor_programu!='4')
{
system("COLOR 0C");
cout<<endl<<endl<<wyswietl_tekst(6,35);//"----Numer programu jest nie poprawny!!! Dokonaj wyboru ponownie----";
cout<<endl<<endl<<wyswietl_tekst(0,1);
getchar();
}
goto strona_glowna;
}
