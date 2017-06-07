#ifndef SISTEM_AYAR_H
#define SISTEM_AYAR_H
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include "GPIO_erisim.h"

using namespace std;

// 			3.3V	-	1	2	-	5V
//	no	GPIO2	I2C	-	3	4	-	5V
//	no	GPIO3	I2C	-	5	6	-	GND
//	Xs	GPIO4		-	7	8	-	TX	GPIO14
//			GND		-	9	10	-	RX	GPIO15
//	Xd	GPIO17		-	11	12	-		GPIO18	Ys
//	Zs	GPIO27		-	13	14	-	GND
//	Zd	GPIO22		-	15	16	-		GPIO23	Yd
//			3.3V	-	17	18	-		GPIO24	As
//	Bs	GPIO10		-	19	20	-	GND	
//	Bd	GPIO9		-	21	22	-		GPIO25	Ad
//	Cs	GPIO11		-	23	24	-		GPIO8	Cd
//			GND		-	25	26	-		GPIO7
//					-	27	28	-	
//	Xh	GPIO5		-	29	30	-	GND
//	Yh	GPIO6		-	31	32	-		GPIO12
//	Zh	GPIO13		-	33	34	-	GND
//		GPIO19		-	35	36	-		GPIO16	basla
//		GPIO26		-	37	38	-		GPIO20	dur
//			GND		-	39	40	-		GPIO21	acil

//GPIO 2-3-14-15 ileride kullanılmak üzere ayrıldı

//kod ayar dosyası
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float fl;
typedef double dbl;

#define max_eksen_sayisi 6

//Kullanıcı girişleri
//pinlerin tanımı
typedef struct pin{
	u8 pin;
	u8 ters;
	u8 bagli;
}pin_t;

typedef struct motor_pinler{
	pin_t step;
	pin_t dir;
	pin_t en;
	pin_t acil;
	pin_t home;
	pin_t end;
	u8 aktif_pulse;
} motor_pinler_t;

typedef struct hareket{
	u16 step_tur; 		// step her tur
	fl step_mm;			// step her mm
	fl ivme;			// mm / s^2
	fl home;			// mm/dk
	fl hiz;				// mm/dk
	fl kesim;			// mm/dk
}hareketlenme_t;

typedef struct eksen{
	u8 tip;		//0 yok, 1 düz, 2 dönen
	u8 eksen;	// 0 x, 1 y, 2 z, 3 a, 4 b, 5 c
}eksen_t;

typedef struct motor{
	motor_pinler_t 	pin;		//pin kontrolleri
	hareketlenme_t 	hiz;		//hız verileri
	eksen_t 			eksen;		//eksen ayarları
}motor_t;

typedef struct genel_pinler{
	pin_t acil;
	pin_t dur;
	pin_t baslat;
}genel_pinler_t;

typedef struct ayar{
	u8 					motor_sayisi;
	genel_pinler_t 	pin;
	u8 					home_sira[max_eksen_sayisi];
	motor_t 			motor[max_eksen_sayisi];	// motorlar
}ayar_t;

enum{
	x = 0, y, z, a, b, c
};

class ayar_dosyasi{
	public:
		ayar_dosyasi();
		void on_ayarlari_al();
		void kaydet();
		bool oku();
		std::string hata;
		void acil_pin(int pn, int ters){pin_ata(&(ayar.pin.acil),pn,ters);};
		void dur_pin(int pn, int ters){pin_ata(&(ayar.pin.dur),pn,ters);};
		void baslat_pin(int pn, int ters){pin_ata(&(ayar.pin.baslat),pn,ters);};
		void motor_step_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.step),pn,ters);};
		void motor_dir_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.dir),pn,ters);};
		void motor_en_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.en),pn,ters);};
		void motor_acil_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.acil),pn,ters);};
		void motor_home_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.home),pn,ters);};
		void motor_end_pin(int mot, int pn, int ters){pin_ata(&(ayar.motor[mot].pin.end),pn,ters);};
		void motor_aktif_pulse(int mot, int pls){ayar.motor[mot].pin.aktif_pulse = pls; degisti = true;};
		void motor_step_tur(int mot, int stp){ayar.motor[mot].hiz.step_tur = stp; degisti = true;};
		void motor_step_her_mm(int mot, fl stp){ayar.motor[mot].hiz.step_mm = stp; degisti = true;};
		void motor_ivme(int mot, fl ivm){ayar.motor[mot].hiz.ivme = ivm; degisti = true;};
		void motor_hiz_home(int mot, fl v){ayar.motor[mot].hiz.home = v; degisti = true;};
		void motor_hiz_normal(int mot, fl v){ayar.motor[mot].hiz.hiz = v; degisti = true;};
		void motor_hiz_kesim(int mot, fl v){ayar.motor[mot].hiz.kesim = v; degisti = true;};
		ayar_t ayarlar(){return ayar;};
	private:
		bool degisti;
		ayar_t ayar;
		//ön ayarlar
		void motor_genel_on_ayar(motor_t *n);
		void pin_genel_on_ayar(pin_t *pin);
		void hiz_genel_on_ayar(hareketlenme_t *h);
		void genel_on_ayar();
		//dosya erişim
		std::string dosya_ad;
		streampos bas, son;
		bool dosya_var_mi(const std::string& ad);
		u32 dosya_boyutu(const std::string& ad);
		//ayar değiştirme
		void pin_ata(pin_t *pin, int pn, int ters);
};

ayar_dosyasi::ayar_dosyasi(){
	degisti = false;
	dosya_ad = "ayar";
	hata = "";
	#ifdef debug
	printf("ayar dosyası başlat\n");
	#endif
}

bool ayar_dosyasi::oku(){
	if(dosya_var_mi(dosya_ad)){
		hata = "ayar dosyası yok";
		return false;
	}
	if(dosya_boyutu(dosya_ad) != 304){
		std::stringstream ss;
		ss << "ayar dosyası bozuk " << dosya_boyutu(dosya_ad);
		hata = ss.str();
		return false;
	}
	ifstream dosya(dosya_ad.c_str(), ios::in|ios::binary);
	dosya.seekg(0,ios::beg);
	dosya.read((char *)&ayar, sizeof(ayar_t));
	dosya.close();
	return true;
}

void ayar_dosyasi::kaydet(){
	if(!degisti){on_ayarlari_al();}
	ofstream dosya(dosya_ad.c_str(), ios::out | ios::binary | ios::trunc);
	dosya.write((char *)(&ayar), sizeof(ayar_t));
	dosya.close();
}

u32 ayar_dosyasi::dosya_boyutu(const std::string& ad){
	ifstream dosya(ad.c_str(), ios::binary);
	bas = dosya.tellg();
	dosya.seekg(0,ios::end);
	son = dosya.tellg();
	dosya.close();
	return (son-bas);
}

bool ayar_dosyasi::dosya_var_mi(const std::string& ad){
	struct stat buffer;
	return !(stat (ad.c_str(), &buffer) == 0);
}

void ayar_dosyasi::on_ayarlari_al(){
	genel_on_ayar();
}

void ayar_dosyasi::genel_on_ayar(){
	ayar.motor_sayisi = 3;
	//sistem pinleri
	pin_genel_on_ayar(&(ayar.pin.acil));
	ayar.pin.acil.pin = 21;
	ayar.pin.acil.bagli = 1;
	pin_genel_on_ayar(&(ayar.pin.dur));
	ayar.pin.dur.pin = 20;
	ayar.pin.dur.bagli = 1;
	pin_genel_on_ayar(&(ayar.pin.baslat));
	ayar.pin.baslat.pin = 16;
	ayar.pin.baslat.bagli = 1;
	ayar.home_sira[0] = z;
	ayar.home_sira[1] = x;
	ayar.home_sira[2] = y;
	ayar.home_sira[3] = a;
	ayar.home_sira[4] = b;
	ayar.home_sira[5] = c;
	//motor ayarları
	for(u8 i=0;i<max_eksen_sayisi;i++)
		motor_genel_on_ayar(&(ayar.motor[i]));
	ayar.motor[0].eksen.eksen = x;
	ayar.motor[0].eksen.tip = 1;
	ayar.motor[0].pin.step.pin = 4;
	ayar.motor[0].pin.step.bagli = 1;
	ayar.motor[0].pin.dir.pin = 17;
	ayar.motor[0].pin.dir.bagli = 1;
	ayar.motor[0].pin.home.pin = 5;
	ayar.motor[0].pin.home.bagli = 1;
	
	ayar.motor[1].eksen.eksen = y;
	ayar.motor[1].eksen.tip = 1;
	ayar.motor[1].pin.step.pin = 18;
	ayar.motor[1].pin.step.bagli = 1;
	ayar.motor[1].pin.dir.pin = 23;
	ayar.motor[1].pin.dir.bagli = 1;
	ayar.motor[1].pin.home.pin = 6;
	ayar.motor[1].pin.home.bagli = 1;
	
	ayar.motor[2].eksen.eksen = z;
	ayar.motor[2].eksen.tip = 1;
	ayar.motor[2].pin.step.pin = 27;
	ayar.motor[2].pin.step.bagli = 1;
	ayar.motor[2].pin.dir.pin = 22;
	ayar.motor[2].pin.dir.bagli = 1;
	ayar.motor[2].pin.home.pin = 13;
	ayar.motor[2].pin.home.bagli = 1;
	
	ayar.motor[3].eksen.eksen = a;
	ayar.motor[3].eksen.tip = 0;
	ayar.motor[4].eksen.eksen = b;
	ayar.motor[4].eksen.tip = 0;
	ayar.motor[5].eksen.eksen = c;
	ayar.motor[5].eksen.tip = 0;
	
}

void ayar_dosyasi::hiz_genel_on_ayar(hareketlenme_t *h){
	(*h).step_tur = 1600;
	(*h).step_mm = 426.666666;
	(*h).ivme = 50.0;
	(*h).home = 100.0;
	(*h).hiz = 500.0;
	(*h).kesim = 200.0;
}

void ayar_dosyasi::pin_genel_on_ayar(pin_t *pin){
	(*pin).pin = 0;
	(*pin).ters = 0;
	(*pin).bagli = 0;
}

void ayar_dosyasi::motor_genel_on_ayar(motor_t *n){
	(*n).eksen.tip = 1;
	pin_genel_on_ayar(&((*n).pin.step));
	pin_genel_on_ayar(&((*n).pin.dir));
	pin_genel_on_ayar(&((*n).pin.en));
	pin_genel_on_ayar(&((*n).pin.acil));
	pin_genel_on_ayar(&((*n).pin.home));
	pin_genel_on_ayar(&((*n).pin.end));
	hiz_genel_on_ayar(&((*n).hiz));
	
}

void ayar_dosyasi::pin_ata(pin_t *pin, int pn, int ters){
	if(pn == 0){
		(*pin).pin = 0;
		(*pin).ters = 0;
		(*pin).bagli = 0;
	}else{
		(*pin).pin = pn;
		(*pin).ters = ters;
		(*pin).bagli = 1;
	}
	degisti = true;
}

//elektronik dilinde ayarlar

typedef struct pin_s{
	u8 pin;
	bool aktif;		//aktif 1 mi 0 mı
}pin_st;

typedef struct motor_pin_s{
	pin_st step;	//step pulse pin
	pin_st dir;	//dir pulse pin
	pin_st en;		//aktif pulse pin
}motor_pin_st;

typedef struct motor_takip_pin_s{
	pin_st acil;
	pin_st home;
	pin_st end;
}motor_takip_pin_st;

typedef struct hareket_s{
	fl derece_step;		//step başına kaç derece döner
	fl mm_step;			//step başına kaç mm ilerler
	fl ivme;			//step/s^2
	fl home;			//step/s
	fl hiz;				//step/s
	fl kesim;			//step/s
}hareket_st;

typedef struct motor_s{
	u8 tip;
	motor_pin_st kontrol;
	motor_takip_pin_st takip;
	hareket_st hareket;
}motor_st;

class sys{
	public:
		void sys_baslat(ayar_t ayr);
	private:
		u8 motor_sayisi;
		pin_st acil, dur, baslat;
		motor_st motor[max_eksen_sayisi];
		
		void giris_pini(pin_st *pin, pin_t *ayp);
		void cikis_pin(pin_st *pin, pin_t *ayp);
};

void sys::sys_baslat(ayar_t ayr){
	setup_io();
	motor_sayisi = ayr.motor_sayisi;
	giris_pini(&(acil), &(ayr.pin.acil));
	giris_pini(&(dur), &(ayr.pin.dur));
	giris_pini(&(baslat), &(ayr.pin.baslat));
	//eksenleri sıralı bul
	int si=0;
	while(si<max_eksen_sayisi){
		#ifdef debug
		printf("%d motor ayarı için arama başlatılıyor \n", si);
		#endif
	for(int i=0;i<max_eksen_sayisi;i++){
		if(ayr.motor[i].eksen.eksen == si){
			motor[si].tip = ayr.motor[i].eksen.tip;
			//pin ayarları
			cikis_pin(&(motor[si].kontrol.step),&(ayr.motor[i].pin.step));
			cikis_pin(&(motor[si].kontrol.dir),&(ayr.motor[i].pin.dir));
			cikis_pin(&(motor[si].kontrol.en),&(ayr.motor[i].pin.en));
			giris_pini(&(motor[si].takip.acil),&(ayr.motor[i].pin.acil));
			giris_pini(&(motor[si].takip.home),&(ayr.motor[i].pin.home));
			giris_pini(&(motor[si].takip.end),&(ayr.motor[i].pin.end));
			//hareket ayarları
			motor[si].hareket.derece_step =(ayr.motor[i].hiz.step_tur == 0.0 ? 0 :  360.0 / ayr.motor[i].hiz.step_tur);
			motor[si].hareket.mm_step = (ayr.motor[i].hiz.step_mm == 0.0 ? 0 : 1.0 / ayr.motor[i].hiz.step_mm);
			motor[si].hareket.ivme = ayr.motor[i].hiz.ivme * ayr.motor[i].hiz.step_mm;
			motor[si].hareket.home = ayr.motor[i].hiz.home * ayr.motor[i].hiz.step_mm;
			motor[si].hareket.hiz = ayr.motor[i].hiz.hiz * ayr.motor[i].hiz.step_mm;
			motor[si].hareket.kesim = ayr.motor[i].hiz.kesim * ayr.motor[i].hiz.step_mm;
			#ifdef debug
			printf("%d ayarından sisteme aktarım yapıldı\n",i);
			#endif
		}
	}
	si++;
	}
	
}

void sys::cikis_pin(pin_st *pn, pin_t *ayp){
	if((*ayp).bagli > 0){
		(*pn).pin = (*ayp).pin;
		(*pn).aktif = ((*ayp).ters == 0);
		pin_cikis((*pn).pin);
	}
}

void sys::giris_pini(pin_st *pn, pin_t *ayp){
	if((*ayp).bagli > 0){
		(*pn).pin = (*ayp).pin;
		(*pn).aktif = ((*ayp).ters == 0);
		pin_giris((*pn).pin);
	}
}

#endif
