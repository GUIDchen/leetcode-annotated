# 题目：1743. 从相邻元素对还原数组（Restore the Array From Adjacent Pairs）
# 思路：把相邻对看成无向图的边建邻接表，度数为 1 的元素一定是数组端点；从端点出发沿邻接表依次排除已用元素往后推。
# 时间复杂度：O(n)，建图与还原各遍历一遍；空间复杂度：O(n)，邻接表存放 2(n-1) 条边。
class Solution:  # LeetCode 约定的题解类
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:  # adjacentPairs：打乱顺序的相邻元素对
        g = defaultdict(list)  # 邻接表：每个元素值映射到与它相邻的所有元素，缺省值为空列表
        for a, b in adjacentPairs:  # 遍历每个相邻对，把这条无向边双向写入邻接表
            g[a].append(b)  # a 的邻居里加上 b
            g[b].append(a)  # b 的邻居里加上 a
        n = len(adjacentPairs) + 1  # 相邻对数量比元素个数少 1，所以原数组长度是 len+1
        ans = [0] * n  # 先用占位值开好结果数组，稍后按下标逐个填
        for i, v in g.items():  # 遍历邻接表；这里的 i 是字典键（某个元素值），v 是它的邻居列表
            if len(v) == 1:  # 度数为 1 说明它是原数组的端点
                ans[0] = i  # 端点放在还原数组的第一个位置
                ans[1] = v[0]  # 端点唯一的邻居就是第二个元素
                break  # 起点已确定，无需继续找
        for i in range(2, n):  # 从第三个位置开始，沿着链一路往后推
            v = g[ans[i - 1]]  # 取出前一个元素在邻接表里的邻居列表（长度为 1 或 2）
            ans[i] = v[0] if v[1] == ans[i - 2] else v[1]  # 若 v[1] 是已用过的前一个，就取 v[0]，否则取 v[1]
        return ans  # 返回还原出的原数组
