# 题目：2966. 划分数组并满足最大差限制（Divide Array Into Arrays With Max Difference）
# 思路：先排序，再每 3 个连续元素贪心分成一组；排序后相邻元素最接近，只要某组首尾差大于 k 就说明无解，返回空列表。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，切片与结果列表占用（Python 排序为 TimSort）。
class Solution:  # LeetCode 约定的题解类
    def divideArray(self, nums: List[int], k: int) -> List[List[int]]:  # nums 是输入数组（长度是 3 的倍数），k 是组内极差上限
        nums.sort()  # 原地排序，保证相邻元素最接近，方便按每 3 个一组贪心划分
        ans = []  # 存放划分结果
        n = len(nums)  # 缓存数组长度
        for i in range(0, n, 3):  # 步长 3 遍历，每 3 个元素一组
            t = nums[i : i + 3]  # 切片取出连续三个元素作为一组
            if t[2] - t[0] > k:  # 排序后 t[0] 最小、t[2] 最大，首尾之差就是组内极差；超过 k 则无解
                return []  # 返回空列表表示无法划分
            ans.append(t)  # 该组合法，追加进结果
        return ans  # 返回划分方案
