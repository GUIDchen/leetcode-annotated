# 题目：1502. 判断能否形成等差数列（Can Make Arithmetic Progression From Sequence）
# 思路：排序后公差由前两个元素确定，再用 pairwise 把相邻元素两两配对，检查每对的差是否都等于公差。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序且 pairwise 是惰性迭代器。
class Solution:  # LeetCode 约定的题解类
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:  # arr：输入数组；返回能否把数组重排成等差数列
        arr.sort()  # 原地升序排序：等差序列排序后相邻差必然处处相等
        d = arr[1] - arr[0]  # 公差取排序后前两个元素之差（题目保证长度 >= 2）
        return all(b - a == d for a, b in pairwise(arr))  # pairwise 把相邻元素两两配对，all 判断每对的差是否都等于公差 d
