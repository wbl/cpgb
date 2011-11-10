/*lookup store pattern*
 *searches store for pattern.*
 *pattern is key:regex*
 *prints out matching record.*
 *store is a file of records seperated by double new lines*
 *each record has lines in key:value form*
 *example: name:Bob Jones *
 *         email:bob@example.com *
 *         keytype:authorization *
 *         comment: signs my subkeys*
 *         key:<64 hex digits> *
 *keytype can be authorization, encryption, signing. Multiple keys per*
 *name and email are allowed, and comment should be used to distinguish them*
 *note that comment is user-interpreted. Be careful!*/
