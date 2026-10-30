# 题目：1425. 带限制的子序列和（Constrained Subsequence Sum）
# 核心思路：设 f[i] 为以 i 结尾的最大子序列和，转移只需前 k 个位置中最大的 f，用单调队列把窗口最值维护成 O(1)。
# 时间复杂度：O(n)，每个下标最多进出队列一次；空间复杂度：O(n)，f 数组与单调队列。
class Solution:  # LeetCode 约定的题解类
    def constrainedSubsetSum(self, nums: List[int], k: int) -> int:  # nums：数组；k：相邻选中元素下标差的上限
        q = deque([0])  # 单调队列存候选下标，0 作为哨兵（f[0] = 0）
        n = len(nums)  # 数组长度
        f = [0] * n  # f[i]：以 i 结尾的合法子序列最大和
        ans = -inf  # 全局最大值，初值取负无穷
        for i, x in enumerate(nums):  # 从左到右枚举每个位置
            while i - q[0] > k:  # 队首下标与 i 的距离超过 k 就不能再用来转移
                q.popleft()  # 弹出过期的队首
            f[i] = max(0, f[q[0]]) + x  # 可以放弃前面的序列（取 0），也可接上队首的最优状态
            ans = max(ans, f[i])  # 更新全局最大值
            while q and f[q[-1]] <= f[i]:  # 维护队列内 f 值单调递减
                q.pop()  # 队尾更差且更靠前，后续不可能再被选中，丢弃
            q.append(i)  # 当前下标入队，供后面位置使用
        return ans  # 返回最大子序列和
