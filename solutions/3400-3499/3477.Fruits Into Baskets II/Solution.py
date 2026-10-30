# 3477. 水果成篮 II（Fruits Into Baskets II）
# 核心思路：按顺序枚举每个水果，找到第一个容量足够且未被占用的篮子并占用它，最后返回放不下的水果数。
# 复杂度：时间 O(n^2)，空间 O(n)
class Solution:  # 解题类
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:  # 返回无法放入任何篮子的水果数量
        n = len(fruits)  # 水果数量（同时也是篮子数量）
        vis = [False] * n  # 标记每个篮子是否已经被占用
        ans = n  # 先假设所有水果都放不下
        for x in fruits:  # 按给定顺序逐个处理水果
            for i, y in enumerate(baskets):  # 从左到右扫描篮子，i 是下标、y 是容量
                if y >= x and not vis[i]:  # 容量足够且该篮子尚未被占用
                    vis[i] = True  # 占用这个篮子
                    ans -= 1  # 放不下的数量减一
                    break  # 该水果已放置，跳出内层循环
        return ans  # 返回最终放不下的水果数
