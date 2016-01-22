#include "hpp.hpp"

Dir::Dir(string V):Sym("dir",V) { mkdir(val.c_str()); }
