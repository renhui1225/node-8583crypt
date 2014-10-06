#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static unsigned char T1[] =
{
	57,49,41,33,25,17, 9, 1,
	59,51,43,35,27,19,11, 3,
	61,53,45,37,29,21,13, 5,
	63,55,47,39,31,23,15, 7,
	56,48,40,32,24,16, 8, 0,
	58,50,42,34,26,18,10, 2,
	60,52,44,36,28,20,12, 4,
	62,54,46,38,30,22,14, 6
};

static unsigned char T2[] =
{
	39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,
	37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,
	35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,
	33, 1,41, 9,49,17,57,25,
	32, 0,40, 8,48,16,56,24
};

static unsigned char T3[] =
{
	31, 0, 1, 2, 3, 4,
	 3, 4, 5, 6, 7, 8,
	 7, 8, 9,10,11,12,
	11,12,13,14,15,16,
	15,16,17,18,19,20,
	19,20,21,22,23,24,
	23,24,25,26,27,28,
	27,28,29,30,31, 0
};

static unsigned char T5[] =
{
	15, 6,19,20,
	28,11,27,16,
	 0,14,22,25,
	 4,17,30, 9,
	 1, 7,23,13,
	31,26, 2, 8,
	18,12,29, 5,
	21,10, 3,24
};

static unsigned char T7_1_2[] =
{
	56,48,40,32,24,16, 8,
	 0,57,49,41,33,25,17,
	 9, 1,58,50,42,34,26,
	18,10, 2,59,51,43,35,
	62,54,46,38,30,22,14,
	 6,61,53,45,37,29,21,
	13, 5,60,52,44,36,28,
	20,12, 4,27,19,11, 3
};

static unsigned char T8[] =
{
	 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0
};

static unsigned char T9[] =
{
	13,16,10,23, 0, 4,
	 2,27,14, 5,20, 9,
	22,18,11, 3,25, 7,
	15, 6,26,19,12, 1,
	40,51,30,36,46,54,
	29,39,50,44,32,47,
	43,48,38,55,33,52,
	45,41,49,35,28,31
};

static unsigned char T6[][64] =
{
    {/* S1 */
	14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
	 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
	 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13
    },
    {/* S2 */
	15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
	 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
	 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
	13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9
    },
    {/* S3 */
	10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
	13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
	 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12
    },
    {/* S4 */
	 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
	13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
	10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
	 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14
    },
    {/* S5 */
	 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
	14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
	 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
	11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3
    },
    {/* S6 */
	12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
	10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
	 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
	 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13
    },
    {/* S7 */
	 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
	13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
	 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
	 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12
    },
    {/* S8 */
	13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
	 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
	 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
	 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
    }
};

unsigned char TE[][4] =
{
	{0,0,0,0},
	{0,0,0,1},
	{0,0,1,0},
	{0,0,1,1},
	{0,1,0,0},
	{0,1,0,1},
	{0,1,1,0},
	{0,1,1,1},
	{1,0,0,0},
	{1,0,0,1},
	{1,0,1,0},
	{1,0,1,1},
	{1,1,0,0},
	{1,1,0,1},
	{1,1,1,0},
	{1,1,1,1}
};

void  Ks (unsigned char *Key, unsigned char Kn[16][48])
{
	unsigned char cd[56];
	unsigned char zt[60];
	int n, i;
	unsigned char tmp11, tmp12, tmp21, tmp22;
	unsigned char *Knn;

	/* choix 1 */
	for (i = 0; i < 56; i++)
	{
		cd[i] = Key[T7_1_2[i]];
	}

	for (n = 0; n < 16; n++)
	{
		if (T8[n] == 0)
		{
			tmp11 = cd[0];
			tmp21 = cd[28];
			memcpy( zt , &cd[1] , 55 );
			memcpy( cd , zt 	, 55 );
			cd[27] = tmp11;
			cd[55] = tmp21;
		}
		else
		{
			tmp11 = cd[0];
			tmp12 = cd[1];
			tmp21=  cd[28];
			tmp22 = cd[29];

			memcpy( zt , &cd[2] , 54 );
			memcpy( cd , zt 	, 54 );

			cd[26] = tmp11;
			cd[27] = tmp12;
			cd[54] = tmp21;
			cd[55] = tmp22;
		}
		Knn = Kn[n];
		for (i = 0; i < 48; i++)
		{
			Knn[i] = cd[T9[i]];
		}
	}
}

void fonction(unsigned char *Knn, unsigned char *r, unsigned char *s)
{

     unsigned char x[100];
     unsigned int *px;
     int i, l;
     unsigned char c;
     unsigned char t;

     memset( x, 0, sizeof( x ) );
    for (i = 0, l = 0, px = (unsigned int *) x; i < 8;)
    {
		c = 32 * (r[T3[l]] ^ Knn[l]);
        l++;
		c += 8 * (r[T3[l]] ^ Knn[l]);
        l++;
		c += 4 * (r[T3[l]] ^ Knn[l]);
        l++;
		c += 2 * (r[T3[l]] ^ Knn[l]);
        l++;
		c += 1 * (r[T3[l]] ^ Knn[l]);
        l++;
		c += 16 * (r[T3[l]] ^ Knn[l]);
        l++;
        t = T6[i][c];
        i++;
	*px = *(unsigned int*)TE[t];
        px++;
    }
	for (i = 0; i < 32; i++)
	{
		s[i] = x[T5[i]];
	}
}

void permutation(unsigned char *org, unsigned char *tab)
{
     unsigned char tmp[64];
     int i;

	memcpy(tmp, org, 64);
	for (i = 0; i < 64; i++)
	{
		org[i] = tmp[tab[i]];
	}
}

void chiffrement(unsigned char *xi, unsigned char *xo, unsigned char Kn[16][48])
{
     unsigned char r[32], l[32];
     unsigned char rp[32], lp[32];

     int i;
	 int n;

	memcpy(l, &xi[0], 32);
	memcpy(r, &xi[32], 32);

	for (n = 0; n < 16; n++)
	{
		memcpy(lp, r, 32);

		fonction(Kn[n], r, rp);
		for (i = 0; i < 32; i++)
		{
			r[i] =( ( l[i]) ^ (rp[i] )  ) ;
		}
		memcpy(l, lp, 32);
	}
	memcpy(&xo[0], r, 32);
	memcpy(&xo[32], l, 32);

}

void dechiffrement(unsigned char *xi, unsigned char *xo, unsigned char Kn[16][48])
{
     unsigned char r[32], l[32], rp[32], lp[32];

     int i;
     int n;

	memcpy(l, &xi[0], 32);
	memcpy(r, &xi[32], 32);

	for (n = 0; n < 16; n++)
	{
		memcpy(lp, r, 32);
		fonction(Kn[15 - n], r, rp);
		for (i = 0; i < 32; i++)
		{
			r[i] =( ( l[i] ) ^ ( rp[i] )) ;
		}
		memcpy(l, lp, 32);
	}

	memcpy(&xo[0], r, 32);
	memcpy(&xo[32], l, 32);
}

void eclater(const unsigned char *buf_bit, unsigned char *byte)
{
     int i;
     unsigned char m;

	for (i = 0; i < 8; i++)
	{
		for (m = 0x80; m != 0;	)
		{
                  if ((buf_bit[i] & m) != 0)
				*byte = 1;
			else
				*byte = 0;
                   byte++;
                  m=m/2 ;
		}
	}

}

void compacter(unsigned char *byte, unsigned char *buf_bit)
{
	 int i;
	 unsigned char m, n;

	for (i = 0; i < 8; i++)
	{
		n = 0;
		for (m = 0x80; m != 0; )
		{
			if (*byte++)
			n = n | m;
				   m=m/2 ;

		}
		buf_bit[i] = n;
	}
}


void mydes(unsigned char *boutput, const unsigned char *binput, const unsigned char *bkey, int direction)
{
	unsigned char  input[64];	/* data input */
	unsigned char  output[64];	/* data output */
	unsigned char  Key[64];
	unsigned char  Kn[16][48];

		
	
	eclater(binput, input);
	eclater(bkey, Key);
	Ks(Key, Kn);
	permutation(input, T1);

	if (direction)  dechiffrement(input, output, Kn);
	else  chiffrement(input, output, Kn);

	permutation(output, T2);
	compacter(output, boutput);

		
}

void  atob (unsigned char *bcd_buf, const char *ascii_buf, int len)
{
    int   i;
    char  ch;

    for (i=0; i<len; i++)
    {
	ch = ascii_buf[i];
	if (ch>='a')  ch -= 'a' - 10;
	else if (ch>='A')  ch -= 'A' - 10;
	else ch -= '0';
	if (i & 1)  *(bcd_buf++) |= ch & 0x0f;
	else  *bcd_buf = ch << 4;
    }
}

void  btoa (char *ascii_buf, const unsigned char *bcd_buf, int len)
{
    int   i;
    char  ch;

    for (i=0; i<len; i++)
    {
	if (i & 1)  ch = *(bcd_buf++) & 0x0f;
	else  ch = *bcd_buf >> 4;
	ascii_buf[i] = ch + ((ch > 9)? 'A'-10 : '0');
    }
    ascii_buf[i] = '\0';
}




void  EncryptPIN (unsigned char cipher[], const char plain[], const char pan[], const unsigned char pin_key[])
{
    char  pin[20];
    unsigned char  buf1[8], buf2[8];
    int   i;

    i = strlen(plain);
    buf1[0] = i;
    strcpy(pin, plain);
    for (; i<14; ++i)  pin[i] = 'F';
    atob(buf1+1, pin, 14);
    buf2[0] = buf2[1] = 0x00;
    atob(buf2+2, pan+strlen(pan)-13, 12);
    for (i=0; i<8; ++i)  buf1[i] ^= buf2[i];
    mydes(cipher, buf1, pin_key, 0);
}

void  DecryptPIN (char plain[], const unsigned char cipher[], const char pan[], const unsigned char pin_key[])
{
    unsigned char  buf1[8], buf2[8];
    int   i;

    mydes(buf1, cipher, pin_key, 1);
    buf2[0] = buf2[1] = 0x00;
    atob(buf2+2, pan+strlen(pan)-13, 12);
    for (i=0; i<8; i++)  buf1[i] ^= buf2[i];
    i = buf1[0];
    if (i <= 14)  btoa(plain, buf1+1, i);
    else  plain[0] = '\0';
}




void mydes3(unsigned char *boutput, const unsigned char *binput, const unsigned char *bkey, int direction)
{
	unsigned char tmp_key[9];
	unsigned char tmp_plain[9];
	unsigned char tmp_plain1[9];
	

	memset(tmp_key, 0, sizeof(tmp_key));
	memset(tmp_plain, 0, sizeof(tmp_plain));	
	memset(tmp_plain1, 0, sizeof(tmp_plain1));
	
	if(direction ==0)	//¼ÓÃÜ
	{
		memset(tmp_key, 0, sizeof(tmp_key));
		memset(tmp_plain, 0, sizeof(tmp_plain));
		memcpy(tmp_key, bkey, 8);
		
				
		mydes(tmp_plain, binput, tmp_key, 0);
		memset(tmp_key, 0, sizeof(tmp_key));
		memset(tmp_plain1, 0, sizeof(tmp_plain1));
		memcpy(tmp_key, bkey+8, 8);
		mydes(tmp_plain1, tmp_plain, tmp_key, 1);
		memset(tmp_key, 0, sizeof(tmp_key));
		memcpy(tmp_key, bkey, 8);
		mydes(boutput, tmp_plain1, tmp_key, 0);
	}
	else	//½âÃÜ
	{
		memset(tmp_key, 0, sizeof(tmp_key));
		memset(tmp_plain, 0, sizeof(tmp_plain));
		memcpy(tmp_key, bkey, 8);
		mydes(tmp_plain, binput, tmp_key, 1);
		memset(tmp_key, 0, sizeof(tmp_key));
		memset(tmp_plain1, 0, sizeof(tmp_plain1));
		memcpy(tmp_key, bkey+8, 8);
		mydes(tmp_plain1, tmp_plain, tmp_key, 0);
		memset(tmp_key, 0, sizeof(tmp_key));
		memcpy(tmp_key, bkey, 8);
		mydes(boutput, tmp_plain1, tmp_key, 1);
	}
}


void CalcMAC_ECB(unsigned char * psMac, const unsigned char * psData, int nLen, const unsigned char * psMacKey, int nKeyLen)
{
	int   i;
    unsigned char  m[8];
    
    memset(m, 0, sizeof(m));
    
	for (i=0; i<nLen; i++)
	{
		m[i&7] ^= psData[i];
	}
	
		
	if(nKeyLen == 8)
	{
		mydes( psMac, m, psMacKey, 0 ); 
	}
	else
	{
		mydes3( psMac, m, psMacKey, 0 ); 
	}
		
}

void  EncryptPINExt(unsigned char cipher[], const char plain[], const char pan[], const unsigned char pin_key[], int nKeyLen)
{
    char  pin[20];
    unsigned char  buf1[8], buf2[8];
    int   i;

    i = strlen(plain);
    buf1[0] = i;
    strcpy(pin, plain);
    for (; i<14; ++i)  pin[i] = 'F';
    atob(buf1+1, pin, 14);
    buf2[0] = buf2[1] = 0x00;
    atob(buf2+2, pan+strlen(pan)-13, 12);
    for (i=0; i<8; ++i)  buf1[i] ^= buf2[i];
	if(nKeyLen == 8)
	{
		mydes(cipher, buf1, pin_key, 0);
	}
	else 
	{
		mydes3(cipher, buf1, pin_key, 0);
	}
}

