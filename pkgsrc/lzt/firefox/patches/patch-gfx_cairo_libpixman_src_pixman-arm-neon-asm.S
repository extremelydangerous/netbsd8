$NetBSD$

--- gfx/cairo/libpixman/src/pixman-arm-neon-asm.S.orig	2016-05-12 17:13:35.000000000 +0000
+++ gfx/cairo/libpixman/src/pixman-arm-neon-asm.S
@@ -34,6 +34,12 @@
  *  - pixman_composite_over_n_8_0565_asm_neon
  */
 
+#if defined(__ARM_EABI__) && !defined(__ARM_DWARF_EH__)
+#define UNWIND
+#else
+#define UNWIND @
+#endif
+
 /* Prevent the stack from becoming executable for no reason... */
 #if defined(__linux__) && defined(__ELF__)
 .section .note.GNU-stack,"",%progbits
@@ -3141,7 +3147,8 @@ pixman_asm_function fname
     TMP4      .req      r9
     STRIDE    .req      r2
 
-    .fnstart
+    .cfi_startproc
+    UNWIND .fnstart
     mov       ip, sp
     .save     {r4, r5, r6, r7, r8, r9}
     push      {r4, r5, r6, r7, r8, r9}
@@ -3244,7 +3251,8 @@ pixman_asm_function fname
 .endif
     pop       {r4, r5, r6, r7, r8, r9}
     bx        lr
-    .fnend
+    UNWIND .fnend
+    .cfi_endproc
 
     .unreq    OUT
     .unreq    TOP
