#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <android/log.h>

int j_j_memcmp(const void *mem1, const void *mem2, int len)
{
    __android_log_print(ANDROID_LOG_DEBUG, "CMP", "%s %s %d", (char *)mem1, (char*)mem2, len);
	return memcmp(mem1, mem2, len);
}
