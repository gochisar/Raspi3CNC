#ifndef SISTEM_AYAR_H
#define SISTEM_AYAR_H
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
using namespace std;

//kod ayar dosyası
typedef uint8_t u8;
typedef uint16_t u16;
typedef float fl;

typedef struct {
	u8 step;
	u8 dir;
	u8 en;
	u8 acil;
	u8 step_ters;
	u8 dir_ters;
	u8 en_ters;
	u8 acil_ters;
	u8 home;
	u8 end;
	u8 home_ters;
	u8 end_ters;
} motor_pin_t;

typedef struct {
	motor_pin_t pinler;
	u8 eksen_tipi;		// 1  düz, 2 dönen
	u8 eksen;			// 0 x, 1 y, 2 z, 3 a, 4 b, 5 c
	fl step_her_mm;		// step/mm
	fl derece_step;		// dönen eksenler için her stepte kaç derece hareket edecek
	fl mm_her_tur;		// 1 tur dönüşte kaç mm yol alınıyor
	u16 step_her_tur;	// 1 tur dönüş için kaç step gerekiyor
	fl hizlanma;		// mm/s2
	fl home_hiz;		// home konumuna giderken hızlanması
	fl normal_hiz;		// normal hareket hız limiti
	fl kesme_hizi;		// kesimde hız limiti
}motor_t;

typedef struct{
	u8 motor_sayisi;		// kaç step motor kontrol edilecek
	u8 pin_acil_stop;		// acil
	u8 pin_durdur;			// dur
	u8 pin_baslat;			// başlat
	u8 pulse_us;			// sinyal aktif süresi
	motor_t motorlar[6];	// motorlar
} sistem_t;

sistem_t sys;



void sistem_on_tanimli(){
	sys.motor_sayisi = 3;
	sys.pin_acil_stop = 21;
	sys.pin_durdur = 20;
	sys.pin_baslat = 16;
	sys.pulse_us = 1;
	//x ekseni
	sys.motorlar[0].eksen_tipi = 1;
	sys.motorlar[0].eksen = 0;
	sys.motorlar[0].step_her_mm = 426.6667;
	sys.motorlar[0].derece_step = 0.225;
	sys.motorlar[0].mm_her_tur = 3.75;
	sys.motorlar[0].step_her_tur = 1600;
	sys.motorlar[0].hizlanma = 50.0;
	sys.motorlar[0].home_hiz = 100.0;
	sys.motorlar[0].normal_hiz = 2000.0;
	sys.motorlar[0].kesme_hizi = 900.0;
	sys.motorlar[0].pinler.step = 4;
	sys.motorlar[0].pinler.dir = 17;
	sys.motorlar[0].pinler.en = 0;
	sys.motorlar[0].pinler.acil = 0;
	sys.motorlar[0].pinler.home = 0;
	sys.motorlar[0].pinler.end = 0;
	sys.motorlar[0].pinler.step_ters = 0;
	sys.motorlar[0].pinler.dir_ters = 0;
	sys.motorlar[0].pinler.en_ters = 0;
	sys.motorlar[0].pinler.acil_ters = 0;
	sys.motorlar[0].pinler.home_ters = 0;
	sys.motorlar[0].pinler.end_ters = 0;
	//y ekseni
	sys.motorlar[1].eksen_tipi = 1;
	sys.motorlar[1].eksen = 1;
	sys.motorlar[1].step_her_mm = 426.6667;
	sys.motorlar[1].derece_step = 0.225;
	sys.motorlar[1].mm_her_tur = 3.75;
	sys.motorlar[1].step_her_tur = 1600;
	sys.motorlar[1].hizlanma = 50.0;
	sys.motorlar[1].home_hiz = 100.0;
	sys.motorlar[1].normal_hiz = 2000.0;
	sys.motorlar[1].kesme_hizi = 900.0;
	sys.motorlar[1].pinler.step = 18;
	sys.motorlar[1].pinler.dir = 23;
	sys.motorlar[1].pinler.en = 0;
	sys.motorlar[1].pinler.acil = 0;
	sys.motorlar[1].pinler.home = 0;
	sys.motorlar[1].pinler.end = 0;
	sys.motorlar[1].pinler.step_ters = 0;
	sys.motorlar[1].pinler.dir_ters = 0;
	sys.motorlar[1].pinler.en_ters = 0;
	sys.motorlar[1].pinler.acil_ters = 0;
	sys.motorlar[1].pinler.home_ters = 0;
	sys.motorlar[1].pinler.end_ters = 0;
	//z ekseni
	sys.motorlar[2].eksen_tipi = 1;
	sys.motorlar[2].eksen = 2;
	sys.motorlar[2].step_her_mm = 426.6667;
	sys.motorlar[2].derece_step = 0.225;
	sys.motorlar[2].mm_her_tur = 3.75;
	sys.motorlar[2].step_her_tur = 1600;
	sys.motorlar[2].hizlanma = 50.0;
	sys.motorlar[2].home_hiz = 100.0;
	sys.motorlar[2].normal_hiz = 2000.0;
	sys.motorlar[2].kesme_hizi = 900.0;
	sys.motorlar[2].pinler.step = 27;
	sys.motorlar[2].pinler.dir = 22;
	sys.motorlar[2].pinler.en = 0;
	sys.motorlar[2].pinler.acil = 0;
	sys.motorlar[2].pinler.home = 0;
	sys.motorlar[2].pinler.end = 0;
	sys.motorlar[2].pinler.step_ters = 0;
	sys.motorlar[2].pinler.dir_ters = 0;
	sys.motorlar[2].pinler.en_ters = 0;
	sys.motorlar[2].pinler.acil_ters = 0;
	sys.motorlar[2].pinler.home_ters = 0;
	sys.motorlar[2].pinler.end_ters = 0;
	//a ekseni
	sys.motorlar[3].eksen_tipi = 2;
	sys.motorlar[3].eksen = 3;
	sys.motorlar[3].step_her_mm = 426.6667;
	sys.motorlar[3].derece_step = 0.225;
	sys.motorlar[3].mm_her_tur = 3.75;
	sys.motorlar[3].step_her_tur = 1600;
	sys.motorlar[3].hizlanma = 50.0;
	sys.motorlar[3].home_hiz = 100.0;
	sys.motorlar[3].normal_hiz = 2000.0;
	sys.motorlar[3].kesme_hizi = 900.0;
	sys.motorlar[3].pinler.step = 24;
	sys.motorlar[3].pinler.dir = 25;
	sys.motorlar[3].pinler.en = 0;
	sys.motorlar[3].pinler.acil = 0;
	sys.motorlar[3].pinler.home = 0;
	sys.motorlar[3].pinler.end = 0;
	sys.motorlar[3].pinler.step_ters = 0;
	sys.motorlar[3].pinler.dir_ters = 0;
	sys.motorlar[3].pinler.en_ters = 0;
	sys.motorlar[3].pinler.acil_ters = 0;
	sys.motorlar[3].pinler.home_ters = 0;
	sys.motorlar[3].pinler.end_ters = 0;
	//b ekseni
	sys.motorlar[4].eksen_tipi = 2;
	sys.motorlar[4].eksen = 4;
	sys.motorlar[4].step_her_mm = 426.6667;
	sys.motorlar[4].derece_step = 0.225;
	sys.motorlar[4].mm_her_tur = 3.75;
	sys.motorlar[4].step_her_tur = 1600;
	sys.motorlar[4].hizlanma = 50.0;
	sys.motorlar[4].home_hiz = 100.0;
	sys.motorlar[4].normal_hiz = 2000.0;
	sys.motorlar[4].kesme_hizi = 900.0;
	sys.motorlar[4].pinler.step = 10;
	sys.motorlar[4].pinler.dir = 9;
	sys.motorlar[4].pinler.en = 0;
	sys.motorlar[4].pinler.acil = 0;
	sys.motorlar[4].pinler.home = 0;
	sys.motorlar[4].pinler.end = 0;
	sys.motorlar[4].pinler.step_ters = 0;
	sys.motorlar[4].pinler.dir_ters = 0;
	sys.motorlar[4].pinler.en_ters = 0;
	sys.motorlar[4].pinler.acil_ters = 0;
	sys.motorlar[4].pinler.home_ters = 0;
	sys.motorlar[4].pinler.end_ters = 0;
	//c ekseni
	sys.motorlar[0].eksen_tipi = 2;
	sys.motorlar[0].eksen = 5;
	sys.motorlar[0].step_her_mm = 426.6667;
	sys.motorlar[0].derece_step = 0.225;
	sys.motorlar[0].mm_her_tur = 3.75;
	sys.motorlar[0].step_her_tur = 1600;
	sys.motorlar[0].hizlanma = 50.0;
	sys.motorlar[0].home_hiz = 100.0;
	sys.motorlar[0].normal_hiz = 2000.0;
	sys.motorlar[0].kesme_hizi = 900.0;
	sys.motorlar[0].pinler.step = 11;
	sys.motorlar[0].pinler.dir = 8;
	sys.motorlar[0].pinler.en = 0;
	sys.motorlar[0].pinler.acil = 0;
	sys.motorlar[0].pinler.home = 0;
	sys.motorlar[0].pinler.end = 0;
	sys.motorlar[0].pinler.step_ters = 0;
	sys.motorlar[0].pinler.dir_ters = 0;
	sys.motorlar[0].pinler.en_ters = 0;
	sys.motorlar[0].pinler.acil_ters = 0;
	sys.motorlar[0].pinler.home_ters = 0;
	sys.motorlar[0].pinler.end_ters = 0;
}

streampos bas, son;

inline bool dosya_kontrol(const std::string& ad){
	struct stat buffer;
	return (stat (ad.c_str(), &buffer) == 0);
}

void dosya_boyutu(){
	ifstream dosya("ayar", ios::binary);
	bas = dosya.tellg();
	dosya.seekg(0,ios::end);
	son = dosya.tellg();
	dosya.close();
	cout << "dosya boyutu: " << (son-bas) << " byte.\n";
}

void ayarlari_yaz(){
	ofstream dosya("ayar", ios::out | ios::binary | ios::trunc);
	dosya.write((char *)(&sys), sizeof(sistem_t));
	dosya.close();
}

void ayarlari_oku(){
	if(!dosya_kontrol("ayar")){
		sistem_on_tanimli();
		ayarlari_yaz();
	}
	ifstream dosya("ayar", ios::in|ios::binary);
	dosya.seekg(0,ios::beg);
	dosya.read((char *)&sys, sizeof(sistem_t));
	dosya.close();
}

#endif
