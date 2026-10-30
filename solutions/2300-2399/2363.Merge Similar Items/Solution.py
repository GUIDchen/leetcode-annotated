# 题目：2363. 合并相似的物品（Merge Similar Items）
# 思路：用 Counter 把两个数组的权重按价值累加，再用 sorted 按键升序输出。
# 时间复杂度：O(n + m + k log k)，k 为不同价值个数；空间复杂度：O(k)。
class Solution:  # LeetCode 约定的题解类
    def mergeSimilarItems(  # 入参 items1/items2 是「价值, 权重」列表，返回合并后的升序列表
        self, items1: List[List[int]], items2: List[List[int]]  # self 是实例本身，两个参数是物品数组
    ) -> List[List[int]]:  # 返回值是二维整数列表
        cnt = Counter()  # 计数器：键是价值，值是权重累加和
        for v, w in chain(items1, items2):  # chain 把两个列表串成一个可迭代对象，只需遍历一次
            cnt[v] += w  # 把权重累加到该价值上，自动完成合并
        return [[v, w] for v, w in sorted(cnt.items())]  # sorted 按键升序，再转成二维列表返回
