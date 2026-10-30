# 题目：2597. 美丽子集的数目（The Number of Beautiful Subsets）
# 思路：回溯枚举「选 / 不选」每个元素，用计数器 cnt 记录当前子集里的值，选 nums[i] 前检查 nums[i]±k 是否已出现。
# 时间复杂度：O(2^n)，最坏枚举全部子集；空间复杂度：O(n + V)，递归深度 n、计数器最多存 V 种值。
class Solution:  # LeetCode 约定的题解类
    def beautifulSubsets(self, nums: List[int], k: int) -> int:  # nums：候选数字；k：允许的最小差值；返回美丽子集（任意两数之差不等于 k）的个数
        def dfs(i: int) -> None:  # 内层回溯函数：i 是当前要决策的元素下标
            nonlocal ans  # 声明 ans 来自外层函数，内层对它的赋值才会改到同一个变量
            if i >= len(nums):  # 所有元素都决策完了，得到一个合法子集
                ans += 1  # 子集个数加一（空集也会被计一次，最后由 ans 初值扣掉）
                return  # 本分支结束，回溯返回上一层
            dfs(i + 1)  # 分支一：不把 nums[i] 放进子集，直接处理下一个元素
            if cnt[nums[i] + k] == 0 and cnt[nums[i] - k] == 0:  # 选 nums[i] 前，nums[i]+k 与 nums[i]-k 都不能已在子集中；Counter 取不存在的键返回 0
                cnt[nums[i]] += 1  # 把 nums[i] 计入当前子集
                dfs(i + 1)  # 分支二：选了 nums[i] 后继续决策后续元素
                cnt[nums[i]] -= 1  # 回溯：撤销本次选择，保证兄弟分支看到的是干净状态

        # 计数从 -1 起，用来抵消递归中把空子集也记上的那一次
        ans = -1  # 值计数器：键是元素值，值是它在当前子集中出现的次数
        cnt = Counter()  # 从下标 0 开始搜索
        dfs(0)  # ans 已扣掉空子集，直接返回美丽子集个数
        return ans
