/*
	Dev-C++ 5.11 TDM-GCC 4.9.2 64-bit Release
	Windows 10 64-Bit
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//Max,Min öðrenci ve sýnav sorusu sayýlarý
#define MAX_N 100
#define MIN_N 1

//Sorulara verilebilecek cevaplarýn saklandýðý dizi.
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
//sýnýf baþarýsýný ekrana yazdýran fonk.
void sinif_basari(double ortalama, double harf_notlari[]);
//harf notunu aralýklarýný hesaplayan fonk.
char * harf_notu(double t_puan, double harf_notlari[]);
int main() {
    //random sayý üretmek için kullanýlýr.
    srand(time(NULL));
    //problemde verilen deðiþkenlerin tanýmlanmasý
    int N, S;
    double B, D;
    
    //Öðrenci sayýsýnýn kullanýcýdan alýndýðý blok, öðrenci sayýsý MIN-MAX aralýðýnda olana kadar sorulur.
    do {
        printf("Ogrenci sayisini giriniz (MAX %d, MIN %d): ", MAX_N, MIN_N);
        scanf("%d", & N);

    } while (N > MAX_N || N < 1);
	//Soru sayýsýnýn kullanýcýdan alýndýðý blok, soru sayýsý MIN-MAX aralýðýnda olana kadar sorulur.
    do {
        printf("Soru sayisini giriniz (MAX %d, MIN %d): ", MAX_N, MIN_N);
        scanf("%d", & S);
    } while (S > MAX_N || S < MIN_N);
	//Boþ býrakma ihtimalinin kullanýcýdan alýndýðý blok, soru sayýsý MIN-MAX aralýðýnda olana kadar sorulur.
    do {
        printf("Herhangi bir sorunun bos birakilma ihtimalini giriniz: (0.0 ~ 1.0): ");
        scanf("%lf", & B);
	//Doðru cevaplama ihtimalinin kullanýcýdan alýndýðý blok, soru sayýsý MIN-MAX aralýðýnda olana kadar sorulur.
    } while (B > 1 || B < 0);
    do {
        printf("Herhangi bir sorunun dogru cevaplanma ihtimalini giriniz: (0.0 ~ 1.0): ");
        scanf("%lf", & D);

    } while (D > 1 || D < 0);

	//kullanýcýdan alýnan deðerlere göre oluþturulan diziler.(Matris boyutu [N][S] açýlabilirdi fakat ödev üzerinde [][100] yazdýðýndan fonksiyon imzalarý bozulmasýn diye böyle kullanýldý.)
    char ogrenci_cevaplari[N][100];
    char cevap_anahtari[S];
    
    //cevap anahtarý üreten fonksiyon çaðrýlýr.
    cevap_anahtari_uret(cevap_anahtari, S);
    //üretilen cevap anahtarýný yazdýran fonksiyon çaðýrýlýr.
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
		*0 ile 5 arasýnda random sayý üretmek için mod 5 iþlemi yapýlýr.random sayý olarak 0,1,2,3,4 dönecektir.
		*Üretilen sayýnýn globalde tanýmlanan cevaplar dizisinde ki karþýlýðý cevap anahtarý dizisine aktarýlýr.
	*/
    for (i = 0; i < S; i++) {
        int r = rand() % 5;
        cevap_anahtari[i] = CEVAPLAR[r];

    }
}
void cevap_anahtari_yazdir(char cevap_anahtari[], int S) {
    int i;
    printf("\nCEVAP ANAHTARI: \n");
    //Üretilen cevap anahtarý döngü ile ekrana yazdýrýlýr.
    for (i = 0; i < S; i++) {
        printf("%03d:%c | ", i + 1, cevap_anahtari[i]);

    }
    printf("\n\n");
}
void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D) {
    int i, j = 0, y = 0;
    //öðrencinin soruya verdiði cevabýn saklandýðý deðiþken.
    char ogrenci_cevap;
    //üretilen sorularýn yanlýþ cevaplarýný saklayan matris. Burada ki amaç öðrenci yanlýþ cevap vereceði zaman bunlardan birini seçmektir.
    char yanlis_cevaplar[S][4];
    
    //sorularýn yanlýþ cevaplarýnýn bulunup ilgili matriste saklanmasýný saðlayan döngü.
    for (i = 0; i < S; i++) {
        y = 0;
        for (j = 0; j < 5; j++) {
            if (CEVAPLAR[j] != cevap_anahtari[i]) {
                yanlis_cevaplar[i][y++] = CEVAPLAR[j];
            }
        }
    }
    /*
		- öðrencinin sýnavýnýn oluþturulduðu blok
		- 0-1 aralýðýnda üretilen random sayýnýn kullanýcýdan girilen orandan küçük olduðu durumda, ihtimalin gerçekleþtiði kabul edilmiþtir. 
		rand() fonksiyonunun uniform olduðu kabul edilmiþtir.
		örneðin: kullanýcý boþ býrakma ihtimalini 0.3 girerse. 
		0-0.3 arasý gelen random sayý bu ihtimalin gerçekleþtiðini gösterir. geriye kalan 0.7 lik bölüm (0.3-1) gerçekleþmediðini gösterir.
    */
    for (i = 0; i < N; i++) {
        for (j = 0; j < S; j++) {
			//0-1 aralýðýnda random sayý üretmek için kullanýldý.
            double rndB = rand() / ((double) RAND_MAX);
            //boþ býrakma ihtimali kontrolü
            if (rndB < B) {
            	//eðer boþ býrakýlacaksa X olarak sorunun iþaretlenmesi
                ogrenci_cevap = 'X';
            } else {
            	//boþ býrakýlmayacak sorunun doðru cevaplanýp cevaplanmayacaðýnýn kontrolü
                double rndD = rand() / ((double) RAND_MAX);
                if (rndD < D) {
                	//doðru cevabýn ilgili deðiþkene atanmasý
                    ogrenci_cevap = cevap_anahtari[j];
                } else {
                	//yanlýþ iþaretlenecek durumda,yanlýþ cevaplar içerisinden rastgele seçilmesi.
                    int r = rand() % 4;
                    ogrenci_cevap = yanlis_cevaplar[j][r];
                }
            }
            //cevabýn ilgili matriste iþaretlenmesi
            ogrenci_cevaplari[i][j] = ogrenci_cevap;
        }
    }
}
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S) {
    int j;
    printf("%03d. Ogrencinin cevaplari: \n", ogrenci_ID + 1);
    //cevap matrisinde ilgili öðrencinin sorularýnýn cevaplarýnýn yazýldýðý döngü
    for (j = 0; j < S; j++) {
        printf("%03d:%c | ", j + 1, ogrenci_cevaplari[ogrenci_ID][j]);
    }
}
void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S) {
    int i, j;
    double puan;//öðrenci puanýnýn saklandýðý deðiþken
    double soru_puan = 100.0 / ((double) S); //sýnavda soru baþýna düþen puanýn hesaplanmasý 100 tam not kabul edilip soru sayýsýna bölünmüþtür.
    
	for (i = 0; i < N; i++) {
        puan = 100;
        for (j = 0; j < S; j++) {
        	//öðrencinin cevabý doðru deðilse
            if (ogrenci_cevaplari[i][j] != cevap_anahtari[j]) {
            	//soru puaný düþülür
                puan -= soru_puan;
                //soru boþ býrakýlmamýþsa 4 yanlýþýn 1 doðruyu götürdüðü sýnavda 1/4 0.25 puan düþülür.
                if (ogrenci_cevaplari[i][j] != 'X') {
                    puan -= 0.25;
                }

            }
        }
        puan = puan < 0 ? 0 : puan; //puan sýfýrdan küçükse 0 kabul edilir.
        HBN[i] = puan; //öðrencinin puaný ilgi dizide saklanýr.
    }
}
double sinif_ortalamasi_hesapla(double HBN[], int N) {
    double ortalama, toplam;
    int i;
    //öðrenci puanlarý toplanýr
    for (i = 0; i < N; i++) {
        toplam += HBN[i];
    }
    // toplam öðrenci sayýsýna bölünerek ortalama döndürülür
    return toplam / ((double) N);
}
double standart_sapma_hesapla(double ortalama, double HBN[], int N) {
    int i;
    double std;
    //standart sapma hesaplanýr.
    for (i = 0; i < N; ++i) {
        std += pow(HBN[i] - ortalama, 2);
    }
    return sqrt(std / N);
}
void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]) {
    int i;
    //T skorunun hesaplandýðý döngü. Soruda verilen formüle göre. 
    for (i = 0; i < N; i++) {
        T_skoru[i] = 60 + (10 * ((HBN[i] - ortalama) / std));
    }
}
void sinif_basari(double ortalama, double harf_notu[]) {
	/*
		Sýnýf ortalamasýna göre sýnýf düzeyi hesaplanýr. Burada alt sýnýrlar dikkate alýnmýþtýr.
		Verilen tablodaki ilgili harf notu aralýklarý(deðerlendirmenin yapýlacaðý) harf_notu dizisinde saklanmýþtýr.
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
        printf("Zayýf");
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
        printf("Ýyi");
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
    //deðerlendirme yapýlacak harf notlarý puanlarýnýn saklandýðý dizide, öðrenci t puanýnýn hangi aralýða geldiði i indisinde saklanýr ve ilgili harf notu döndürülür.
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
