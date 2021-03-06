$NetBSD$

--- media/mtransport/third_party/nrappkit/src/port/generic/include/sys/queue.h.orig	2016-05-12 17:13:18.000000000 +0000
+++ media/mtransport/third_party/nrappkit/src/port/generic/include/sys/queue.h
@@ -30,7 +30,13 @@
  * $FreeBSD: src/sys/sys/queue.h,v 1.58 2004/04/07 04:19:49 imp Exp $
  */
 
-#ifndef _SYS_QUEUE_H_
+#if (defined(BSD) && !defined(__OpenBSD__)) || defined(DARWIN)
+#include_next <sys/queue.h>
+# if defined(__DragonFly__)
+#define STAILQ_FOREACH_SAFE STAILQ_FOREACH_MUTABLE
+#define TAILQ_FOREACH_SAFE TAILQ_FOREACH_MUTABLE
+# endif
+#elif !defined(_SYS_QUEUE_H_)
 #define	_SYS_QUEUE_H_
 
 #include <stddef.h>
