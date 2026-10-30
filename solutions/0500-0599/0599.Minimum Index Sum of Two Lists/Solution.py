# 题目：599. 两个列表的最小索引总和（Minimum Index Sum of Two Lists）
# 思路：用字典记录 list2 中「餐厅 → 下标」，再顺序遍历 list1，在查表的同时维护最小索引和以及并列的餐厅列表。
# 时间复杂度：O(m + n)，两次线性遍历；空间复杂度：O(n)，字典存下 list2 的全部餐厅。
class Solution:  # LeetCode 约定的题解类
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:  # list1、list2 是两个列表，要求返回索引和最小的共同餐厅
        d = {s: i for i, s in enumerate(list2)}  # 字典推导式：一次性把 list2 的餐厅名映射到它的下标
        ans = []  # 结果列表：保存当前最小索引和对应的所有餐厅
        mi = inf  # 最小索引和，先设为正无穷，保证第一个匹配就能更新
        for i, s in enumerate(list1):  # 遍历 list1，同时拿到下标 i 与餐厅名 s
            if s in d:  # 只处理同时出现在 list2 中的餐厅
                j = d[s]  # 取出同一家餐厅在 list2 中的下标 j
                if i + j < mi:  # 出现了更小的索引和，之前的候选都不再是答案
                    mi = i + j  # 更新最小索引和
                    ans = [s]  # 用当前餐厅重建结果列表，丢弃原有候选
                elif i + j == mi:  # 索引和与当前最小值相同，说明存在并列
                    ans.append(s)  # 并列的餐厅一并加入结果
        return ans  # 返回所有索引和最小的共同餐厅
