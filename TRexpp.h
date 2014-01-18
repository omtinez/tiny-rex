#ifndef _TREXPP_H_
#define _TREXPP_H_

extern "C" {
#include "trex.h"
}

struct TRexParseException{TRexParseException(const TRexChar *c):desc(c){}const TRexChar *desc;};

class TRexpp {
public:
	TRexpp() { _exp = (TRex *)0; }
	~TRexpp() { CleanUp(); }
	// compiles a regular expression
	void Compile(const TRexChar *pattern) { 
		const TRexChar *error;
		CleanUp();
		if(!(_exp = trex_compile(pattern,&error)))
			throw TRexParseException(error);
	}
	// return true if the given text match the expression
	bool Match(const TRexChar* text) { 
		return _exp?(trex_match(_exp,text) != 0):false; 
	}
	// Searches for the first match of the expression in a zero terminated string
	bool Search(const TRexChar* text, const TRexChar** out_begin, const TRexChar** out_end) { 
		return _exp?(trex_search(_exp,text,out_begin,out_end) != 0):false; 
	}
	// Searches for the first match of the expression in a string sarting at text_begin and ending at text_end
	bool SearchRange(const TRexChar* text_begin,const TRexChar* text_end,const TRexChar** out_begin, const TRexChar** out_end) { 
		return _exp?(trex_searchrange(_exp,text_begin,text_end,out_begin,out_end) != 0):false; 
	}
	bool GetSubExp(int n, const TRexChar** out_begin, int *out_len)
	{
		TRexMatch match;
		TRexBool res = _exp?(trex_getsubexp(_exp,n,&match)):TRex_False; 
		if(res) {
			*out_begin = match.begin;
			*out_len = match.len;
			return true;
		}
		return false;
	}
	int GetSubExpCount() { return _exp?trex_getsubexpcount(_exp):0; }
private:
	void CleanUp() { if(_exp) trex_free(_exp); _exp = (TRex *)0; }
	TRex *_exp;
};
#endif //_TREXPP_H_
