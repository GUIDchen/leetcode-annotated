# 题目：3152. 特殊数组 II（Special Array II）
# 思路：预处理 d[i] 表示 i 所在奇偶交替段的起始下标，询问 [f, t] 只需判断 d[t] <= f。
# 时间复杂度：O(n + q)，预处理一次、每个询问 O(1)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:  # nums 是原数组，queries 是若干询问区间，返回每个区间是否为特殊子数组
        n = len(nums)  # 数组长度
        d = list(range(n))  # d[i] 记录 i 所在奇偶交替段的起始下标，初始各自成段
        for i in range(1, n):  # 从左到右递推每个位置的段起点
            if nums[i] % 2 != nums[i - 1] % 2:  # 相邻两数奇偶不同，可以与前一段接上
                d[i] = d[i - 1]  # 与左邻居同段，继承它的段起点
        return [d[t] <= f for f, t in queries]  # 右端点的段起点不晚于左端点，说明整段都落在区间内
