# 题目：3149. 找出分数最低的排列（Find the Minimum Cost Array Permutation）
# 思路：状压 DP + 记忆化，dfs(mask, pre) 返回补全排列的最小代价，再按最优值回溯出具体排列。
# 时间复杂度：O(2^n * n^2)，状态 2^n * n 个、每个枚举 n 个后继；空间复杂度：O(2^n * n)。
class Solution:  # LeetCode 约定的题解类
    def findPermutation(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回分数最低的排列
        @cache  # 记忆化装饰器：同一个 (mask, pre) 只计算一次
        def dfs(mask: int, pre: int) -> int:  # mask 是已选元素的位掩码，pre 是排列末尾元素
            if mask == (1 << n) - 1:  # 所有元素都已选完
                return abs(pre - nums[0])  # 收尾：末尾要与 nums[0] 相邻，代价为两者之差的绝对值
            res = inf  # 先设为正无穷，便于后面取最小值
            for cur in range(1, n):  # 枚举下一个元素；0 固定排首位，所以从 1 开始
                if mask >> cur & 1 ^ 1:  # 第 cur 位为 0 表示 cur 还没被用过
                    res = min(res, abs(pre - nums[cur]) + dfs(mask | 1 << cur, cur))  # 选 cur 之后的总代价，取最小值
            return res  # 返回该状态下的最小剩余代价

        def g(mask: int, pre: int):  # 依据 dfs 的最优值回溯，构造出具体排列
            ans.append(pre)  # 当前元素确定放在这一位，写入答案
            if mask == (1 << n) - 1:  # 元素已全部摆放完毕
                return  # 构造结束，直接返回
            res = dfs(mask, pre)  # 当前状态的最优值，用于挑出最优后继
            for cur in range(1, n):  # 从小到大枚举，保证得到的排列字典序最小
                if mask >> cur & 1 ^ 1:  # cur 尚未被使用
                    if abs(pre - nums[cur]) + dfs(mask | 1 << cur, cur) == res:  # 该后继正好能取到最优值，说明它位于某条最优路径上
                        g(mask | 1 << cur, cur)  # 沿这条最优边继续向下构造
                        break  # 只要一条最优路径，找到即可退出枚举

        n = len(nums)  # 排列长度
        ans = []  # 保存最终答案排列
        g(1, 0)  # 0 已固定在首位：mask=1、pre=0，开始构造
        return ans  # 返回最小代价对应的排列
