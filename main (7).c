/*
	Dev-C++ 5.11 TDM-GCC 4.9.2 64-bit Release
	Windows 10 64-Bit
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//Max,Min ��renci ve s�nav sorusu say�lar�
#define MAX_N 100
#define MIN_N 1

//Sorulara verilebilecek cevaplar�n sakland��� dizi.
char CEVAPLAR[5] = {
    'A',
    'B',
    'C',
    'D',
    'E'
};

void cevap_anahtari_uret(char cevap_anahtari[], int S);
void cevap_anahtari_yazdir(char cevap_anahtari[], int S);
void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D);
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S);
void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S);
double sinif_ortalamasi_hesapla(double HBN[], int N);
double standart_sapma_hesapla(double ortalama, double HBN[], int N);
void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]);
//s�n�f ba�ar�s�n� ekrana yazd�ran fonk.
void sinif_basari(double ortalama, double harf_notlari[]);
//harf notunu aral�klar�n� hesaplayan fonk.
char * harf_notu(double t_puan, double harf_notlari[]);
int main() {
    //random say� �retmek i�in kullan�l�r.
    srand(time(NULL));
    //problemde verilen de�i�kenlerin tan�mlanmas�
    int N, S;
    double B, D;
    
    //��renci say�s�n�n kullan�c�dan al�nd��� blok, ��renci say�s� MIN-MAX aral���nda olana kadar sorulur.
    do {
        printf("Ogrenci sayisini giriniz (MAX %d, MIN %d): ", MAX_N, MIN_N);
        scanf("%d", & N);

    } while (N > MAX_N || N < 1);
	//Soru say�s�n�n kullan�c�dan al�nd��� blok, soru say�s� MIN-MAX aral���nda olana kadar sorulur.
    do {
        printf("Soru sayisini giriniz (MAX %d, MIN %d): ", MAX_N, MIN_N);
        scanf("%d", & S);
    } while (S > MAX_N || S < MIN_N);
	//Bo� b�rakma ihtimalinin kullan�c�dan al�nd��� blok, soru say�s� MIN-MAX aral���nda olana kadar sorulur.
    do {
        printf("Herhangi bir sorunun bos birakilma ihtimalini giriniz: (0.0 ~ 1.0): ");
        scanf("%lf", & B);
	//Do�ru cevaplama ihtimalinin kullan�c�dan al�nd��� blok, soru say�s� MIN-MAX aral���nda olana kadar sorulur.
    } while (B > 1 || B < 0);
    do {
        printf("Herhangi bir sorunun dogru cevaplanma ihtimalini giriniz: (0.0 ~ 1.0): ");
        scanf("%lf", & D);

    } while (D > 1 || D < 0);

	//kullan�c�dan al�nan de�erlere g�re olu�turulan diziler.(Matris boyutu [N][S] a��labilirdi fakat �dev �zerinde [][100] yazd���ndan fonksiyon imzalar� bozulmas�n diye b�yle kullan�ld�.)
    char ogrenci_cevaplari[N][100];
    char cevap_anahtari[S];
    
    //cevap anahtar� �reten fonksiyon �a�r�l�r.
    cevap_anahtari_uret(cevap_anahtari, S);
    //�retilen cevap anahtar�n� yazd�ran fonksiyon �a��r�l�r.
    cevap_anahtari_yazdir(cevap_anahtari, S);

    sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D);
    int i;
    for (i = 0; i < N; i++) {
        ogrenci_cevabini_yazdir(ogrenci_cevaplari, i, S);
        printf("\n");
    }
    double HBN[N], T_skoru[N];
    ogrencileri_puanla(ogrenci_cevaplari, cevap_anahtari, HBN, N, S);
    double ortalama = sinif_ortalamasi_hesapla(HBN, N);
    double std = standart_sapma_hesapla(ortalama, HBN, N);
    double harf_notlari[8];
    printf("\nSinif ortalamasi: %.2lf, standart sapma: %.2lf \n", ortalama, std);
    sinif_basari(ortalama, harf_notlari);

    //	printf("harf notu araligi: \n");
    //	for(i=0;i<7;i++){
    //		printf("%lf ",harf_notlari[i]);
    //	}

    T_skoru_hesapla(ortalama, HBN, N, std, T_skoru);

    printf("\nOgrenci notlari: \n");
    for (i = 0; i < N; i++) {
        printf("%03d. ogrencinin HBN: %.2lf T-skoru: %.2lf, harf notu: %s \n", i + 1, HBN[i], T_skoru[i], harf_notu(T_skoru[i], harf_notlari));
    }
    return 0;
}

void cevap_anahtari_uret(char cevap_anahtari[], int S) {
    int i;
    /*
		*0 ile 5 aras�nda random say� �retmek i�in mod 5 i�lemi yap�l�r.random say� olarak 0,1,2,3,4 d�necektir.
		*�retilen say�n�n globalde tan�mlanan cevaplar dizisinde ki kar��l��� cevap anahtar� dizisine aktar�l�r.
	*/
    for (i = 0; i < S; i++) {
        int r = rand() % 5;
        cevap_anahtari[i] = CEVAPLAR[r];

    }
}
void cevap_anahtari_yazdir(char cevap_anahtari[], int S) {
    int i;
    printf("\nCEVAP ANAHTARI: \n");
    //�retilen cevap anahtar� d�ng� ile ekrana yazd�r�l�r.
    for (i = 0; i < S; i++) {
        printf("%03d:%c | ", i + 1, cevap_anahtari[i]);

    }
    printf("\n\n");
}
void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D) {
    int i, j = 0, y = 0;
    //��rencinin soruya verdi�i cevab�n sakland��� de�i�ken.
    char ogrenci_cevap;
    //�retilen sorular�n yanl�� cevaplar�n� saklayan matris. Burada ki ama� ��renci yanl�� cevap verece�i zaman bunlardan birini se�mektir.
    char yanlis_cevaplar[S][4];
    
    //sorular�n yanl�� cevaplar�n�n bulunup ilgili matriste saklanmas�n� sa�layan d�ng�.
    for (i = 0; i < S; i++) {
        y = 0;
        for (j = 0; j < 5; j++) {
            if (CEVAPLAR[j] != cevap_anahtari[i]) {
                yanlis_cevaplar[i][y++] = CEVAPLAR[j];
            }
        }
    }
    /*
		- ��rencinin s�nav�n�n olu�turuldu�u blok
		- 0-1 aral���nda �retilen random say�n�n kullan�c�dan girilen orandan k���k oldu�u durumda, ihtimalin ger�ekle�ti�i kabul edilmi�tir. 
		rand() fonksiyonunun uniform oldu�u kabul edilmi�tir.
		�rne�in: kullan�c� bo� b�rakma ihtimalini 0.3 girerse. 
		0-0.3 aras� gelen random say� bu ihtimalin ger�ekle�ti�ini g�sterir. geriye kalan 0.7 lik b�l�m (0.3-1) ger�ekle�medi�ini g�sterir.
    */
    for (i = 0; i < N; i++) {
        for (j = 0; j < S; j++) {
			//0-1 aral���nda random say� �retmek i�in kullan�ld�.
            double rndB = rand() / ((double) RAND_MAX);
            //bo� b�rakma ihtimali kontrol�
            if (rndB < B) {
            	//e�er bo� b�rak�lacaksa X olarak sorunun i�aretlenmesi
                ogrenci_cevap = 'X';
            } else {
            	//bo� b�rak�lmayacak sorunun do�ru cevaplan�p cevaplanmayaca��n�n kontrol�
                double rndD = rand() / ((double) RAND_MAX);
                if (rndD < D) {
                	//do�ru cevab�n ilgili de�i�kene atanmas�
                    ogrenci_cevap = cevap_anahtari[j];
                } else {
                	//yanl�� i�aretlenecek durumda,yanl�� cevaplar i�erisinden rastgele se�ilmesi.
                    int r = rand() % 4;
                    ogrenci_cevap = yanlis_cevaplar[j][r];
                }
            }
            //cevab�n ilgili matriste i�aretlenmesi
            ogrenci_cevaplari[i][j] = ogrenci_cevap;
        }
    }
}
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S) {
    int j;
    printf("%03d. Ogrencinin cevaplari: \n", ogrenci_ID + 1);
    //cevap matrisinde ilgili ��rencinin sorular�n�n cevaplar�n�n yaz�ld��� d�ng�
    for (j = 0; j < S; j++) {
        printf("%03d:%c | ", j + 1, ogrenci_cevaplari[ogrenci_ID][j]);
    }
}
void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S) {
    int i, j;
    double puan;//��renci puan�n�n sakland��� de�i�ken
    double soru_puan = 100.0 / ((double) S); //s�navda soru ba��na d��en puan�n hesaplanmas� 100 tam not kabul edilip soru say�s�na b�l�nm��t�r.
    
	for (i = 0; i < N; i++) {
        puan = 100;
        for (j = 0; j < S; j++) {
        	//��rencinin cevab� do�ru de�ilse
            if (ogrenci_cevaplari[i][j] != cevap_anahtari[j]) {
            	//soru puan� d���l�r
                puan -= soru_puan;
                //soru bo� b�rak�lmam��sa 4 yanl���n 1 do�ruyu g�t�rd��� s�navda 1/4 0.25 puan d���l�r.
                if (ogrenci_cevaplari[i][j] != 'X') {
                    puan -= 0.25;
                }

            }
        }
        puan = puan < 0 ? 0 : puan; //puan s�f�rdan k���kse 0 kabul edilir.
        HBN[i] = puan; //��rencinin puan� ilgi dizide saklan�r.
    }
}
double sinif_ortalamasi_hesapla(double HBN[], int N) {
    double ortalama, toplam;
    int i;
    //��renci puanlar� toplan�r
    for (i = 0; i < N; i++) {
        toplam += HBN[i];
    }
    // toplam ��renci say�s�na b�l�nerek ortalama d�nd�r�l�r
    return toplam / ((double) N);
}
double standart_sapma_hesapla(double ortalama, double HBN[], int N) {
    int i;
    double std;
    //standart sapma hesaplan�r.
    for (i = 0; i < N; ++i) {
        std += pow(HBN[i] - ortalama, 2);
    }
    return sqrt(std / N);
}
void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]) {
    int i;
    //T skorunun hesapland��� d�ng�. Soruda verilen form�le g�re. 
    for (i = 0; i < N; i++) {
        T_skoru[i] = 60 + (10 * ((HBN[i] - ortalama) / std));
    }
}
void sinif_basari(double ortalama, double harf_notu[]) {
	/*
		S�n�f ortalamas�na g�re s�n�f d�zeyi hesaplan�r. Burada alt s�n�rlar dikkate al�nm��t�r.
		Verilen tablodaki ilgili harf notu aral�klar�(de�erlendirmenin yap�laca��) harf_notu dizisinde saklanm��t�r.
	*/
    printf("Sinif duzeyi: ");
    int i;
    int baslangic;
    if (ortalama <= 42.5) {
        printf("Kotu");
        baslangic = 46;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    } else if (ortalama <= 47.5) {
        printf("Zay�f");
        baslangic = 44;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }

    } else if (ortalama <= 52.5) {
        printf("Orta");
        baslangic = 42;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }

    } else if (ortalama <= 57.5) {
        printf("Ortanin Ustu");
        baslangic = 40;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    } else if (ortalama <= 62.5) {
        printf("�yi");
        baslangic = 38;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    } else if (ortalama <= 70) {
        printf("Cok iyi");
        baslangic = 36;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    } else if (ortalama <= 80) {
        printf("Mukemmel");
        baslangic = 34;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    } else if (ortalama <= 100) {
        printf("Ustun basari");
        baslangic = 32;
        for (i = 0; i < 8; i++) {
            harf_notu[i] = baslangic;
            baslangic += 5;
        }
    }
    printf("\n");
}
char * harf_notu(double t_puan, double harf_notlari[]) {
    int i = 0;
    //de�erlendirme yap�lacak harf notlar� puanlar�n�n sakland��� dizide, ��renci t puan�n�n hangi aral��a geldi�i i indisinde saklan�r ve ilgili harf notu d�nd�r�l�r.
    while (harf_notlari[i] < t_puan) {
        i++;
    }
    if (i == 0) {
        return "FF";
    } else if (i == 1) {
        return "FD";
    } else if (i == 2) {
        return "DD";
    } else if (i == 3) {
        return "DC";
    } else if (i == 4) {
        return "CC";
    } else if (i == 5) {
        return "CB";
    } else if (i == 6) {
        return "BB";
    } else if (i == 7) {
        return "BA";
    } else {
        return "AA";
    }
}
