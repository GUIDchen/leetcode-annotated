# 题目：78. 子集（Subsets）
# 思路：回溯 + 每个元素「选或不选」。先递归处理「不选 nums[i]」的分支，再把 nums[i] 加入路径 t 递归处理另一个分支，叶子即一个子集。
# 时间复杂度：O(n * 2^n)，共 2^n 个子集、每个子集拷贝 O(n) 个元素；空间复杂度：O(n)，递归栈与路径数组的深度。
class Solution:  # LeetCode 约定的题解类
    def subsets(self, nums: List[int]) -> List[List[int]]:  # nums 是不含重复元素的数组，要求返回它的全部子集
        def dfs(i: int):  # 递归函数：i 是当前要决定「选不选」的下标
            if i == len(nums):  # 所有元素都决策完毕，当前路径就是一个完整子集
                ans.append(t[:])  # 用 t[:] 拷贝一份存入答案，否则后续修改 t 会污染结果
                return  # 到达叶子，回溯返回
            dfs(i + 1)  # 分支一：不选 nums[i]，直接处理下一个下标
            t.append(nums[i])  # 分支二：把 nums[i] 加入当前子集
            dfs(i + 1)  # 带着这个选择递归处理下一个下标
            t.pop()  # 撤销选择、恢复现场，保证回到上一层时路径状态正确

        ans = []  # 收集所有子集
        t = []  # 当前正在构造的子集（回溯路径）
        dfs(0)  # 从下标 0 开始做「选或不选」的决策
        return ans  # 返回收集到的全部子集
