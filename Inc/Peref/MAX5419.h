#ifndef _MAX5419_H_
#define _MAX5419_H_

#include "std.h"

typedef struct {
	Byte  SpiId;					// 
} MAX5419, *pMAX5419;

void MAX5419_Init(MAX5419 *);							// Инициализация
void MAX5419_Update(MAX5419 *);							//

#endif