# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
# 1 "/data/Apparat/MAVR/kentavr-firmware//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Framework/AVR/USB/avr-usb-config.h" 1
# 9 "Framework/AVR/USB/avr-usb-config.h"
# 1 "Framework/Core/oscillator.h" 1
# 10 "Framework/AVR/USB/avr-usb-config.h" 2
# 1 "<command-line>" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
# 33 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 1
# 70 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 1
# 66 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
# 1 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 3 4
# 1 "/usr/lib/avr/include/stdint.h" 1 3 4
# 125 "/usr/lib/avr/include/stdint.h" 3 4

# 125 "/usr/lib/avr/include/stdint.h" 3 4
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 146 "/usr/lib/avr/include/stdint.h" 3 4
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 163 "/usr/lib/avr/include/stdint.h" 3 4
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 217 "/usr/lib/avr/include/stdint.h" 3 4
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 277 "/usr/lib/avr/include/stdint.h" 3 4
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 10 "/usr/lib/gcc/avr/7.3.0/include/stdint.h" 2 3 4
# 67 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/gcc/avr/7.3.0/include/stdbool.h" 1 3 4
# 68 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/string.h" 1 3
# 46 "/usr/lib/avr/include/string.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 216 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef unsigned int size_t;
# 47 "/usr/lib/avr/include/string.h" 2 3
# 125 "/usr/lib/avr/include/string.h" 3
extern int ffs(int __val) __attribute__((__const__));





extern int ffsl(long __val) __attribute__((__const__));





__extension__ extern int ffsll(long long __val) __attribute__((__const__));
# 150 "/usr/lib/avr/include/string.h" 3
extern void *memccpy(void *, const void *, int, size_t);
# 162 "/usr/lib/avr/include/string.h" 3
extern void *memchr(const void *, int, size_t) __attribute__((__pure__));
# 180 "/usr/lib/avr/include/string.h" 3
extern int memcmp(const void *, const void *, size_t) __attribute__((__pure__));
# 191 "/usr/lib/avr/include/string.h" 3
extern void *memcpy(void *, const void *, size_t);
# 203 "/usr/lib/avr/include/string.h" 3
extern void *memmem(const void *, size_t, const void *, size_t) __attribute__((__pure__));
# 213 "/usr/lib/avr/include/string.h" 3
extern void *memmove(void *, const void *, size_t);
# 225 "/usr/lib/avr/include/string.h" 3
extern void *memrchr(const void *, int, size_t) __attribute__((__pure__));
# 235 "/usr/lib/avr/include/string.h" 3
extern void *memset(void *, int, size_t);
# 248 "/usr/lib/avr/include/string.h" 3
extern char *strcat(char *, const char *);
# 262 "/usr/lib/avr/include/string.h" 3
extern char *strchr(const char *, int) __attribute__((__pure__));
# 274 "/usr/lib/avr/include/string.h" 3
extern char *strchrnul(const char *, int) __attribute__((__pure__));
# 287 "/usr/lib/avr/include/string.h" 3
extern int strcmp(const char *, const char *) __attribute__((__pure__));
# 305 "/usr/lib/avr/include/string.h" 3
extern char *strcpy(char *, const char *);
# 320 "/usr/lib/avr/include/string.h" 3
extern int strcasecmp(const char *, const char *) __attribute__((__pure__));
# 333 "/usr/lib/avr/include/string.h" 3
extern char *strcasestr(const char *, const char *) __attribute__((__pure__));
# 344 "/usr/lib/avr/include/string.h" 3
extern size_t strcspn(const char *__s, const char *__reject) __attribute__((__pure__));
# 364 "/usr/lib/avr/include/string.h" 3
extern char *strdup(const char *s1);
# 377 "/usr/lib/avr/include/string.h" 3
extern size_t strlcat(char *, const char *, size_t);
# 388 "/usr/lib/avr/include/string.h" 3
extern size_t strlcpy(char *, const char *, size_t);
# 399 "/usr/lib/avr/include/string.h" 3
extern size_t strlen(const char *) __attribute__((__pure__));
# 411 "/usr/lib/avr/include/string.h" 3
extern char *strlwr(char *);
# 422 "/usr/lib/avr/include/string.h" 3
extern char *strncat(char *, const char *, size_t);
# 434 "/usr/lib/avr/include/string.h" 3
extern int strncmp(const char *, const char *, size_t) __attribute__((__pure__));
# 449 "/usr/lib/avr/include/string.h" 3
extern char *strncpy(char *, const char *, size_t);
# 464 "/usr/lib/avr/include/string.h" 3
extern int strncasecmp(const char *, const char *, size_t) __attribute__((__pure__));
# 478 "/usr/lib/avr/include/string.h" 3
extern size_t strnlen(const char *, size_t) __attribute__((__pure__));
# 491 "/usr/lib/avr/include/string.h" 3
extern char *strpbrk(const char *__s, const char *__accept) __attribute__((__pure__));
# 505 "/usr/lib/avr/include/string.h" 3
extern char *strrchr(const char *, int) __attribute__((__pure__));
# 515 "/usr/lib/avr/include/string.h" 3
extern char *strrev(char *);
# 533 "/usr/lib/avr/include/string.h" 3
extern char *strsep(char **, const char *);
# 544 "/usr/lib/avr/include/string.h" 3
extern size_t strspn(const char *__s, const char *__accept) __attribute__((__pure__));
# 557 "/usr/lib/avr/include/string.h" 3
extern char *strstr(const char *, const char *) __attribute__((__pure__));
# 576 "/usr/lib/avr/include/string.h" 3
extern char *strtok(char *, const char *);
# 593 "/usr/lib/avr/include/string.h" 3
extern char *strtok_r(char *, const char *, char **);
# 606 "/usr/lib/avr/include/string.h" 3
extern char *strupr(char *);



extern int strcoll(const char *s1, const char *s2);
extern char *strerror(int errnum);
extern size_t strxfrm(char *dest, const char *src, size_t n);
# 69 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 328 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef int wchar_t;
# 426 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 437 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 3 4
} max_align_t;
# 70 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2

# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Architectures.h" 1
# 72 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/BoardTypes.h" 1
# 73 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/ArchitectureSpecific.h" 1
# 74 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/CompilerSpecific.h" 1
# 75 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Attributes.h" 1
# 76 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
# 1 "/usr/lib/avr/include/avr/io.h" 1 3
# 99 "/usr/lib/avr/include/avr/io.h" 3
# 1 "/usr/lib/avr/include/avr/sfr_defs.h" 1 3
# 126 "/usr/lib/avr/include/avr/sfr_defs.h" 3
# 1 "/usr/lib/avr/include/inttypes.h" 1 3
# 77 "/usr/lib/avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;



typedef uint32_t uint_farptr_t;
# 127 "/usr/lib/avr/include/avr/sfr_defs.h" 2 3
# 100 "/usr/lib/avr/include/avr/io.h" 2 3
# 144 "/usr/lib/avr/include/avr/io.h" 3
# 1 "/usr/lib/avr/include/avr/iom32u4.h" 1 3
# 145 "/usr/lib/avr/include/avr/io.h" 2 3
# 627 "/usr/lib/avr/include/avr/io.h" 3
# 1 "/usr/lib/avr/include/avr/portpins.h" 1 3
# 628 "/usr/lib/avr/include/avr/io.h" 2 3

# 1 "/usr/lib/avr/include/avr/common.h" 1 3
# 630 "/usr/lib/avr/include/avr/io.h" 2 3

# 1 "/usr/lib/avr/include/avr/version.h" 1 3
# 632 "/usr/lib/avr/include/avr/io.h" 2 3






# 1 "/usr/lib/avr/include/avr/fuse.h" 1 3
# 239 "/usr/lib/avr/include/avr/fuse.h" 3
typedef struct
{
    unsigned char low;
    unsigned char high;
    unsigned char extended;
} __fuse_t;
# 639 "/usr/lib/avr/include/avr/io.h" 2 3


# 1 "/usr/lib/avr/include/avr/lock.h" 1 3
# 642 "/usr/lib/avr/include/avr/io.h" 2 3
# 95 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/interrupt.h" 1 3
# 96 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/pgmspace.h" 1 3
# 89 "/usr/lib/avr/include/avr/pgmspace.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 90 "/usr/lib/avr/include/avr/pgmspace.h" 2 3
# 1158 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern const void * memchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
# 1172 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int memcmp_P(const void *, const void *, size_t) __attribute__((__pure__));






extern void *memccpy_P(void *, const void *, int __val, size_t);
# 1188 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern void *memcpy_P(void *, const void *, size_t);






extern void *memmem_P(const void *, size_t, const void *, size_t) __attribute__((__pure__));
# 1207 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern const void * memrchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
# 1217 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strcat_P(char *, const char *);
# 1233 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern const char * strchr_P(const char *, int __val) __attribute__((__const__));
# 1245 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern const char * strchrnul_P(const char *, int __val) __attribute__((__const__));
# 1258 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strcmp_P(const char *, const char *) __attribute__((__pure__));
# 1268 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strcpy_P(char *, const char *);
# 1285 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strcasecmp_P(const char *, const char *) __attribute__((__pure__));






extern char *strcasestr_P(const char *, const char *) __attribute__((__pure__));
# 1305 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strcspn_P(const char *__s, const char * __reject) __attribute__((__pure__));
# 1321 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strlcat_P (char *, const char *, size_t );
# 1334 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strlcpy_P (char *, const char *, size_t );
# 1346 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strnlen_P(const char *, size_t) __attribute__((__const__));
# 1357 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strncmp_P(const char *, const char *, size_t) __attribute__((__pure__));
# 1376 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strncasecmp_P(const char *, const char *, size_t) __attribute__((__pure__));
# 1387 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strncat_P(char *, const char *, size_t);
# 1401 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strncpy_P(char *, const char *, size_t);
# 1416 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strpbrk_P(const char *__s, const char * __accept) __attribute__((__pure__));
# 1427 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern const char * strrchr_P(const char *, int __val) __attribute__((__const__));
# 1447 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strsep_P(char **__sp, const char * __delim);
# 1460 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strspn_P(const char *__s, const char * __accept) __attribute__((__pure__));
# 1474 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strstr_P(const char *, const char *) __attribute__((__pure__));
# 1496 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strtok_P(char *__s, const char * __delim);
# 1516 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strtok_rP(char *__s, const char * __delim, char **__last);
# 1529 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strlen_PF(uint_farptr_t src) __attribute__((__const__));
# 1545 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strnlen_PF(uint_farptr_t src, size_t len) __attribute__((__const__));
# 1560 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern void *memcpy_PF(void *dest, uint_farptr_t src, size_t len);
# 1575 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strcpy_PF(char *dest, uint_farptr_t src);
# 1595 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strncpy_PF(char *dest, uint_farptr_t src, size_t len);
# 1611 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strcat_PF(char *dest, uint_farptr_t src);
# 1632 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strlcat_PF(char *dst, uint_farptr_t src, size_t siz);
# 1649 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strncat_PF(char *dest, uint_farptr_t src, size_t len);
# 1665 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strcmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
# 1682 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
# 1698 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strcasecmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
# 1716 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
# 1732 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern char *strstr_PF(const char *s1, uint_farptr_t s2);
# 1744 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz);
# 1760 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern int memcmp_PF(const void *, uint_farptr_t, size_t) __attribute__((__pure__));
# 1779 "/usr/lib/avr/include/avr/pgmspace.h" 3
extern size_t __strlen_P(const char *) __attribute__((__const__));
__attribute__((__always_inline__)) static __inline__ size_t strlen_P(const char * s);
static __inline__ size_t strlen_P(const char *s) {
  return __builtin_constant_p(__builtin_strlen(s))
     ? __builtin_strlen(s) : __strlen_P(s);
}
# 97 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/eeprom.h" 1 3
# 57 "/usr/lib/avr/include/avr/eeprom.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include/stddef.h" 1 3 4
# 58 "/usr/lib/avr/include/avr/eeprom.h" 2 3
# 146 "/usr/lib/avr/include/avr/eeprom.h" 3
uint8_t eeprom_read_byte (const uint8_t *__p) __attribute__((__pure__));




uint16_t eeprom_read_word (const uint16_t *__p) __attribute__((__pure__));




uint32_t eeprom_read_dword (const uint32_t *__p) __attribute__((__pure__));




float eeprom_read_float (const float *__p) __attribute__((__pure__));





void eeprom_read_block (void *__dst, const void *__src, size_t __n);





void eeprom_write_byte (uint8_t *__p, uint8_t __value);




void eeprom_write_word (uint16_t *__p, uint16_t __value);




void eeprom_write_dword (uint32_t *__p, uint32_t __value);




void eeprom_write_float (float *__p, float __value);





void eeprom_write_block (const void *__src, void *__dst, size_t __n);





void eeprom_update_byte (uint8_t *__p, uint8_t __value);




void eeprom_update_word (uint16_t *__p, uint16_t __value);




void eeprom_update_dword (uint32_t *__p, uint32_t __value);




void eeprom_update_float (float *__p, float __value);





void eeprom_update_block (const void *__src, void *__dst, size_t __n);
# 98 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/boot.h" 1 3
# 107 "/usr/lib/avr/include/avr/boot.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include-fixed/limits.h" 1 3 4
# 108 "/usr/lib/avr/include/avr/boot.h" 2 3
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/math.h" 1 3
# 127 "/usr/lib/avr/include/math.h" 3
extern double cos(double __x) __attribute__((__const__));





extern double sin(double __x) __attribute__((__const__));





extern double tan(double __x) __attribute__((__const__));






extern double fabs(double __x) __attribute__((__const__));






extern double fmod(double __x, double __y) __attribute__((__const__));
# 168 "/usr/lib/avr/include/math.h" 3
extern double modf(double __x, double *__iptr);


extern float modff (float __x, float *__iptr);




extern double sqrt(double __x) __attribute__((__const__));


extern float sqrtf (float) __attribute__((__const__));




extern double cbrt(double __x) __attribute__((__const__));
# 195 "/usr/lib/avr/include/math.h" 3
extern double hypot (double __x, double __y) __attribute__((__const__));







extern double square(double __x) __attribute__((__const__));






extern double floor(double __x) __attribute__((__const__));






extern double ceil(double __x) __attribute__((__const__));
# 235 "/usr/lib/avr/include/math.h" 3
extern double frexp(double __x, int *__pexp);







extern double ldexp(double __x, int __exp) __attribute__((__const__));





extern double exp(double __x) __attribute__((__const__));





extern double cosh(double __x) __attribute__((__const__));





extern double sinh(double __x) __attribute__((__const__));





extern double tanh(double __x) __attribute__((__const__));







extern double acos(double __x) __attribute__((__const__));







extern double asin(double __x) __attribute__((__const__));






extern double atan(double __x) __attribute__((__const__));
# 299 "/usr/lib/avr/include/math.h" 3
extern double atan2(double __y, double __x) __attribute__((__const__));





extern double log(double __x) __attribute__((__const__));





extern double log10(double __x) __attribute__((__const__));





extern double pow(double __x, double __y) __attribute__((__const__));






extern int isnan(double __x) __attribute__((__const__));
# 334 "/usr/lib/avr/include/math.h" 3
extern int isinf(double __x) __attribute__((__const__));






__attribute__((__const__)) static inline int isfinite (double __x)
{
    unsigned char __exp;
    __asm__ (
 "mov	%0, %C1		\n\t"
 "lsl	%0		\n\t"
 "mov	%0, %D1		\n\t"
 "rol	%0		"
 : "=r" (__exp)
 : "r" (__x) );
    return __exp != 0xff;
}






__attribute__((__const__)) static inline double copysign (double __x, double __y)
{
    __asm__ (
 "bst	%D2, 7	\n\t"
 "bld	%D0, 7	"
 : "=r" (__x)
 : "0" (__x), "r" (__y) );
    return __x;
}
# 377 "/usr/lib/avr/include/math.h" 3
extern int signbit (double __x) __attribute__((__const__));






extern double fdim (double __x, double __y) __attribute__((__const__));
# 393 "/usr/lib/avr/include/math.h" 3
extern double fma (double __x, double __y, double __z) __attribute__((__const__));







extern double fmax (double __x, double __y) __attribute__((__const__));







extern double fmin (double __x, double __y) __attribute__((__const__));






extern double trunc (double __x) __attribute__((__const__));
# 427 "/usr/lib/avr/include/math.h" 3
extern double round (double __x) __attribute__((__const__));
# 440 "/usr/lib/avr/include/math.h" 3
extern long lround (double __x) __attribute__((__const__));
# 454 "/usr/lib/avr/include/math.h" 3
extern long lrint (double __x) __attribute__((__const__));
# 100 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/util/delay.h" 1 3
# 45 "/usr/lib/avr/include/util/delay.h" 3
# 1 "/usr/lib/avr/include/util/delay_basic.h" 1 3
# 40 "/usr/lib/avr/include/util/delay_basic.h" 3
static __inline__ void _delay_loop_1(uint8_t __count) __attribute__((__always_inline__));
static __inline__ void _delay_loop_2(uint16_t __count) __attribute__((__always_inline__));
# 80 "/usr/lib/avr/include/util/delay_basic.h" 3
void
_delay_loop_1(uint8_t __count)
{
 __asm__ volatile (
  "1: dec %0" "\n\t"
  "brne 1b"
  : "=r" (__count)
  : "0" (__count)
 );
}
# 102 "/usr/lib/avr/include/util/delay_basic.h" 3
void
_delay_loop_2(uint16_t __count)
{
 __asm__ volatile (
  "1: sbiw %0,1" "\n\t"
  "brne 1b"
  : "=w" (__count)
  : "0" (__count)
 );
}
# 46 "/usr/lib/avr/include/util/delay.h" 2 3
# 86 "/usr/lib/avr/include/util/delay.h" 3
static __inline__ void _delay_us(double __us) __attribute__((__always_inline__));
static __inline__ void _delay_ms(double __ms) __attribute__((__always_inline__));
# 165 "/usr/lib/avr/include/util/delay.h" 3
void
_delay_ms(double __ms)
{
 double __tmp ;



 uint32_t __ticks_dc;
 extern void __builtin_avr_delay_cycles(unsigned long);
 __tmp = ((
# 174 "/usr/lib/avr/include/util/delay.h"
          16000000UL
# 174 "/usr/lib/avr/include/util/delay.h" 3
               ) / 1e3) * __ms;
# 184 "/usr/lib/avr/include/util/delay.h" 3
  __ticks_dc = (uint32_t)(ceil(fabs(__tmp)));


 __builtin_avr_delay_cycles(__ticks_dc);
# 210 "/usr/lib/avr/include/util/delay.h" 3
}
# 254 "/usr/lib/avr/include/util/delay.h" 3
void
_delay_us(double __us)
{
 double __tmp ;



 uint32_t __ticks_dc;
 extern void __builtin_avr_delay_cycles(unsigned long);
 __tmp = ((
# 263 "/usr/lib/avr/include/util/delay.h"
          16000000UL
# 263 "/usr/lib/avr/include/util/delay.h" 3
               ) / 1e6) * __us;
# 273 "/usr/lib/avr/include/util/delay.h" 3
  __ticks_dc = (uint32_t)(ceil(fabs(__tmp)));


 __builtin_avr_delay_cycles(__ticks_dc);
# 299 "/usr/lib/avr/include/util/delay.h" 3
}
# 101 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2

   
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
  typedef uint8_t uint_reg_t;






# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Endianness.h" 1
# 400 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Endianness.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((const)) __attribute__ ((always_inline))
   static inline uint16_t SwapEndian_16(const uint16_t Word)
   {
    if (__builtin_constant_p(Word))
      return (uint16_t)((((Word) & 0xFF00) >> 8) | (((Word) & 0x00FF) << 8));

    uint8_t Temp;

    union
    {
     uint16_t Word;
     uint8_t Bytes[2];
    } Data;

    Data.Word = Word;

    Temp = Data.Bytes[0];
    Data.Bytes[0] = Data.Bytes[1];
    Data.Bytes[1] = Temp;

    return Data.Word;
   }
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Endianness.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((const)) __attribute__ ((always_inline))
   static inline uint32_t SwapEndian_32(const uint32_t DWord)
   {
    if (__builtin_constant_p(DWord))
      return (uint32_t)((((DWord) & 0xFF000000UL) >> 24UL) | (((DWord) & 0x00FF0000UL) >> 8UL) | (((DWord) & 0x0000FF00UL) << 8UL) | (((DWord) & 0x000000FFUL) << 24UL));

    uint8_t Temp;

    union
    {
     uint32_t DWord;
     uint8_t Bytes[4];
    } Data;

    Data.DWord = DWord;

    Temp = Data.Bytes[0];
    Data.Bytes[0] = Data.Bytes[3];
    Data.Bytes[3] = Temp;

    Temp = Data.Bytes[1];
    Data.Bytes[1] = Data.Bytes[2];
    Data.Bytes[2] = Temp;

    return Data.DWord;
   }
# 465 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Endianness.h"
   __attribute__ ((nonnull (1)))
   static inline void SwapEndian_n(void* const Data,
                                   uint8_t Length)
   {
    uint8_t* CurrDataPos = (uint8_t*)Data;

    while (Length > 1)
    {
     uint8_t Temp = *CurrDataPos;
     *CurrDataPos = *(CurrDataPos + Length - 1);
     *(CurrDataPos + Length - 1) = Temp;

     CurrDataPos++;
     Length -= 2;
    }
   }
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 2
# 249 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((const))
   static inline uint8_t BitReverse(uint8_t Byte)
   {
    Byte = (((Byte & 0xF0) >> 4) | ((Byte & 0x0F) << 4));
    Byte = (((Byte & 0xCC) >> 2) | ((Byte & 0x33) << 2));
    Byte = (((Byte & 0xAA) >> 1) | ((Byte & 0x55) << 1));

    return Byte;
   }







   __attribute__ ((always_inline))
   static inline void Delay_MS(uint16_t Milliseconds)
   {

    if (__builtin_constant_p(Milliseconds))
    {
     _delay_ms(Milliseconds);
    }
    else
    {
     while (Milliseconds--)
       _delay_ms(1);
    }
# 295 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
   }
# 305 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline uint_reg_t GetGlobalInterruptMask(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    return 
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 3
          (*(volatile uint8_t *)((0x3F) + 0x20))
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
              ;





   }
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
   __attribute__ ((always_inline))
   static inline void SetGlobalInterruptMask(const uint_reg_t GlobalIntState)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 333 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 3
   (*(volatile uint8_t *)((0x3F) + 0x20)) 
# 333 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
        = GlobalIntState;
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
    __asm__ __volatile__("" ::: "memory");;
   }





   __attribute__ ((always_inline))
   static inline void GlobalInterruptEnable(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 356 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 3
   __asm__ __volatile__ ("sei" ::: "memory")
# 356 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
        ;






    __asm__ __volatile__("" ::: "memory");;
   }





   __attribute__ ((always_inline))
   static inline void GlobalInterruptDisable(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h" 3
   __asm__ __volatile__ ("cli" ::: "memory")
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../../../Common/Common.h"
        ;






    __asm__ __volatile__("" ::: "memory");;
   }
# 71 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 2

# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDReportData.h" 1
# 73 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h" 1
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h" 1
# 53 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/../../../Common/Common.h" 1
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/USBMode.h" 1
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h" 1
# 89 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_UIDChange(void);
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
# 117 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_DeviceAttached(void);
# 131 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_DeviceUnattached(void);
# 149 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                               const uint8_t SubErrorCode);
# 166 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_DeviceEnumerationComplete(void);
# 183 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Host_StartOfFrame(void);
# 205 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_Connect(void);
# 223 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_Disconnect(void);
# 249 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_ControlRequest(void);
# 263 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_ConfigurationChanged(void);
# 281 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_Suspend(void);
# 299 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_WakeUp(void);
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_Reset(void);
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/Events.h"
   void EVENT_USB_Device_StartOfFrame(void);
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h" 2
# 207 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   enum USB_DescriptorTypes_t
   {
    DTYPE_Device = 0x01,
    DTYPE_Configuration = 0x02,
    DTYPE_String = 0x03,
    DTYPE_Interface = 0x04,
    DTYPE_Endpoint = 0x05,
    DTYPE_DeviceQualifier = 0x06,
    DTYPE_Other = 0x07,
    DTYPE_InterfacePower = 0x08,
    DTYPE_InterfaceAssociation = 0x0B,
   };


   enum USB_Descriptor_ClassSubclassProtocol_t
   {
    USB_CSCP_NoDeviceClass = 0x00,


    USB_CSCP_NoDeviceSubclass = 0x00,


    USB_CSCP_NoDeviceProtocol = 0x00,


    USB_CSCP_VendorSpecificClass = 0xFF,


    USB_CSCP_VendorSpecificSubclass = 0xFF,


    USB_CSCP_VendorSpecificProtocol = 0xFF,


    USB_CSCP_IADDeviceClass = 0xEF,


    USB_CSCP_IADDeviceSubclass = 0x02,


    USB_CSCP_IADDeviceProtocol = 0x01,


   };
# 262 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t Size;
    uint8_t Type;


   } __attribute__ ((packed)) USB_Descriptor_Header_t;
# 279 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


   } __attribute__ ((packed)) USB_StdDescriptor_Header_t;
# 296 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint16_t USBSpecification;



    uint8_t Class;
    uint8_t SubClass;
    uint8_t Protocol;

    uint8_t Endpoint0Size;

    uint16_t VendorID;
    uint16_t ProductID;
    uint16_t ReleaseNumber;



    uint8_t ManufacturerStrIndex;





    uint8_t ProductStrIndex;



    uint8_t SerialNumStrIndex;
# 338 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
    uint8_t NumberOfConfigurations;


   } __attribute__ ((packed)) USB_Descriptor_Device_t;
# 352 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint16_t bcdUSB;



    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;



    uint8_t iManufacturer;





    uint8_t iProduct;



    uint8_t iSerialNumber;
# 394 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
    uint8_t bNumConfigurations;


   } __attribute__ ((packed)) USB_StdDescriptor_Device_t;
# 406 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint16_t USBSpecification;



    uint8_t Class;
    uint8_t SubClass;
    uint8_t Protocol;

    uint8_t Endpoint0Size;
    uint8_t NumberOfConfigurations;


    uint8_t Reserved;
   } __attribute__ ((packed)) USB_Descriptor_DeviceQualifier_t;
# 432 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint16_t bcdUSB;



    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint8_t bNumConfigurations;


    uint8_t bReserved;
   } __attribute__ ((packed)) USB_StdDescriptor_DeviceQualifier_t;
# 461 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint16_t TotalConfigurationSize;


    uint8_t TotalInterfaces;

    uint8_t ConfigurationNumber;
    uint8_t ConfigurationStrIndex;

    uint8_t ConfigAttributes;



    uint8_t MaxPowerConsumption;



   } __attribute__ ((packed)) USB_Descriptor_Configuration_Header_t;
# 492 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint16_t wTotalLength;


    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;


    uint8_t bMaxPower;



   } __attribute__ ((packed)) USB_StdDescriptor_Configuration_Header_t;
# 522 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint8_t InterfaceNumber;
    uint8_t AlternateSetting;




    uint8_t TotalEndpoints;

    uint8_t Class;
    uint8_t SubClass;
    uint8_t Protocol;

    uint8_t InterfaceStrIndex;
   } __attribute__ ((packed)) USB_Descriptor_Interface_t;
# 550 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;




    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;


   } __attribute__ ((packed)) USB_StdDescriptor_Interface_t;
# 586 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint8_t FirstInterfaceIndex;
    uint8_t TotalInterfaces;

    uint8_t Class;
    uint8_t SubClass;
    uint8_t Protocol;

    uint8_t IADStrIndex;


   } __attribute__ ((packed)) USB_Descriptor_Interface_Association_t;
# 618 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;


   } __attribute__ ((packed)) USB_StdDescriptor_Interface_Association_t;
# 643 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint8_t EndpointAddress;


    uint8_t Attributes;


    uint16_t EndpointSize;


    uint8_t PollingIntervalMS;


   } __attribute__ ((packed)) USB_Descriptor_Endpoint_t;
# 671 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint8_t bEndpointAddress;


    uint8_t bmAttributes;


    uint16_t wMaxPacketSize;


    uint8_t bInterval;


   } __attribute__ ((packed)) USB_StdDescriptor_Endpoint_t;
# 706 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;


    wchar_t UnicodeString[];
# 726 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   } __attribute__ ((packed)) USB_Descriptor_String_t;
# 744 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint16_t bString[];
# 759 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/../../Core/StdDescriptors.h"
   } __attribute__ ((packed)) USB_StdDescriptor_String_t;
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 1
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h" 2
# 546 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h"
  enum HID_Descriptor_ClassSubclassProtocol_t
  {
   HID_CSCP_HIDClass = 0x03,


   HID_CSCP_NonBootSubclass = 0x00,


   HID_CSCP_BootSubclass = 0x01,


   HID_CSCP_NonBootProtocol = 0x00,


   HID_CSCP_KeyboardBootProtocol = 0x01,


   HID_CSCP_MouseBootProtocol = 0x02,


  };


  enum HID_ClassRequests_t
  {
   HID_REQ_GetReport = 0x01,
   HID_REQ_GetIdle = 0x02,
   HID_REQ_GetProtocol = 0x03,
   HID_REQ_SetReport = 0x09,
   HID_REQ_SetIdle = 0x0A,
   HID_REQ_SetProtocol = 0x0B,
  };


  enum HID_DescriptorTypes_t
  {
   HID_DTYPE_HID = 0x21,
   HID_DTYPE_Report = 0x22,
  };


  enum HID_ReportItemTypes_t
  {
   HID_REPORT_ITEM_In = 0,
   HID_REPORT_ITEM_Out = 1,
   HID_REPORT_ITEM_Feature = 2,
  };
# 603 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h"
  typedef struct
  {
   USB_Descriptor_Header_t Header;

   uint16_t HIDSpec;



   uint8_t CountryCode;

   uint8_t TotalReportDescriptors;

   uint8_t HIDReportType;
   uint16_t HIDReportLength;
  } __attribute__ ((packed)) USB_HID_Descriptor_HID_t;
# 629 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h"
  typedef struct
  {
   uint8_t bLength;
   uint8_t bDescriptorType;



   uint16_t bcdHID;



   uint8_t bCountryCode;

   uint8_t bNumDescriptors;

   uint8_t bDescriptorType2;
   uint16_t wDescriptorLength;
  } __attribute__ ((packed)) USB_HID_StdDescriptor_HID_t;





  typedef struct
  {
   uint8_t Button;
   int8_t X;
   int8_t Y;
  } __attribute__ ((packed)) USB_MouseReport_Data_t;





  typedef struct
  {
   uint8_t Modifier;


   uint8_t Reserved;
   uint8_t KeyCode[6];
  } __attribute__ ((packed)) USB_KeyboardReport_Data_t;


  typedef uint8_t USB_Descriptor_HIDReport_Datatype_t;
# 74 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 2
# 147 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   enum HID_Parse_ErrorCodes_t
   {
    HID_PARSE_Successful = 0,
    HID_PARSE_HIDStackOverflow = 1,
    HID_PARSE_HIDStackUnderflow = 2,
    HID_PARSE_InsufficientReportItems = 3,
    HID_PARSE_UnexpectedEndCollection = 4,
    HID_PARSE_InsufficientCollectionPaths = 5,
    HID_PARSE_UsageListOverflow = 6,
    HID_PARSE_InsufficientReportIDItems = 7,
    HID_PARSE_NoUnfilteredReportItems = 8,
   };






   typedef struct
   {
    uint32_t Minimum;
    uint32_t Maximum;
   } HID_MinMax_t;





   typedef struct
   {
    uint32_t Type;
    uint8_t Exponent;
   } HID_Unit_t;





   typedef struct
   {
    uint16_t Page;
    uint16_t Usage;
   } HID_Usage_t;






   typedef struct HID_CollectionPath
   {
    uint8_t Type;
    HID_Usage_t Usage;
    struct HID_CollectionPath* Parent;
   } HID_CollectionPath_t;





   typedef struct
   {
    uint8_t BitSize;

    HID_Usage_t Usage;
    HID_Unit_t Unit;
    HID_MinMax_t Logical;
    HID_MinMax_t Physical;
   } HID_ReportItem_Attributes_t;





   typedef struct
   {
    uint16_t BitOffset;
    uint8_t ItemType;
    uint16_t ItemFlags;
    uint8_t ReportID;
    HID_CollectionPath_t* CollectionPath;

    HID_ReportItem_Attributes_t Attributes;

    uint32_t Value;


    uint32_t PreviousValue;
   } HID_ReportItem_t;





   typedef struct
   {
    uint8_t ReportID;
    uint16_t ReportSizeBits[3];


   } HID_ReportSizeInfo_t;





   typedef struct
   {
    uint8_t TotalReportItems;
    HID_ReportItem_t ReportItems[20];


    HID_CollectionPath_t CollectionPaths[10];


    uint8_t TotalDeviceReports;
    HID_ReportSizeInfo_t ReportIDSizes[10];
    uint16_t LargestReportSizeBits;
    
# 265 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 3 4
   _Bool 
# 265 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
                        UsingReportIDs;


   } HID_ReportInfo_t;
# 280 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   uint8_t USB_ProcessHIDReport(const uint8_t* ReportData,
                                uint16_t ReportSize,
                                HID_ReportInfo_t* const ParserData) __attribute__ ((nonnull (1))) __attribute__ ((nonnull (3)));
# 297 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   
# 297 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 3 4
  _Bool 
# 297 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
       USB_GetHIDReportItemInfo(const uint8_t* ReportData,
                                 HID_ReportItem_t* const ReportItem) __attribute__ ((nonnull (1)));
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   void USB_SetHIDReportItemInfo(uint8_t* ReportData,
                                 HID_ReportItem_t* const ReportItem) __attribute__ ((nonnull (1)));
# 325 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   uint16_t USB_GetHIDReportSize(HID_ReportInfo_t* const ParserData,
                                 const uint8_t ReportID,
                                 const uint8_t ReportType) __attribute__ ((const)) __attribute__ ((nonnull (1)));
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
   
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h" 3 4
  _Bool 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.h"
       CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* const CurrentItem);




   typedef struct
   {
     HID_ReportItem_Attributes_t Attributes;
     uint8_t ReportCount;
     uint8_t ReportID;
   } HID_StateTable_t;
# 34 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 2

uint8_t USB_ProcessHIDReport(const uint8_t* ReportData,
                             uint16_t ReportSize,
                             HID_ReportInfo_t* const ParserData)
{
 HID_StateTable_t StateTable[2];
 HID_StateTable_t* CurrStateTable = &StateTable[0];
 HID_CollectionPath_t* CurrCollectionPath = 
# 41 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                                           ((void *)0)
# 41 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                               ;
 HID_ReportSizeInfo_t* CurrReportIDInfo = &ParserData->ReportIDSizes[0];
 uint16_t UsageList[8];
 uint8_t UsageListSize = 0;
 HID_MinMax_t UsageMinMax = {0, 0};

 memset(ParserData, 0x00, sizeof(HID_ReportInfo_t));
 memset(CurrStateTable, 0x00, sizeof(HID_StateTable_t));
 memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));

 ParserData->TotalDeviceReports = 1;

 while (ReportSize)
 {
  uint8_t HIDReportItem = *ReportData;
  uint32_t ReportItemData;

  ReportData++;
  ReportSize--;

  switch (HIDReportItem & 0x03)
  {
   case 0x03:
    ReportItemData = (((uint32_t)ReportData[3] << 24) | ((uint32_t)ReportData[2] << 16) |
                          ((uint16_t)ReportData[1] << 8) | ReportData[0]);
    ReportSize -= 4;
    ReportData += 4;
    break;

   case 0x02:
    ReportItemData = (((uint16_t)ReportData[1] << 8) | (ReportData[0]));
    ReportSize -= 2;
    ReportData += 2;
    break;

   case 0x01:
    ReportItemData = ReportData[0];
    ReportSize -= 1;
    ReportData += 1;
    break;

   default:
    ReportItemData = 0;
    break;
  }

  switch (HIDReportItem & (0x0C | 0xF0))
  {
   case (0x04 | 0xA0 | 0x00) :
    if (CurrStateTable == &StateTable[2 - 1])
      return HID_PARSE_HIDStackOverflow;

    memcpy((CurrStateTable + 1),
           CurrStateTable,
           sizeof(HID_StateTable_t));

    CurrStateTable++;
    break;

   case (0x04 | 0xB0 | 0x00) :
    if (CurrStateTable == &StateTable[0])
      return HID_PARSE_HIDStackUnderflow;

    CurrStateTable--;
    break;

   case (0x04 | 0x00 | 0x00) :
    CurrStateTable->Attributes.Usage.Page = ReportItemData;
    break;

   case (0x04 | 0x10 | 0x00) :
    CurrStateTable->Attributes.Logical.Minimum = ReportItemData;
    break;

   case (0x04 | 0x20 | 0x00) :
    CurrStateTable->Attributes.Logical.Maximum = ReportItemData;
    break;

   case (0x04 | 0x30 | 0x00) :
    CurrStateTable->Attributes.Physical.Minimum = ReportItemData;
    break;

   case (0x04 | 0x40 | 0x00) :
    CurrStateTable->Attributes.Physical.Maximum = ReportItemData;
    break;

   case (0x04 | 0x50 | 0x00) :
    CurrStateTable->Attributes.Unit.Exponent = ReportItemData;
    break;

   case (0x04 | 0x60 | 0x00) :
    CurrStateTable->Attributes.Unit.Type = ReportItemData;
    break;

   case (0x04 | 0x70 | 0x00) :
    CurrStateTable->Attributes.BitSize = ReportItemData;
    break;

   case (0x04 | 0x90 | 0x00) :
    CurrStateTable->ReportCount = ReportItemData;
    break;

   case (0x04 | 0x80 | 0x00) :
    CurrStateTable->ReportID = ReportItemData;

    if (ParserData->UsingReportIDs)
    {
     CurrReportIDInfo = 
# 148 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                       ((void *)0)
# 148 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                           ;

     for (uint8_t i = 0; i < ParserData->TotalDeviceReports; i++)
     {
      if (ParserData->ReportIDSizes[i].ReportID == CurrStateTable->ReportID)
      {
       CurrReportIDInfo = &ParserData->ReportIDSizes[i];
       break;
      }
     }

     if (CurrReportIDInfo == 
# 159 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                            ((void *)0)
# 159 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                )
     {
      if (ParserData->TotalDeviceReports == 10)
        return HID_PARSE_InsufficientReportIDItems;

      CurrReportIDInfo = &ParserData->ReportIDSizes[ParserData->TotalDeviceReports++];
      memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));
     }
    }

    ParserData->UsingReportIDs = 
# 169 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                                1
# 169 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                    ;

    CurrReportIDInfo->ReportID = CurrStateTable->ReportID;
    break;

   case (0x08 | 0x00 | 0x00) :
    if (UsageListSize == 8)
      return HID_PARSE_UsageListOverflow;

    if ((HIDReportItem & 0x03) == 0x03)
      CurrStateTable->Attributes.Usage.Page = (ReportItemData >> 16);

    UsageList[UsageListSize++] = ReportItemData;
    break;

   case (0x08 | 0x10 | 0x00) :
    UsageMinMax.Minimum = ReportItemData;
    break;

   case (0x08 | 0x20 | 0x00) :
    UsageMinMax.Maximum = ReportItemData;
    break;

   case (0x00 | 0xA0 | 0x00) :
    if (CurrCollectionPath == 
# 193 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                             ((void *)0)
# 193 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                 )
    {
     CurrCollectionPath = &ParserData->CollectionPaths[0];
    }
    else
    {
     HID_CollectionPath_t* ParentCollectionPath = CurrCollectionPath;

     CurrCollectionPath = &ParserData->CollectionPaths[1];

     while (CurrCollectionPath->Parent != 
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                                         ((void *)0)
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                             )
     {
      if (CurrCollectionPath == &ParserData->CollectionPaths[10 - 1])
        return HID_PARSE_InsufficientCollectionPaths;

      CurrCollectionPath++;
     }

     CurrCollectionPath->Parent = ParentCollectionPath;
    }

    CurrCollectionPath->Type = ReportItemData;
    CurrCollectionPath->Usage.Page = CurrStateTable->Attributes.Usage.Page;

    if (UsageListSize)
    {
     CurrCollectionPath->Usage.Usage = UsageList[0];

     for (uint8_t i = 1; i < UsageListSize; i++)
       UsageList[i - 1] = UsageList[i];

     UsageListSize--;
    }
    else if (UsageMinMax.Minimum <= UsageMinMax.Maximum)
    {
     CurrCollectionPath->Usage.Usage = UsageMinMax.Minimum++;
    }

    break;

   case (0x00 | 0xC0 | 0x00) :
    if (CurrCollectionPath == 
# 234 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                             ((void *)0)
# 234 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                                 )
      return HID_PARSE_UnexpectedEndCollection;

    CurrCollectionPath = CurrCollectionPath->Parent;
    break;

   case (0x00 | 0x80 | 0x00) :
   case (0x00 | 0x90 | 0x00) :
   case (0x00 | 0xB0 | 0x00) :
    for (uint8_t ReportItemNum = 0; ReportItemNum < CurrStateTable->ReportCount; ReportItemNum++)
    {
     HID_ReportItem_t NewReportItem;

     memcpy(&NewReportItem.Attributes,
            &CurrStateTable->Attributes,
            sizeof(HID_ReportItem_Attributes_t));

     NewReportItem.ItemFlags = ReportItemData;
     NewReportItem.CollectionPath = CurrCollectionPath;
     NewReportItem.ReportID = CurrStateTable->ReportID;

     if (UsageListSize)
     {
      NewReportItem.Attributes.Usage.Usage = UsageList[0];

      for (uint8_t i = 1; i < UsageListSize; i++)
        UsageList[i - 1] = UsageList[i];

      UsageListSize--;
     }
     else if (UsageMinMax.Minimum <= UsageMinMax.Maximum)
     {
      NewReportItem.Attributes.Usage.Usage = UsageMinMax.Minimum++;
     }

     uint8_t ItemTypeTag = (HIDReportItem & (0x0C | 0xF0));

     if (ItemTypeTag == (0x00 | 0x80 | 0x00) )
       NewReportItem.ItemType = HID_REPORT_ITEM_In;
     else if (ItemTypeTag == (0x00 | 0x90 | 0x00) )
       NewReportItem.ItemType = HID_REPORT_ITEM_Out;
     else
       NewReportItem.ItemType = HID_REPORT_ITEM_Feature;

     NewReportItem.BitOffset = CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType];

     CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType] += CurrStateTable->Attributes.BitSize;

     ParserData->LargestReportSizeBits = (((ParserData->LargestReportSizeBits) > (CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType])) ? (ParserData->LargestReportSizeBits) : (CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType]));

     if (ParserData->TotalReportItems == 20)
       return HID_PARSE_InsufficientReportItems;

     memcpy(&ParserData->ReportItems[ParserData->TotalReportItems],
            &NewReportItem, sizeof(HID_ReportItem_t));

     if (!(ReportItemData & (1 << 0)) && CALLBACK_HIDParser_FilterHIDReportItem(&NewReportItem))
       ParserData->TotalReportItems++;
    }

    break;

   default:
    break;
  }

  if ((HIDReportItem & 0x0C) == 0x00)
  {
   UsageMinMax.Minimum = 0;
   UsageMinMax.Maximum = 0;
   UsageListSize = 0;
  }
 }

 if (!(ParserData->TotalReportItems))
   return HID_PARSE_NoUnfilteredReportItems;

 return HID_PARSE_Successful;
}


# 314 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
_Bool 
# 314 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
    USB_GetHIDReportItemInfo(const uint8_t* ReportData,
                              HID_ReportItem_t* const ReportItem)
{
 if (ReportItem == 
# 317 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                  ((void *)0)
# 317 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                      )
   return 
# 318 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
         0
# 318 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
              ;

 uint16_t DataBitsRem = ReportItem->Attributes.BitSize;
 uint16_t CurrentBit = ReportItem->BitOffset;
 uint32_t BitMask = (1 << 0);

 if (ReportItem->ReportID)
 {
  if (ReportItem->ReportID != ReportData[0])
    return 
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
          0
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
               ;

  ReportData++;
 }

 ReportItem->PreviousValue = ReportItem->Value;
 ReportItem->Value = 0;

 while (DataBitsRem--)
 {
  if (ReportData[CurrentBit / 8] & (1 << (CurrentBit % 8)))
    ReportItem->Value |= BitMask;

  CurrentBit++;
  BitMask <<= 1;
 }

 return 
# 344 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
       1
# 344 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
           ;
}

void USB_SetHIDReportItemInfo(uint8_t* ReportData,
                              HID_ReportItem_t* const ReportItem)
{
 if (ReportItem == 
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c" 3 4
                  ((void *)0)
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Class/Common/HIDParser.c"
                      )
   return;

 uint16_t DataBitsRem = ReportItem->Attributes.BitSize;
 uint16_t CurrentBit = ReportItem->BitOffset;
 uint32_t BitMask = (1 << 0);

 if (ReportItem->ReportID)
 {
  ReportData[0] = ReportItem->ReportID;
  ReportData++;
 }

 ReportItem->PreviousValue = ReportItem->Value;

 while (DataBitsRem--)
 {
  if (ReportItem->Value & BitMask)
    ReportData[CurrentBit / 8] |= (1 << (CurrentBit % 8));

  CurrentBit++;
  BitMask <<= 1;
 }
}

uint16_t USB_GetHIDReportSize(HID_ReportInfo_t* const ParserData,
                              const uint8_t ReportID,
                              const uint8_t ReportType)
{
 for (uint8_t i = 0; i < 10; i++)
 {
  uint16_t ReportSizeBits = ParserData->ReportIDSizes[i].ReportSizeBits[ReportType];

  if (ParserData->ReportIDSizes[i].ReportID == ReportID)
    return (ReportSizeBits / 8) + ((ReportSizeBits % 8) ? 1 : 0);
 }

 return 0;
}
