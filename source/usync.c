/*****************************************************************************
 *  µSync, a small synchronization function set. Inspired by uITRON.         *
 *  Copyright (C)2009 SquidMan (Alex Marshall)       <SquidMan72@gmail.com>  *
 *****************************************************************************/

#include <usync.h>

static uSyncObject uSyncLocks[_USYNC_LOCK_MAX];
static int uSyncEnabled = 0;
static int idcnt = -1;

static int _compare(void* aq, void* bq, int size)
{
	int i;
	unsigned char* a;
	unsigned char* b;
	if(aq == bq)
		return 1;
	a = (unsigned char*)aq;
	b = (unsigned char*)bq;
	for(i = 0; i < size; i++) {
		if(a[i] != b[i])
			return 0;
	}
	return 1;
}

static void _copy(void* aq, void* bq, int size)
{
	int i;
	unsigned char* a;
	unsigned char* b;
	if(aq == bq)
		return;
	a = (unsigned char*)aq;
	b = (unsigned char*)bq;
	for(i = 0; i < size; i++) {
		a[i] = b[i];
	}
}

static void _clear(void* aq, int size)
{
	int i;
	unsigned char* a;
	a = (unsigned char*)aq;
	for(i = 0; i < size; i++)
		a[i] = 0;
}

static int validate_usync_object(int idx)
{
	uSyncObject obj = uSyncLocks[idx];
	int oid = 0;
	if(_compare(obj.enabled, "uSYNC", 5)) {
		oid = (obj.enabled[5]);
		if(oid == idx)
			return 1;
	}
	return 0;
}

static void enable_usync_object(int idx)
{
	uSyncObject* obj = &uSyncLocks[idx];
	_copy(obj->enabled, "uSYNC", 5);
	obj->enabled[5] = idx & 0xFF;
}

int uSyncInit()
{
	int i;
	for(i = 0; i < _USYNC_LOCK_MAX; i++) {
		_clear(uSyncLocks[i].enabled, 8);
#ifdef _USYNC_HOLD_DATA
		uSyncLocks[i].data       = 0;
#endif
		uSyncLocks[i].enabled[6] = 0;
	}
	uSyncEnabled = 1;
	idcnt = 0;
	return uSyncEnabled;
}

#ifdef _USYNC_HOLD_DATA
int uSyncCreate(void* data)
#else
int uSyncCreate()
#endif
{
	if(!uSyncEnabled)
		return -1;
	if(idcnt >= (_USYNC_LOCK_MAX - 1))
		return -1;
	uSyncLocks[idcnt].enabled[6] = 0;
#ifdef _USYNC_HOLD_DATA
	uSyncLocks[idcnt].data = data;
#endif
	enable_usync_object(++idcnt);
	return idcnt;
}

int uSyncDelete(int idx)
{
	if(!uSyncEnabled)
		return 0;
	if((idx > idcnt) || (idx < 0))
		return 0;
	_clear(uSyncLocks[idcnt].enabled, 8);
#ifdef _USYNC_HOLD_DATA
	uSyncLocks[idcnt].data = 0;
#endif
	idcnt--;
	return 1;
}

#ifdef _USYNC_HOLD_DATA
void* uSyncObtain(int idx)
#else
int uSyncObtain(int idx)
#endif
{
	if(!uSyncEnabled)
		return 0;
	if((idx > idcnt) || (idx < 0))
		return 0;
	if(!validate_usync_object(idx))
		return 0;
	if(uSyncLocks[idx].enabled[6]) {
		return 0;
	}else{
		uSyncLocks[idx].enabled[6] = 1;
#ifdef _USYNC_HOLD_DATA
		return uSyncLocks[idx].data;
#else
		return 1;
#endif
	}
}

int uSyncRelease(int idx)
{
	if(!uSyncEnabled)
		return 0;
	if((idx > idcnt) || (idx < 0))
		return 0;
	if(!validate_usync_object(idx))
		return 0;
	if(uSyncLocks[idx].enabled[6]) {
		uSyncLocks[idx].enabled[6] = 0;
#ifdef _USYNC_HOLD_DATA
		uSyncLocks[idx].data = 0;
#endif
		return 1;
	}else{
		return 1;
	}
}
