/***************************************************************************

  Author: Michael Stumpfl

  Date:   2019-07-15

  API:    C

  Libraries:
    ---

  Functionality:
    Various hacks to work around the "unresolved external symbols" errors
    that result when this library is built for "dll-...-(debug|release)"
    configurations.

  Known Bugs:
    Only the 'input_s()' implementation (i.e. the _SAFECRT_IMPL) verifiably
    works and passes all tests in 'testbed.c'.

    While the aforementioned hacks allow the 'input_l()' variant to com-
    pile, the test suite crashes while executing 'fprintf (stderr, "OK");'
    in 'test_sscanf()'.

****************************************************************************/
#ifdef _SAFECRT_IMPL
  #ifdef __cplusplus
  extern "C" {
  #endif

  size_t __crtDebugFillThreshold =
    #ifdef _DEBUG
    SIZE_MAX
    #else
    0
    #endif
      ;

  #ifdef __cplusplus
  }
  #endif
#else
  /* crt\src\rterr.h:30 */
  #define _RT_FLOAT                               2               /* floating point not loaded */
  #define _RT_LOCALE                              32              /* lack of space for locale */

  #ifdef __cplusplus
  extern "C" {
  #endif

  /* crt\src\cmiscdat.c */
  PFV _cfltcvt_tab[10] = {
      _fptrap,    /*  _cfltcvt */
      _fptrap,    /*  _cropzeros */
      _fptrap,    /*  _fassign */
      _fptrap,    /*  _forcdecpt */
      _fptrap,    /*  _positive */
      _fptrap,    /*  _cldcvt */
      _fptrap,    /*  _cfltcvt_l */
      _fptrap,    /*  _fassign_l */
      _fptrap,    /*  _cropzeros_l */
      _fptrap     /*  _forcdecpt_l */
  };

  /* crt\src\crt0fp.c:43 */
  void __cdecl _fptrap(
          void
          )
  {
          _amsg_exit(_RT_FLOAT);
  }

  /* crt\src\xthdloc.c:18 */
  extern int __globallocalestatus; /* = (~_GLOBAL_LOCALE_BIT) ;*/

  /* crt\src\ctype.c:302 */
  const unsigned short __newctype[384] = {
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0,
          0,                      /* -1 EOF   */
          _CONTROL,               /* 00 (NUL) */
          _CONTROL,               /* 01 (SOH) */
          _CONTROL,               /* 02 (STX) */
          _CONTROL,               /* 03 (ETX) */
          _CONTROL,               /* 04 (EOT) */
          _CONTROL,               /* 05 (ENQ) */
          _CONTROL,               /* 06 (ACK) */
          _CONTROL,               /* 07 (BEL) */
          _CONTROL,               /* 08 (BS)  */
          _SPACE+_CONTROL,        /* 09 (HT)  */
          _SPACE+_CONTROL,        /* 0A (LF)  */
          _SPACE+_CONTROL,        /* 0B (VT)  */
          _SPACE+_CONTROL,        /* 0C (FF)  */
          _SPACE+_CONTROL,        /* 0D (CR)  */
          _CONTROL,               /* 0E (SI)  */
          _CONTROL,               /* 0F (SO)  */
          _CONTROL,               /* 10 (DLE) */
          _CONTROL,               /* 11 (DC1) */
          _CONTROL,               /* 12 (DC2) */
          _CONTROL,               /* 13 (DC3) */
          _CONTROL,               /* 14 (DC4) */
          _CONTROL,               /* 15 (NAK) */
          _CONTROL,               /* 16 (SYN) */
          _CONTROL,               /* 17 (ETB) */
          _CONTROL,               /* 18 (CAN) */
          _CONTROL,               /* 19 (EM)  */
          _CONTROL,               /* 1A (SUB) */
          _CONTROL,               /* 1B (ESC) */
          _CONTROL,               /* 1C (FS)  */
          _CONTROL,               /* 1D (GS)  */
          _CONTROL,               /* 1E (RS)  */
          _CONTROL,               /* 1F (US)  */
          _SPACE+_BLANK,          /* 20 SPACE */
          _PUNCT,                 /* 21 !     */
          _PUNCT,                 /* 22 "     */
          _PUNCT,                 /* 23 #     */
          _PUNCT,                 /* 24 $     */
          _PUNCT,                 /* 25 %     */
          _PUNCT,                 /* 26 &     */
          _PUNCT,                 /* 27 '     */
          _PUNCT,                 /* 28 (     */
          _PUNCT,                 /* 29 )     */
          _PUNCT,                 /* 2A *     */
          _PUNCT,                 /* 2B +     */
          _PUNCT,                 /* 2C ,     */
          _PUNCT,                 /* 2D -     */
          _PUNCT,                 /* 2E .     */
          _PUNCT,                 /* 2F /     */
          _DIGIT+_HEX,            /* 30 0     */
          _DIGIT+_HEX,            /* 31 1     */
          _DIGIT+_HEX,            /* 32 2     */
          _DIGIT+_HEX,            /* 33 3     */
          _DIGIT+_HEX,            /* 34 4     */
          _DIGIT+_HEX,            /* 35 5     */
          _DIGIT+_HEX,            /* 36 6     */
          _DIGIT+_HEX,            /* 37 7     */
          _DIGIT+_HEX,            /* 38 8     */
          _DIGIT+_HEX,            /* 39 9     */
          _PUNCT,                 /* 3A :     */
          _PUNCT,                 /* 3B ;     */
          _PUNCT,                 /* 3C <     */
          _PUNCT,                 /* 3D =     */
          _PUNCT,                 /* 3E >     */
          _PUNCT,                 /* 3F ?     */
          _PUNCT,                 /* 40 @     */
          _UPPER+_HEX,            /* 41 A     */
          _UPPER+_HEX,            /* 42 B     */
          _UPPER+_HEX,            /* 43 C     */
          _UPPER+_HEX,            /* 44 D     */
          _UPPER+_HEX,            /* 45 E     */
          _UPPER+_HEX,            /* 46 F     */
          _UPPER,                 /* 47 G     */
          _UPPER,                 /* 48 H     */
          _UPPER,                 /* 49 I     */
          _UPPER,                 /* 4A J     */
          _UPPER,                 /* 4B K     */
          _UPPER,                 /* 4C L     */
          _UPPER,                 /* 4D M     */
          _UPPER,                 /* 4E N     */
          _UPPER,                 /* 4F O     */
          _UPPER,                 /* 50 P     */
          _UPPER,                 /* 51 Q     */
          _UPPER,                 /* 52 R     */
          _UPPER,                 /* 53 S     */
          _UPPER,                 /* 54 T     */
          _UPPER,                 /* 55 U     */
          _UPPER,                 /* 56 V     */
          _UPPER,                 /* 57 W     */
          _UPPER,                 /* 58 X     */
          _UPPER,                 /* 59 Y     */
          _UPPER,                 /* 5A Z     */
          _PUNCT,                 /* 5B [     */
          _PUNCT,                 /* 5C \     */
          _PUNCT,                 /* 5D ]     */
          _PUNCT,                 /* 5E ^     */
          _PUNCT,                 /* 5F _     */
          _PUNCT,                 /* 60 `     */
          _LOWER+_HEX,            /* 61 a     */
          _LOWER+_HEX,            /* 62 b     */
          _LOWER+_HEX,            /* 63 c     */
          _LOWER+_HEX,            /* 64 d     */
          _LOWER+_HEX,            /* 65 e     */
          _LOWER+_HEX,            /* 66 f     */
          _LOWER,                 /* 67 g     */
          _LOWER,                 /* 68 h     */
          _LOWER,                 /* 69 i     */
          _LOWER,                 /* 6A j     */
          _LOWER,                 /* 6B k     */
          _LOWER,                 /* 6C l     */
          _LOWER,                 /* 6D m     */
          _LOWER,                 /* 6E n     */
          _LOWER,                 /* 6F o     */
          _LOWER,                 /* 70 p     */
          _LOWER,                 /* 71 q     */
          _LOWER,                 /* 72 r     */
          _LOWER,                 /* 73 s     */
          _LOWER,                 /* 74 t     */
          _LOWER,                 /* 75 u     */
          _LOWER,                 /* 76 v     */
          _LOWER,                 /* 77 w     */
          _LOWER,                 /* 78 x     */
          _LOWER,                 /* 79 y     */
          _LOWER,                 /* 7A z     */
          _PUNCT,                 /* 7B {     */
          _PUNCT,                 /* 7C |     */
          _PUNCT,                 /* 7D }     */
          _PUNCT,                 /* 7E ~     */
          _CONTROL,               /* 7F (DEL) */
          /* and the rest are 0... */
  };

  const unsigned char __newclmap[384] = {
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
          0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
          0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
          0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
          0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
          0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
          0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
          0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
          0x00,   /* 00 (NUL) */
          0x01,   /* 01 (SOH) */
          0x02,   /* 02 (STX) */
          0x03,   /* 03 (ETX) */
          0x04,   /* 04 (EOT) */
          0x05,   /* 05 (ENQ) */
          0x06,   /* 06 (ACK) */
          0x07,   /* 07 (BEL) */
          0x08,   /* 08 (BS)  */
          0x09,   /* 09 (HT)  */
          0x0A,   /* 0A (LF)  */
          0x0B,   /* 0B (VT)  */
          0x0C,   /* 0C (FF)  */
          0x0D,   /* 0D (CR)  */
          0x0E,   /* 0E (SI)  */
          0x0F,   /* 0F (SO)  */
          0x10,   /* 10 (DLE) */
          0x11,   /* 11 (DC1) */
          0x12,   /* 12 (DC2) */
          0x13,   /* 13 (DC3) */
          0x14,   /* 14 (DC4) */
          0x15,   /* 15 (NAK) */
          0x16,   /* 16 (SYN) */
          0x17,   /* 17 (ETB) */
          0x18,   /* 18 (CAN) */
          0x19,   /* 19 (EM)  */
          0x1A,   /* 1A (SUB) */
          0x1B,   /* 1B (ESC) */
          0x1C,   /* 1C (FS)  */
          0x1D,   /* 1D (GS)  */
          0x1E,   /* 1E (RS)  */
          0x1F,   /* 1F (US)  */
          0x20,   /* 20 SPACE */
          0x21,   /* 21 !     */
          0x22,   /* 22 "     */
          0x23,   /* 23 #     */
          0x24,   /* 24 $     */
          0x25,   /* 25 %     */
          0x26,   /* 26 &     */
          0x27,   /* 27 '     */
          0x28,   /* 28 (     */
          0x29,   /* 29 )     */
          0x2A,   /* 2A *     */
          0x2B,   /* 2B +     */
          0x2C,   /* 2C ,     */
          0x2D,   /* 2D -     */
          0x2E,   /* 2E .     */
          0x2F,   /* 2F /     */
          0x30,   /* 30 0     */
          0x31,   /* 31 1     */
          0x32,   /* 32 2     */
          0x33,   /* 33 3     */
          0x34,   /* 34 4     */
          0x35,   /* 35 5     */
          0x36,   /* 36 6     */
          0x37,   /* 37 7     */
          0x38,   /* 38 8     */
          0x39,   /* 39 9     */
          0x3A,   /* 3A :     */
          0x3B,   /* 3B ;     */
          0x3C,   /* 3C <     */
          0x3D,   /* 3D =     */
          0x3E,   /* 3E >     */
          0x3F,   /* 3F ?     */
          0x40,   /* 40 @     */
          0x61,   /* 41 A     */
          0x62,   /* 42 B     */
          0x63,   /* 43 C     */
          0x64,   /* 44 D     */
          0x65,   /* 45 E     */
          0x66,   /* 46 F     */
          0x67,   /* 47 G     */
          0x68,   /* 48 H     */
          0x69,   /* 49 I     */
          0x6A,   /* 4A J     */
          0x6B,   /* 4B K     */
          0x6C,   /* 4C L     */
          0x6D,   /* 4D M     */
          0x6E,   /* 4E N     */
          0x6F,   /* 4F O     */
          0x70,   /* 50 P     */
          0x71,   /* 51 Q     */
          0x72,   /* 52 R     */
          0x73,   /* 53 S     */
          0x74,   /* 54 T     */
          0x75,   /* 55 U     */
          0x76,   /* 56 V     */
          0x77,   /* 57 W     */
          0x78,   /* 58 X     */
          0x79,   /* 59 Y     */
          0x7A,   /* 5A Z     */
          0x5B,   /* 5B [     */
          0x5C,   /* 5C \     */
          0x5D,   /* 5D ]     */
          0x5E,   /* 5E ^     */
          0x5F,   /* 5F _     */
          0x60,   /* 60 `     */
          0x61,   /* 61 a     */
          0x62,   /* 62 b     */
          0x63,   /* 63 c     */
          0x64,   /* 64 d     */
          0x65,   /* 65 e     */
          0x66,   /* 66 f     */
          0x67,   /* 67 g     */
          0x68,   /* 68 h     */
          0x69,   /* 69 i     */
          0x6A,   /* 6A j     */
          0x6B,   /* 6B k     */
          0x6C,   /* 6C l     */
          0x6D,   /* 6D m     */
          0x6E,   /* 6E n     */
          0x6F,   /* 6F o     */
          0x70,   /* 70 p     */
          0x71,   /* 71 q     */
          0x72,   /* 72 r     */
          0x73,   /* 73 s     */
          0x74,   /* 74 t     */
          0x75,   /* 75 u     */
          0x76,   /* 76 v     */
          0x77,   /* 77 w     */
          0x78,   /* 78 x     */
          0x79,   /* 79 y     */
          0x7A,   /* 7A z     */
          0x7B,   /* 7B {     */
          0x7C,   /* 7C |     */
          0x7D,   /* 7D }     */
          0x7E,   /* 7E ~     */
          0x7F,   /* 7F (DEL) */
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
          0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
          0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
          0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
          0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
          0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
          0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
          0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
  };

  const unsigned char __newcumap[384] = {
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
          0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
          0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
          0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
          0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
          0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
          0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
          0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
          0x00,   /* 00 (NUL) */
          0x01,   /* 01 (SOH) */
          0x02,   /* 02 (STX) */
          0x03,   /* 03 (ETX) */
          0x04,   /* 04 (EOT) */
          0x05,   /* 05 (ENQ) */
          0x06,   /* 06 (ACK) */
          0x07,   /* 07 (BEL) */
          0x08,   /* 08 (BS)  */
          0x09,   /* 09 (HT)  */
          0x0A,   /* 0A (LF)  */
          0x0B,   /* 0B (VT)  */
          0x0C,   /* 0C (FF)  */
          0x0D,   /* 0D (CR)  */
          0x0E,   /* 0E (SI)  */
          0x0F,   /* 0F (SO)  */
          0x10,   /* 10 (DLE) */
          0x11,   /* 11 (DC1) */
          0x12,   /* 12 (DC2) */
          0x13,   /* 13 (DC3) */
          0x14,   /* 14 (DC4) */
          0x15,   /* 15 (NAK) */
          0x16,   /* 16 (SYN) */
          0x17,   /* 17 (ETB) */
          0x18,   /* 18 (CAN) */
          0x19,   /* 19 (EM)  */
          0x1A,   /* 1A (SUB) */
          0x1B,   /* 1B (ESC) */
          0x1C,   /* 1C (FS)  */
          0x1D,   /* 1D (GS)  */
          0x1E,   /* 1E (RS)  */
          0x1F,   /* 1F (US)  */
          0x20,   /* 20 SPACE */
          0x21,   /* 21 !     */
          0x22,   /* 22 "     */
          0x23,   /* 23 #     */
          0x24,   /* 24 $     */
          0x25,   /* 25 %     */
          0x26,   /* 26 &     */
          0x27,   /* 27 '     */
          0x28,   /* 28 (     */
          0x29,   /* 29 )     */
          0x2A,   /* 2A *     */
          0x2B,   /* 2B +     */
          0x2C,   /* 2C ,     */
          0x2D,   /* 2D -     */
          0x2E,   /* 2E .     */
          0x2F,   /* 2F /     */
          0x30,   /* 30 0     */
          0x31,   /* 31 1     */
          0x32,   /* 32 2     */
          0x33,   /* 33 3     */
          0x34,   /* 34 4     */
          0x35,   /* 35 5     */
          0x36,   /* 36 6     */
          0x37,   /* 37 7     */
          0x38,   /* 38 8     */
          0x39,   /* 39 9     */
          0x3A,   /* 3A :     */
          0x3B,   /* 3B ;     */
          0x3C,   /* 3C <     */
          0x3D,   /* 3D =     */
          0x3E,   /* 3E >     */
          0x3F,   /* 3F ?     */
          0x40,   /* 40 @     */
          0x41,   /* 41 A     */
          0x42,   /* 42 B     */
          0x43,   /* 43 C     */
          0x44,   /* 44 D     */
          0x45,   /* 45 E     */
          0x46,   /* 46 F     */
          0x47,   /* 47 G     */
          0x48,   /* 48 H     */
          0x49,   /* 49 I     */
          0x4A,   /* 4A J     */
          0x4B,   /* 4B K     */
          0x4C,   /* 4C L     */
          0x4D,   /* 4D M     */
          0x4E,   /* 4E N     */
          0x4F,   /* 4F O     */
          0x50,   /* 50 P     */
          0x51,   /* 51 Q     */
          0x52,   /* 52 R     */
          0x53,   /* 53 S     */
          0x54,   /* 54 T     */
          0x55,   /* 55 U     */
          0x56,   /* 56 V     */
          0x57,   /* 57 W     */
          0x58,   /* 58 X     */
          0x59,   /* 59 Y     */
          0x5A,   /* 5A Z     */
          0x5B,   /* 5B [     */
          0x5C,   /* 5C \     */
          0x5D,   /* 5D ]     */
          0x5E,   /* 5E ^     */
          0x5F,   /* 5F _     */
          0x60,   /* 60 `     */
          0x41,   /* 61 a     */
          0x42,   /* 62 b     */
          0x43,   /* 63 c     */
          0x44,   /* 64 d     */
          0x45,   /* 65 e     */
          0x46,   /* 66 f     */
          0x47,   /* 67 g     */
          0x48,   /* 68 h     */
          0x49,   /* 69 i     */
          0x4A,   /* 6A j     */
          0x4B,   /* 6B k     */
          0x4C,   /* 6C l     */
          0x4D,   /* 6D m     */
          0x4E,   /* 6E n     */
          0x4F,   /* 6F o     */
          0x50,   /* 70 p     */
          0x51,   /* 71 q     */
          0x52,   /* 72 r     */
          0x53,   /* 73 s     */
          0x54,   /* 74 t     */
          0x55,   /* 75 u     */
          0x56,   /* 76 v     */
          0x57,   /* 77 w     */
          0x58,   /* 78 x     */
          0x59,   /* 79 y     */
          0x5A,   /* 7A z     */
          0x7B,   /* 7B {     */
          0x7C,   /* 7C |     */
          0x7D,   /* 7D }     */
          0x7E,   /* 7E ~     */
          0x7F,   /* 7F (DEL) */
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
          0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
          0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
          0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
          0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
          0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
          0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
          0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
  };

  /* crt\src\lconv.c:18 */
  char __lconv_static_decimal[] = ".";
  char __lconv_static_null[] = "";

  struct lconv __lconv_c = {
                  __lconv_static_decimal, /* decimal_point */
                  __lconv_static_null,       /* thousands_sep */
                  __lconv_static_null,       /* grouping */
                  __lconv_static_null,       /* int_curr_symbol */
                  __lconv_static_null,       /* currency_symbol */
                  __lconv_static_null,       /* mon_decimal_point */
                  __lconv_static_null,       /* mon_thousands_sep */
                  __lconv_static_null,       /* mon_grouping */
                  __lconv_static_null,       /* positive_sign */
                  __lconv_static_null,       /* negative_sign */
                  CHAR_MAX,                           /* int_frac_digits */
                  CHAR_MAX,                           /* frac_digits */
                  CHAR_MAX,                           /* p_cs_precedes */
                  CHAR_MAX,                           /* p_sep_by_space */
                  CHAR_MAX,                           /* n_cs_precedes */
                  CHAR_MAX,                           /* n_sep_by_space */
                  CHAR_MAX,                           /* p_sign_posn */
                  CHAR_MAX                               /* n_sign_posn */
                  };

  struct lconv *__lconv = &__lconv_c;

  /* crt\src\strftime.c:70 */
  __declspec(selectany) struct __lc_time_data __lc_time_c = {

          {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"},

          {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
                  "Friday", "Saturday", },

          {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                  "Sep", "Oct", "Nov", "Dec"},

          {"January", "February", "March", "April", "May", "June",
                  "July", "August", "September", "October",
                  "November", "December"},

          {"AM", "PM"},

          { "MM/dd/yy" },
          { "dddd, MMMM dd, yyyy" },
          { "HH:mm:ss" },

          0x0409,
          1,

          0
          };

  struct __lc_time_data *__lc_time_curr = &__lc_time_c;

  /* crt\src\nlsdata2.c:24 */
  char __clocalestr[] = "C";

  threadlocinfo __initiallocinfo = {
      1,                                        /* refcount                 */
      _CLOCALECP,                               /* lc_codepage              */
      _CLOCALECP,                               /* lc_collate_cp            */
      {   _CLOCALEHANDLE,                       /* lc_handle[_ALL]          */
          _CLOCALEHANDLE,                       /* lc_handle[_COLLATE]      */
          _CLOCALEHANDLE,                       /* lc_handle[_CTYPE]        */
          _CLOCALEHANDLE,                       /* lc_handle[_MONETARY]     */
          _CLOCALEHANDLE,                       /* lc_handle[_NUMERIC]      */
          _CLOCALEHANDLE                        /* lc_handle[_TIME]         */
      },
      {   {0, 0, 0},                            /* lc_id[LC_ALL]            */
          {0, 0, 0},                            /* lc_id[LC_COLLATE]        */
          {0, 0, 0},                            /* lc_id[LC_CTYPE]          */
          {0, 0, 0},                            /* lc_id[LC_MONETARY]       */
          {0, 0, 0},                            /* lc_id[LC_NUMERIC]        */
          {0, 0, 0}                             /* lc_id[LC_TIME]           */
      },
      {   {NULL, NULL, NULL, NULL},             /* lc_category[LC_ALL]      */
          {__clocalestr, NULL, NULL, NULL},     /* lc_category[LC_COLLATE]  */
          {__clocalestr, NULL, NULL, NULL},     /* lc_category[LC_CTYPE]    */
          {__clocalestr, NULL, NULL, NULL},     /* lc_category[LC_MONETARY] */
          {__clocalestr, NULL, NULL, NULL},     /* lc_category[LC_NUMERIC]  */
          {__clocalestr, NULL, NULL, NULL}      /* lc_category[LC_TIME]     */
      },
      1,                                        /* lc_clike                 */
      1,                                        /* mb_cur_max               */
      NULL,                                     /* lconv_intl_refcount      */
      NULL,                                     /* lconv_num_refcount       */
      NULL,                                     /* lconv_mon_refcount       */
      &__lconv_c,                               /* lconv                    */
      NULL,                                     /* ctype1_refcount          */
      NULL,                                     /* ctype1                   */
      __newctype + 128,                         /* pctype                   */
      __newclmap + 128,                         /* pclmap                   */
      __newcumap + 128,                         /* pcumap                   */
      &__lc_time_c,                             /* lc_time_curr             */
  };

  /*
   * global pointer to the current per-thread locale information structure.
   */
  pthreadlocinfo __ptlocinfo = &__initiallocinfo;

  /* crt\src\mbctype.c:60 */
  threadmbcinfo __initialmbcinfo =
  {
      0,
      _CLOCALECP, /* _MB_CP_ANSI */
      0,
      0,
      { 0, 0, 0, 0, 0, 0 },
      {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
      0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
      0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00 /* rest is zero */
      },
      {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
      0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73,
      0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
      0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
      0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00 /* rest is zero */
      }
  };

  pthreadmbcinfo __ptmbcinfo = &__initialmbcinfo;

  pthreadmbcinfo __cdecl __updatetmbcinfo(void)
  {
          pthreadmbcinfo ptmbci = NULL;

          _ptiddata ptd = _getptd();
          if (!(ptd->_ownlocale & __globallocalestatus)|| !ptd->ptlocinfo) {
          _mlock(_MB_CP_LOCK);

          __try
          {

              if ( (ptmbci = ptd->ptmbcinfo) != __ptmbcinfo )
              {
                  /*
                   * Decrement the reference count in the old mbc info structure
                   * and free it, if necessary
                   */
                      if ( (ptmbci != NULL) && (InterlockedDecrement((volatile LONG *)&(ptmbci->refcount)) == 0) && ptmbci != &__initialmbcinfo )
                  {
                      /*
                       * Free it
                       */
                      _free_crt(ptmbci);
                  }

                  /*
                   * Point to the current mbc info structure and increment its
                   * reference count.
                   */
                  ptmbci = ptd->ptmbcinfo = __ptmbcinfo;
                      InterlockedIncrement((volatile LONG *)&(ptmbci->refcount));
              }
          }
          __finally
          {
              _munlock(_MB_CP_LOCK);
          }
          } else {
              ptmbci = ptd->ptmbcinfo;
          }

          if(!ptmbci)
          {
              _amsg_exit(_RT_LOCALE);
          }

          return ptmbci;
  }

  /* crt\src\msdos.h:42 */
  #define FTEXT           0x80    /* file handle is in text mode */

  /* crt\src\ioinit.c:32 */
  #pragma warning (push)
  #pragma warning (disable : 4310)  /* input_l.c(115) : warning C4310: cast truncates constant value */

  _CRTIMP ioinfo __badioinfo = {
          (intptr_t)(-1), /* osfhnd */
          (char)FTEXT,          /* osfile */
          10,             /* pipech */
          0               /* lockinitflag */
          };

  _CRTIMP ioinfo * __pioinfo[IOINFO_ARRAYS];

  /* crt\src\initmon.c:252 */
  void __cdecl __free_lconv_mon(
          struct lconv *l
          )
  {
      if (l == NULL)
          return;

      if ( l->int_curr_symbol != __lconv_c.int_curr_symbol )
          _free_crt(l->int_curr_symbol);

      if ( l->currency_symbol != __lconv_c.currency_symbol )
          _free_crt(l->currency_symbol);

      if ( l->mon_decimal_point != __lconv_c.mon_decimal_point )
          _free_crt(l->mon_decimal_point);

      if ( l->mon_thousands_sep != __lconv_c.mon_thousands_sep )
          _free_crt(l->mon_thousands_sep);

      if ( l->mon_grouping != __lconv_c.mon_grouping )
          _free_crt(l->mon_grouping);

      if ( l->positive_sign != __lconv_c.positive_sign )
          _free_crt(l->positive_sign);

      if ( l->negative_sign != __lconv_c.negative_sign )
          _free_crt(l->negative_sign);
  }

  /* crt\src\initnum:208 */
  void __cdecl __free_lconv_num(
          struct lconv *l
          )
  {
      if (l == NULL)
          return;

      if ( l->decimal_point != __lconv_c.decimal_point )
          _free_crt(l->decimal_point);

      if ( l->thousands_sep != __lconv_c.thousands_sep )
          _free_crt(l->thousands_sep);

      if ( l->grouping != __lconv_c.grouping )
          _free_crt(l->grouping);
  }

  /* crt\src\inittime.c:176 */
  void __cdecl __free_lc_time (
          struct __lc_time_data *lc_time
          )
  {
          if (lc_time == NULL)
                  return;

          _free_crt (lc_time->wday_abbr[1]);
          _free_crt (lc_time->wday_abbr[2]);
          _free_crt (lc_time->wday_abbr[3]);
          _free_crt (lc_time->wday_abbr[4]);
          _free_crt (lc_time->wday_abbr[5]);
          _free_crt (lc_time->wday_abbr[6]);
          _free_crt (lc_time->wday_abbr[0]);

          _free_crt (lc_time->wday[1]);
          _free_crt (lc_time->wday[2]);
          _free_crt (lc_time->wday[3]);
          _free_crt (lc_time->wday[4]);
          _free_crt (lc_time->wday[5]);
          _free_crt (lc_time->wday[6]);
          _free_crt (lc_time->wday[0]);

          _free_crt (lc_time->month_abbr[0]);
          _free_crt (lc_time->month_abbr[1]);
          _free_crt (lc_time->month_abbr[2]);
          _free_crt (lc_time->month_abbr[3]);
          _free_crt (lc_time->month_abbr[4]);
          _free_crt (lc_time->month_abbr[5]);
          _free_crt (lc_time->month_abbr[6]);
          _free_crt (lc_time->month_abbr[7]);
          _free_crt (lc_time->month_abbr[8]);
          _free_crt (lc_time->month_abbr[9]);
          _free_crt (lc_time->month_abbr[10]);
          _free_crt (lc_time->month_abbr[11]);

          _free_crt (lc_time->month[0]);
          _free_crt (lc_time->month[1]);
          _free_crt (lc_time->month[2]);
          _free_crt (lc_time->month[3]);
          _free_crt (lc_time->month[4]);
          _free_crt (lc_time->month[5]);
          _free_crt (lc_time->month[6]);
          _free_crt (lc_time->month[7]);
          _free_crt (lc_time->month[8]);
          _free_crt (lc_time->month[9]);
          _free_crt (lc_time->month[10]);
          _free_crt (lc_time->month[11]);

          _free_crt (lc_time->ampm[0]);
          _free_crt (lc_time->ampm[1]);

          _free_crt (lc_time->ww_sdatefmt);
          _free_crt (lc_time->ww_ldatefmt);
          _free_crt (lc_time->ww_timefmt);
  /* Don't need to make these pointers NULL */
  }

  /* crt\src\setlocal.c:141 */
  void __cdecl __freetlocinfo (
          pthreadlocinfo ptloci
          )
  {
      int category;
      /*
       * Free up lconv struct
       */
      if ( (ptloci->lconv != NULL) &&
           (ptloci->lconv != &__lconv_c) &&
           ((ptloci->lconv_intl_refcount != NULL) &&
           (*(ptloci->lconv_intl_refcount) == 0)))
      {
          if ( (ptloci->lconv_mon_refcount != NULL) &&
               (*(ptloci->lconv_mon_refcount) == 0))
          {
              _free_crt(ptloci->lconv_mon_refcount);
              __free_lconv_mon(ptloci->lconv);
          }

          if ( (ptloci->lconv_num_refcount != NULL) &&
               (*(ptloci->lconv_num_refcount) == 0))
          {
              _free_crt(ptloci->lconv_num_refcount);
              __free_lconv_num(ptloci->lconv);
          }

          _free_crt(ptloci->lconv_intl_refcount);
          _free_crt(ptloci->lconv);
      }

      /*
       * Free up ctype tables
       */
      if ( (ptloci->ctype1_refcount != NULL) &&
           (*(ptloci->ctype1_refcount) == 0) )
      {
          _free_crt(ptloci->ctype1-_COFFSET);
          _free_crt((char *)(ptloci->pclmap - _COFFSET - 1));
          _free_crt((char *)(ptloci->pcumap - _COFFSET - 1));
          _free_crt(ptloci->ctype1_refcount);
      }

      /*
       * Free up the __lc_time_data struct
       */
      if ( ptloci->lc_time_curr != &__lc_time_c &&
           ((ptloci->lc_time_curr->refcount) == 0) )
      {
          __free_lc_time(ptloci->lc_time_curr);
          _free_crt(ptloci->lc_time_curr);
      }

      for (category = LC_MIN; category <= LC_MAX; ++category) {
          if ((ptloci->lc_category[category].locale != __clocalestr) &&
                (ptloci->lc_category[category].refcount != NULL) &&
                (*ptloci->lc_category[category].refcount == 0) )
          {
              _free_crt(ptloci->lc_category[category].refcount);
          }
          _ASSERTE(((ptloci->lc_category[category].wlocale != NULL) && (ptloci->lc_category[category].wrefcount != NULL)) ||
                   ((ptloci->lc_category[category].wlocale == NULL) && (ptloci->lc_category[category].wrefcount == NULL)));
          if ((ptloci->lc_category[category].wlocale != NULL) &&
                (ptloci->lc_category[category].wrefcount != NULL) &&
                (*ptloci->lc_category[category].wrefcount == 0) )
          {
              _free_crt(ptloci->lc_category[category].wrefcount);
          }
      }

      /*
       * Free up the threadlocinfo struct
       */
      _free_crt(ptloci);
  }

  void __cdecl __addlocaleref( pthreadlocinfo ptloci)
  {
      int category;
      InterlockedIncrement((volatile LONG *)&(ptloci->refcount));
      if ( ptloci->lconv_intl_refcount != NULL )
          InterlockedIncrement((volatile LONG *)ptloci->lconv_intl_refcount);

      if ( ptloci->lconv_mon_refcount != NULL )
          InterlockedIncrement((volatile LONG *)ptloci->lconv_mon_refcount);

      if ( ptloci->lconv_num_refcount != NULL )
          InterlockedIncrement((volatile LONG *)ptloci->lconv_num_refcount);

      if ( ptloci->ctype1_refcount != NULL )
          InterlockedIncrement((volatile LONG *)ptloci->ctype1_refcount);

      for (category = LC_MIN; category <= LC_MAX; ++category) {
          if (ptloci->lc_category[category].locale != __clocalestr &&
              ptloci->lc_category[category].refcount != NULL)
              InterlockedIncrement((volatile LONG *)ptloci->lc_category[category].refcount);
          if (ptloci->lc_category[category].wlocale != NULL &&
              ptloci->lc_category[category].wrefcount != NULL)
              InterlockedIncrement((volatile LONG *)ptloci->lc_category[category].wrefcount);
      }
      InterlockedIncrement((volatile LONG *)&(ptloci->lc_time_curr->refcount));
  }

  void * __cdecl __removelocaleref( pthreadlocinfo ptloci)
  {
      int category;
      if ( ptloci != NULL )
      {
          InterlockedDecrement((volatile LONG *)&(ptloci->refcount));

          if ( ptloci->lconv_intl_refcount != NULL )
              InterlockedDecrement((volatile LONG *)ptloci->lconv_intl_refcount);

          if ( ptloci->lconv_mon_refcount != NULL )
              InterlockedDecrement((volatile LONG *)ptloci->lconv_mon_refcount);

          if ( ptloci->lconv_num_refcount != NULL )
              InterlockedDecrement((volatile LONG *)ptloci->lconv_num_refcount);

          if ( ptloci->ctype1_refcount != NULL )
              InterlockedDecrement((volatile LONG *)ptloci->ctype1_refcount);

          for (category = LC_MIN; category <= LC_MAX; ++category) {
              if (ptloci->lc_category[category].locale != __clocalestr &&
                  ptloci->lc_category[category].refcount != NULL)
                  InterlockedDecrement((volatile LONG *)ptloci->lc_category[category].refcount);
              if (ptloci->lc_category[category].wlocale != NULL &&
                  ptloci->lc_category[category].wrefcount != NULL)
                  InterlockedDecrement((volatile LONG *)ptloci->lc_category[category].wrefcount);
          }
          InterlockedDecrement((volatile LONG *)&(ptloci->lc_time_curr->refcount));
      }
      return ptloci;
  }

  static pthreadlocinfo __cdecl _updatetlocinfoEx_nolock(
      pthreadlocinfo *pptlocid,
      pthreadlocinfo ptlocis)
  {
      pthreadlocinfo ptloci;

      if (ptlocis == NULL || pptlocid == NULL)
          return NULL;
      ptloci = *pptlocid;
      if ( ptloci != ptlocis)
      {
          /*
           * Update to the current locale info structure and increment the
           * reference counts.
           */
          *pptlocid = ptlocis;
          __addlocaleref(ptlocis);
          /*
           * Decrement the reference counts in the old locale info
           * structure.
           */
          if ( ptloci != NULL )
          {
              __removelocaleref(ptloci);
          }
          /*
           * Free the old locale info structure, if necessary.  Must be done
           * after incrementing reference counts in current locale in case
           * any refcounts are shared with the old locale.
           */
          if ( (ptloci != NULL) &&
               (ptloci->refcount == 0) &&
               (ptloci != &__initiallocinfo) )
              __freetlocinfo(ptloci);

      }

      return ptlocis;
  }

  pthreadlocinfo __cdecl __updatetlocinfo(void)
  {
      pthreadlocinfo ptloci = NULL;
      _ptiddata ptd = _getptd();

      if (!(ptd->_ownlocale & __globallocalestatus)|| !ptd->ptlocinfo) {
          _mlock(_SETLOCALE_LOCK);
          __try
          {
              ptloci = _updatetlocinfoEx_nolock(&ptd->ptlocinfo, __ptlocinfo);
          }
          __finally
          {
              _munlock(_SETLOCALE_LOCK);
          }
      } else {
          ptloci = _getptd()->ptlocinfo;
      }
      if(!ptloci)
      {
          _amsg_exit(_RT_LOCALE);
      }

      return ptloci;
  }

  #pragma warning (pop)

  #ifdef __cplusplus
  }
  #endif
#endif
