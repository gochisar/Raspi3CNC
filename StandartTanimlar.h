#ifndef StandartTanimlar_h
#define StandartTanimlar_h

#include <iostream>
#include <stdint.h> //integer tip

using namespace std;

// ** ***  ****   *****    1    *****   ****  *** ** //
// Genel değişkenler

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float fl;
typedef double dbl;

// ** ***  ****   *****    2    *****   ****  *** ** //
// G Kod tanımlamaları

typedef enum karakter_grup{
	bosluk = 0,
	rakam,
	isaret,
	komut,
	konum,
	satir,
	aciklama,
	diger
}karakter_grup_t;

// ** ***  ****   *****    3    *****   ****  *** ** //
// ASCII

u8 karakterGrup[128] = {
	diger,		//0		NULL
	diger,		//1		SOH
	diger,		//2		STX
	diger,		//3		ETX
	diger,		//4 	EOT
	diger,		//5 	ENQ
	diger,		//6 	ACK
	diger,		//7		BEL
	diger,		//8		BS
	bosluk,		//9		HT tab
	satir,		//10	LF yeni satır
	bosluk,		//11	VT tab
	satir,		//12	FF yeni satır
	satir,		//13	CR yeni satır
	diger,		//14	SO
	diger,		//15	SI
	diger,		//16	DLE
	diger,		//17	DC1
	diger,		//18	DC2
	diger,		//19	DC3
	diger,		//20	DC4
	diger,		//21
	diger,		//22
	diger,		//23
	diger,		//24
	diger,		//25
	diger,		//26
	diger,		//27
	diger,		//28
	diger,		//29
	diger,		//30
	diger,		//31
	bosluk,		//32	boşluk
	aciklama,	//33	!
	diger,		//34	"
	diger,		//35	#
	diger,		//36	$
	aciklama,	//37	%
	diger,		//38	&
	diger,		//39	'
	aciklama,	//40	(
	diger,		//41	)
	diger,		//42	*
	isaret,		//43	+
	isaret,		//44	, virgül
	isaret,		//45	-
	isaret,		//46	.
	diger,		//47	/
	rakam,		//48	0
	rakam,		//49	1
	rakam,		//50	2
	rakam,		//51	3
	rakam,		//52	4
	rakam,		//53	5
	rakam,		//54	6
	rakam,		//55	7
	rakam,		//56	8
	rakam,		//57	9
	diger,		//58	:
	aciklama,	//59	;
	diger,		//60	<
	diger,		//61	=
	diger,		//62	>
	diger,		//63	?
	diger,		//64	@
	konum,		//65	A
	konum,		//66	B
	konum,		//67	C
	komut,		//68	D
	konum,		//69	E
	komut,		//70	F
	komut,		//71	G
	konum,		//72	H
	konum,		//73	I
	konum,		//74	J
	konum,		//75	K
	diger,		//76	L
	komut,		//77	M
	komut,		//78	N
	komut,		//79	O
	komut,		//80	P
	diger,		//81	Q
	konum,		//82	R
	komut,		//83	S
	komut,		//84	T
	konum,		//85	U
	konum,		//86	V
	konum,		//87	W
	konum,		//88	X
	konum,		//89	Y
	konum,		//90	Z
	diger,		//91	[
	diger,		//92	/ tersi
	diger,		//93	]
	diger,		//94	^
	diger,		//95	_
	diger,		//96	`
	konum,		//97	a
	konum,		//98	b
	konum,		//99	c
	komut,		//100	d
	konum,		//101	e
	komut,		//102	f
	komut,		//103	g
	konum,		//104	h
	konum,		//105	i
	konum,		//106	j
	konum,		//107	k
	diger,		//108	l
	komut,		//109	m
	komut,		//110	n
	komut,		//111	o
	komut,		//112	p
	diger,		//113	q
	konum,		//114	r
	komut,		//115	s
	komut,		//116	t
	konum,		//117	u
	konum,		//118	v
	konum,		//119	w
	konum,		//120	x
	konum,		//121	y
	konum,		//122	z
	diger,		//123	{
	diger,		//124	|
	diger,		//125	}
	diger,		//126	~
	diger		//127	DEL
};

#endif
