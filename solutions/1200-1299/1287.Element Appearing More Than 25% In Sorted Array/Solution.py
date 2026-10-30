# 题目：1287. 有序数组中出现次数超过 25% 的元素（Element Appearing More Than 25% In Sorted Array）
# 核心思路：数组有序，答案元素出现超过 n/4 次，则必存在位置 i 使 arr[i] == arr[i + n/4]；枚举 i 返回首个命中者。
# 时间复杂度：O(n)，最多扫描 n 个位置；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findSpecialInteger(self, arr: List[int]) -> int:  # 题解方法对外可见
        n = len(arr)  # arr 是升序数组，返回其中出现次数超过 25% 的那个元素
        for i, x in enumerate(arr):  # i 从 0 开始且不设上界：题目保证答案存在，循环必然在数组内部返回
            if x == arr[(i + (n >> 2))]:  # 关键判定：有序数组中相隔 n/4 的两处若相等，说明该值至少出现 n/4+1 次，即超过 25%
                return x  # 命中目标元素，直接返回它的值
