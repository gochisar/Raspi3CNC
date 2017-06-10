#ifndef GKodOkuyucu_h
#define GKodOkuyucu_h

#include <iostream>
#include <stdlib.h>
#include <string> //std::string
#include <vector>
#include <sys/stat.h> //dosya var mı
#include <stdint.h> //integer tip
#include <fstream> //ifstream
#include "StandartTanimlar.h"

using namespace std;


//G-kod dosyasını okur ve zamanlama dosyası oluşturur
class dosya{
	public:
		dosya(std::string adi);
		~dosya(){
			satirlar.clear();
		};
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
		karakter_grup anlamli_mi(char chr);//karakter anlamlı bir değer mi
		
};

void dosya::parcala(){
	bool yeni_satir = true;//ilk karakterler yeni bir satırda gelir
	bool yeni_komut = false;
	bool yeni_rakam = false;
	int i = 0;
	string ystr = "";
	while(i<boyut){
		u8 grup = karakterGrup[(int)tampon[i]];
		switch(grup){
			case satir:
				if(!yeni_satir){
					yeni_satir = true;
					yeni_komut = false;
					yeni_rakam = false;
					satirlar.push_back(ystr);
				}
				ystr = "";
			break;
			case bosluk://boşlukları siliyoruz
			break;
			case aciklama://açıklama işaretinden sonrakileri yok say
			case diger://eğer açıklama satırı dışında anlamsız karakter varsa satırı yok sayıyoruz
				while((satir != karakterGrup[(int)tampon[i]]) && (i<boyut)){
					i++;
				}
				yeni_satir = true;
			break;
			case konum://bir konum yada komut karakteri ile başlayanları ele al
			case komut:
				yeni_satir = false;
				ystr += tampon[i];
				yeni_komut = true;
				yeni_rakam = false;
			break;
			case isaret:
			case rakam:
				if(yeni_komut){
					yeni_rakam = true;
					yeni_komut = false;
				}
				if(yeni_rakam){
					ystr += tampon[i];
				}
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
};

void dosya::hafiza_bosalt(){
	free(tampon);
	tampon = NULL;
}


#endif
