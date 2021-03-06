$NetBSD$

--- modules/inotify-kernel.c.orig	2010-02-09 12:16:14.000000000 +0000
+++ modules/inotify-kernel.c
@@ -30,6 +30,9 @@
 #include <glib.h>
 #include "inotify-kernel.h"
 #include <sys/inotify.h>
+#ifdef __sun
+#include <sys/filio.h>
+#endif
 
 /* Timings for pairing MOVED_TO / MOVED_FROM events */
 #define PROCESS_EVENTS_TIME 1000 /* milliseconds (1 hz) */
