# 题目：1310. 子数组异或查询（XOR Queries of a Subarray）
# 核心思路：用 accumulate 构造前缀异或数组 s（s[i] = arr[0]^...^arr[i-1]），区间 [l, r] 的异或即 s[r+1] ^ s[l]。
# 时间复杂度：O(n + q)，建表 O(n)、每个查询 O(1)；空间复杂度：O(n)，前缀异或数组与答案列表。
class Solution:  # LeetCode 约定的题解类
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:  # arr 是原数组，queries 是若干 [l, r]
        s = list(accumulate(arr, xor, initial=0))  # 前缀异或：initial=0 让 s[0]=0，xor 作为二元运算函数（判题环境已导入）
        return [s[r + 1] ^ s[l] for l, r in queries]  # 逐查询求前缀异或之差，即区间 [l, r] 的异或
