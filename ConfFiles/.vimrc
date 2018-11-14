" AUTHOR:
" COPYRIGHT (C) KARLKORP
" VIM CONFIGURATION FILE
" E-MAIL: LISPGOD@GMAIL.COM

" =============================================================================
set nocompatible

" =============================================================================
filetype plugin indent on
syntax enable

" =============================================================================
set nopaste
set clipboard=unnamed
set cryptmethod=blowfish
runtime macros/matchit.vim

" =============================================================================


set buftype=
set smarttab
set expandtab
set tabstop=4
set shiftround
set shiftwidth=4
set softtabstop=4
set autoindent
set copyindent
set smartindent

" =============================================================================
set nojoinspaces

" =============================================================================
set nobackup
set noswapfile
set virtualedit=block

" =============================================================================
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,cp1251,koi8-r
set fileformat=unix
set fileformats=unix,dos,mac

" =============================================================================
set backspace=indent,eol,start
set complete=.,b,d,i,k,s,t,U,u,w
set omnifunc=syntaxcomplete#Complete
set completeopt=longest,menu,menuone,preview
set pumheight=7
set cinwords=class,def,do,elif,else,except
set cinwords+=finally,for,if,switch,try,while,with
set sessionoptions=blank,buffers,curdir,folds,help
set sessionoptions+=options,slash,tabpages,unix,winsize

" =============================================================================
if (&filetype == "lisp")
    set lisp
endif

" =============================================================================
set autoread
set autowrite
set autochdir

" =============================================================================
set cmdheight=1
set cmdwinheight=7
set textwidth=80
set colorcolumn=81

" =============================================================================
set foldenable
set foldclose=""
set foldcolumn=1
set foldlevel=10
set foldlevelstart=10
set foldmethod=indent
set foldopen=block,hor,mark,percent,quickfix,search,tag,undo

" =============================================================================
set hidden
set hlsearch
set incsearch
set smartcase
set infercase
set ignorecase
set iminsert=0
set imsearch=0
set helplang=en
set langmenu=en
language messages POSIX

" =============================================================================
set lazyredraw
set list
set listchars=tab:>~,trail:.
set showmatch
set matchpairs=<:>,(:),{:},[:]
set modeline
set modelines=1

" =============================================================================
set mouse=a
set mousehide
set mousemodel=extend

" =============================================================================
set noconfirm
set nocursorline
set nocursorcolumn
set magic
set nogdefault
set noruler
set nospell
set spelllang=en_us
set noerrorbells
set novisualbell

" =============================================================================
set number
set numberwidth=3
set relativenumber
set report=0
set scrolloff=10
set scrolljump=10
set shortmess=I
set showcmd
set showfulltag
set noshowmode
set splitbelow
set splitright
set equalalways

" =============================================================================
set laststatus=2
set statusline=%F%r%h%w
set statusline+=\ %m
set statusline+=\ %=%y
set statusline+=\ [%{&ff}]
set statusline+=\ Buffer:[%n]
set statusline+=\ Column:[%v]
set statusline+=\ Line:%l/%L[%p%%]
set statusline+=\ Mode:[%{ShowCurrentMode()}]
" =============================================================================
set switchbuf=newtab,split,useopen,usetab
set tabline=""
set showtabline=2
set timeout
set timeoutlen=3000
set ttimeoutlen=100
set title
set ttyfast
set history=1000
set undolevels=5000
set viewoptions=cursor,folds,options,slash,unix

" =============================================================================
set wildmenu
set wildmode=longest:full,full
set wildignore=*.bak,*.bin,*.class,*.exe,*.o,*.obj,*.pyc,*.pyo,*.swp
set wrap
set wrapscan
set nolinebreak
set whichwrap=<,>,[,]

" =============================================================================
set t_Co=256
colorscheme default
set background=light
if has("gui_running")
    winsize 111 37
    set linespace=0
    silent! cd $HOME
    set guioptions=""
    set guitablabel=""
    try
        if has("mac")
            set antialias
            set guifont=Monaco:h12
        elseif has("unix")
            set guifont=DejaVu\ Sans\ Mono\ 12
        elseif (has("win32") || has("win64"))
            set guifont=DejaVu_Sans_Mono:h12
        endif
    catch /.*/
        echoerr "Font not listed in the system font list!"
    endtry
    highlight ColorColumn guibg=NONE guifg=#FF0000 gui=BOLD
    highlight FoldColumn guibg=NONE guifg=#000000 gui=NONE
else
    highlight ColorColumn ctermbg=NONE ctermfg=1* cterm=BOLD
    highlight FoldColumn ctermbg=NONE ctermfg=0 cterm=NONE
endif

" =============================================================================
function! FormatFile()
    silent! normal ml
    silent! normal gg=G
    silent! %s/\s\+$//e
    silent! normal 'lzz
    silent! delmarks l
endfunction

" =============================================================================
function! ShowCurrentMode()
    let s:showMode = ""
    let s:currentMode = mode()
    if (s:currentMode ==# "i")
        let s:showMode = "Insert"
    elseif (s:currentMode ==# "R")
        let s:showMode = "Replace"
    elseif (s:currentMode ==# "n")
        let s:showMode = "Normal"
    else
        let s:showMode = "Visual"
    endif
    return s:showMode
endfunction

" =============================================================================
function! UseTemplates(type)
    let s:scriptLine = "#!/usr/bin/env "
    let s:scriptEncoding = "# -*- coding: utf-8 -*-"
    if (a:type == "sh")
        execute setline(1, s:scriptLine . "bash")
        execute setline(2, "")
    elseif (a:type == "perl")
        execute setline(1, s:scriptLine . "perl")
        execute setline(2, "")
        execute setline(3, "use strict;")
        execute setline(4, "use warnings;")
        execute setline(5, "")
    elseif (a:type == "python")
        execute setline(1, s:scriptLine . "python")
        execute setline(2, s:scriptEncoding)
        execute setline(3, "")
    endif
    silent! normal Go
endfunction

" =============================================================================
function! Run()
    silent! write
    try
        if (&filetype == "perl")
            execute "!perl %"
        elseif (&filetype == "python")
            execute "!python %"
        elseif ((&filetype == "sh") && (has("unix") || has("mac")))
            execute "!sh %"
        else
            return
        endif
    catch /.*/
        echoerr "Error while calling function: Run()"
    endtry
endfunction

" =============================================================================
function! MakeExecutable()
    if ((getline(1) =~ "#!") && (getline(1) =~ "bin/"))
        silent! execute "!chmod a+x <afile>"
    endif
endfunction

" =============================================================================
if has("autocmd")
    augroup BeforeWritingFile
        autocmd!
        autocmd BufWritePre * retab
        autocmd BufWritePre * call FormatFile()
    augroup END
    augroup AfterWritingFile
        autocmd!
        autocmd BufWritePost $MYVIMRC source $MYVIMRC
        if (has("unix") || has("mac"))
            autocmd BufWritePost * call MakeExecutable()
        endif
    augroup END
    augroup CreateNewFile
        autocmd!
        autocmd BufNewFile *.sh call UseTemplates("sh")
        autocmd BufNewFile *.pl,*.pm call UseTemplates("perl")
        autocmd BufNewFile *.py,*.pyw call UseTemplates("python")
    augroup END
endif





" =============================================================================
cnoreabbrev q q!
cnoreabbrev Q q!
cnoreabbrev w w!
cnoreabbrev W w!
let mapleader=","
nnoremap j gj
nnoremap k gk
nnoremap <C-h> <C-W>h
nnoremap <C-j> <C-W>j
nnoremap <C-k> <C-W>k
nnoremap <C-l> <C-W>l
nnoremap <silent>n nzz
nnoremap <silent>N Nzz
nnoremap <silent>* *zz
nnoremap <silent># #zz
nnoremap // :nohlsearch<Return>
nnoremap <leader>r :call Run()<Return>
vnoremap < <gv
vnoremap > >gv

"for prefix in ['i', 'n', 'v']
"    for key in ['<Up>', '<Down>', '<Left>', '<Right>']
"        execute prefix . "noremap " . key . " <Nop>"
"    endfor
"endfor


"================================================================================

"НАСТРОЙКИ ГОРЯЧИХ КЛАВИШ
" F2 - сохранить файл
nmap <F2> :w<cr>
vmap <F2> <esc>:w<cr>i
imap <F2> <esc>:w<cr>i
" F3 - рекурсивный поиск по файлам (плагин grep.vim)
nnoremap <silent> <F3> :Rgrep<cr>
" Shift-F<F3> - добавление найденного к прошлым результатам поиска
nnoremap <silent> <S-F<F3>> :RgrepAdd<cr>
" Ctrl-F<F3> - поиск в открытых буферах
nnoremap <silent> <C-F<F3>> :GrepBuffer<cr>
" F5 - просмотр списка буферов
nmap <F5> <Esc>:buffers<cr>
vmap <F5> <esc>:buffers<cr>
imap <F5> <esc><esc>:buffers<cr>a
" при включенном плагине можно использовать его
nmap <S-F5> :BufExplorer<CR>
" F6 - предыдущий буфер
map <F6> :bp<cr>
vmap <F6> <esc>:bp<cr>i
imap <F6> <esc>:bp<cr>i
" F7 - следующий буфер
map <F7> :bn<cr>
vmap <F7> <esc>:bn<cr>i
imap <F7> <esc>:bn<cr>i
" F9 - сохранение файла и запуск компиляции (make)
map <F9> :w<cr>:make<cr>
vmap <F9> <esc>:w<cr>:make<cr>i
imap <F9> <esc>:w<cr>:make<cr>i
"




"
" F11 - включить-выключить нумерацию строк
imap <F11> <Esc>:set<Space>nu!<CR>a
nmap <F11> :set<Space>nu!<CR>

" F12 - обозреватель файлов (:Ex для стандартного обозревателя,
" плагин NERDTree - дерево каталогов)
map <F12> :Explore<cr>
vmap <F12> <esc>:Explore<cr>i
imap <F12> <esc>:Explore<cr>i


" Save and make current file.o
function! Make()
    let curr_dir = expand('%:h')
    if curr_dir == ''
        let curr_dir = '.'
    endif
    echo curr_dir
    execute 'lcd ' . curr_dir
    execute 'make %:r.o'
    execute 'lcd -'
endfunction
nnoremap <F10> :update<CR>:call Make()<CR>





"" Переключение табов (вкладок) (rxvt-style)
map <S-left> :tabprevious<cr>
nmap <S-left> :tabprevious<cr>
imap <S-left> <ESC>:tabprevious<cr>i
map <S-right> :tabnext<cr>
nmap <S-right> :tabnext<cr>

imap <S-right> <ESC>:tabnext<cr>i




" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

Plugin 'SirVer/ultisnips'
Plugin 'honza/vim-snippets'
Plugin 'Valloric/YouCompleteMe'
Plugin 'jlanzarotta/bufexplorer'


Plugin 'git://GitHub.com/Wh0p/FSwitch.git'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line


let g:UltiSnipsExpandTrigger="<tab>"
let g:UltisnipsJumpForwardTrigger="<c-b>"
let g:UltisnipsJumpBackwardTrigger="<c-z>"

let g:ycm_global_ycm_extra_conf = "~/.vim/.ycm_extra_conf.py"

