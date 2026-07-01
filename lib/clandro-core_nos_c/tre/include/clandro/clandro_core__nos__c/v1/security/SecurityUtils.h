#ifndef LIBCLANDRO_CORE__NOS__C__SECURITY_UTILS___H
#define LIBCLANDRO_CORE__NOS__C__SECURITY_UTILS___H

#ifdef __cplusplus
extern "C" {
#endif



/**
 * Generate a 32bytes/256bit UUID.
 *
 * The buffer size must at least be `69`.
 *
 * @param logTag The log tag to use for logging.
 * @param buffer The output uuid buffer.
 * @param bufferSize The output uuid buffer size.
 * @return Returns the `char *` to uuid on success, otherwise `NULL`
 * on failures.
 */
char * generateUuid(const char* logTag, char *buffer, size_t bufferSize);



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__SECURITY_UTILS___H
