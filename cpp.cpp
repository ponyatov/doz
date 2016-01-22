#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(Sym*o)		{ cout << o->dump(); }				// \ writers
void W(string s)	{ cout << s; }						// /

Sym::Sym(string T,string V) { tag=T; val=V; }			// <T:V> \ constructor
Sym::Sym(string V):Sym("sym",V) {}						// token /
void Sym::push(Sym*o) { nest.push_back(o); }			// add nest[]ed

string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::tagstr() { return "<"+tag+":'"+val+"'>"; }	// <T:'V'>
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)	// par{}ameters
		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }
string Sym::pad(int n) {								// pad as tree
	string S;
	for(int i=0;i<n-1;i++) S+="|   ";
	if (n) S+="\\___";
	return S; }

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// env[] lookup
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		(*it) = (*it)->eval();
	return this; }
														// ---- operators ----
Sym* Sym::doc(Sym*o){ par["doc"]=o; return this; }
Sym* Sym::eq(Sym*o) { env[val]=o; return o; }
Sym* Sym::at(Sym*o) { push(o); return this; }

														// ==== scalars ====
														// ---- specials ----
Sym* N = new Sym("N","");
Sym* T = new Sym("bool","true");
Sym* F = new Sym("bool","false");
Sym* E = new Sym("error","");
Sym* D = new Sym("default","");
														// ---- string ----
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
														// ==== functionals ====
Op::Op(string V):Sym("op",V) {}							// ---- operator ----
Sym* Op::eval() {
	if (val=="=") {	assert(nest.size()==2);
		return nest[0]->eq(nest[1]->eval()); }
	Sym::eval();
	if (nest.size()==2) {
		if (val=="doc")	return nest[0]->doc(nest[1]);
		if (val=="@")	return nest[0]->at(nest[1]);
	}
	return this; }

Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }			// ---- function ----
Sym* Fn::at(Sym*o) { return fn(o); }

														// ==== file io ====

Sym* dir(Sym*o) { return new Dir(o->val); }				// ---- directory ----
string Dir::tagval() { return tagstr(); }

map<string, Sym*> env;									// \ global environment
void env_init() {										// /
	// ---- metainformation ----
	env["MODULE"]	=new Str(MODULE);
	env["TITLE"]	=new Str(TITLE);
	// ---- specials ----
	env["N"] = N;	env["T"] = T;	env["F"] = F;
	env["E"] = E;	env["D"] = D;
	// ---- file io ----
	env["dir"]		=new Fn("dir",dir);
}

