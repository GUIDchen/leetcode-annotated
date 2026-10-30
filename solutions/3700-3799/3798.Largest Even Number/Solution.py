# 3798. 最大的偶数 / Largest Even Number
# 核心思路：偶数必须以 2 结尾，而字符只有 1 和 2，因此删掉末尾所有 1 后剩下的字符串就是最大的偶数。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义 LeetCode 题解类
    def largestEven(self, s: str) -> str:  # 返回能表示偶数的最大结果字符串
        return s.rstrip("1")  # 去掉末尾所有 1，剩下的就是以 2 结尾的最大偶数
