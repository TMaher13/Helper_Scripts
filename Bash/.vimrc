" Configuration for vim editor 

" Enable syntax highlighting
syntax on

" Set tab as 4 spaces
set expandtab
set tabstop=4
set shiftwidth=4

" Auto-indent when starting new lines
set autoindent

" Show line numbers 
set number

" Show column and line number
set ruler

" Correct formatting for Makefiles
filetype on
filetype plugin on
filetype indent on

autocmd FileType make noexpandtab shiftwidth=8 softtabstop=0
