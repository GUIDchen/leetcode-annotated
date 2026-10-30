# 题目：2934. 最大化数组末位元素的最少操作次数（Minimum Operations to Maximize Last Elements in Arrays）
# 思路：最终末位只有两种可能——保持 (nums1[-1], nums2[-1]) 或交换成 (nums2[-1], nums1[-1])；分别求最少交换次数再取小。
# 时间复杂度：O(n)，两种方案各线性扫描一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:  # 两个等长数组，一次操作可交换同一位置上的两个元素
        def f(x: int, y: int) -> int:  # 内部函数：让末位变成 (x, y) 时，前面 n-1 个位置需要的最少交换次数
            cnt = 0  # 该方案下累计的交换次数
            for a, b in zip(nums1[:-1], nums2[:-1]):  # 只遍历前 n-1 个位置，末位由参数 x、y 决定
                if a <= x and b <= y:  # 不交换就已满足不超过末位，无需操作
                    continue  # 直接跳过当前位置
                if not (a <= y and b <= x):  # 交换后仍不满足，说明这个目标末位无法达成
                    return -1  # 返回 -1 表示该方案无解
                cnt += 1  # 只能靠交换满足条件，计数加一
            return cnt  # 返回该方案所需的最少交换次数

        a, b = f(nums1[-1], nums2[-1]), f(nums2[-1], nums1[-1])  # 两种末位方案各自的最少交换次数（第二种尚未计入末位那一次交换）
        return -1 if a + b == -2 else min(a, b + 1)  # 两种都无解返回 -1；否则取较小值，方案二记得加上末位交换的那一次
