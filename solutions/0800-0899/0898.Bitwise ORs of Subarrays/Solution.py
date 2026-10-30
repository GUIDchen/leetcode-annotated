# 题目：898. 子数组按位或操作（Bitwise ORs of Subarrays）
# 核心思路：集合 s 记录以当前元素结尾的所有子数组或值，逐元素滚动更新并累计到 ans。
# 时间复杂度：O(n log C)，每个位置的不同或值至多 O(log C) 种；空间复杂度：O(n log C)。
class Solution:  # LeetCode 约定的题解类
    def subarrayBitwiseORs(self, arr: List[int]) -> int:  # arr：输入数组
        ans = set()  # 所有出现过的子数组或值
        s = set()  # 以当前元素结尾的所有子数组或值
        for x in arr:  # 从左到右逐个处理元素
            s = {x | y for y in s} | {x}  # 旧或值接上 x，再加上只含 x 的子数组
            ans |= s  # 本轮结果并入答案集合
        return len(ans)  # 不同或值的个数即为答案
