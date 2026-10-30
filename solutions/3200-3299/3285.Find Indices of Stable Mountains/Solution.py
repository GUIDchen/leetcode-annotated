# 3285. 找到稳定山的下标（Find Indices of Stable Mountains）
# 核心思路：稳定山就是「前一座山的高度严格大于阈值」的山；从下标 1 开始枚举，检查前一个位置的高度是否超过 threshold，满足就收集该下标。
# 复杂度：时间 O(n)，空间 O(1)（不计返回值）

class Solution:  # 定义题解类
    def stableMountains(self, height: List[int], threshold: int) -> List[int]:  # 返回所有稳定山的下标（升序）
        return [i for i in range(1, len(height)) if height[i - 1] > threshold]  # 从下标 1 开始枚举，前一座山高度大于阈值时收集该下标
