$NetBSD$

--- libretroshare/src/dbase/findex.h.orig	2017-10-24 21:56:21.784813812 +0000
+++ libretroshare/src/dbase/findex.h
@@ -27,7 +27,7 @@
 #include <string>
 #include <map>
 #include <set>
-#if __MACH__
+#if __MACH__ || defined(__clang__)
 #include <unordered_set>
 #else
 #include <tr1/unordered_set>
@@ -250,7 +250,7 @@ class FileIndex
 
 		PersonEntry *root;
 
-#ifdef __MACH__
+#if __MACH__ || defined(__clang__)
 		static std::unordered_set<void*> _pointers ;
 #else
 		static std::tr1::unordered_set<void*> _pointers ;
