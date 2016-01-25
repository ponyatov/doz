#include "hpp.hpp"

Dir::Dir(string V):Sym("dir",V) { mkdir(val.c_str()); }

Sym* Dir::add(Sym*o) { 
//	File* F = new File(val+'/'+o->val);
	o->partag(Wr); o->partag(this); push(o);
	assert (o->tag=="file");
	assert( dynamic_cast<File*>(o)->fh = fopen( (val+'/'+o->val).c_str(),"w") );
	return o; }

