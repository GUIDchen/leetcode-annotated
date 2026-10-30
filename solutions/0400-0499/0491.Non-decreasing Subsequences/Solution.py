# 题目：491. 非递减子序列（Non-decreasing Subsequences）
# 思路：按下标回溯，每个元素分「选」与「不选」两支；选的前提是它不小于已选序列的末尾值 last，不选时若它与 last 相同则跳过，以此消除同一层重复元素造成的重复子序列。
# 时间复杂度：O(n·2ⁿ)，每个下标两种决策、每个合法子序列拷贝 O(n)；空间复杂度：O(n)，递归深度与路径数组（不计结果集）。
class Solution:  # LeetCode 约定的题解类
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:  # nums：可能含重复元素的数组；返回所有长度 ≥ 2 的非递减子序列
        def dfs(u, last, t):  # 内部递归：u 为当前下标，last 为已选子序列的末尾值，t 为当前路径
            if u == len(nums):  # 已经走到数组末尾，一条完整的决策链结束
                if len(t) > 1:  # 长度至少为 2 才符合「子序列」要求
                    ans.append(t[:])  # 用 t[:] 拷贝一份存入答案，避免之后被回溯改动
                return  # 到达出口，返回上一层继续做别的决策
            if nums[u] >= last:  # 选 nums[u]：只有它不小于 last，选完才仍保持非递减
                t.append(nums[u])  # 把当前值加入路径
                dfs(u + 1, nums[u], t)  # 带着新的 last 继续处理下一个下标
                t.pop()  # 回溯：撤销刚才的选择，恢复路径以便尝试其他分支
            if nums[u] != last:  # 「不选」分支：若 nums[u] 与 last 相同，该支会与上面重复，因此跳过
                dfs(u + 1, last, t)  # 不选 nums[u]，直接处理下一个下标

        ans = []  # 结果集，用闭包让内部函数直接写入
        dfs(0, -1000, [])  # 从下标 0 开始搜；-1000 充当 -∞（题目元素值 ≥ -100）
        return ans  # 返回全部结果
