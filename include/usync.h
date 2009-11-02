/*****************************************************************************
 *  µSync, a small synchronization function set.                             *
 *  Copyright (C)2009 SquidMan (Alex Marshall)       <SquidMan72@gmail.com>  *
 *****************************************************************************/

#ifndef _USYNC_H

#define _USYNC_LOCK_MAX	256
/* #define _USYNC_HOLD_DATA */

/* We only use 8 bytes per sync object without holding data. */
/* Only 12bytes with (on a 32bit system that doesn't raise sizes to align) */
/* Requires no external libraries (not even a libc) */

typedef struct {
	unsigned char	enabled[8]; /* uSYNC#L_ */
#ifdef _USYNC_HOLD_DATA
	void*		data;
#endif
} uSyncObject;

int uSyncInit();
#ifdef _USYNC_HOLD_DATA
int uSyncCreate(void* data);
#else
int uSyncCreate();
#endif
int uSyncDelete(int idx);
#ifdef _USYNC_HOLD_DATA
void* uSyncObtain(int idx);
#else
int uSyncObtain(int idx);
#endif
int uSyncRelease(int idx);

#define _USYNC_H
#endif

