/* Created by "go tool cgo" - DO NOT EDIT. */

/* package github.com/Zumium/fyer/client */

/* Start of preamble from import "C" comments.  */


#line 3 "/mnt/hgfs/goproject/src/github.com/Zumium/fyer/client/main.go"



#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef char* char_ptr;

typedef struct {
	uint64_t size;
	unsigned char hash[16];
	uint64_t frag_count;
	time_t upload_time;
} file_info;

void set_c_str_array(char *array[], int index, char *str);

#line 1 "cgo-generated-wrapper"


/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

typedef struct { const char *p; GoInt n; } GoString;
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif


//REQUIRED

extern void SetLocalServeAddress(char* p0);

//REQUIRED

extern void SetCenterAddress(char* p0);

extern void SetPort(int p0);

extern void SetMaxSendRecvMessageSize(int p0);

extern void SetClientPort(int p0);

extern int RegisterFile(char* p0);

extern int UnregisterFile(char* p0);

extern int StartFyerworkServer();

extern void StartFyerworkServerInBackground();

extern void WaitFyerworkServer();

extern int Files(char*** p0, int* p1);

extern int FileInfo(char* p0, file_info* p1);

extern int UploadFile(char* p0, uint64_t p1, unsigned char* p2, size_t p3);

extern int DownloadFile(char* p0, char* p1);

#ifdef __cplusplus
}
#endif
