$NetBSD$

--- shell/rb-python-module.c.orig	2010-03-25 00:10:15.000000000 +0000
+++ shell/rb-python-module.c
@@ -169,7 +169,7 @@ rb_python_module_init_python (void)
 
 	mdict = PyModule_GetDict (pygtk);
 	require = PyDict_GetItemString (mdict, "require");
-	PyObject_CallObject (require, Py_BuildValue ("(S)", PyString_FromString ("2.8")));
+	PyObject_CallObject (require, Py_BuildValue ("(S)", PyString_FromString ("2.0")));
 
 	/* import gobject */
 	init_pygobject ();
