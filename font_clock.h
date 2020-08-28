// Data file for numeric scoreboard fonts
#pragma once

MD_MAX72XX::fontType_t NumFontLower[] PROGMEM = 
{
  'F', 1, 32, 68, 8,
  3,0x00,0x00,0x00, 		// 32 - 'Space'
  3,0x0c,0x0c,0x00,		// 33 - '! celsius'
  0,				// 34 - '""'
  0,				// 35 - '#'
  0, 				// 36 - '$'
  3,0x24,0x90,0x00,		// 37 - '%'
  0,				// 38 - '&'
  0, 				// 39 - '''
  0,				// 40 - '('
  0,				// 41 - ')'
  0,				// 42 - '*'
  0,				// 43 - '+'
  0,				// 44 - ','
  0,				// 45 - '-'
  3,0x00,0x80,0x00,		// 46 - '.'
  3,0x80,0x40,0x20,		// 47 - '/'
  3,0xfc,0x84,0xfc,		// 48 - '0'
  3,0x88,0xfc,0x80,		// 49 - '1'
  3,0xf4,0x94,0x9c,		// 50 - '2'
  3,0x84,0x94,0xfc,		// 51 - '3'
  3,0x3c,0x20,0xfc,		// 52 - '4'
  3,0x9c,0x94,0xf4,		// 53 - '5'
  3,0xfc,0x94,0xf4,		// 54 - '6'
  3,0x04,0xe4,0x1c,		// 55 - '7'
  3,0xfc,0x94,0xfc,		// 56 - '8'
  3,0xbc,0xa4,0xfc,		// 57 - '9'
  3,0x00,0x24,0x00,		// 58 - ':'
  0,				// 59 - ''
  0,				// 60 - ''
  7,0xfc,0x04,0xfc,0x00,0xfc,0x10,0xfc,	// 61 - '��'
  7,0xfc,0x94,0xec,0x00,0x04,0xfc,0x04,	// 62 - '��'
  7,0xfc,0x84,0x84,0x00,0xfc,0x24,0x3c,	// 63 - '��'
  7,0x3c,0x20,0xfc,0x00,0x04,0xfc,0x04,	// 64 - '��'
  7,0xfc,0x04,0xfc,0x00,0x04,0xfc,0x04,	// 65 - '��'
  7,0xfc,0x84,0x84,0x00,0xfc,0x94,0xf4,	// 66 - '��'
  7,0xfc,0x94,0xec,0x00,0xfc,0x84,0x84,	// 67 - '��'
  7,0xf8,0x7c,0xec,0x7c,0xec,0x7c,0xf8,	// 68 - 'ghost'
};

MD_MAX72XX::fontType_t NumFontUpperBold[] PROGMEM = 
{
  'F', 1, 32, 58, 8,
  3, 0, 0, 0,	 		// 32 - 'Space'
  0,				// 33 - '!'
  0,				// 34 - '""'
  0,				// 35 - '#'
  0, 				// 36 - '$'
  0,				// 37 - '%'
  0,				// 38 - '&'
  0, 				// 39 - '''
  0,				// 40 - '('
  0,				// 41 - ')'
  0,				// 42 - '*'
  0,				// 43 - '+'
  0,				// 44 - ','
  0,				// 45 - '-'
  1,0x40, 	 		// 46 - '.'
  0,				// 47 - '/'
  5,0x7e,0xff,0x81,0xff,0x7e,	// 48 - '0'
  5,0x00,0x04,0xfe,0xff,0x00,	// 49 - '1'
  5,0xc6,0xe7,0xb1,0x9f,0x8e,	// 50 - '2'
  5,0x42,0xcb,0x89,0xff,0x76,	// 51 - '3'
  5,0x38,0x2c,0x26,0xff,0xff,	// 52 - '4'
  5,0x4f,0xcf,0x85,0xfd,0x79,	// 53 - '5'
  5,0x7e,0xff,0x89,0xfb,0x72,	// 54 - '6'
  5,0x01,0xe1,0xf9,0x1f,0x07,	// 55 - '7'
  5,0x76,0xff,0x89,0xff,0x76,	// 56 - '8'
  5,0x4e,0xdf,0x91,0xff,0x7e,	// 57 - '9'
  3,0,0x24,0,			// 58 - ':'
};

MD_MAX72XX::fontType_t NumFontUpperThin[] PROGMEM = 
{
  'F', 1, 32, 58, 8,
  3, 0, 0, 0,	 		// 32 - 'Space'
  0,				// 33 - '!'
  0,				// 34 - '""'
  0,				// 35 - '#'
  0, 				// 36 - '$'
  0,				// 37 - '%'
  0,				// 38 - '&'
  0, 				// 39 - '''
  0,				// 40 - '('
  0,				// 41 - ')'
  0,				// 42 - '*'
  0,				// 43 - '+'
  0,				// 44 - ','
  0,				// 45 - '-'
  1,0x40, 	 		// 46 - '.'
  0,				// 47 - '/'
  5,0x7e,0x81,0x81,0x81,0x7e,	// 48 - '0'
  5,0x00,0x82,0xff,0x80,0x00,	// 49 - '1'
  5,0xc2,0xa1,0x91,0x89,0x86,	// 50 - '2'
  5,0x42,0x81,0x89,0x89,0x76,	// 51 - '3'
  5,0x30,0x28,0x24,0x22,0xff,	// 52 - '4'
  5,0x4f,0x89,0x89,0x89,0x71,	// 53 - '5'
  5,0x7e,0x89,0x89,0x89,0x72,	// 54 - '6'
  5,0x01,0xe1,0x11,0x09,0x07,	// 55 - '7'
  5,0x76,0x89,0x89,0x89,0x76,	// 56 - '8'
  5,0x4e,0x91,0x91,0x91,0x7e,	// 57 - '9'
  3,0,0x24,0,			// 58 - ':'
};


MD_MAX72XX::fontType_t NumFontUpper[] PROGMEM = 
{
  'F', 1, 32, 122, 8,
  3, 0, 0, 0,	 		// 32 - 'Space'
  0,				// 33 - '!'
  0,				// 34 - '""'
  0,				// 35 - '#'
  0, 				// 36 - '$'
  0,				// 37 - '%'
  0,				// 38 - '&'
  0, 				// 39 - '''
  0,				// 40 - '('
  0,				// 41 - ')'
  0,				// 42 - '*'
  0,				// 43 - '+'
  0,				// 44 - ','
  0,				// 45 - '-'
  1,0x40, 	 		// 46 - '.'
  0,				// 47 - '/'
  5,0x7e,0x81,0x81,0x81,0x7e,	// 48 - '0'
  5,0x00,0x82,0xff,0x80,0x00,	// 49 - '1'
  5,0x70,0x89,0x89,0x89,0x06,	// 50 - '2'
  5,0x81,0x89,0x89,0x89,0x76,	// 51 - '3'
  5,0x0e,0x10,0x10,0x10,0xef,	// 52 - '4'
  5,0x8f,0x89,0x89,0x89,0x71,	// 53 - '5'
  5,0x76,0x89,0x89,0x89,0x70,	// 54 - '6'
  5,0x01,0x01,0xf1,0x09,0x07,	// 55 - '7'
  5,0x76,0x89,0x89,0x89,0x76,	// 56 - '8'
  5,0x0e,0x91,0x91,0x91,0x6e,	// 57 - '9'
  3,0,0x24,0,			// 58 - ':'
  2, 0x80, 0x68,  		// 59 - ';'
  4, 0x08, 0x14, 0x22, 0x41,  	// 60 - '<'
  5, 0x14, 0x14, 0x14, 0x14, 0x14,  	// 61 - '='
  4, 0x41, 0x22, 0x14, 0x08,  		// 62 - '>'
  5, 0x02, 0x01, 0x59, 0x09, 0x06,  	// 63 - '?'
  5, 0x3e, 0x41, 0x5d, 0x59, 0x4e,  	// 64 - '@'
  5, 0x7c, 0x12, 0x11, 0x12, 0x7c,  	// 65 - 'A'
  5, 0x7f, 0x49, 0x49, 0x49, 0x36,  	// 66 - 'B'
  5, 0x3e, 0x41, 0x41, 0x41, 0x22,  	// 67 - 'C'
  5, 0x7f, 0x41, 0x41, 0x41, 0x3e,  	// 68 - 'D'
  5, 0x7f, 0x49, 0x49, 0x49, 0x41,  	// 69 - 'E'
  5, 0x7f, 0x09, 0x09, 0x09, 0x01,  	// 70 - 'F'
  5, 0x3e, 0x41, 0x41, 0x51, 0x73,  	// 71 - 'G'
  5, 0x7f, 0x08, 0x08, 0x08, 0x7f,  	// 72 - 'H'
  3, 0x41, 0x7f, 0x41,  		// 73 - 'I'
  5, 0x20, 0x40, 0x41, 0x3f, 0x01,  	// 74 - 'J'
  5, 0x7f, 0x08, 0x14, 0x22, 0x41,  	// 75 - 'K'
  5, 0x7f, 0x40, 0x40, 0x40, 0x40,  	// 76 - 'L'
  5, 0x7f, 0x02, 0x1c, 0x02, 0x7f,  	// 77 - 'M'
  5, 0x7f, 0x04, 0x08, 0x10, 0x7f,  	// 78 - 'N'
  5, 0x3e, 0x41, 0x41, 0x41, 0x3e,  	// 79 - 'O'
  5, 0x7f, 0x09, 0x09, 0x09, 0x06,  	// 80 - 'P'
  5, 0x3e, 0x41, 0x51, 0x21, 0x5e,  	// 81 - 'Q'
  5, 0x7f, 0x09, 0x19, 0x29, 0x46,  	// 82 - 'R'
  5, 0x26, 0x49, 0x49, 0x49, 0x32,  	// 83 - 'S'
  5, 0x03, 0x01, 0x7f, 0x01, 0x03,  	// 84 - 'T'
  5, 0x3f, 0x40, 0x40, 0x40, 0x3f,  	// 85 - 'U'
  5, 0x1f, 0x20, 0x40, 0x20, 0x1f,  	// 86 - 'V'
  5, 0x3f, 0x40, 0x38, 0x40, 0x3f,  	// 87 - 'W'
  5, 0x63, 0x14, 0x08, 0x14, 0x63,  	// 88 - 'X'
  5, 0x03, 0x04, 0x78, 0x04, 0x03,  	// 89 - 'Y'
  5, 0x61, 0x59, 0x49, 0x4d, 0x43,  	// 90 - 'Z'
  3, 0x7f, 0x41, 0x41,  		// 91 - '['
  5, 0x02, 0x04, 0x08, 0x10, 0x20,  	// 92 - '\'
  3, 0x41, 0x41, 0x7f,  		// 93 - ']'
  5, 0x04, 0x02, 0x01, 0x02, 0x04,  	// 94 - '^'
  5, 0x40, 0x40, 0x40, 0x40, 0x40,  	// 95 - '_'
  3, 0x03, 0x07, 0x08,  		// 96 - '`'
  5, 0x20, 0x54, 0x54, 0x78, 0x40,  	// 97 - 'a'
  5, 0x7f, 0x28, 0x44, 0x44, 0x38,  	// 98 - 'b'
  5, 0x38, 0x44, 0x44, 0x44, 0x28,  	// 99 - 'c'
  5, 0x38, 0x44, 0x44, 0x28, 0x7f,  	// 100 - 'd'
  5, 0x38, 0x54, 0x54, 0x54, 0x18,  	// 101 - 'e'
  4, 0x08, 0x7e, 0x09, 0x02,  		// 102 - 'f'
  5, 0x18, 0xa4, 0xa4, 0x9c, 0x78,  	// 103 - 'g'
  5, 0x7f, 0x08, 0x04, 0x04, 0x78,  	// 104 - 'h'
  3, 0x44, 0x7d, 0x40,  		// 105 - 'i'
  4, 0x40, 0x80, 0x80, 0x7a,  		// 106 - 'j'
  4, 0x7f, 0x10, 0x28, 0x44,  		// 107 - 'k'
  3, 0x41, 0x7f, 0x40,  		// 108 - 'l'
  5, 0x7c, 0x04, 0x78, 0x04, 0x78,  	// 109 - 'm'
  5, 0x7c, 0x08, 0x04, 0x04, 0x78,  	// 110 - 'n'
  5, 0x38, 0x44, 0x44, 0x44, 0x38,  	// 111 - 'o'
  5, 0xfc, 0x18, 0x24, 0x24, 0x18,  	// 112 - 'p'
  5, 0x18, 0x24, 0x24, 0x18, 0xfc,  	// 113 - 'q'
  5, 0x7c, 0x08, 0x04, 0x04, 0x08,  	// 114 - 'r'
  5, 0x48, 0x54, 0x54, 0x54, 0x24,  	// 115 - 's'
  4, 0x04, 0x3f, 0x44, 0x24,  		// 116 - 't'
  5, 0x3c, 0x40, 0x40, 0x20, 0x7c,  	// 117 - 'u'
  5, 0x1c, 0x20, 0x40, 0x20, 0x1c,  	// 118 - 'v'
  5, 0x3c, 0x40, 0x30, 0x40, 0x3c,  	// 119 - 'w'
  5, 0x44, 0x28, 0x10, 0x28, 0x44,  	// 120 - 'x'
  5, 0x4c, 0x90, 0x90, 0x90, 0x7c,  	// 121 - 'y'
  5, 0x44, 0x64, 0x54, 0x4c, 0x44,  	// 122 - 'z'
};
