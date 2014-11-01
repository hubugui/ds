#ifndef __FILE_RW__
#define __FILE_RW__

#ifdef __cplusplus
extern "C" {
#endif

unsigned char *file_read(const char *filepath, size_t size);
size_t file_write(const char *filepath, size_t size, unsigned char *buffer);

#ifdef __cplusplus
#endif
#endif
