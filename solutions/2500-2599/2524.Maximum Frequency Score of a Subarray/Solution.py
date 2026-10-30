# 题目：2524. 子数组的最大频率分数（Maximum Frequency Score of a Subarray）
# 思路：固定长度 k 的滑动窗口 + 哈希计数，用快速幂增量维护窗口分数（移入加、移出减）。
# 时间复杂度：O(n log k)，每次移动做常数次快速幂；空间复杂度：O(n)，哈希表最多存 n 种值。
class Solution:  # LeetCode 约定的题解类
    def maxFrequencyScore(self, nums: List[int], k: int) -> int:  # nums：原数组；k：子数组长度；返回所有长度 k 子数组的最大频率分数
        mod = 10**9 + 7  # 模数 10^9+7，题目要求分数对它取模
        cnt = Counter(nums[:k])  # 统计第一个长度为 k 的窗口内每个值的出现次数
        ans = cur = sum(pow(k, v, mod) for k, v in cnt.items()) % mod  # ans 与 cur 同时赋值：第一个窗口的分数 = 各不同值「值^次数」之和再取模
        i = k  # i 指向即将进入窗口的元素下标，从 k 开始向右滑
        while i < len(nums):  # 窗口右移，直到数组末尾
            a, b = nums[i - k], nums[i]  # a 是要移出窗口的旧元素，b 是要移入的新元素
            if a != b:  # 新旧元素相同则窗口多重集不变，分数不用重算
                cur += (b - 1) * pow(b, cnt[b], mod) if cnt[b] else b  # 新增一个 b：原本有 cnt[b] 个时增量是 (b-1)*b^cnt[b]，否则由 0 变 b
                cur -= (a - 1) * pow(a, cnt[a] - 1, mod) if cnt[a] > 1 else a  # 删掉一个 a：原本超过 1 个时减少 (a-1)*a^(cnt[a]-1)，否则直接减 a
                cur %= mod  # Python 的 % 对负数也返回非负，等价于把可能的负数修正回来
                cnt[b] += 1  # b 的计数加一，表示已进入窗口
                cnt[a] -= 1  # a 的计数减一，表示已离开窗口
                ans = max(ans, cur)  # 用当前窗口的分数更新答案
            i += 1  # 右指针前进一格
        return ans  # 返回所有窗口中的最大频率分数
