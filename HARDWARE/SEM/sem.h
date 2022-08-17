#ifndef __SEM_H
#define __SEM_H

#include "sys.h"

typedef u8 SemType;

typedef enum
{
	sem_none,
	sem_valid,
}sem_sta;

void sem_init( volatile SemType *Sem );

void sem_set( volatile SemType *Sem );

sem_sta  sem_wait( volatile SemType *Sem ) ;

#endif
