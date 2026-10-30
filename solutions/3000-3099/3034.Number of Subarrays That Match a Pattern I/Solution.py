# 题目：3034. 匹配模式数组的子数组数目 I（Number of Subarrays That Match a Pattern I）
# 思路：把相邻元素的大小关系压缩成 1/0/-1，再枚举每个起点，用 all() 判断整段关系是否与 pattern 完全一致。
# 时间复杂度：O(n·m)，每个起点最多检查 m 个关系；空间复杂度：O(1)，除答案外只用了常数个局部变量。
class Solution:  # LeetCode 约定的题解类
    def countMatchingSubarrays(self, nums: List[int], pattern: List[int]) -> int:  # nums 是原数组，pattern 是关系模式
        def f(a: int, b: int) -> int:  # 小工具函数：把相邻两个元素的大小关系标准化
            return 0 if a == b else (1 if a < b else -1)  # 相等记 0，后者更大记 1，否则记 -1

        ans = 0  # 累计匹配成功的子数组个数
        for i in range(len(nums) - len(pattern)):  # 枚举子数组左端点 i，子数组长度为 m+1
            ans += all(  # 所有 m 个关系都成立时 True 参与加法相当于 1，否则相当于 0
                f(nums[i + k], nums[i + k + 1]) == p for k, p in enumerate(pattern)  # 第 k 对相邻元素的关系与 pattern[k] 比较
            )
        return ans  # 返回匹配的子数组总数
