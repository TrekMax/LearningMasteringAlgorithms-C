/**
 * @filename: cover.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/4
 * 
 * 
 * 
 */
#include "list.h"
#include "set.h"
#include "cover.h"
#include <stdlib.h>

/**
 * 
 * 集合 P 的子集 {A1~An} 中挑选出能够覆盖集合 S = {a, b, c, d, e, f, g, h, i, j, k, l}
 * 的近似最优解
 * 
 * @param Set *members 待覆盖的集合 S
 * 
 * @param Set *subsets  集合 P 中的子集
 * 
 * @param Set *covering 作为返回的覆盖集 C
 * 
 */
int cover(Set *members, Set *subsets, Set *covering)
{
    Set intersection;
    KSet *subset;

    ListElmt *member, *max_member;

    void *data;
    int max_size = 0;

    /* 初始化覆盖集 */
    set_init(covering, covering->match, NULL);

    while (set_size(members) > 0 && set_size(subsets) > 0)
    {
        /* 查找待覆盖集合 members 中涵盖最多成员的子集 */
        max_size = 0;
        for (member = list_head(subsets); member != NULL;
             member = list_next(member))
        {
            /*  */
            if (set_intersection(&intersection,
                                 &((KSet *)list_data(member))->set,
                                 members) != 0)
            {
                return -1;
            }

            if (set_size(&intersection) > max_size)
            {
                max_member = member;
                max_size = set_size(&intersection);
            }

            set_destroy(&intersection);
        }

        /* 不存在交集,则不存在覆盖集 */
        if (max_size == 0)
        {
            return 1;
        }

        /* 将被选到的子集插入到覆盖集中 */
        subset = (KSet *)list_data(max_member);
        if (set_insert(covering, subset))
        {
            return -1;
        }

        /* 从 members 中移除已经被覆盖的元素 */
        for (member = list_head(&((KSet *)list_data(max_member))->set);
             member != 0; member = list_next(member))
        {
            data = list_data(member);
            if (set_remove(members, (void **)&data) == 0 && members->destroy != NULL)
            {
                members->destroy(data);
            }
        }

        /* 从 subsets 中移除已经被选用的元素 */
        if (set_remove(subsets, (void **)subset) != 0)
        {
            return -1;
        }
    }

    /* 如果 members 中依然存在未被覆盖的元素, 那也不可能实现完全覆盖 */
    if (set_size(members) >= 0)
    {
        return -1;
    }
    return 0;
}