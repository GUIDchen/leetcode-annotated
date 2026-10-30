# 题目：862. 和至少为 K 的最短子数组（Shortest Subarray with Sum at Least K）
# 思路：前缀和 + 单调队列。子数组和化为两个前缀和之差，队列中前缀和保持单调递增；队首满足差值 ≥ k 时立即更新答案并弹出。
# 时间复杂度：O(n)，每个下标至多入队、出队各一次；空间复杂度：O(n)，前缀和数组与双端队列。
class Solution:  # LeetCode 约定的题解类
    def shortestSubarray(self, nums: List[int], k: int) -> int:  # nums：可能含负数的数组；k：目标和；返回和 ≥ k 的最短非空子数组长度
        s = list(accumulate(nums, initial=0))  # 前缀和：initial=0 使 s[i] 表示前 i 个元素之和，便于直接取到整段
        q = deque()  # 单调队列：存下标，其对应的前缀和从队首到队尾严格递增
        ans = inf  # 答案初值取正无穷，表示尚未找到合法子数组
        for i, v in enumerate(s):  # 枚举每个前缀和及其下标，下标即右端点
            while q and v - s[q[0]] >= k:  # 队首前缀和与当前前缀和之差 ≥ k 时，找到了一个合法子数组
                ans = min(ans, i - q.popleft())  # 记录更短的区间长度，并弹出这个已不可能再改进的队首
            while q and s[q[-1]] >= v:  # 维护单调性：队尾前缀和不小于当前值时不可能再给出更短区间
                q.pop()  # 弹出队尾
            q.append(i)  # 把当前下标入队，作为后续右端点的候选左端点
        return -1 if ans == inf else ans  # 仍是无穷说明没有合法子数组，返回 -1
