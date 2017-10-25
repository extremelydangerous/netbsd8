$NetBSD$

--- libbitdht/src/util/bdthreads.cc.orig	2017-10-24 21:38:03.342075076 +0000
+++ libbitdht/src/util/bdthreads.cc
@@ -129,7 +129,7 @@ void bdThread::join() /* waits for the t
 #if defined(_WIN32) || defined(__MINGW32__)
 	/* Its a struct in Windows compile and the member .p ist checked in the pthreads library */
 #else
-	if(mTid > 0)
+	if(mTid)
 #endif
 		pthread_join(mTid, NULL);
 
