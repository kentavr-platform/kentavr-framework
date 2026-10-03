# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
# 1 "/data/Apparat/MAVR/kentavr-firmware//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Framework/AVR/USB/avr-usb-config.h" 1
# 9 "Framework/AVR/USB/avr-usb-config.h"
# 1 "Framework/Core/oscillator.h" 1
# 10 "Framework/AVR/USB/avr-usb-config.h" 2
# 1 "<command-line>" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
# 31 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 1
# 66 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
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
# 67 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "/usr/lib/gcc/avr/7.3.0/include/stdbool.h" 1 3 4
# 68 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 69 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 70 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2

# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Architectures.h" 1
# 72 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/BoardTypes.h" 1
# 73 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/ArchitectureSpecific.h" 1
# 74 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/CompilerSpecific.h" 1
# 75 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Attributes.h" 1
# 76 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
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
# 95 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/interrupt.h" 1 3
# 96 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 97 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 98 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 1 "/usr/lib/avr/include/avr/boot.h" 1 3
# 107 "/usr/lib/avr/include/avr/boot.h" 3
# 1 "/usr/lib/gcc/avr/7.3.0/include-fixed/limits.h" 1 3 4
# 108 "/usr/lib/avr/include/avr/boot.h" 2 3
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 100 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
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
# 101 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2

   
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
  typedef uint8_t uint_reg_t;






# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Endianness.h" 1
# 400 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Endianness.h"
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
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Endianness.h"
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
# 465 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Endianness.h"
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
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 2
# 249 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
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
# 295 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
   }
# 305 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline uint_reg_t GetGlobalInterruptMask(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    return 
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 3
          (*(volatile uint8_t *)((0x3F) + 0x20))
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
              ;





   }
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
   __attribute__ ((always_inline))
   static inline void SetGlobalInterruptMask(const uint_reg_t GlobalIntState)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 333 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 3
   (*(volatile uint8_t *)((0x3F) + 0x20)) 
# 333 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
        = GlobalIntState;
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
    __asm__ __volatile__("" ::: "memory");;
   }





   __attribute__ ((always_inline))
   static inline void GlobalInterruptEnable(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 356 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 3
   __asm__ __volatile__ ("sei" ::: "memory")
# 356 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
        ;






    __asm__ __volatile__("" ::: "memory");;
   }





   __attribute__ ((always_inline))
   static inline void GlobalInterruptDisable(void)
   {
    __asm__ __volatile__("" ::: "memory");;


    
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 3
   __asm__ __volatile__ ("cli" ::: "memory")
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h"
        ;






    __asm__ __volatile__("" ::: "memory");;
   }
# 32 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 2



# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../USBMode.h" 1
# 69 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../USBMode.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../../../../Common/Common.h" 1
# 70 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../USBMode.h" 2
# 36 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 2



# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h" 1
# 77 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../USBMode.h" 1
# 78 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h" 2
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h"
   typedef struct
   {
    uint8_t Address;
    uint16_t Size;
    uint8_t Type;
    uint8_t Banks;
   } USB_Endpoint_Table_t;
# 115 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 1
# 76 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../../../../Common/Common.h" 1
# 77 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 1
# 45 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../../../../Common/Common.h" 1
# 46 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBMode.h" 1
# 47 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBController.h" 1
# 138 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBController.h"
  enum USB_Modes_t
  {
   USB_MODE_None = 0,
   USB_MODE_Device = 1,
   USB_MODE_Host = 2,
   USB_MODE_UID = 3,


  };



# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 1
# 52 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../../../../Common/Common.h" 1
# 53 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBMode.h" 1
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h" 1
# 62 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../../../../Common/Common.h" 1
# 63 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBMode.h" 1
# 64 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h" 2
# 89 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_UIDChange(void);
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
# 117 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_DeviceAttached(void);
# 131 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_DeviceUnattached(void);
# 149 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                               const uint8_t SubErrorCode);
# 166 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_DeviceEnumerationComplete(void);
# 183 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Host_StartOfFrame(void);
# 205 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_Connect(void);
# 223 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_Disconnect(void);
# 249 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_ControlRequest(void);
# 263 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_ConfigurationChanged(void);
# 281 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_Suspend(void);
# 299 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_WakeUp(void);
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_Reset(void);
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h"
   void EVENT_USB_Device_StartOfFrame(void);
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBTask.h" 1
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBInterrupt.h" 1
# 60 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBInterrupt.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 1
# 45 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../../../../Common/Common.h" 1
# 46 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 2
# 60 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
   enum USB_Interrupts_t
   {

    USB_INT_VBUSTI = 0,





    USB_INT_WAKEUPI = 2,
    USB_INT_SUSPI = 3,
    USB_INT_EORSTI = 4,
    USB_INT_SOFI = 5,
    USB_INT_RXSTPI = 6,
# 84 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
   };


   __attribute__ ((always_inline))
   static inline void USB_INT_Enable(const uint8_t Interrupt)
   {
    switch (Interrupt)
    {

     case USB_INT_VBUSTI:
      
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xD8)) 
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     0
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                           );
      break;







     case USB_INT_WAKEUPI:
      
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     4
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;
     case USB_INT_SUSPI:
      
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     0
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                          );
      break;
     case USB_INT_EORSTI:
      
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     3
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                           );
      break;
     case USB_INT_SOFI:
      
# 113 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 113 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 113 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     2
# 113 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                         );
      break;
     case USB_INT_RXSTPI:
      
# 116 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xF0)) 
# 116 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            |= (1 << 
# 116 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                     3
# 116 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                           );
      break;
# 142 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
     default:
      break;
    }
   }

   __attribute__ ((always_inline))
   static inline void USB_INT_Disable(const uint8_t Interrupt)
   {
    switch (Interrupt)
    {

     case USB_INT_VBUSTI:
      
# 154 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xD8)) 
# 154 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 154 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      0
# 154 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;







     case USB_INT_WAKEUPI:
      
# 164 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 164 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 164 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      4
# 164 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                             );
      break;
     case USB_INT_SUSPI:
      
# 167 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 167 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 167 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      0
# 167 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                           );
      break;
     case USB_INT_EORSTI:
      
# 170 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 170 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 170 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      3
# 170 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;
     case USB_INT_SOFI:
      
# 173 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE2)) 
# 173 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 173 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      2
# 173 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                          );
      break;
     case USB_INT_RXSTPI:
      
# 176 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xF0)) 
# 176 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 176 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      3
# 176 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;
# 202 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
     default:
      break;
    }
   }

   __attribute__ ((always_inline))
   static inline void USB_INT_Clear(const uint8_t Interrupt)
   {
    switch (Interrupt)
    {

     case USB_INT_VBUSTI:
      
# 214 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xDA)) 
# 214 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 214 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      0
# 214 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;







     case USB_INT_WAKEUPI:
      
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE1)) 
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      4
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                             );
      break;
     case USB_INT_SUSPI:
      
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE1)) 
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      0
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                           );
      break;
     case USB_INT_EORSTI:
      
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE1)) 
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      3
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;
     case USB_INT_SOFI:
      
# 233 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE1)) 
# 233 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 233 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      2
# 233 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                          );
      break;
     case USB_INT_RXSTPI:
      
# 236 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
     (*(volatile uint8_t *)(0xE8)) 
# 236 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
            &= ~(1 << 
# 236 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                      3
# 236 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                            );
      break;
# 262 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
     default:
      break;
    }
   }

   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline 
# 268 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3 4
                _Bool 
# 268 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                     USB_INT_IsEnabled(const uint8_t Interrupt)
   {
    switch (Interrupt)
    {

     case USB_INT_VBUSTI:
      return (
# 274 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xD8)) 
# 274 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 274 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            0
# 274 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));






     case USB_INT_WAKEUPI:
      return (
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE2)) 
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            4
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                   ));
     case USB_INT_SUSPI:
      return (
# 284 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE2)) 
# 284 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 284 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            0
# 284 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                 ));
     case USB_INT_EORSTI:
      return (
# 286 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE2)) 
# 286 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 286 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            3
# 286 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));
     case USB_INT_SOFI:
      return (
# 288 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE2)) 
# 288 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 288 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            2
# 288 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                ));
     case USB_INT_RXSTPI:
      return (
# 290 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xF0)) 
# 290 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 290 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            3
# 290 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));
# 308 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
     default:
      return 
# 309 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3 4
            0
# 309 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                 ;
    }
   }

   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline 
# 314 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3 4
                _Bool 
# 314 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                     USB_INT_HasOccurred(const uint8_t Interrupt)
   {
    switch (Interrupt)
    {

     case USB_INT_VBUSTI:
      return (
# 320 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xDA)) 
# 320 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 320 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            0
# 320 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));






     case USB_INT_WAKEUPI:
      return (
# 328 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE1)) 
# 328 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 328 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            4
# 328 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                   ));
     case USB_INT_SUSPI:
      return (
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE1)) 
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            0
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                 ));
     case USB_INT_EORSTI:
      return (
# 332 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE1)) 
# 332 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 332 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            3
# 332 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));
     case USB_INT_SOFI:
      return (
# 334 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE1)) 
# 334 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 334 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            2
# 334 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                ));
     case USB_INT_RXSTPI:
      return (
# 336 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
             (*(volatile uint8_t *)(0xE8)) 
# 336 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                    & (1 << 
# 336 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3
                            3
# 336 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                                  ));
# 354 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
     default:
      return 
# 355 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 3 4
            0
# 355 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h"
                 ;
    }
   }


# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../USBMode.h" 1
# 361 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../Events.h" 1
# 362 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../USBController.h" 1
# 363 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/USBInterrupt_AVR8.h" 2


   void USB_INT_ClearAllInterrupts(void);
   void USB_INT_DisableAllInterrupts(void);
# 61 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBInterrupt.h" 2
# 57 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 67 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h" 1
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h" 1
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Events.h" 1
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h" 2
# 207 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 262 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    uint8_t Size;
    uint8_t Type;


   } __attribute__ ((packed)) USB_Descriptor_Header_t;
# 279 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


   } __attribute__ ((packed)) USB_StdDescriptor_Header_t;
# 296 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 338 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
    uint8_t NumberOfConfigurations;


   } __attribute__ ((packed)) USB_Descriptor_Device_t;
# 352 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 394 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
    uint8_t bNumConfigurations;


   } __attribute__ ((packed)) USB_StdDescriptor_Device_t;
# 406 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 432 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 461 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 492 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 522 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 550 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 586 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 618 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
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
# 643 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;

    uint8_t EndpointAddress;


    uint8_t Attributes;


    uint16_t EndpointSize;


    uint8_t PollingIntervalMS;


   } __attribute__ ((packed)) USB_Descriptor_Endpoint_t;
# 671 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint8_t bEndpointAddress;


    uint8_t bmAttributes;


    uint16_t wMaxPacketSize;


    uint8_t bInterval;


   } __attribute__ ((packed)) USB_StdDescriptor_Endpoint_t;
# 706 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    USB_Descriptor_Header_t Header;


    wchar_t UnicodeString[];
# 726 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   } __attribute__ ((packed)) USB_Descriptor_String_t;
# 744 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   typedef struct
   {
    uint8_t bLength;
    uint8_t bDescriptorType;


    uint16_t bString[];
# 759 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdDescriptors.h"
   } __attribute__ ((packed)) USB_StdDescriptor_String_t;
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBInterrupt.h" 1
# 57 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Endpoint.h" 1
# 58 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h" 2
# 78 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h"
   enum USB_Device_States_t
   {
    DEVICE_STATE_Unattached = 0,


    DEVICE_STATE_Powered = 1,



    DEVICE_STATE_Default = 2,



    DEVICE_STATE_Addressed = 3,



    DEVICE_STATE_Configured = 4,



    DEVICE_STATE_Suspended = 5,




   };
# 133 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h"
   uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                       const uint16_t wIndex,
                                       const void** const DescriptorAddress


                                       , uint8_t* const DescriptorMemorySpace

                                       ) __attribute__ ((warn_unused_result)) __attribute__ ((nonnull (3)));



# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 1
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../StdDescriptors.h" 1
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../USBInterrupt.h" 1
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../Endpoint.h" 1
# 57 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 2
# 157 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
   void USB_Device_SendRemoteWakeup(void);







   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline uint16_t USB_Device_GetFrameNumber(void)
   {
    return 
# 168 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
          (*(volatile uint16_t *)(0xE4))
# 168 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                ;
   }
# 178 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
    __attribute__ ((always_inline))
    static inline void USB_Device_EnableSOFEvents(void)
    {
     USB_INT_Enable(USB_INT_SOFI);
    }






    __attribute__ ((always_inline))
    static inline void USB_Device_DisableSOFEvents(void)
    {
     USB_INT_Disable(USB_INT_SOFI);
    }






   __attribute__ ((always_inline))
   static inline void USB_Device_SetLowSpeed(void)
   {
    
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
   (*(volatile uint8_t *)(0xE0)) 
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
         |= (1 << 
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                   2
# 203 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                      );
   }

   __attribute__ ((always_inline))
   static inline void USB_Device_SetFullSpeed(void)
   {
    
# 209 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
   (*(volatile uint8_t *)(0xE0)) 
# 209 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
         &= ~(1 << 
# 209 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                   2
# 209 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                      );
   }


   __attribute__ ((always_inline))
   static inline void USB_Device_SetDeviceAddress(const uint8_t Address)
   {
    
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
   (*(volatile uint8_t *)(0xE3)) 
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
          = (
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
             (*(volatile uint8_t *)(0xE3)) 
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                    & (1 << 
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                            7
# 216 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                                 )) | (Address & 0x7F);
   }

   __attribute__ ((always_inline))
   static inline void USB_Device_EnableDeviceAddress(const uint8_t Address)
   {
    (void)Address;

    
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
   (*(volatile uint8_t *)(0xE3)) 
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
          |= (1 << 
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                   7
# 224 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                        );
   }

   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline 
# 228 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3 4
                _Bool 
# 228 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                     USB_Device_IsAddressSet(void)
   {
    return (
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
           (*(volatile uint8_t *)(0xE3)) 
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                  & (1 << 
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                          7
# 230 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                               ));
   }


   __attribute__ ((nonnull (1)))
   static inline void USB_Device_GetSerialString(uint16_t* const UnicodeString)
   {
    uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
    GlobalInterruptDisable();

    uint8_t SigReadAddress = 0x0E;

    for (uint8_t SerialCharNum = 0; SerialCharNum < (80 / 4); SerialCharNum++)
    {
     uint8_t SerialByte = 
# 244 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                         (__extension__({ uint8_t __result; __asm__ __volatile__ ( "sts %1, %2\n\t" "lpm %0, Z" "\n\t" : "=r" (__result) : "i" (((uint16_t) &((*(volatile uint8_t *)((0x37) + 0x20))))), "r" ((uint8_t)(((1 << (0)) | (1 << (5))))), "z" ((uint16_t)(
# 244 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                         SigReadAddress
# 244 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h" 3
                         )) ); __result; }))
# 244 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/Device_AVR8.h"
                                                                ;

     if (SerialCharNum & 0x01)
     {
      SerialByte >>= 4;
      SigReadAddress++;
     }

     SerialByte &= 0x0F;

     UnicodeString[SerialCharNum] = ((SerialByte >= 10) ? (('A' - 10) + SerialByte) : ('0' + SerialByte))
                                                                 ;
    }

    SetGlobalInterruptMask(CurrentGlobalInt);
   }
# 145 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Device.h" 2
# 68 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../Endpoint.h" 1
# 69 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 1
# 49 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdRequestType.h" 1
# 163 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdRequestType.h"
   typedef struct
   {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
   } __attribute__ ((packed)) USB_Request_Header_t;
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../StdRequestType.h"
   enum USB_Control_Request_t
   {
    REQ_GetStatus = 0,



    REQ_ClearFeature = 1,



    REQ_SetFeature = 3,



    REQ_SetAddress = 5,



    REQ_GetDescriptor = 6,



    REQ_SetDescriptor = 7,


    REQ_GetConfiguration = 8,



    REQ_SetConfiguration = 9,



    REQ_GetInterface = 10,


    REQ_SetInterface = 11,


    REQ_SynchFrame = 12,


   };




   enum USB_Feature_Selectors_t
   {
    FEATURE_SEL_EndpointHalt = 0x00,




    FEATURE_SEL_DeviceRemoteWakeup = 0x01,




    FEATURE_SEL_TestMode = 0x02,


   };
# 50 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBTask.h" 1
# 51 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../USBController.h" 1
# 52 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 2
# 72 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
    enum USB_DescriptorMemorySpaces_t
    {

     MEMSPACE_FLASH = 0,


     MEMSPACE_EEPROM = 1,

     MEMSPACE_RAM = 2,
    };
# 94 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
   extern uint8_t USB_Device_ConfigurationNumber;
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
    extern 
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 3 4
          _Bool 
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
               USB_Device_RemoteWakeupEnabled;
# 120 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
    extern 
# 120 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h" 3 4
          _Bool 
# 120 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
               USB_Device_CurrentlySelfPowered;
# 136 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../DeviceStandardReq.h"
   void USB_Device_ProcessControlRequest(void);
# 70 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../EndpointStream.h" 1
# 69 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../EndpointStream.h"
   enum Endpoint_Stream_RW_ErrorCodes_t
   {
    ENDPOINT_RWSTREAM_NoError = 0,
    ENDPOINT_RWSTREAM_EndpointStalled = 1,


    ENDPOINT_RWSTREAM_DeviceDisconnected = 2,


    ENDPOINT_RWSTREAM_BusSuspended = 3,



    ENDPOINT_RWSTREAM_Timeout = 4,



    ENDPOINT_RWSTREAM_IncompleteTransfer = 5,




   };


   enum Endpoint_ControlStream_RW_ErrorCodes_t
   {
    ENDPOINT_RWCSTREAM_NoError = 0,
    ENDPOINT_RWCSTREAM_HostAborted = 1,
    ENDPOINT_RWCSTREAM_DeviceDisconnected = 2,


    ENDPOINT_RWCSTREAM_BusSuspended = 3,



   };



# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h" 1
# 55 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/../USBTask.h" 1
# 56 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h" 2
# 122 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Discard_Stream(uint16_t Length,
                                   uint16_t* const BytesProcessed);
# 175 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Null_Stream(uint16_t Length,
                                uint16_t* const BytesProcessed);
# 238 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Stream_LE(const void* const Buffer,
                                    uint16_t Length,
                                    uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 256 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Stream_BE(const void* const Buffer,
                                    uint16_t Length,
                                    uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 315 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Stream_LE(void* const Buffer,
                                   uint16_t Length,
                                   uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 333 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Stream_BE(void* const Buffer,
                                   uint16_t Length,
                                   uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 357 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_Stream_LE(const void* const Buffer,
                                            uint16_t Length) __attribute__ ((nonnull (1)));
# 380 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_Stream_BE(const void* const Buffer,
                                            uint16_t Length) __attribute__ ((nonnull (1)));
# 403 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Control_Stream_LE(void* const Buffer,
                                           uint16_t Length) __attribute__ ((nonnull (1)));
# 426 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Control_Stream_BE(void* const Buffer,
                                           uint16_t Length) __attribute__ ((nonnull (1)));
# 442 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_EStream_LE(const void* const Buffer,
                                     uint16_t Length,
                                     uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 455 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_EStream_BE(const void* const Buffer,
                                     uint16_t Length,
                                     uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 468 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_EStream_LE(void* const Buffer,
                                    uint16_t Length,
                                    uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 481 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_EStream_BE(void* const Buffer,
                                    uint16_t Length,
                                    uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 503 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_EStream_LE(const void* const Buffer,
                                             uint16_t Length) __attribute__ ((nonnull (1)));
# 524 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_EStream_BE(const void* const Buffer,
                                             uint16_t Length) __attribute__ ((nonnull (1)));
# 545 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Control_EStream_LE(void* const Buffer,
                                            uint16_t Length) __attribute__ ((nonnull (1)));
# 566 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Read_Control_EStream_BE(void* const Buffer,
                                            uint16_t Length) __attribute__ ((nonnull (1)));
# 584 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_PStream_LE(const void* const Buffer,
                                     uint16_t Length,
                                     uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 599 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_PStream_BE(const void* const Buffer,
                                     uint16_t Length,
                                     uint16_t* const BytesProcessed) __attribute__ ((nonnull (1)));
# 623 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_PStream_LE(const void* const Buffer,
                                             uint16_t Length) __attribute__ ((nonnull (1)));
# 646 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../AVR8/EndpointStream_AVR8.h"
   uint8_t Endpoint_Write_Control_PStream_BE(const void* const Buffer,
                                             uint16_t Length) __attribute__ ((nonnull (1)));
# 110 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/../EndpointStream.h" 2
# 71 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 2
# 176 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
    __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
    static inline 
# 177 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                 _Bool 
# 177 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                      USB_VBUS_GetStatus(void)
    {
     return ((
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
             (*(volatile uint8_t *)(0xD9)) 
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                    & (1 << 
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                            0
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                )) ? 
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                                     1 
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                          : 
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                                            0
# 179 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                                 );
    }






   __attribute__ ((always_inline))
   static inline void USB_Detach(void)
   {
    
# 190 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xE0)) 
# 190 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 190 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    0
# 190 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );
   }
# 201 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
   __attribute__ ((always_inline))
   static inline void USB_Attach(void)
   {
    
# 204 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xE0)) 
# 204 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 204 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    0
# 204 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );
   }
# 252 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
   void USB_Init(
# 264 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                  const uint8_t Options

                  );





   void USB_Disable(void);




   void USB_ResetInterface(void);
# 308 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
    extern volatile uint8_t USB_Options;
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
   __attribute__ ((always_inline))
   static inline void USB_PLL_On(void)
   {
    
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)((0x29) + 0x20)) 
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          = (1 << 
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
            4
# 330 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
            );
    
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)((0x29) + 0x20)) 
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          = ((1 << 
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
             4
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
             ) | (1 << 
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                                 1
# 331 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                     ));
   }

   __attribute__ ((always_inline))
   static inline void USB_PLL_Off(void)
   {
    
# 337 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)((0x29) + 0x20)) 
# 337 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          = 0;
   }

   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                _Bool 
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                     USB_PLL_IsReady(void)
   {
    return ((
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
            (*(volatile uint8_t *)((0x29) + 0x20)) 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                   & (1 << 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                           0
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                )) ? 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                                     1 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                          : 
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3 4
                                            0
# 343 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                                                 );
   }

   __attribute__ ((always_inline))
   static inline void USB_REG_On(void)
   {

    
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD7)) 
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    0
# 350 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );



   }

   __attribute__ ((always_inline))
   static inline void USB_REG_Off(void)
   {

    
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD7)) 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    0
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );



   }


   __attribute__ ((always_inline))
   static inline void USB_OTGPAD_On(void)
   {
    
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    4
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                           );
   }

   __attribute__ ((always_inline))
   static inline void USB_OTGPAD_Off(void)
   {
    
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    4
# 376 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                           );
   }


   __attribute__ ((always_inline))
   static inline void USB_CLK_Freeze(void)
   {
    
# 383 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 383 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 383 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    5
# 383 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );
   }

   __attribute__ ((always_inline))
   static inline void USB_CLK_Unfreeze(void)
   {
    
# 389 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 389 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 389 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    5
# 389 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                          );
   }

   __attribute__ ((always_inline))
   static inline void USB_Controller_Enable(void)
   {
    
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    7
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                        );
   }

   __attribute__ ((always_inline))
   static inline void USB_Controller_Disable(void)
   {
    
# 401 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 401 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 401 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    7
# 401 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                        );
   }

   __attribute__ ((always_inline))
   static inline void USB_Controller_Reset(void)
   {
    
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          &= ~(1 << 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    7
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                        );
    
# 408 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
   (*(volatile uint8_t *)(0xD8)) 
# 408 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
          |= (1 << 
# 408 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h" 3
                    7
# 408 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../AVR8/USBController_AVR8.h"
                        );
   }
# 151 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBController.h" 2
# 48 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../Events.h" 1
# 49 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../StdRequestType.h" 1
# 50 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../StdDescriptors.h" 1
# 51 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2


# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../DeviceStandardReq.h" 1
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 2
# 81 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
   extern volatile 
# 81 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h" 3 4
                  _Bool 
# 81 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
                       USB_IsInitialized;
# 91 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
    extern USB_Request_Header_t USB_ControlRequest;
# 144 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
     extern volatile uint8_t USB_DeviceState;
# 173 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBTask.h"
   void USB_USBTask(void);
# 78 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 2
# 1 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/../USBInterrupt.h" 1
# 79 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 2
# 93 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   static inline uint8_t Endpoint_BytesToEPSizeMask(const uint16_t Bytes) __attribute__ ((warn_unused_result)) __attribute__ ((const))
                                                                          __attribute__ ((always_inline));
   static inline uint8_t Endpoint_BytesToEPSizeMask(const uint16_t Bytes)
   {
    uint8_t MaskVal = 0;
    uint16_t CheckBytes = 8;

    while (CheckBytes < Bytes)
    {
     MaskVal++;
     CheckBytes <<= 1;
    }

    return (MaskVal << 
# 106 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                      4
# 106 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                             );
   }


   void Endpoint_ClearEndpoints(void);
   
# 111 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
  _Bool 
# 111 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
       Endpoint_ConfigureEndpoint_Prv(const uint8_t Number,
                                       const uint8_t UECFG0XData,
                                       const uint8_t UECFG1XData);
# 145 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   enum Endpoint_WaitUntilReady_ErrorCodes_t
   {
    ENDPOINT_READYWAIT_NoError = 0,
    ENDPOINT_READYWAIT_EndpointStalled = 1,


    ENDPOINT_READYWAIT_DeviceDisconnected = 2,


    ENDPOINT_READYWAIT_BusSuspended = 3,



    ENDPOINT_READYWAIT_Timeout = 4,



   };
# 196 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   static inline 
# 196 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 196 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_ConfigureEndpoint(const uint8_t Address,
                                                 const uint8_t Type,
                                                 const uint16_t Size,
                                                 const uint8_t Banks) __attribute__ ((always_inline));
   static inline 
# 200 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 200 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_ConfigureEndpoint(const uint8_t Address,
                                                 const uint8_t Type,
                                                 const uint16_t Size,
                                                 const uint8_t Banks)
   {
    uint8_t Number = (Address & 0x0F);

    if (Number >= 7)
      return 
# 208 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
            0
# 208 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;

    return Endpoint_ConfigureEndpoint_Prv(Number,
                                          ((Type << 
# 211 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                                   6
# 211 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                          ) | ((Address & 0x80) ? (1 << 
# 211 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                                                                                   0
# 211 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                                                                        ) : 0)),
                                          ((1 << 
# 212 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                                1
# 212 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                     ) | ((Banks > 1) ? (1 << 
# 212 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                                                              2
# 212 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                                                   ) : 0) | Endpoint_BytesToEPSizeMask(Size)));
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint16_t Endpoint_BytesInEndpoint(void)
   {



     return (((uint16_t)
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                       (*(volatile uint8_t *)(0xF3)) 
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                              << 8) | 
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                      (*(volatile uint8_t *)(0xF2))
# 227 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                            );



   }





   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint8_t Endpoint_GetEndpointDirection(void)
   {
    return (
# 240 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xEC)) 
# 240 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 240 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           0
# 240 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                )) ? 0x80 : 0x00;
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint8_t Endpoint_GetCurrentEndpoint(void)
   {

     return ((
# 253 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
             (*(volatile uint8_t *)(0xE9)) 
# 253 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & 0x0F) | Endpoint_GetEndpointDirection());



   }
# 266 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_SelectEndpoint(const uint8_t Address)
   {

     
# 270 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
    (*(volatile uint8_t *)(0xE9)) 
# 270 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Address & 0x0F);

   }






   __attribute__ ((always_inline))
   static inline void Endpoint_ResetEndpoint(const uint8_t Address)
   {
    
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEA)) 
# 282 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
         = (1 << (Address & 0x0F));
    
# 283 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEA)) 
# 283 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
         = 0;
   }






   __attribute__ ((always_inline))
   static inline void Endpoint_EnableEndpoint(void)
   {
    
# 294 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEB)) 
# 294 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          |= (1 << 
# 294 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   0
# 294 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                       );
   }




   __attribute__ ((always_inline))
   static inline void Endpoint_DisableEndpoint(void)
   {
    
# 303 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEB)) 
# 303 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          &= ~(1 << 
# 303 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                    0
# 303 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                        );
   }





   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 311 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsEnabled(void)
   {
    return ((
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xEB)) 
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           0
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                               )) ? 
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                    1 
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                         : 
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                           0
# 313 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                );
   }
# 324 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline)) __attribute__ ((warn_unused_result))
   static inline uint8_t Endpoint_GetBusyBanks(void)
   {
    return (
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xEE)) 
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (0x03 << 
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                              0
# 327 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                      ));
   }
# 337 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   static inline void Endpoint_AbortPendingIN(void)
   {
    while (Endpoint_GetBusyBanks() != 0)
    {
     
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
    (*(volatile uint8_t *)(0xE8)) 
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
           |= (1 << 
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                    2
# 341 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                          );
     while (
# 342 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xE8)) 
# 342 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                  & (1 << 
# 342 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                          2
# 342 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                ));
    }
   }
# 357 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 358 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 358 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsReadWriteAllowed(void)
   {
    return ((
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xE8)) 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           5
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                               )) ? 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                    1 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                         : 
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                           0
# 360 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                );
   }





   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 368 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 368 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsConfigured(void)
   {
    return ((
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xEE)) 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                    & (1 << 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                            7
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                 )) ? 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                      1 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                           : 
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                             0
# 370 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                  );
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint8_t Endpoint_GetEndpointInterrupts(void)
   {
    return 
# 382 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
          (*(volatile uint8_t *)(0xF4))
# 382 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
               ;
   }
# 392 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 393 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 393 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_HasEndpointInterrupted(const uint8_t Address)
   {
    return ((Endpoint_GetEndpointInterrupts() & (1 << (Address & 0x0F))) ? 
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                                                                         1 
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                                                              : 
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                                                                                0
# 395 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                                                                     );
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 405 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 405 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsINReady(void)
   {
    return ((
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xE8)) 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           0
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                )) ? 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                     1 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                          : 
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                            0
# 407 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                 );
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 417 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 417 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsOUTReceived(void)
   {
    return ((
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xE8)) 
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           2
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                 )) ? 
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                      1 
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                           : 
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                             0
# 419 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                  );
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 429 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 429 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsSETUPReceived(void)
   {
    return ((
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xE8)) 
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           3
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                 )) ? 
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                      1 
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                           : 
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                             0
# 431 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                  );
   }
# 441 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_ClearSETUP(void)
   {
    
# 444 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xE8)) 
# 444 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          &= ~(1 << 
# 444 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                    3
# 444 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                          );
   }






   __attribute__ ((always_inline))
   static inline void Endpoint_ClearIN(void)
   {

     
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
    (*(volatile uint8_t *)(0xE8)) 
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
           &= ~((1 << 
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                      0
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                           ) | (1 << 
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                     7
# 456 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                            ));



   }






   __attribute__ ((always_inline))
   static inline void Endpoint_ClearOUT(void)
   {

     
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
    (*(volatile uint8_t *)(0xE8)) 
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
           &= ~((1 << 
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                      2
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                            ) | (1 << 
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                      7
# 471 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                             ));



   }
# 488 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_StallTransaction(void)
   {
    
# 491 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEB)) 
# 491 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          |= (1 << 
# 491 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   5
# 491 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                          );
   }





   __attribute__ ((always_inline))
   static inline void Endpoint_ClearStall(void)
   {
    
# 501 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEB)) 
# 501 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          |= (1 << 
# 501 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   4
# 501 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                           );
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline 
# 511 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                _Bool 
# 511 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                     Endpoint_IsStalled(void)
   {
    return ((
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
            (*(volatile uint8_t *)(0xEB)) 
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                   & (1 << 
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                           5
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                  )) ? 
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                       1 
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                            : 
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
                                              0
# 513 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                   );
   }


   __attribute__ ((always_inline))
   static inline void Endpoint_ResetDataToggle(void)
   {
    
# 520 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEB)) 
# 520 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          |= (1 << 
# 520 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   3
# 520 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                        );
   }





   __attribute__ ((always_inline))
   static inline void Endpoint_SetEndpointDirection(const uint8_t DirectionMask)
   {
    
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xEC)) 
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
           = ((
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
               (*(volatile uint8_t *)(0xEC)) 
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                       & ~(1 << 
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                0
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                     )) | (DirectionMask ? (1 << 
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                                                                 0
# 530 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                                                                      ) : 0));
   }







   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint8_t Endpoint_Read_8(void)
   {
    return 
# 542 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
          (*(volatile uint8_t *)(0xF1))
# 542 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                ;
   }







   __attribute__ ((always_inline))
   static inline void Endpoint_Write_8(const uint8_t Data)
   {
    
# 554 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 554 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = Data;
   }





   __attribute__ ((always_inline))
   static inline void Endpoint_Discard_8(void)
   {
    uint8_t Dummy;

    Dummy = 
# 566 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 566 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;

    (void)Dummy;
   }
# 578 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint16_t Endpoint_Read_16_LE(void)
   {
    union
    {
     uint16_t Value;
     uint8_t Bytes[2];
    } Data;

    Data.Bytes[0] = 
# 587 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 587 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[1] = 
# 588 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 588 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;

    return Data.Value;
   }
# 600 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint16_t Endpoint_Read_16_BE(void)
   {
    union
    {
     uint16_t Value;
     uint8_t Bytes[2];
    } Data;

    Data.Bytes[1] = 
# 609 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 609 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[0] = 
# 610 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 610 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;

    return Data.Value;
   }
# 622 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_Write_16_LE(const uint16_t Data)
   {
    
# 625 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 625 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data & 0xFF);
    
# 626 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 626 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 8);
   }
# 636 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_Write_16_BE(const uint16_t Data)
   {
    
# 639 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 639 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 8);
    
# 640 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 640 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data & 0xFF);
   }





   __attribute__ ((always_inline))
   static inline void Endpoint_Discard_16(void)
   {
    uint8_t Dummy;

    Dummy = 
# 652 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 652 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;
    Dummy = 
# 653 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 653 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;

    (void)Dummy;
   }
# 665 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint32_t Endpoint_Read_32_LE(void)
   {
    union
    {
     uint32_t Value;
     uint8_t Bytes[4];
    } Data;

    Data.Bytes[0] = 
# 674 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 674 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[1] = 
# 675 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 675 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[2] = 
# 676 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 676 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[3] = 
# 677 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 677 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;

    return Data.Value;
   }
# 689 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((warn_unused_result)) __attribute__ ((always_inline))
   static inline uint32_t Endpoint_Read_32_BE(void)
   {
    union
    {
     uint32_t Value;
     uint8_t Bytes[4];
    } Data;

    Data.Bytes[3] = 
# 698 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 698 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[2] = 
# 699 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 699 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[1] = 
# 700 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 700 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;
    Data.Bytes[0] = 
# 701 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
                   (*(volatile uint8_t *)(0xF1))
# 701 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                         ;

    return Data.Value;
   }
# 713 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_Write_32_LE(const uint32_t Data)
   {
    
# 716 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 716 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data & 0xFF);
    
# 717 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 717 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 8);
    
# 718 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 718 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 16);
    
# 719 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 719 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 24);
   }
# 729 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   __attribute__ ((always_inline))
   static inline void Endpoint_Write_32_BE(const uint32_t Data)
   {
    
# 732 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 732 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 24);
    
# 733 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 733 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 16);
    
# 734 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 734 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data >> 8);
    
# 735 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
   (*(volatile uint8_t *)(0xF1)) 
# 735 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
          = (Data & 0xFF);
   }





   __attribute__ ((always_inline))
   static inline void Endpoint_Discard_32(void)
   {
    uint8_t Dummy;

    Dummy = 
# 747 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 747 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;
    Dummy = 
# 748 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 748 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;
    Dummy = 
# 749 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 749 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;
    Dummy = 
# 750 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3
           (*(volatile uint8_t *)(0xF1))
# 750 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
                 ;

    (void)Dummy;
   }
# 772 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
    extern uint8_t USB_Device_ControlEndpointSize;
# 789 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   
# 789 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h" 3 4
  _Bool 
# 789 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
       Endpoint_ConfigureEndpointTable(const USB_Endpoint_Table_t* const Table,
                                        const uint8_t Entries);







   void Endpoint_ClearStatusStage(void);
# 809 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../AVR8/Endpoint_AVR8.h"
   uint8_t Endpoint_WaitUntilReady(void);
# 116 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/../Endpoint.h" 2
# 40 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 2


uint8_t USB_Device_ControlEndpointSize = 8;



# 45 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
_Bool 
# 45 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
    Endpoint_ConfigureEndpointTable(const USB_Endpoint_Table_t* const Table,
                                     const uint8_t Entries)
{
 for (uint8_t i = 0; i < Entries; i++)
 {
  if (!(Table[i].Address))
    continue;

  if (!(Endpoint_ConfigureEndpoint(Table[i].Address, Table[i].Type, Table[i].Size, Table[i].Banks)))
    return 
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
          0
# 54 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
               ;
 }

 return 
# 57 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
       1
# 57 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
           ;
}


# 60 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
_Bool 
# 60 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
    Endpoint_ConfigureEndpoint_Prv(const uint8_t Number,
                                    const uint8_t UECFG0XData,
                                    const uint8_t UECFG1XData)
{
# 74 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
 for (uint8_t EPNum = Number; EPNum < 7; EPNum++)
 {
  uint8_t UECFG0XTemp;
  uint8_t UECFG1XTemp;
  uint8_t UEIENXTemp;

  Endpoint_SelectEndpoint(EPNum);

  if (EPNum == Number)
  {
   UECFG0XTemp = UECFG0XData;
   UECFG1XTemp = UECFG1XData;
   UEIENXTemp = 0;
  }
  else
  {
   UECFG0XTemp = 
# 90 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
                (*(volatile uint8_t *)(0xEC))
# 90 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
                       ;
   UECFG1XTemp = 
# 91 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
                (*(volatile uint8_t *)(0xED))
# 91 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
                       ;
   UEIENXTemp = 
# 92 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
                (*(volatile uint8_t *)(0xF0))
# 92 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
                      ;
  }

  if (!(UECFG1XTemp & (1 << 
# 95 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
                           1
# 95 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
                                )))
    continue;

  Endpoint_DisableEndpoint();
  
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xED)) 
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         &= ~(1 << 
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
                   1
# 99 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
                        );

  Endpoint_EnableEndpoint();
  
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xEC)) 
# 102 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = UECFG0XTemp;
  
# 103 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xED)) 
# 103 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = UECFG1XTemp;
  
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xF0)) 
# 104 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = UEIENXTemp;

  if (!(Endpoint_IsConfigured()))
    return 
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
          0
# 107 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
               ;
 }

 Endpoint_SelectEndpoint(Number);
 return 
# 111 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3 4
       1
# 111 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
           ;

}

void Endpoint_ClearEndpoints(void)
{
 
# 117 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
(*(volatile uint8_t *)(0xF4)) 
# 117 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
      = 0;

 for (uint8_t EPNum = 0; EPNum < 7; EPNum++)
 {
  Endpoint_SelectEndpoint(EPNum);
  
# 122 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xF0)) 
# 122 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = 0;
  
# 123 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xE8)) 
# 123 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = 0;
  
# 124 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c" 3
 (*(volatile uint8_t *)(0xED)) 
# 124 "Framework/AVR/USB/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
         = 0;
  Endpoint_DisableEndpoint();
 }
}

void Endpoint_ClearStatusStage(void)
{
 if (USB_ControlRequest.bmRequestType & (1 << 7))
 {
  while (!(Endpoint_IsOUTReceived()))
  {
   if (USB_DeviceState == DEVICE_STATE_Unattached)
     return;
  }

  Endpoint_ClearOUT();
 }
 else
 {
  while (!(Endpoint_IsINReady()))
  {
   if (USB_DeviceState == DEVICE_STATE_Unattached)
     return;
  }

  Endpoint_ClearIN();
 }
}


uint8_t Endpoint_WaitUntilReady(void)
{

 uint8_t TimeoutMSRem = 100;




 uint16_t PreviousFrameNumber = USB_Device_GetFrameNumber();

 for (;;)
 {
  if (Endpoint_GetEndpointDirection() == 0x80)
  {
   if (Endpoint_IsINReady())
     return ENDPOINT_READYWAIT_NoError;
  }
  else
  {
   if (Endpoint_IsOUTReceived())
     return ENDPOINT_READYWAIT_NoError;
  }

  uint8_t USB_DeviceState_LCL = USB_DeviceState;

  if (USB_DeviceState_LCL == DEVICE_STATE_Unattached)
    return ENDPOINT_READYWAIT_DeviceDisconnected;
  else if (USB_DeviceState_LCL == DEVICE_STATE_Suspended)
    return ENDPOINT_READYWAIT_BusSuspended;
  else if (Endpoint_IsStalled())
    return ENDPOINT_READYWAIT_EndpointStalled;

  uint16_t CurrentFrameNumber = USB_Device_GetFrameNumber();

  if (CurrentFrameNumber != PreviousFrameNumber)
  {
   PreviousFrameNumber = CurrentFrameNumber;

   if (!(TimeoutMSRem--))
     return ENDPOINT_READYWAIT_Timeout;
  }
 }
}
