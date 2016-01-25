# lexical fileset skeleton

next		= dir @ MODULE					"next generation dos"

readme		= next + file @ 'README.md'		"README"
files		= [
do			= next + file @ 'do.do'
log			= next + file @ 'log.log'
ypp			= next + file @ 'ypp.ypp'		"parser /bison/"
lpp			= next + file @ 'lpp.lpp'		"lexer /flex/"
hpp			= next + file @ 'hpp.hpp'		"c++ core headers"
cpp			= next + file @ 'cpp.cpp'		"c++ core code"
win32h		= next + file @ 'win32.hpp'
win32c		= next + file @ 'win32.cpp'
make		= next + file @ 'Makefile'
]
bat			= next + file @ 'bat.bat'		"(g)vim helper"
win32rc		= next + file @ 'rc.rc'			"win32 resources"
gitignore	= next + file @ '.gitignore'

# README

readme += '# ![logo](https://github.com/ponyatov/icons/raw/master/'+LOGO+'.png) '
readme += MODULE+' : '+TITLE+'\n'
readme += '### '+ABOUT+'\n'
readme += '\n'+AUTHOR+'\n'
readme += '\nlicense: '+LICENSE+'\n'
readme += '\nGitHub: '+GITHUB+'\n'

# bat

bat += '@start .\n'
bat += '@gvim -c "colorscheme peachpuff" -p '+files/' '+'\n'

# .gitignore

gitignore += '*~\n*.swp\n*.exe\n*.*log\nypp.tab.?pp\nlex.yy.c\nres.res\n'
gitignore += MODULE+'/\n'

