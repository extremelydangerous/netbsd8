$NetBSD$

--- olwm/winicon.c.orig	1993-06-29 05:12:04.000000000 +0000
+++ olwm/winicon.c
@@ -1,4 +1,3 @@
-#ident	"@(#)winicon.c	26.42	93/06/28 SMI"
 
 /*
  *      (c) Copyright 1989 Sun Microsystems, Inc.
@@ -32,6 +31,10 @@
 extern 	Bool	PropGetWMName();
 extern 	Bool	PropGetWMIconName();
 
+static int heightTopIcon();
+static int heightBottomIcon();
+static int widthBothIcon();
+
 /***************************************************************************
 * private data
 ***************************************************************************/
