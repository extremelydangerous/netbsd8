$NetBSD$

--- imap/sync_client.c.orig	2012-12-01 19:57:54.000000000 +0000
+++ imap/sync_client.c
@@ -573,7 +573,7 @@ static int folder_unannotation(const cha
 /* ====================================================================== */
 
 static int sieve_upload(const char *userid, const char *filename,
-			unsigned long last_update)
+			time_t last_update)
 {
     const char *cmd = "SIEVE";
     struct dlist *kl;
@@ -913,9 +913,9 @@ static void log_record(const char *name,
 		       struct index_record *record)
 {
     syslog(LOG_NOTICE, "SYNCNOTICE: %s uid:%u modseq:" MODSEQ_FMT " "
-	  "last_updated:%lu internaldate:%lu flags:(%s)",
+	  "last_updated:" MODSEQ_FMT " internaldate:" MODSEQ_FMT " flags:(%s)",
 	   name, record->uid, record->modseq,
-	   record->last_updated, record->internaldate,
+	   (modseq_t)record->last_updated, (modseq_t)record->internaldate,
 	   make_flags(mailbox, record));
 }
 
