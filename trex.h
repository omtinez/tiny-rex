#ifndef _TREX_H_
#define _TREX_H_

#ifdef _UNICODE
#define TRexChar unsigned short
#define MAX_CHAR 0xFFFF
#define _TREXC(c) L##c 
#define trex_strlen wcslen
#define trex_printf wprintf
#else
#define TRexChar char
#define MAX_CHAR 0xFF
#define _TREXC(c) (c) 
#define trex_strlen strlen
#define trex_printf printf
#endif

#ifndef TREX_API
#define TREX_API extern
#endif

#define TRex_True 1
#define TRex_False 0

typedef unsigned int TRexBool;
typedef struct TRex TRex;

typedef struct {
	const TRexChar *begin;
	int len;
} TRexMatch;

TREX_API TRex *trex_compile(const TRexChar *pattern,const TRexChar **error);
TREX_API void trex_free(TRex *exp);
TREX_API TRexBool trex_match(TRex* exp,const TRexChar* text);
TREX_API TRexBool trex_search(TRex* exp,const TRexChar* text, const TRexChar** out_begin, const TRexChar** out_end);
TREX_API TRexBool trex_searchrange(TRex* exp,const TRexChar* text_begin,const TRexChar* text_end,const TRexChar** out_begin, const TRexChar** out_end);
TREX_API int trex_getsubexpcount(TRex* exp);
TREX_API TRexBool trex_getsubexp(TRex* exp, int n, TRexMatch *subexp);

#endif
