/**
 * @filename: set.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#include <stdlib.h>
#include "list.h"
#include "set.h"

/**
 * 初始化集合
 * 
 * @param Set *set 指定需要初始化的集合
 * 
 * @param int (*match)(const void *key1, const void *key2) 指定匹配判断函数
 * 
 * @param void (*destroy)(void *data) 指定用于销毁集合的操作
 * 
 */
void set_init(Set *set, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data))
{
    list_init(set, destroy);
    set->match = match;

    return;
}

/**
 * 将一个成员插入集合中
 * 
 * @param Set *set 指定要插入的集合
 * 
 * @param const void *data 插入元素数据
 * 
 */
int set_insert(Set *set, const void *data)
{
    if (set_is_member(set, data))
    {
        return 1;
    }

    return list_ins_next(set, list_tail(set), data);
}

/**
 * 将一个成员从集合中移除
 * 
 * @param Set *set 指定要操作的集合
 * 
 * @param const void *data 指定要移除的元素数据
 * 
 */
int set_remove(Set *set, void **data)
{
    ListElmt *member, *prev;

    prev = NULL;

    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if ((set)->match(*data, member->data))
        {
            break;
        }
        prev = member;
    }

    if (member == NULL)
    {
        return -1;
    }
    return list_rem_next(set, prev, data);
}

/**
 * 求 set1 与 set2 的并集
 * 
 * @param Set *setu set1 set2 的并集
 * 
 * @param Set *set set1
 * 
 * @param Set *set set2
 * 
 */
int set_union(Set *setu, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void *data;

    set_init(setu, setu->match, NULL);

    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    for (member = list_head(set2); member != NULL; member = list_next(member))
    {
        if (!set_is_member(set1, member->data))
        {
            data = list_data(member);
            if (list_ins_next(setu, list_tail(setu), data) != 0)
            {
                set_destroy(setu);
                return -1;
            }
        }
    }

    return 0;
}

/**
 * 求 set1 与 set2 的交集
 * 
 * @param Set *seti set1 与 set2 交集
 * 
 * @param Set *set set1
 * 
 * @param Set *set set2
 * 
 */
int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void *data;

    set_init(seti, seti->match, NULL);

    for (member = list_head(set2); member != NULL; list_next(member))
    {
        data = list_data(member);
        if (set_is_member(set1, data))
        {
            if (list_ins_next(seti, list_tail(seti), data))
            {
                set_destroy(seti);
                return -1;
            }
        }
    }
}

/**
 * 求 set1 与 set2 的差集
 * 
 * @param Set *setd set1 与 set2 差集
 * 
 * @param Set *set set1
 * 
 * @param Set *set set2
 * 
 */
int set_difference(Set *setd, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void *data;

    set_init(setd, setd->match, NULL);
    for (member = list_head(set2); member != NULL; member = list_next(member))
    {
        data = list_data(member);
        if (!set_is_member(set1, data))
        {
            if (list_ins_next(setd, list_tail(setd), data))
            {
                set_destroy(setd);
                return -1;
            }
        }
    }

    return 0;
}

/**
 * 判断元素是否属于集合 set
 * 
 * @param Set *setd 集合
 * 
 * @param const void *data 需要匹配的元素数据
 * 
 */
int set_is_member(const Set *set, const void *data)
{
    ListElmt *member;
    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if (set->match(data, list_data(member)))
        {
            return 1;
        }
    }

    return 0;
}

/**
 * 判断 set1 是否为 set2 的子集
 * 
 * @param Set *set1
 * 
 * @param Set *set2
 * 
 */
int set_is_subset(const Set *set1, const Set *set2)
{
    ListElmt *member;
    if (set_size(set1) > set_size(set2))
    {
        return 0;
    }

    for (member = list_head(set1); member != NULL; list_next(member))
    {
        if (!set_is_member(set2, list_data(member)))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * 判断两个集合是否相等
 * 
 * @param Set *set1
 * 
 * @param Set *set2
 * 
 */
int set_is_equal(const Set *set1, const Set *set2)
{
    if (set_size(set1) != set_size(set2))
    {
        return 0;
    }

    return set_is_subset(set2, set1);
}
