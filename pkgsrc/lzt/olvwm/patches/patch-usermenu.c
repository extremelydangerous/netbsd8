$NetBSD$

--- usermenu.c.orig	2000-03-02 21:41:31.000000000 +0000
+++ usermenu.c
@@ -193,7 +193,7 @@ extern int  StartDSDMFunc();
 extern int  StopDSDMFunc();
 
 extern int  GenWinMenuFunc();
-extern int  GenDirMenuFunc();
+void GenDirMenuFunc(Display *dpy, MenuInfo *menuInfo, int bindex, MenuCache *cache, WinGeneric *winInfo, int depth);
 extern int  StickSelnFunc();
 extern int  MoveDesktopFunc();
 
@@ -884,7 +884,7 @@ makeMenuSearchPath()
 		home = ".";
  
 	if ((owHome = getenv("OPENWINHOME")) == NULL)
-		owHome = "/usr/openwin";
+		owHome = PREFIX;
  
 	menuSearchPath = (char **)MemAlloc(NUM_SEARCH_PATH*sizeof(char *));
  
@@ -900,16 +900,6 @@ makeMenuSearchPath()
 	sprintf(buf, "%s/.%%s", home);
 	menuSearchPath[i++] = MemNewString(buf);
 
-#ifdef OW_I18N_L3
-	/* $OPENWINHOME/share/locale/<locale>/olwm/<menufile> */
-	sprintf(buf, "%s/share/locale/%%2$s/olwm/%%1$s", owHome);
-	menuSearchPath[i++] = MemNewString(buf);
-
-	/* $OPENWINHOME/lib/<menufile>.<locale> */
-	sprintf(buf, "%s/lib/%%1$s.%%2$s", owHome);
-	menuSearchPath[i++] = MemNewString(buf);
-#endif
-
 	/* $OPENWINHOME/lib/<menufile> */
 	sprintf(buf, "%s/lib/%%s", owHome);
 	menuSearchPath[i++] = MemNewString(buf);
