This is the pkgsrc and etc files for NetBSD8 this install mate-desktop http://mate-desktop.org
from the package directory pkgsrc/lzt/mate it takes a looong time to build  more than 10 hours
in a very fast amd cpu.. it builds about 930 packages for a complete system

CLANG is build ON THE BASE SYSTEM, so there is NO gcc, no cc ... and NO libstdc++* either..
a corresponding modification is done in the /etc/mk.conf so the system MUST be compiled using the NATIVE clang
special packcages as libtool and boost are sensible to that.. 

The pkgsrc/mk is modified to include the following changes:
1) insert of a Makefile.local logic, the same as FreeBSD ports, 
2) it copies using pkgsrc logic all the packages files that installs on share/examples/rc.d -> /etc/rc.d

