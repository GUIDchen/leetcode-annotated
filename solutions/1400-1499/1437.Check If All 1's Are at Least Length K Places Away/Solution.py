# 题目：1437. 是否所有 1 都至少相隔 k 个元素（Check If All 1's Are at Least Length K Places Away）
# 思路：遍历时记住上一个 1 的下标，遇到新的 1 就检查它与上一个 1 之间是否隔着至少 k 个元素。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def kLengthApart(self, nums: List[int], k: int) -> bool:  # nums 是 0/1 数组，k 是要求的最小间隔元素个数
        j = -inf  # j 是上一个 1 的下标；用负无穷初始化，让第一个 1 的间隔天然满足要求
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            if x:  # x 非零即真，表示当前位置是 1
                if i - j - 1 < k:  # 与上一个 1 之间夹着的元素个数不足 k
                    return False  # 不合要求，立即返回假
                j = i  # 记下这个 1 的位置
        return True  # 全部检查通过
