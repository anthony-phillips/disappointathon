
#define u8 unsigned char

typedef struct {
	unsigned char r, g, b;
} RGB;
struct img
{
	unsigned int w, h;
	std::vector<u8> p;
};
typedef double matrix[9];


#define BAYER_SIZE 8
typedef double bayer[BAYER_SIZE][BAYER_SIZE];

void dither(img* a, bayer bi,RGB P[]);

#pragma region Bayer Matrices
#define cb(x) ((float)x/(BAYER_SIZE*BAYER_SIZE))
bayer BAYER =
{
#if BAYER_SIZE == 2
	cb(0),cb(2),
	cb(3),cb(1)
#endif
#if BAYER_SIZE == 3
	cb(0),cb(7),cb(3),
	cb(6),cb(5),cb(2),
	cb(4),cb(1),cb(8)
#endif
#if BAYER_SIZE == 8
		 cb(0),  cb(32), cb(8 ),cb(40),cb( 2),cb(34),cb(10),cb(42),		
		 cb(48), cb(16), cb(56),cb(24),cb(50),cb(18),cb(58),cb(26),	
		 cb(12), cb(44), cb(4 ),cb(36),cb(14),cb(46),cb( 6),cb(38),		
		 cb(60), cb(28), cb(52),cb(20),cb(62),cb(30),cb(54),cb(22	),
		  cb(3), cb(35), cb(11),cb(43),cb( 1),cb(33),cb( 9),cb(41),		
		 cb(51), cb(19), cb(59),cb(27),cb(49),cb(17),cb(57),cb(25),	
		 cb(15), cb(47), cb(7 ),cb(39),cb(13),cb(45),cb( 5),cb(37),		
		 cb(63), cb(31), cb(55),cb(23),cb(61),cb(29),cb(53),cb(21)
#endif
};



#pragma endregion


img gen();