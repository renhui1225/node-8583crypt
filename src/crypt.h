#ifndef _CRYPT_H_
#define _CRYPT_H_


#define EN0     0       /* MODE == encrypt */
#define DE1     1       /* MODE == decrypt */


extern void  mydes(unsigned char *output, const unsigned char *input, const unsigned char *key, int direction);
extern void  EncryptPIN (unsigned char cipher[], const char plain[], const char pan[], const unsigned char pin_key[]);
extern void  DecryptPIN (char plain[], const unsigned char cipher[], const char pan[], const unsigned char pin_key[]);
extern void  CalcMAC_X99 (char mac[], const char data[], int len, const unsigned char mac_key[]);
extern void  EncryptKey (char cipher[], const unsigned char plain[]);
extern void  DecryptKey (unsigned char plain[], const char cipher[]);
extern void mydes3(unsigned char *boutput, const unsigned char *binput, const unsigned char *bkey, int direction);
extern void CalcMAC_ECB(unsigned char * psMac, const unsigned char * psData, int nLen, const unsigned char * psMacKey, int nKeyLen);
extern void  EncryptPINExt(unsigned char cipher[], const char plain[], const char pan[], const unsigned char pin_key[], int nKeyLen);

#endif

