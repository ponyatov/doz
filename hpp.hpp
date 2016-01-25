#ifndef _H_DOS
#define _H_DOS
										// ==== metainformation ====

#define TITLE "# [d]ymaniac [o]bject [s]ystem"
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/dos"
#define LOGO "Rubik_64x64"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

struct Sym {							// ==== abstract symbolic type ====
	string tag;							// data tag / class
	string val;							// value
	Sym(string,string);					// <T:V> \ ---- constructors ----
	Sym(string);						// token /
	vector<Sym*> nest;					// \ ---- nest[]ed elements ----
	void push(Sym*);					// /
	map<string,Sym*> par;				// \ ---- par{}ameters ----
	void partag(Sym*);					//   par[obj.tag]=obj
	void parval(Sym*);					// / par[obj.val]=obj
	string dump(int depth=0);			// \ ---- dump as text ----
	string pad(int);
	virtual string tagval();			// <T:V> header string
	virtual Sym* eval();				// ---- compute (evaluate) object ----
	virtual Sym* doc(Sym*);				// A "B"
	virtual Sym* eq(Sym*);				// A = B
	virtual Sym* at(Sym*);				// A @ B
	virtual Sym* add(Sym*);				// A + B
	virtual Sym* div(Sym*);				// A / B
	virtual Sym* ins(Sym*);				// A += B
	virtual Sym* str();					// str(A)
};
extern map<string, Sym*> env;			// \ ==== global environment ====
extern void env_init();					// /

extern void W(Sym*);					// \ ==== writers ====
extern void W(string);					// /

										// ==== directive ====
struct Directive:Sym { Directive(string); };

										// ==== scalars ====

										// ---- specials ----
extern Sym* N;							// nil/false
extern Sym* T;							// true
extern Sym* F;							// false
extern Sym* E;							// error
extern Sym* D;							// default
extern Sym* Rd;							// read
extern Sym* Wr;							// write

struct Str:Sym { Str(string); 			// ---- string ----
	Sym*add(Sym*o); };

										// ==== composites ====
struct List:Sym { List(); 				// [list]
	Sym*str(); Sym*div(Sym*); };

										// ==== functionals ====
struct Op:Sym { Op(string); Sym*eval(); };
typedef Sym*(*FN)(Sym*);
struct Fn:Sym { Fn(string,FN); FN fn; Sym*at(Sym*); };

										// ==== file io ====
struct Dir:Sym { Dir(string); Sym* add(Sym*); };
extern Sym* dir(Sym*);
struct File:Sym { File(string); FILE *fh; ~File(); Sym*ins(Sym*); };
extern Sym* file(Sym*);

extern int yylex();						// \ ==== lexer interface /flex/ ====
extern int yylineno;
extern char* yytext;
extern int yyparse();					// \ ==== parser interface /bison/ ====
extern void yyerror(string);			// / error callback
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
#include "ypp.tab.hpp"					// tokens definitions

#if __MINGW32__
#include "win32.hpp"
#endif

#endif // _H_DOS
