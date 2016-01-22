# lexical skeleton

next		= dir @ MODULE					"next generation dos"

readme		= next + file @ 'README.md'		"README"
bat			= next + file @ 'bat.bat'		"(g)vim helper"
win32rc		= next + file @ 'rc.rc'			"win32 resources"
gitignore	= next + file @ '.gitignore'

do			= next + file @ 'do.do'
log			= next + file @ 'log.log'
ypp			= next + file @ 'ypp.ypp'		"parser /bison/"
lpp			= next + file @ 'lpp.lpp'		"lexer /flex/"
hpp			= next + file @ 'hpp.hpp'		"c++ core headers"
cpp			= next + file @ 'cpp.cpp'		"c++ core code"
win32h		= next + file @ 'win32.hpp'
win32c		= next + file @ 'win32.cpp'
make		= next + file @ 'Makefile'

