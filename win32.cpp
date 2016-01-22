#include "hpp.hpp"

Dir::Dir(string V):Sym("dir",V) { mkdir(val.c_str()); }

Sym* Dir::add(Sym*o) { 
	File* F = new File(val+'/'+o->val);
	F->setpar(Wr); push(F);
	assert( F->fh = fopen( F->val.c_str(),"w") );
	return F; }

