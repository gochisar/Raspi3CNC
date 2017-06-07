/* Raspberry pi 3 CNC kontrol yazılımı
 * 
 */

#define debug
#include <iostream>

#include "sistem_ayar.h" 	//sistem ayarları kayıt, okuma
#include "GKodOkuyucu.h"	//G kodu dosyasını okur, hareketleri hazırlar.

/*
#include "GPIO_erisim.h" 	//pin giriş çıkış fonksiyonları
#include "zaman.h"			//1MHz timer erişimi
#include "basa_git.h"		//home konumuna gitme işlemi

#include "hareket.h"		//Hareket sistemini kontrol eder.
*/


int main(int argc, char **argv)
{
	#ifdef debug
	printf("tanımlamalar yapılıyor\n");
	#endif
	
	ayar_dosyasi ay;
	
	if(!ay.oku()){
		#ifdef debug
		printf("ayar dosyası bulunamadı \nyeni ayar dosyası oluşturuluyor \n");
		#endif
		ay.on_ayarlari_al();
		ay.kaydet();
	}
	#ifdef debug
	printf("ayar dosyası alındı\n");
	#endif
	
	sys sistem;
	
	#ifdef debug
	printf("sistem değişkeni tanımlandı\n");
	#endif
	
	sistem.sys_baslat(ay.ayarlar());
	
	#ifdef debug
	printf("sistem değişkenine ayarlar aktarıldı\n");
	#endif
	
	dosya gkod("GKod.tab");
	gkod.yukle();
	#ifdef debug
	printf("GKod dosyası yüklendi \n");
	#endif
	
	gkod.parcala();
	#ifdef debug
	printf("GKod dosyası temizlendi. Satır sayısı %d\n", gkod.satirlar.size());
	
	for(int i=0;i<100;i++){
		printf("%d, %s\n", i, gkod.satirlar[i].c_str());
	}
	#endif
	
	return 0;
}

