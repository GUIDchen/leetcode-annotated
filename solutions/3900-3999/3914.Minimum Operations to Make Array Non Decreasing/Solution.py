# 3914. Minimum Operations to Make Array Non Decreasing | 使数组非递减需要的最小累计值（中等）
# 核心思路：从左往右检查每一对相邻元素，凡是出现下降（a > b）的地方，就必须补齐 a - b 次；把所有下降落差累加起来就是最小操作次数。
# 复杂度：时间 O(n)，一次线性扫描；空间 O(1)，只用了累计变量。
class Solution:  # 定义题解类
    def minOperations(self, nums: list[int]) -> int:  # 用 pairwise 遍历相邻对，把每处下降的落差 max(a - b, 0) 累加后返回
        return sum(max(a - b, 0) for a, b in pairwise(nums))  # 方法结束
