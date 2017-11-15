# `Tarbomb Game` - Inspired by xkcd

## Description:
![xkcd image #1168](https://imgs.xkcd.com/comics/tar.png)

## Building with Makefile
Must be compiled with `-lncurses` flag as well as `-std=c++11`, so a makefile
has been included as well. Use the bash `make` command in the directory to produce
the tarbombgame executable. You need ncurses to compile it, but every installation
of linux since the 90s should have that at the very least. Not compatable with
Windows currently.

## Acceptable inputs.
`tar` must be used at the start. Flags are not required and it will accept
multiple flags like `-t -v -c`. Only one or none are acceptable. Auto flag is
also unacceptable.

## Improvements for the future?
- [ ] Ncurses may perform unexpectedly in some terminal emulators.
- [ ] Ncurses may not link during compiling on some systems.
- [ ] Add color.
- [ ] Exploding animation.
- [ ] Add bomb graphic.
- [ ] Resize with changes in terminal size.
- [ ] Greater options on tar command, possibly with regex or a file input.
- [ ] Allow use of arrow keys to edit input.
- [ ] Better makefile design?