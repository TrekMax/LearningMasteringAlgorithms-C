/**
 * @filename: frames.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/1
 * 
 * 
 * 
 */
#ifndef FRAMES_H
#define FRAMES_H

#include "list.h"

int alloc_frame(List *frames);
int free_frame(List *frames, int frame_number);

#endif