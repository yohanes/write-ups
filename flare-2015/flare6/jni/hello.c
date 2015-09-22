#include <stdlib.h>
#include <dlfcn.h>
void (*orig_memset)(void *s, int c, size_t n) = 0;

#define PREP_OVERRIDE(syscall) do {		\
	if (!orig_##syscall) {\
		  orig_##syscall = dlsym(RTLD_NEXT, #syscall);\
	} } while (0)

int _pos_ = 0;
int _ctr_ = 0;
int _stop_ = 0;
int _correct_ = 0;

//hack to call from main, hopefully not called from somewhere else
char *strrchr(const char *string, int c)
{
	if (string==0) {
		//printf("correct count = %d\n", c);
		_pos_ = c;
		return 0;
	}
	
	//printf("STRCHR %d", c);
	if (c==-2) {
		//printf("correct  %d pos %d\n", _correct_, _pos_);
		return _correct_>=_pos_;
	}
	
	if (c==-1) {
		//printf("reset state");
		_ctr_= 0;
		_stop_ = 0;
		_correct_ = 0;		
	}
	return 0;
}
	
void *memset(void *s, int c, size_t n)
{
	PREP_OVERRIDE(memset);
	//printf("j_j_memset %d\n", n);
	//	_ctr_++;
	orig_memset(s, c, n);
}


size_t (*orig_strlen)(const char *s);

size_t strlen(const char *s)
{
	PREP_OVERRIDE(strlen);
	if (_stop_) {
		return 0;
	}
	
       	size_t sl = orig_strlen(s);
	//	printf("strlen = %d\n", sl);
	return sl;
}

int (*orig_memcmp)(const void *s1, const void *s2, size_t n);

int memcmp(const void *s1, const void *s2, size_t n)
{
	PREP_OVERRIDE(memcmp);
	int sl = orig_memcmp(s1,s2,n);

	if (sl==0) {
		//printf("memcmp sz = %d = %d\n", n, sl);
		_correct_++;
		//printf("_cor = %d pos = %d\n", _correct_, _pos_);
		if (_correct_==_pos_) {
			_stop_ = 1;
		}
	} else {
		_stop_ = 1;
	}
	return sl;
}
