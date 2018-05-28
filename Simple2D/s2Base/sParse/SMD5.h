/**
 * @file md5.h
 * @The header file of md5.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Oct 19 2014
 *
 */

#ifndef _SMD5_H_
#define _SMD5_H_

/* Parameters of MD5. */
#define MD5_S11 7
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21 5
#define MD5_S22 9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31 4
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41 6
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

/**
 * @Basic MD5 functions.
 *
 * @param there bit32.
 *
 * @return one bit32.
 */
#define MD5_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define MD5_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define MD5_I(x, y, z) ((y) ^ ((x) | (~z)))

/**
 * @Rotate Left.
 *
 * @param {num} the raw number.
 *
 * @param {n} rotate left n.
 *
 * @return the number after rotated left.
 */
#define MD5_ROTATELEFT(num, n) (((num) << (n)) | ((num) >> (32-(n))))

/**
 * @Transformations for rounds 1, 2, 3, and 4.
 */
#define MD5_FF(a, b, c, d, x, s, ac) { \
  (a) += MD5_F ((b), (c), (d)) + (x) + ac; \
  (a) = MD5_ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define MD5_GG(a, b, c, d, x, s, ac) { \
  (a) += MD5_G ((b), (c), (d)) + (x) + ac; \
  (a) = MD5_ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define MD5_HH(a, b, c, d, x, s, ac) { \
  (a) += MD5_H ((b), (c), (d)) + (x) + ac; \
  (a) = MD5_ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define MD5_II(a, b, c, d, x, s, ac) { \
  (a) += MD5_I ((b), (c), (d)) + (x) + ac; \
  (a) = MD5_ROTATELEFT ((a), (s)); \
  (a) += (b); \
}

#include <string>
#include <cstring>

/* Define of btye.*/
//typedef unsigned char byte;
/* Define of byte. */
//typedef unsigned int bit32;
class SMD5 
{
    /* Define of btye.*/
    typedef unsigned char byte;
    /* Define of byte. */
    typedef unsigned int bit32;
public:
  /* Construct a MD5 object with a string. */
  SMD5(const std::string& message);

  /* Generate md5 digest. */
  const byte* GetDigest();

  /* Convert digest to string value */
  std::string ToStr();

private:
  /* Initialization the md5 object, processing another message block,
   * and updating the context.*/
  void init(const byte* input, size_t len);

  /* MD5 basic transformation. Transforms state based on block. */
  void transform(const byte block[64]);

  /* Encodes input (usigned long) into output (byte). */
  void encode(const bit32* input, byte* output, size_t length);

  /* Decodes input (byte) into output (usigned long). */
  void decode(const byte* input, bit32* output, size_t length);

private:
  /* Flag for mark whether calculate finished. */
  bool finished;

    /* state (ABCD). */
  bit32 state[4];

  /* number of bits, low-order word first. */
  bit32 count[2];

  /* input buffer. */
  byte buffer[64];

  /* message digest. */
  byte digest[16];

    /* padding for calculate. */
  static const byte PADDING[64];

  /* Hex numbers. */
  static const char HEX_NUMBERS[16];
};

#endif // _S2MD5_H_
