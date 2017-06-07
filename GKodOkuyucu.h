#ifndef GKodOkuyucu_h
#define GKodOkuyucu_h

#include <iostream>
#include <stdlib.h>
#include <string> //std::string
#include <vector>
#include <sys/stat.h> //dosya var mı
#include <stdint.h> //integer tip
#include <fstream> //ifstream

using namespace std;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float fl;
typedef double dbl;


typedef struct line{
	u32 no;
	line *onceki;
	line *sonraki;
	char *satir;
}line_t;

typedef enum karakter_grup{
	bosluk = 0,
	rakam,
	isaret,
	komut,
	konum,
	satir,
	degil
}karakter_grup;

typedef struct karakter{
	char karakter;
	karakter_grup grup;
}karakter_t;



//G-kod dosyasını okur ve zamanlama dosyası oluşturur
class dosya{
	public:
		dosya(std::string adi);
		int boyut;
		char *tampon;
		void yukle();
		void hafiza_bosalt();
		void yeni(std::string adi);
		void parcala();
		std::vector <string> satirlar; //g kod satırları, elenmiş
	private:
		FILE *dsy;//dosya tutucu
		bool var;
		bool hata;
		std::string ad;//dosya adı
		karakter_t anlamli[64];//g kod için anlamlı karakterler listesi
		karakter_grup anlamli_mi(char chr);//karakter anlamlı bir değer mi
		
};

karakter_grup dosya::anlamli_mi(char chr){
	for(int i=0;i<64;i++){
		if(chr == anlamli[i].karakter){
			return anlamli[i].grup;
		}
	}
	return degil;
};

void dosya::parcala(){
	bool anlamli_satir = false;
	bool yeni_satir = true;
	std::string ystr = "";
	bool hatali = false;
	
	int i = 0;
	while(i<boyut){
		u8 grup = anlamli_mi(tampon[i]);
		switch(grup){
			case bosluk://bizi ilgilendirmiyor
			break;
			case degil:
				hatali = true;
			break;
			case rakam:
				yeni_satir = false;
				if(anlamli_satir){ystr += tampon[i];}//bir sayır rakamla başlayamaz
			break;
			case isaret:
				yeni_satir = false;
				if(anlamli_satir){ystr += tampon[i];}//bir satır işaretle başlayamaz
			break;
			case komut:
				anlamli_satir = true;
				yeni_satir = false;
				ystr +=tampon[i];
			break;
			case konum:
				anlamli_satir = true;
				yeni_satir = false;
				ystr +=tampon[i];
			break;
			case satir:
				yeni_satir = true; //yeni bir satıra başlandı, depolanan veri varsa gönder
				if(anlamli_satir && !hatali){
					//ekleme işlemleri
					satirlar.push_back(ystr);
				}
				ystr= "";
				hatali = false;
				anlamli_satir = false;
			break;
			
		}
		i++;
	}
	
}

void dosya::yeni(std::string adi){
	ad = adi;
	dsy = (fopen(ad.c_str(), "r"));
	if(dsy){
		var = true;
		fseek(dsy, 0, SEEK_END);//dosya sonuna git
		boyut = ftell(dsy);//dosya konumunu oku
		rewind(dsy);//başa git
		hata = false;
		var = true;
		
	}else{var = false; hata = true;}
}

void dosya::yukle(){
	if(!hata){
		int okunan;
		tampon = (char *) malloc(sizeof(char)*(boyut+1));
		okunan = fread(tampon, sizeof(char), boyut, dsy);
		tampon[boyut] = '\0';
		if(boyut != okunan){
			hata = true;
			hafiza_bosalt();
		}
		fclose(dsy);
	}
}

dosya::dosya(std::string adi){
	yeni(adi);
	anlamli[0].karakter = 32;
	anlamli[1].grup = bosluk;
	anlamli[1].karakter = 48;//0
	anlamli[2].karakter = 49;//1
	anlamli[3].karakter = 50;//2
	anlamli[4].karakter = 51;//3
	anlamli[5].karakter = 52;//4
	anlamli[6].karakter = 53;//5
	anlamli[7].karakter = 54;//6
	anlamli[8].karakter = 55;//7
	anlamli[9].karakter = 56;//8
	anlamli[10].karakter = 57;//9
	for(int i=1;i<11;i++)anlamli[i].grup = rakam;
	anlamli[11].karakter = 45;//-
	anlamli[12].karakter = 43;//+
	anlamli[13].karakter = 46;//.
	for(int i=11;i<14;i++)anlamli[i].grup = isaret;
	anlamli[14].karakter = 68;//D
	anlamli[15].karakter = 100;//d
	anlamli[16].karakter = 71;//G
	anlamli[17].karakter = 103;//g
	anlamli[18].karakter = 72;//H
	anlamli[19].karakter = 104;//h
	anlamli[20].karakter = 77;//M
	anlamli[21].karakter = 109;//m
	anlamli[22].karakter = 78;//N
	anlamli[23].karakter = 110;//n
	anlamli[24].karakter = 79;//O
	anlamli[25].karakter = 111;//o
	anlamli[26].karakter = 80;//P
	anlamli[27].karakter = 112;//p
	anlamli[28].karakter = 81;//Q
	anlamli[29].karakter = 113;//q
	anlamli[30].karakter = 83;//S
	anlamli[31].karakter = 115;//s
	anlamli[32].karakter = 84;//T
	anlamli[33].karakter = 116;//t
	for(int i=14;i<34;i++)anlamli[i].grup = komut;
	anlamli[34].karakter = 65;//A
	anlamli[35].karakter = 97;//a
	anlamli[36].karakter = 66;//B
	anlamli[37].karakter = 98;//b
	anlamli[38].karakter = 67;//C
	anlamli[39].karakter = 99;//c
	anlamli[40].karakter = 70;//F
	anlamli[41].karakter = 102;//f
	anlamli[42].karakter = 73;//I
	anlamli[43].karakter = 105;//i
	anlamli[44].karakter = 74;//J
	anlamli[45].karakter = 106;//j
	anlamli[46].karakter = 75;//K
	anlamli[47].karakter = 107;//k
	anlamli[48].karakter = 82;//R
	anlamli[49].karakter = 114;//r
	anlamli[50].karakter = 85;//U
	anlamli[51].karakter = 117;//u
	anlamli[52].karakter = 86;//V
	anlamli[53].karakter = 118;//v
	anlamli[54].karakter = 87;//W
	anlamli[55].karakter = 119;//w
	anlamli[56].karakter = 88;//X
	anlamli[57].karakter = 120;//x
	anlamli[58].karakter = 89;//Y
	anlamli[59].karakter = 121;//y
	anlamli[60].karakter = 90;//Z
	anlamli[61].karakter = 122;//z
	for(int i=34;i<62;i++)anlamli[i].grup = konum;
	anlamli[62].karakter = 10;//satır başı
	anlamli[63].karakter = 13;//satır başı
	for(int i=62;i<64;i++)anlamli[i].grup = satir;
};

void dosya::hafiza_bosalt(){
	free(tampon);
	tampon = NULL;
}


#endif
