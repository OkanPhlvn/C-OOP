#include <iostream>
#include <string.h>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <math.h>

#define enFazla 255
#define enAz 0

using namespace std;

template <class Type>
class Matrix
{
protected:
	Type satir;
	Type sutun;
	Type** data;

public:

	//Kapsulleme
	void setSatir(int rc);
	void setSutun(int cc);
	int getSatir();
	int getSutun();
	int getDataItem(int i, int j);
	void setDataItem(int i, int j, int value);

	Matrix(int satir = 10, int sutun = 10, int deger = 0); //Birinci Constructor tanimi
	Matrix(int satir, int sutun, char deger);              //ikinci Constructor tanimi
	~Matrix();                                             //Destructor tanimi


	void resize(Type row, Type column);        //Yeniden boyutlandirma
	void T();                                  //Transpoze alma
	void emul(Matrix<Type>& obje);             //Eleman duzeyinde carpma
    int det();                                 //Determinant alma
	int determinant(int **data, int satir);    //Det fonksiyonuna geri donen fonksiyon
	void print();                              //Konsola matris yazdirma
	void print(string dosyaAdi);               //Dosyaya matris yazdirma


	Matrix<Type>& operator+(Type const& number); //Operator Overloading (+ number)
	Matrix<Type>& operator-(Type const& number); //Operator overloading (- number)
	Matrix<Type>& operator*(Type const& number); //Operator overloading (* number)
	Matrix<Type>& operator/(Type const& number); //Operator overloading (/ number)
	Matrix<Type>& operator%(Type const& number); //Operator overloading (% number)
	Matrix<Type>& operator^(Type const& number); //Operator overloading (^ number)
};

template <class Type>
void Matrix<Type>:: setSatir( int rc )
{
    satir = rc;
}

template <class Type>
void Matrix<Type>:: setSutun( int cc )
{
    sutun = cc;
}

template <class Type>
int Matrix<Type>:: getSatir()
{
    return satir;
}


template <class Type>
int Matrix<Type>:: getSutun()
{
    return sutun;
}


template <class Type>
int Matrix<Type>:: getDataItem(int i, int j)
{
    return data[i][j];
}


template <class Type>
void Matrix<Type>:: setDataItem(int i, int j, int value)
{
    data[i][j] = value;
}


//Birinci Constructor
template <class Type>
Matrix<Type>:: Matrix(int satir,int sutun ,int deger)
{
    setSatir(satir);
    setSutun(sutun);

    data = new Type * [getSatir()];

    for (int i = 0; i < getSatir(); i++)
    {
        data[i] = new Type[getSutun()];
    }

    for (int i = 0; i < getSatir(); i++)
    {
        for (int j = 0; j < getSutun(); j++)
        {
            setDataItem(i, j, deger);
        }
    }
}


//Ikinci Constructor
template <class Type>
Matrix<Type>:: Matrix(int satir, int sutun, char deger)
{

    setSatir(satir);
    setSutun(sutun);

    srand(time(0)); //Rastgele sayi uretme

    data = new Type * [getSatir()];

    for (int i = 0; i < getSatir(); i++)
    {
        data[i] = new Type[getSutun()];
    }

    //Birim matris
    if (deger == 'e') {

        for (int i = 0; i < getSatir(); i++)
        {
            for (int j = 0; j < getSutun(); j++)
            {
                if (i == j)
                {
                    setDataItem(i, j, 1);
                }
                else {
                    setDataItem(i, j, 0);
                }
            }
        }
    }

    //Random deger ureten Matris
    else if (deger == 'r') {

        for (int i = 0; i < getSatir(); i++)
        {
            for (int j = 0; j < getSutun(); j++)
            {
                int value = rand() % (enFazla - enAz + 1) + enAz;
                setDataItem(i, j, value);
            }
        }
    }

    else if(deger == 'L')
    {
        int k = 1;

        for(int i = 0; i < getSatir(); i++)
        {
            for(int j = 0; j < getSutun(); j++)
            {
                data[i][j] = k++;
            }
        }

        for(int i = 0; i < getSatir(); i++)
        {
            for(int j = 0; j < getSutun(); j++)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }



    else
    {
        cout << "HATALI GIRIS... Lutfen Birim matris icin: 'e' , Rastgele matris icin: 'r' degerini giriniz " << endl;
        exit(0);
    }
}


//Destructor tanimi
template <class Type>
Matrix<Type> :: ~Matrix()
{
    for(int i = 0; i < getSatir(); i++)
    {
        delete data[i];
    }

    delete data;
}


//Operator Overloading (+) --iki matris toplami
template <class Type>
Matrix<Type>& operator+(Matrix<Type>& obje1 , Matrix<Type>& obje2)
{
    Matrix<Type>* topla = new Matrix<Type>(obje1.getSatir(), obje2.getSutun());

    if (obje1.getSatir() == obje2.getSatir() && obje1.getSutun() == obje2.getSutun()) {
        for (int i = 0; i < obje1.getSatir(); i++)
        {
            for (int j = 0; j < obje1.getSutun(); j++)
            {
                int value = obje1.getDataItem(i, j) + obje2.getDataItem(i, j);
                topla->setDataItem(i, j, value);
            }
        }
    }
    else
    {
        cout << "Satir ve sutun sayisi esit olmadigindan -1 degerleri yazdirildi" << endl;
        topla = new Matrix<Type>(obje1.getSatir(), obje1.getSutun(), -1);
    }
    return *topla;
}


//Operator Overloading (-) --iki matris farki
template <class Type>
Matrix<Type>& operator-(Matrix<Type>& obje1 , Matrix<Type>& obje2)
{
    Matrix<Type>* cikar = new Matrix<Type>(obje1.getSatir(), obje1.getSutun());

    if (obje1.getSatir() == obje2.getSatir() && obje1.getSutun() == obje2.getSutun()) {
        for (int i = 0; i < obje1.getSatir(); i++)
        {
            for (int j = 0; j < obje1.getSutun(); j++)
            {
                int value = obje1.getDataItem(i, j) - obje2.getDataItem(i, j);
                cikar->setDataItem(i, j, value);
            }
        }
    }
    else
    {
        cout << "Satir ve sutun sayisi esit olmadigindan -1 degerleri yazdirildi" << endl;
        cikar = new Matrix<Type>(obje1.getSatir(), obje1.getSutun(), -1);
    }
    return *cikar;
}


//Operator Overloading (*) -- iki matris carpimi
template <class Type>
Matrix<Type>& operator*(Matrix<Type>& obje1 , Matrix<Type>& obje2)
{
    int sum = 0;

    Matrix<int>* carp = new Matrix<Type>(obje1.getSatir(), obje2.getSutun());

    for (int i = 0; i < obje1.getSatir(); i++)
    {
        for (int j = 0; j < obje2.getSutun(); j++)
        {
            for (int k = 0; k < obje1.getSutun(); k++)
            {
                int sayi1 = obje1.getDataItem(i, k);
                int sayi2 = obje2.getDataItem(k, j);
                sum += sayi1 * sayi2;
            }

            carp->setDataItem(i, j, sum);
            sum = 0;
        }
    }
    return *carp;
}


//Operator overloading ( + number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator+(Type const &number)
{
    Matrix<Type>* topla = new Matrix<Type>(getSatir(), getSutun());

    for (int i = 0; i < getSatir(); i++)
    {
        for (int j = 0; j < getSutun(); j++)
        {
            int value = getDataItem(i, j) + number;
            topla->setDataItem(i, j, value);
        }
    }
    return *topla;
}


//Operator Overloaing ( - number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator-(Type const &number)
{
	Matrix<Type>* cikar = new Matrix<Type>(getSatir(), getSutun());

	for (int i = 0; i < getSatir(); i++)
	{
		for (int j = 0; j < getSutun(); j++)
		{
			int value = getDataItem(i, j) - number;
			cikar->setDataItem(i, j, value);
		}
	}
	return *cikar;
}


//Operator Overloaing ( * number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator*(Type const &number)
{
	Matrix<Type>* carp = new Matrix<Type>(getSatir(), getSutun());

		for (int i = 0; i < getSatir(); i++)
		{
			for (int j = 0; j < getSutun(); j++)
			{
				int value = getDataItem(i, j) * number;
				carp->setDataItem(i, j, value);
			}
		}
		return *carp;
}


//Operator Overloaing ( / number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator/(Type const &number)
{
	Matrix<Type>* bolme = new Matrix<Type>(getSatir(), getSutun());

		for (int i = 0; i < getSatir(); i++)
		{
			for (int j = 0; j < getSutun(); j++)
			{
				int value = getDataItem(i, j) / number;
				bolme->setDataItem(i, j, value);
			}
		}
		return *bolme;
}


//Operator Overloaing ( % number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator%(Type const &number)
{
	Matrix<Type>* kalan = new Matrix<Type>(getSatir(), getSutun());

		for (int i = 0; i < getSatir(); i++)
		{
			for (int j = 0; j < getSutun(); j++)
			{
				int value = getDataItem(i, j) % number;
				kalan->setDataItem(i, j, value);
			}
		}
		return *kalan;
}


//Operator Overloaing ( ^ number )
template <class Type>
Matrix<Type>& Matrix<Type> ::operator^(Type const &number)
{
	Matrix<Type>* us = new Matrix<Type>(getSatir(), getSutun());

		for (int i = 0; i < getSatir(); i++)
		{
			for (int j = 0; j < getSutun(); j++)
			{
				int value = pow(getDataItem(i, j), number);
				us->setDataItem(i, j, value);
			}
		}
		return *us;
}


//Matris yeniden boyutlandirma
template <class Type>
void Matrix<Type> :: resize(Type row , Type column)
{
    if (row <= 0 || column <= 0)
    {
        cout << "Yeniden boyutlandiramazsiniz." << endl;
        return;
    }

    if (row == getSatir() && column == getSutun())
    {
        return;
    }

    Type** newData;
    newData = new Type * [row];

    for (int i = 0; i < row; i++)
    {
        newData[i] = new Type[column];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (i < getSatir() && j < getSutun())
            {
                newData[i][j] = getDataItem(i, j);
            }
            else {
                newData[i][j] = 0;
            }
        }
    }

    data = newData;
    setSatir(row);
    setSutun(column);
}


//Matris Transpoz alma
template <class Type>
void Matrix<Type> :: T()
{
    Type** Tdata;

    Tdata = new Type * [getSutun()];

    for (int i = 0; i < getSutun(); i++)
    {
        Tdata[i] = new Type[getSatir()];

    }
    for (int i = 0; i < getSatir(); i++)
    {
        for (int j = 0; j < getSutun(); j++)
        {
            Tdata[j][i] = getDataItem(i,j);
        }
    }

    for (int i = 0; i < getSutun(); i++)
    {
        for (int j = 0; j < getSatir(); j++)
        {
            setDataItem(i,j, Tdata[i][j]);
        }
    }
}


//Eleman duzeyinde Matris carpimi
template <class Type>
void Matrix<Type> :: emul(Matrix<Type>& obje)
{
    Type** sonuc;

    sonuc = new Type * [getSatir()];

    for (int i = 0; i < getSatir(); i++)
    {
        sonuc[i] = new Type[getSutun()];
    }


    if(getSatir() == obje.getSatir() && getSutun() == obje.getSutun())
    {
        for (int i = 0; i < getSatir(); i++)
        {
            for (int j = 0; j < getSutun(); j++)
            {
                sonuc[i][j] = getDataItem(i, j) * obje.getDataItem(i, j);
            }
        }
        data = sonuc; // yeni matrisim degistirilen matrisin boyutuna esitlendi
    }

    else
    {
        cout << "Lutfen iki matrisin satir ve sutun sayilarini esit giriniz..." << endl;
        exit(0);
    }

}


//Matris determinant alma
template <class Type>
int Matrix<Type> :: det()
{
    return determinant(data, satir);
}


template <class Type>
int Matrix<Type> :: determinant(int** data, int satir)
{
    int det1 = 0;
    Type** submatrix;

    submatrix = new Type * [satir];

    for (int i = 0; i < satir; i++)
    {
        submatrix[i] = new Type[satir];
    }

    submatrix = data;

    //2x2'lik matris determinanti
    if (satir == 2)
    {
        int sonuc = (submatrix[0][0] * submatrix[1][1]) - (submatrix[1][0] * submatrix[0][1]);
        return sonuc;
    }

    // 2x2 den buyuk matrislerin determinanti
    else
    {
        for (int x = 0; x < satir; x++) {
            int subi = 0;
            for (int i = 1; i < satir; i++)
            {
                int subj = 0;
                for (int j = 0; j < satir; j++)
                {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = submatrix[i][j];
                    subj++;
                }
                subi++;
            }
            det1 = det1 + (pow(-1, x) * submatrix[0][x] * determinant(submatrix, satir - 1));
        }
    }

    return det1;
}


//Konsola Matris yazdirma
template <class Type>
void Matrix<Type> :: print()
{
    for (int i = 0; i < satir; i++)
    {
        for (int j = 0; j < sutun; j++)
        {
            cout << setw(3) << getDataItem(i,j) << " ";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}


//Dosyaya (file.txt) Matris yazdirma
template <class Type>
void Matrix<Type> :: print(string dosyaAdi)
{
    ofstream matrisYaz(dosyaAdi.c_str());
    if (!matrisYaz.is_open())
    {
        cout << "Dosya acma islemi basarisiz!" << endl;
        exit(0);
    }

    for (int i = 0; i < satir; i++)
    {
        for (int j = 0; j < sutun; j++)
        {
            matrisYaz << setw(3) << getDataItem(i,j);
        }
        matrisYaz << endl;
    }
}


//Table Sinifi
template <class Type>
class Table : public Matrix<Type> {
protected:
	string  row[53] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52" };
	string  col[53] = { " ","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","AA","BB","CC","DD","EE","FF","GG","HH","II","JJ","KK","LL","MM","NN","OO","PP","QQ","RR","SS","TT","UU","VV","WW","XX","YY","ZZ" };
public:

	Table() :Matrix<Type>() { }                               //10x10 0 degerli tablo
	Table(int r, int c, int d) :Matrix<Type>(r, c, d) { }     //rxc d degerli tablo
	Table(int r, int c, char ch) :Matrix<Type>(r, c, ch) { }  //rxc 0-255 arasi degerli tablo

	int itemAt(int r , int c);            //rxc -> Degeri getir.
	int itemAt(string rs, string cs);     // itemAt("1","A")
	int itemAt(string s); 			      //itemAt("A2") -> [2,0] degerini verir.
	void setRowNames(string s[], int n);  //Satir adlarini gunceller.
	void setColNames(string c[], int n);  //Sutun adlarini gunceller.
	void print(); 						  //Tablo seklinde yazdirma
};


//Matriste rxc -> Degeri verir
template <class Type>
int Table<Type> :: itemAt(int r , int c)
{
	return this->getDataItem(r, c);
}


//itemAt("1","A") degerini verir.
template <class Type>
int Table<Type> :: itemAt(string rs, string cs)
{
	int _row; //Satir
	int _col; //Sutun

	int rowLength = sizeof(row) / sizeof(row[0]); //row dizisinin uzunlugu
	int colLength = sizeof(col) / sizeof(col[0]); //col dizisinin uzunlugu

	for (int i = 0; i < rowLength; i++)
	{
		if (row[i] == rs)
		{
			_row = i;
			break;
		}
	}

	for (int j = 0; j < colLength; j++)
	{
		if (col[j] == cs)
		{
			_col = j;
			break;
		}
	}

	return this->getDataItem(_row, _col - 1); //col dizisinde bosluk alinmamasi icin -1 yapildi.
}


//itemAt("A2") -> [2,0] degerini verir
template <class Type>
int Table<Type> :: itemAt(string s)
{
	int n = s.length(); //String uzunlugu
	char char_array[n + 1]; //CHAR dizisine aktar uzunlugu

	strcpy(char_array, s.c_str()); //Verileri char dizisine aktar

	int _col = (int)char_array[0] - 'A';
	int _row = (int)char_array[1] - '0';

	return this->getDataItem(_row, _col);
}


//Satir adlarini gunceller.
template <class Type>
void Table<Type> :: setRowNames(string s[], int n)
{
	for (int i = 0; i < n; i++)
	{
		row[i] = s[i];
	}
}


//Sutun adlarini gunceller.
template <class Type>
void Table<Type> :: setColNames(string c[], int n)
{
	for (int j = 0; j < n; j++)
	{
		col[j + 1] = c[j];
	}
}


//Tablo seklinde matris yazdirir.
template <class Type>
void Table<Type> :: print()
{
	for (int i = 0; i < this->getSatir() + 1; i++)
    {
        for (int j = 0; j < this->getSutun() + 1; j++)
        {
            if (i == 0)
            {
                cout << setw(5) << col[j];
            }
            else if (j == 0)
            {
                cout << setw(4) << row[i - 1] << "|";
            }
            else
            {
                cout << setw(5) << this->getDataItem(i - 1, j - 1);
            }
            if (j == this->getSutun()) cout << endl;
        }
    }
    cout << endl;
}

int main()
{
    /////////////////////////////////////////////////
    //                MATRÝX CLASS                 //
    /////////////////////////////////////////////////

    //Matrix<int>  *m1 = new Matrix<int>();
	//Matrix<int>  *m2 = new Matrix<int>(3 , 3 , 5);
    //Matrix<int>  *m3 = new Matrix<int>(4 , 4 , 8);
	//Matrix<int>  *m4 = new Matrix<int>(4 , 4 , 'e');
	//Matrix<int>  *m5 = new Matrix<int>(2 , 2 , 'r');

    //m5->T();

	//m5->resize(4,4);

	//cout << "Determinant : " << m3->det() << endl;

	//m2->emul(*m3);

	//*m2 = (*m2) * (*m3);
	//*m2 = *m2 + *m3;
	//*m2 = *m2 - *m3;
	//*m2 = *m2 + 12;
	//*m2 = *m2 - 4;
	//*m2 = *m2 * 4;
	//*m2 = *m2 / 2;
    //*m2 = *m2 % 5;
	//*m2 = *m2 ^ 5;

	//m1->print();
    //m2->print();
	//m3->print();
	//m4->print();
	//m5->print();

	//m2->print("file.txt");


    ///////////////////////////////////////
    //            TABLE CLASS            //
    ///////////////////////////////////////

	//Table<int> *t1 = new Table<int>();
	//Table<int> *t2 = new Table<int>(7,4,5);
	//Table<int> *t3 = new Table<int>(5,5,'r');

	//string s[] = {"0. satir", "1. satir", "2. satir" , "3. satir" , "4. satir"};
	//t3->setRowNames(s , 5);

	//string c[] = {"0. sutun ", "1. sutun " , "2. sutun " ,"3. sutun " ,"4. sutun "};
	//t3->setColNames(c , 5);

	//t1->print();
	//t2->print();
	//t3->print();

	//cout <<   "Deger : "  <<   t3->itemAt(0,1)                       << endl;
	//cout <<   "Deger : "  <<   t3->itemAt("4","C")                   << endl;
	//cout <<   "Deger : "  <<   t3->itemAt("A2")                      << endl;
	//cout <<   "Deger : "  <<   t3->itemAt("2. satir", "1. sutun ")   << endl;

	return 0;
}
