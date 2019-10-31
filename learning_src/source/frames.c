/**
 * @filename: frames.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/1
 * 
 * 
 * 
 */
#include <stdio.h>

#include "frames.h"


/**
 * 从空闲页帧表中获取空闲帧号
 * 
 * @param List *frames 指定的空闲页帧表
 * 
 * @return int >=0 获取到的空闲帧号
 *             -1 获取空闲帧号失败
 */
int alloc_frame(List *frames)
{
    int frame_number, *data;
    if (list_size(frames) == 0)
    {
        /* 无空闲帧可用 */
        return -1;
    }
    else
    {
        if (list_rem_next(frames, NULL, (void**)&data) != 0)
        {
            /* 无法获取到空闲帧页 */
            return -1;
        }
        else
        {
            /* 保存可用的空闲帧号 */
            frame_number = *data;
            free(data);
        }
    }
    return frame_number;
}

/**
 * 将一个页帧号返回到空闲页帧表中
 * 
 * @param List *frames 指定的空闲页帧表
 * 
 * @param int *frame_number 指定要返回到空闲页帧表的帧号
 * 
 * @return int 0 插入空闲页帧表成功
 *             -1 插入空闲页帧表失败
 */
int free_frame(List *frames, int frame_number)
{
    int *data;
    if (data = (int *)malloc(sizeof(int)) == NULL)
    {
        return -1;
    }
    *data = frame_number;
    if (list_ins_next(frames, NULL, data) != 0)
    {
        return 1;
    }
    return 0;
}
