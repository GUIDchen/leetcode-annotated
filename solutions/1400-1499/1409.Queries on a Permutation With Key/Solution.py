# 题目：1409. 查询带键的排列（Queries on a Permutation With Key）
# 思路：列表模拟排列，用 index 找到查询值的位置，pop 掉再 insert 到队首。
# 时间复杂度：O(q * m)，q 为查询个数，index 与插入都是 O(m)；空间复杂度：O(m)，保存排列与答案。
class Solution:  # LeetCode 约定的题解类
    def processQueries(self, queries: List[int], m: int) -> List[int]:  # queries 是查询序列，m 是初始排列长度；返回每次查询值所在的下标
        p = list(range(1, m + 1))  # 初始排列 1,2,...,m
        ans = []  # 保存每次查询得到的下标
        for v in queries:  # 按顺序处理每一个查询值 v
            j = p.index(v)  # index 返回 v 在排列中的位置，正是本次查询的答案
            ans.append(j)  # 把下标计入答案
            p.pop(j)  # 删除原位置的 v，后面的元素整体前移
            p.insert(0, v)  # 把 v 插到排列最前面，其余元素整体后移
        return ans  # 返回全部查询的结果
