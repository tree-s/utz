#include "utz.h"

const urule_packed_t zone_rules[20] = {
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AN	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  8, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AN	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AS	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  8, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AS	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AT	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  1, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AT	2001	max	-	Oct	Sun>=1	2:00s	1:00	D
{  7, 255, 7,  8,  1,  2, 0, 2,  3, 1}, // 	Canada	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{  7, 255, 7,  1,  1,  1, 0, 1, 11, 0}, // 	Canada	2007	max	-	Nov	Sun>=1	2:00	0	S
{ 19, 255, 7,  2,  0,  3, 0, 0,  4, 0}, // 	Chile	2019	max	-	Apr	Sun>=2	3:00u	0	-
{ 23, 255, 7,  2,  0,  4, 0, 0,  9, 1}, // 	Chile	2023	max	-	Sep	Sun>=2	4:00u	1:00	-
{  0, 255, 7,  0,  0,  1, 0, 1,  3, 1}, // 	EU	1981	max	-	Mar	lastSun	 1:00u	1:00	S
{  0, 255, 7,  0,  0,  1, 0, 0, 10, 0}, // 	EU	1996	max	-	Oct	lastSun	 1:00u	0	-
{ 23, 255, 5,  0,  1,  0, 0, 1,  4, 1}, // 	Egypt	2023	max	-	Apr	lastFri	 0:00	1:00	S
{ 23, 255, 4,  0,  1, 23, 0, 0, 10, 0}, // 	Egypt	2023	max	-	Oct	lastThu	24:00	0	-
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	NZ	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  7, 255, 7,  0,  1,  2, 0, 2,  9, 1}, // 	NZ	2007	max	-	Sep	lastSun	2:00s	1:00	D
{  7, 255, 7,  8,  1,  2, 0, 2,  3, 1}, // 	US	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{  7, 255, 7,  1,  1,  1, 0, 1, 11, 0}, // 	US	2007	max	-	Nov	Sun>=1	2:00	0	S
{ 13, 255, 5, 23,  1,  2, 0, 2,  3, 1}, // 	Zion	2013	max	-	Mar	Fri>=23	2:00	1:00	D
{ 13, 255, 7,  0,  1,  1, 0, 1, 10, 0}, // 	Zion	2013	max	-	Oct	lastSun	2:00	0	S
};

const char zone_abrevs[162] = {
'E','E','%','c','T','\0',
'W','A','T','\0',
'C','A','T','\0',
'E','A','T','\0',
'A','K','%','c','T','\0',
'S','\0',
'C','%','c','T','\0',
'M','%','c','T','\0',
'A','%','c','T','\0',
'P','%','c','T','\0',
'%','c','\0',
'C','S','T','\0',
'E','%','c','T','\0',
'M','S','T','\0',
'N','%','c','T','\0',
'H','K','S','T','\0',
'I','%','c','T','\0',
'P','K','S','T','\0',
'I','S','T','\0',
'K','S','T','\0',
'J','S','T','\0',
'A','C','%','c','T','\0',
'A','E','S','T','\0',
'A','C','S','T','\0',
'A','E','%','c','T','\0',
'A','W','S','T','\0',
'U','T','C','\0',
'C','E','%','c','T','\0',
'G','M','T','/','B','S','T','\0',
'M','S','K','\0',
'N','Z','%','c','T','\0',
'C','h','S','T','\0',
'H','S','T','\0',
'S','S','T','\0',
};

const uzone_packed_t zone_defns[47] = {
// Africa/Cairo	2:00	Egypt	EE%sT
{  8,  12,   2,   0},
// Africa/Lagos	1:00	-	WAT
{  4,   0,   0,   6},
// Africa/Maputo	2:00	-	CAT
{  8,   0,   0,  10},
// Africa/Nairobi	3:00	-	EAT
{ 12,   0,   0,  14},
// America/Anchorage	-9:00	US	AK%sT
{-36,  16,   2,  18},
// America/Argentina/Buenos_Aires	-3:00	Arg	%z
// America/Sao_Paulo	-3:00	Brazil	%z
{-12,   0,   0,  24},
// America/Chicago	-6:00	US	C%sT
{-24,  16,   2,  26},
// America/Denver	-7:00	US	M%sT
{-28,  16,   2,  31},
// America/Halifax	-4:00	Canada	A%sT
{-16,   6,   2,  36},
// America/Los_Angeles	-8:00	US	P%sT
// America/Tijuana	-8:00	US	P%sT
{-32,  16,   2,  41},
// America/Manaus	-4:00	-	%z
{-16,   0,   0,  46},
// America/Mexico_City	-6:00	Mexico	C%sT
// America/Regina	-6:00	-	CST
{-24,   0,   0,  49},
// America/New_York	-5:00	US	E%sT
{-20,  16,   2,  53},
// America/Nuuk	-2:00	EU	%z
{ -8,  10,   2,  46},
// America/Phoenix	-7:00	-	MST
{-28,   0,   0,  58},
// America/Santiago	-4:00	Chile	%z
{-16,   8,   2,  46},
// America/St_Johns	-3:30	Canada	N%sT
{-10,   6,   2,  62},
// Asia/Bangkok	7:00	-	%z
{ 28,   0,   0,  46},
// Asia/Dubai	4:00	-	%z
{ 16,   0,   0,  46},
// Asia/Hong_Kong	8:00	HK	HK%sT
{ 32,   0,   0,  67},
// Asia/Jerusalem	2:00	Zion	I%sT
{  8,  18,   2,  72},
// Asia/Karachi	5:00	Pakistan	PK%sT
{ 20,   0,   0,  77},
// Asia/Kathmandu	5:45	-	%z
{ 23,   0,   0,  46},
// Asia/Kolkata	5:30	-	IST
{ 22,   0,   0,  82},
// Asia/Riyadh	3:00	-	%z
// Europe/Istanbul	3:00	-	%z
{ 12,   0,   0,  46},
// Asia/Seoul	9:00	ROK	K%sT
{ 36,   0,   0,  86},
// Asia/Shanghai	8:00	PRC	C%sT
// Asia/Taipei	8:00	Taiwan	C%sT
{ 32,   0,   0,  49},
// Asia/Singapore	8:00	-	%z
{ 32,   0,   0,  46},
// Asia/Tehran	3:30	Iran	%z
{ 14,   0,   0,  24},
// Asia/Tokyo	9:00	Japan	J%sT
{ 36,   0,   0,  90},
// Asia/Yangon	6:30	-	%z
{ 26,   0,   0,  46},
// Australia/Adelaide	9:30	AS	AC%sT
{ 38,   2,   2,  94},
// Australia/Brisbane	10:00	AQ	AE%sT
{ 40,   0,   0, 100},
// Australia/Darwin	9:30	Aus	AC%sT
{ 38,   0,   0, 105},
// Australia/Hobart	10:00	AT	AE%sT
{ 40,   4,   2, 110},
// Australia/Perth	8:00	AW	AW%sT
{ 32,   0,   0, 116},
// Australia/Sydney	10:00	AN	AE%sT
{ 40,   0,   2, 110},
// Etc/UTC	0	-	UTC
{  0,   0,   0, 121},
// Europe/Athens	2:00	EU	EE%sT
// Europe/Helsinki	2:00	EU	EE%sT
{  8,  10,   2,   0},
// Europe/Belgrade	1:00	EU	CE%sT
// Europe/Berlin	1:00	EU	CE%sT
// Europe/Brussels	1:00	EU	CE%sT
// Europe/Madrid	1:00	EU	CE%sT
// Europe/Rome	1:00	EU	CE%sT
{  4,  10,   2, 125},
// Europe/London	0:00	EU	GMT/BST
{  0,  10,   2, 131},
// Europe/Moscow	3:00	-	MSK
{ 12,   0,   0, 139},
// Pacific/Auckland	12:00	NZ	NZ%sT
{ 48,  14,   2, 143},
// Pacific/Guam	10:00	-	ChST
{ 40,   0,   0, 149},
// Pacific/Honolulu	-10:00	-	HST
{-40,   0,   0, 154},
// Pacific/Pago_Pago	-11:00	-	SST
{-44,   0,   0, 158},
// Pacific/Tarawa	12:00	-	%z
{ 48,   0,   0,  46},
};

const unsigned char zone_names[856] = {
    'C','a','i','r','o',' ','\0',0, // zone 0
    'B','r','a','z','z','a','\0',1, // zone 1
    'H','a','r','a','r','e','\0',2, // zone 2
    'N','a','i','r','o','b','\0',3, // zone 3
    'A','n','c','h','o','r','\0',4, // zone 4
    'S','a','o',' ','P','a','\0',5, // zone 5
    'B','u','e','n','o','s','\0',5, // zone 6
    'R','i','o',' ','d','e','\0',5, // zone 7
    'B','e','l','o',' ','H','\0',5, // zone 8
    'C','h','i','c','a','g','\0',6, // zone 9
    'D','a','l','l','a','s','\0',6, // zone 10
    'H','o','u','s','t','o','\0',6, // zone 11
    'D','e','n','v','e','r','\0',7, // zone 12
    'H','a','l','i','f','a','\0',8, // zone 13
    'L','o','s',' ','A','n','\0',9, // zone 14
    'T','i','j','u','a','n','\0',9, // zone 15
    'S','a','n',' ','F','r','\0',9, // zone 16
    'I','n','l','a','n','d','\0',9, // zone 17
    'M','a','n','a','u','s','\0',10, // zone 18
    'M','e','x','i','c','o','\0',11, // zone 19
    'R','e','g','i','n','a','\0',11, // zone 20
    'G','u','a','d','a','l','\0',11, // zone 21
    'N','e','w',' ','Y','o','\0',12, // zone 22
    'W','a','s','h','i','n','\0',12, // zone 23
    'P','h','i','l','a','d','\0',12, // zone 24
    'M','i','a','m','i',' ','\0',12, // zone 25
    'A','t','l','a','n','t','\0',12, // zone 26
    'B','o','s','t','o','n','\0',12, // zone 27
    'G','o','d','t','h','a','\0',13, // zone 28
    'P','h','o','e','n','i','\0',14, // zone 29
    'S','a','n','t','i','a','\0',15, // zone 30
    'S','t',' ','J','o','h','\0',16, // zone 31
    'B','a','n','g','k','o','\0',17, // zone 32
    'D','u','b','a','i',' ','\0',18, // zone 33
    'H','o','n','g',' ','K','\0',19, // zone 34
    'J','e','r','u','s','a','\0',20, // zone 35
    'K','a','r','a','c','h','\0',21, // zone 36
    'L','a','h','o','r','e','\0',21, // zone 37
    'K','a','t','m','a','n','\0',22, // zone 38
    'K','o','l','k','a','t','\0',23, // zone 39
    'C','a','l','c','u','t','\0',23, // zone 40
    'D','e','l','h','i',' ','\0',23, // zone 41
    'M','u','m','b','a','i','\0',23, // zone 42
    'B','a','n','g','a','l','\0',23, // zone 43
    'C','h','e','n','n','a','\0',23, // zone 44
    'H','y','d','e','r','a','\0',23, // zone 45
    'A','h','m','e','d','a','\0',23, // zone 46
    'P','u','n','e',' ',' ','\0',23, // zone 47
    'S','u','r','a','t',' ','\0',23, // zone 48
    'I','s','t','a','n','b','\0',24, // zone 49
    'K','u','w','a','i','t','\0',24, // zone 50
    'A','n','k','a','r','a','\0',24, // zone 51
    'S','e','o','u','l',' ','\0',25, // zone 52
    'S','h','a','n','g','h','\0',26, // zone 53
    'T','a','i','p','e','i','\0',26, // zone 54
    'C','h','o','n','g','q','\0',26, // zone 55
    'G','u','a','n','g','z','\0',26, // zone 56
    'B','e','i','j','i','n','\0',26, // zone 57
    'S','h','e','n','z','h','\0',26, // zone 58
    'W','u','h','a','n',' ','\0',26, // zone 59
    'C','h','e','n','g','d','\0',26, // zone 60
    'T','i','a','n','j','i','\0',26, // zone 61
    'H','a','n','g','z','h','\0',26, // zone 62
    'X','i',' ',',',',',',','\0',26, // zone 63
    'C','h','a','n','g','z','\0',26, // zone 64
    'N','a','n','j','i','n','\0',26, // zone 65
    'J','i','n','a','n',' ','\0',26, // zone 66
    'Z','h','e','n','g','z','\0',26, // zone 67
    'Q','i','n','g','d','a','\0',26, // zone 68
    'S','h','e','n','y','a','\0',26, // zone 69
    'W','e','n','z','h','o','\0',26, // zone 70
    'N','a','n','c','h','a','\0',26, // zone 71
    'K','u','a','l','a',' ','\0',27, // zone 72
    'T','e','h','r','a','n','\0',28, // zone 73
    'T','o','k','y','o',' ','\0',29, // zone 74
    'O','s','a','k','a',' ','\0',29, // zone 75
    'N','a','g','o','y','a','\0',29, // zone 76
    'R','a','n','g','o','o','\0',30, // zone 77
    'A','d','e','l','a','i','\0',31, // zone 78
    'B','r','i','s','b','a','\0',32, // zone 79
    'D','a','r','w','i','n','\0',33, // zone 80
    'H','o','b','a','r','t','\0',34, // zone 81
    'P','e','r','t','h',' ','\0',35, // zone 82
    'S','y','d','n','e','y','\0',36, // zone 83
    'U','T','C',' ',' ',' ','\0',37, // zone 84
    'A','t','h','e','n','s','\0',38, // zone 85
    'H','e','l','s','i','n','\0',38, // zone 86
    'B','e','l','g','r','a','\0',39, // zone 87
    'B','e','r','l','i','n','\0',39, // zone 88
    'B','r','u','s','s','e','\0',39, // zone 89
    'M','a','d','r','i','d','\0',39, // zone 90
    'R','o','m','e',' ',' ','\0',39, // zone 91
    'A','m','s','t','e','r','\0',39, // zone 92
    'S','a','r','a','j','e','\0',39, // zone 93
    'R','h','i','n','e','-','\0',39, // zone 94
    'B','a','r','c','e','l','\0',39, // zone 95
    'M','u','n','i','c','h','\0',39, // zone 96
    'S','t','u','t','t','g','\0',39, // zone 97
    'H','a','m','b','u','r','\0',39, // zone 98
    'M','i','l','a','n',' ','\0',39, // zone 99
    'L','o','n','d','o','n','\0',40, // zone 100
    'M','o','s','c','o','w','\0',41, // zone 101
    'A','u','c','k','l','a','\0',42, // zone 102
    'G','u','a','m',' ',' ','\0',43, // zone 103
    'H','o','n','o','l','u','\0',44, // zone 104
    'M','i','d','w','a','y','\0',45, // zone 105
    'M','a','j','u','r','o','\0',46, // zone 106
};
