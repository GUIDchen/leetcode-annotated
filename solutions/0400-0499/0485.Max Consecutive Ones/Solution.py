# 题目：485. 最大连续 1 的个数（Max Consecutive Ones）
# 思路：一次遍历，用 cnt 累计当前连续 1 的长度，遇到 1 就加一并用它刷新答案，遇到 0 就把 cnt 归零。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用两个计数变量。
class Solution:  # LeetCode 约定的题解类
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:  # nums 是只含 0 和 1 的数组，返回最长连续 1 的长度
        ans = cnt = 0  # ans 记录历史最大值，cnt 记录当前连续 1 的个数，两者一起初始化为 0
        for x in nums:  # 逐个元素遍历
            if x:  # 当前元素为 1（非零即为真）
                cnt += 1  # 连续长度加一
                ans = max(ans, cnt)  # 用当前长度刷新历史最大值
            else:  # 否则当前元素是 0
                cnt = 0  # 连续段被打断，长度清零
        return ans  # 返回最大连续 1 的个数
