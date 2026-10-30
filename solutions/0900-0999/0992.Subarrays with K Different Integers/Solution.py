# 题目：992. K 个不同整数的子数组（Subarrays with K Different Integers）
# 思路：滑动窗口。恰好 k 个 = 至多 k-1 个的起点数 - 至多 k 个的起点数，两次窗口统计相减。
# 时间复杂度：O(n)，左右指针各自最多移动 n 步；空间复杂度：O(n)，计数器与每个右端点的结果数组。
class Solution:  # LeetCode 约定的题解类
    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：要求的「不同整数个数」；返回满足条件的子数组数量
        def f(k):  # 内部函数：返回数组 pos，pos[i] 是以 i 结尾、不同整数个数不超过 k 的最左起点 j
            pos = [0] * len(nums)  # pos 保存每个右端点对应的窗口最左起点
            cnt = Counter()  # 计数器：统计窗口内每个值的出现次数
            j = 0  # j 是滑动窗口的左端点
            for i, x in enumerate(nums):  # 枚举右端点 i 与对应元素 x
                cnt[x] += 1  # 把 x 计入窗口
                while len(cnt) > k:  # 不同整数个数超过 k，需要收缩左边界
                    cnt[nums[j]] -= 1  # 把左端点元素移出窗口
                    if cnt[nums[j]] == 0:  # 该元素已经彻底离开窗口
                        cnt.pop(nums[j])  # 从计数器中删除它，保证 len(cnt) 就等于不同整数个数
                    j += 1  # 左端点右移
                pos[i] = j  # 记录当前右端点对应的合法最左起点
            return pos  # 返回所有右端点的结果

        return sum(a - b for a, b in zip(f(k - 1), f(k)))  # 恰好 k 个 = f(k-1)[i] - f(k)[i]，逐项相减再求和
