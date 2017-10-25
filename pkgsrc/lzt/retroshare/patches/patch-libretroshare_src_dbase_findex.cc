$NetBSD$

--- libretroshare/src/dbase/findex.cc.orig	2017-10-24 22:09:51.018290925 +0000
+++ libretroshare/src/dbase/findex.cc
@@ -33,7 +33,7 @@
 #include <stdlib.h>
 #include <algorithm>
 #include <iostream>
-#ifdef __MACH__
+#if __MACH__ || defined(__clang__)
 #include <unordered_set>
 #else
 #include <tr1/unordered_set>
@@ -58,7 +58,7 @@ static const char FILE_CACHE_SEPARATOR_C
  ****/
 
 static RsMutex FIndexPtrMtx("FIndexPtrMtx") ;
-#ifdef __MACH__
+#if __MACH__ || defined(__clang__)
 std::unordered_set<void*> FileIndex::_pointers ;
 #else
 std::tr1::unordered_set<void*> FileIndex::_pointers ;
