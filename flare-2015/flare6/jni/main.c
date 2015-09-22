#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <jni.h>

#include "strs2.h"

int (*check)(JNIEnv *, void * obj, jstring);

jsize   MyGetStringLength(JNIEnv*env, jstring s)
{
	const char *ss = (char *)s;
	printf("get string length : %d\n", ss);fflush(stdout);
	return strlen(ss);
}

jsize MyGetStringUTFLength(JNIEnv *env, jstring s)
{
	const char *ss = (char *)s;
	printf("\nget string utf length : %d\n", ss);
	fflush(stdout);
	return strlen(ss);
}

jstring  MyNewStringUTF(JNIEnv*env, const char*s)
{
	//	printf("new string utf chars :  %s\n", s);fflush(stdout);
	return (jstring)strdup(s);
}

const char* MyGetStringUTFChars(JNIEnv *env, jstring s, jboolean* isCopy)
{
	const char *ss = (char *)s;
	//printf("get string utf chars : %p %d\n", ss, strlen(ss));fflush(stdout);
	return strdup(ss);
}

void     MyReleaseStringUTFChars(JNIEnv*env, jstring ss, const char*s)
{
	free(s);
	//printf("Release string UTF8 %s\n", s);
}


int test()
{
	printf("****** test called\n");fflush(stdout);
	return 0;
}


char rootparam[] = "______________________________________________";
//char rootparam[] = "Should_havAYg0ne_to_tashi_$tatio_@flare-on.com";

int main(int argc, char *argv[])
{
	struct JNINativeInterface *myenv;
	myenv = malloc(sizeof(struct JNINativeInterface));
	int l = sizeof(struct JNINativeInterface);
	printf("size of interface: %d\n", l);
	int i;
	int *intf = (int*)myenv;
	printf("count methods = %d\n", l/4);
	for(i=0; i < l/4; i++) {
		intf[i] = test;
	}

	myenv->GetStringLength = MyGetStringLength;
	myenv->GetStringUTFLength = MyGetStringUTFLength;
	myenv->GetStringUTFChars = MyGetStringUTFChars;
	myenv->ReleaseStringUTFChars = MyReleaseStringUTFChars;
	myenv->NewStringUTF = MyNewStringUTF;

	void *f = dlopen("/data/local/tmp/libvalidate.so", RTLD_NOW);
	printf("Error %p f-pointer = %p\n", dlerror(), f);
	check = dlsym(f, "Java_com_flareon_flare_ValidateActivity_validate");
	printf("pointer = %p", check);

	/* check(&myenv, 1, (jstring)"Should_havAYg0ne_to_tashi_$tation@flare-on.com"); */
	/* exit(0); */
	
	int repos = 0; //replace position
	int found = 0;
	while (repos<46) {
		strrchr(0, 1 + (repos/2)); //set current pair
		found = 0;
		for (i=0; pairs[i]; i++) {
			//printf("testing i %d\n", i);
			const char *xx = pairs[i];
			strrchr(xx, -1);
			int j;
			rootparam[repos] = xx[0];
			rootparam[repos+1] = xx[1];
			check(&myenv, 1, (jstring)rootparam);
			if (strrchr(xx, -2)) {
				printf("GOT %d %s\n", repos, rootparam);
				repos += 2;
				found = 1;
				break;
			}
		}
		if (!found) {
			printf("ERROR: not found");
			break;
		}
	}
		//root(0, 0, 0);
	//root(0);
	printf("hello world\n");fflush(stdout);
	return 0;
}
