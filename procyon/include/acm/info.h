#if !defined(acm_hdr_info)
#define acm_hdr_info

#include <acm/bs.h>

#include <stdint.h>

char const *   acm_shipnm( acm_shipid       ship);
uint_least64_t acm_sysdist(uint_least64_t   sys);
uint_least64_t acm_jmplen( acm_ship const * ship);

#endif
