$NetBSD: patch-Makefile.PL,v 1.1 2017/06/07 14:42:25 ryoon Exp $

* Fix build with Perl 5.26.0

--- Makefile.PL.orig	2008-01-15 21:58:35.000000000 +0000
+++ Makefile.PL
@@ -1,3 +1,5 @@
+use FindBin;
+use lib $FindBin::Bin;
 use inc::Module::Install;
 
 name 'Context-Preserve';
