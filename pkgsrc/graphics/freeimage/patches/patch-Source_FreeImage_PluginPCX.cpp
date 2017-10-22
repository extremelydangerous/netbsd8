$NetBSD: patch-Source_FreeImage_PluginPCX.cpp,v 1.1 2017/02/20 08:00:42 snj Exp $

Fix CVE-2015-0852.

http://freeimage.cvs.sourceforge.net/viewvc/freeimage/FreeImage/Source/FreeImage/PluginPCX.cpp?r1=1.17&r2=1.18&pathrev=MAIN

--- Source/FreeImage/PluginPCX.cpp.orig	2015-03-02 02:07:08.000000000 -0800
+++ Source/FreeImage/PluginPCX.cpp	2017-02-19 23:39:07.000000000 -0800
@@ -30,7 +30,7 @@
 //   Constants + headers
 // ----------------------------------------------------------
 
-#define IO_BUF_SIZE	2048
+#define PCX_IO_BUF_SIZE	2048
 
 // ----------------------------------------------------------
 
@@ -120,17 +120,17 @@ readline(FreeImageIO &io, fi_handle hand
 
 		while (length--) {
 			if (count == 0) {
-				if (*ReadPos >= IO_BUF_SIZE - 1 ) {
-					if (*ReadPos == IO_BUF_SIZE - 1) {
+				if (*ReadPos >= PCX_IO_BUF_SIZE - 1 ) {
+					if (*ReadPos == PCX_IO_BUF_SIZE - 1) {
 						// we still have one BYTE, copy it to the start pos
 
-						*ReadBuf = ReadBuf[IO_BUF_SIZE - 1];
+						*ReadBuf = ReadBuf[PCX_IO_BUF_SIZE - 1];
 
-						io.read_proc(ReadBuf + 1, 1, IO_BUF_SIZE - 1, handle);
+						io.read_proc(ReadBuf + 1, 1, PCX_IO_BUF_SIZE - 1, handle);
 					} else {
 						// read the complete buffer
 
-						io.read_proc(ReadBuf, 1, IO_BUF_SIZE, handle);
+						io.read_proc(ReadBuf, 1, PCX_IO_BUF_SIZE, handle);
 					}
 
 					*ReadPos = 0;
@@ -346,19 +346,9 @@ Load(FreeImageIO *io, fi_handle handle, 
 	BOOL header_only = (flags & FIF_LOAD_NOPIXELS) == FIF_LOAD_NOPIXELS;
 
 	try {
-		// check PCX identifier
-
-		long start_pos = io->tell_proc(handle);
-		BOOL validated = pcx_validate(io, handle);		
-		io->seek_proc(handle, start_pos, SEEK_SET);
-		if(!validated) {
-			throw FI_MSG_ERROR_MAGIC_NUMBER;
-		}
-
-		// process the header
-
 		PCXHEADER header;
 
+		// process the header
 		if(io->read_proc(&header, sizeof(PCXHEADER), 1, handle) != 1) {
 			throw FI_MSG_ERROR_PARSING;
 		}
@@ -366,20 +356,38 @@ Load(FreeImageIO *io, fi_handle handle, 
 		SwapHeader(&header);
 #endif
 
-		// allocate a new DIB
+		// process the window
+		const WORD *window = header.window;	// left, upper, right,lower pixel coord.
+		const int left		= window[0];
+		const int top		= window[1];
+		const int right		= window[2];
+		const int bottom	= window[3];
 
-		unsigned width = header.window[2] - header.window[0] + 1;
-		unsigned height = header.window[3] - header.window[1] + 1;
-		unsigned bitcount = header.bpp * header.planes;
+		// check image size
+		if((left >= right) || (top >= bottom)) {
+			throw FI_MSG_ERROR_PARSING;
+		}
 
-		if (bitcount == 24) {
-			dib = FreeImage_AllocateHeader(header_only, width, height, bitcount, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
-		} else {
-			dib = FreeImage_AllocateHeader(header_only, width, height, bitcount);			
+		const unsigned width = right - left + 1;
+		const unsigned height = bottom - top + 1;
+		const unsigned bitcount = header.bpp * header.planes;
+
+		// allocate a new dib
+		switch(bitcount) {
+			case 1:
+			case 4:
+			case 8:
+				dib = FreeImage_AllocateHeader(header_only, width, height, bitcount);
+				break;
+			case 24:
+				dib = FreeImage_AllocateHeader(header_only, width, height, bitcount, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
+				break;
+			default:
+				throw FI_MSG_ERROR_DIB_MEMORY;
+				break;
 		}
 
 		// if the dib couldn't be allocated, throw an error
-
 		if (!dib) {
 			throw FI_MSG_ERROR_DIB_MEMORY;
 		}
@@ -426,19 +434,23 @@ Load(FreeImageIO *io, fi_handle handle, 
 
 				if (palette_id == 0x0C) {
 					BYTE *cmap = (BYTE*)malloc(768 * sizeof(BYTE));
-					io->read_proc(cmap, 768, 1, handle);
 
-					pal = FreeImage_GetPalette(dib);
-					BYTE *pColormap = &cmap[0];
+					if(cmap) {
+						io->read_proc(cmap, 768, 1, handle);
 
-					for(int i = 0; i < 256; i++) {
-						pal[i].rgbRed   = pColormap[0];
-						pal[i].rgbGreen = pColormap[1];
-						pal[i].rgbBlue  = pColormap[2];
-						pColormap += 3;
+						pal = FreeImage_GetPalette(dib);
+						BYTE *pColormap = &cmap[0];
+
+						for(int i = 0; i < 256; i++) {
+							pal[i].rgbRed   = pColormap[0];
+							pal[i].rgbGreen = pColormap[1];
+							pal[i].rgbBlue  = pColormap[2];
+							pColormap += 3;
+						}
+
+						free(cmap);
 					}
 
-					free(cmap);
 				}
 
 				// wrong palette ID, perhaps a gray scale is needed ?
@@ -463,12 +475,12 @@ Load(FreeImageIO *io, fi_handle handle, 
 			return dib;
 		}
 
-		// calculate the line length for the PCX and the DIB
+		// calculate the line length for the PCX and the dib
 
 		// length of raster line in bytes
-		unsigned linelength = header.bytes_per_line * header.planes;
-		// length of DIB line (rounded to DWORD) in bytes
-		unsigned pitch = FreeImage_GetPitch(dib);
+		const unsigned linelength = header.bytes_per_line * header.planes;
+		// length of dib line (rounded to DWORD) in bytes
+		const unsigned pitch = FreeImage_GetPitch(dib);
 
 		// run-length encoding ?
 
@@ -478,14 +490,18 @@ Load(FreeImageIO *io, fi_handle handle, 
 		// ---------------
 
 		line = (BYTE*)malloc(linelength * sizeof(BYTE));
-		if(!line) throw FI_MSG_ERROR_MEMORY;
+		if(!line) {
+			throw FI_MSG_ERROR_MEMORY;
+		}
 		
-		ReadBuf = (BYTE*)malloc(IO_BUF_SIZE * sizeof(BYTE));
-		if(!ReadBuf) throw FI_MSG_ERROR_MEMORY;
+		ReadBuf = (BYTE*)malloc(PCX_IO_BUF_SIZE * sizeof(BYTE));
+		if(!ReadBuf) {
+			throw FI_MSG_ERROR_MEMORY;
+		}
 		
 		bits = FreeImage_GetScanLine(dib, height - 1);
 
-		int ReadPos = IO_BUF_SIZE;
+		int ReadPos = PCX_IO_BUF_SIZE;
 
 		if ((header.planes == 1) && ((header.bpp == 1) || (header.bpp == 8))) {
 			BYTE skip;
@@ -497,7 +513,7 @@ Load(FreeImageIO *io, fi_handle handle, 
 				// skip trailing garbage at the end of the scanline
 
 				for (unsigned count = written; count < linelength; count++) {
-					if (ReadPos < IO_BUF_SIZE) {
+					if (ReadPos < PCX_IO_BUF_SIZE) {
 						ReadPos++;
 					} else {
 						io->read_proc(&skip, sizeof(BYTE), 1, handle);
@@ -513,7 +529,9 @@ Load(FreeImageIO *io, fi_handle handle, 
 			unsigned x, y, written;
 
 			buffer = (BYTE*)malloc(width * sizeof(BYTE));
-			if(!buffer) throw FI_MSG_ERROR_MEMORY;
+			if(!buffer) {
+				throw FI_MSG_ERROR_MEMORY;
+			}
 
 			for (y = 0; y < height; y++) {
 				written = readline(*io, handle, line, linelength, bIsRLE, ReadBuf, &ReadPos);
@@ -532,7 +550,7 @@ Load(FreeImageIO *io, fi_handle handle, 
 					}
 				}
 
-				// then write the DIB row
+				// then write the dib row
 
 				for (x = 0; x < width / 2; x++) {
 					bits[x] = (buffer[2*x] << 4) | buffer[2*x+1];
@@ -541,7 +559,7 @@ Load(FreeImageIO *io, fi_handle handle, 
 				// skip trailing garbage at the end of the scanline
 
 				for (unsigned count = written; count < linelength; count++) {
-					if (ReadPos < IO_BUF_SIZE) {
+					if (ReadPos < PCX_IO_BUF_SIZE) {
 						ReadPos++;
 					} else {
 						io->read_proc(&skip, sizeof(BYTE), 1, handle);