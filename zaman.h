
#ifndef ZAMAN_H
#define ZAMAN_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

#define nop10 asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;")
#define nop20 nop10; nop10;
#define nop50 nop20; nop20; nop10;
#define nop100 nop50; nop50;
#define nop200 nop100; nop100;
#define nop500 nop200; nop200; nop100;

#define us_ nop500; nop50;// 1us için işlevsel.

#define ST_BASE (0x3F003000)
#define TIMER_OFFSET (4)
 
 class tmr {
	 long long int t, prev, *timer, frk;
	 int fd;
	 void *st_base;
	 bool hazir;
	public:
	 tmr();
	 long long int fark();
 };
 
 tmr::tmr(){
	if(!(-1 == (fd = open("/dev/mem", 
			O_RDONLY))) && !(MAP_FAILED == (st_base = mmap(NULL, 4096, 
			PROT_READ, MAP_SHARED, fd, ST_BASE)))){
		this->hazir = true;
		timer = (long long int *)((char *)st_base + TIMER_OFFSET);
		prev = *timer;
	}else{
		this->hazir = false;
	}
 }
 
 long long int tmr::fark(){
	t = *timer;
	frk = t - prev;
	prev = t;
	return frk;
 }

//referans için
 void bekleme(int a){
	 for(int i=0; i<a;i++){
		 asm("nop");
	 }
 }
 
 //60 	1us
 //135 	2us
 //208	3us
 //277	4us
 //360	5us
 //435	6us
 //510	7us
 //585	8us
 //660	9us
 //735	10us
 //810	11us
 //880	12us
 //960	13us
 //1030	14us
 //1105	15us
 //1185	16us
 //1260	17us
 
#endif
