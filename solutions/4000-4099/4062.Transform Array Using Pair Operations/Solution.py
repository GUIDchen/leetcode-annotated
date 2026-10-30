# 4062. 成对操作转化数组  Transform Array Using Pair Operations
# 核心思路：每次成对操作都保持数组元素总和不变，因此只需判断两个数组的总和是否相等。
# 复杂度：时间 O(n + m)，空间 O(1)。

class Solution:
    def canTransform(self, source: list[int], target: list[int]) -> bool:  # 判断 source 能否通过成对操作转成 target
        return sum(source) == sum(target)  # 总和相等即可完成转化
