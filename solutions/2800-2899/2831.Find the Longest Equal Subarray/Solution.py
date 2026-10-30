# 题目：2831. 找出最长等值子数组（Find the Longest Equal Subarray）
# 思路：滑动窗口配合计数器。窗口 [l, r] 中最大频次为 mx，窗口长度是 r-l+1，需要删除的非众数元素个数为 r-l+1-mx；一旦它超过 k 就右移左边界，过程中记录的最大 mx 即答案。
# 时间复杂度：O(n)，两个指针各自单调右移；空间复杂度：O(n)，Counter 最多记录 n 种不同的值。
class Solution:  # LeetCode 约定的题解类
    def longestEqualSubarray(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：最多可删除的元素个数
        cnt = Counter()  # 计数器：记录当前窗口内每个值出现的次数
        l = 0  # 滑动窗口左端点
        mx = 0  # 窗口内出现次数的最大值
        for r, x in enumerate(nums):  # 右端点 r 从左到右扩展窗口，x 是当前进入窗口的元素
            cnt[x] += 1  # 把元素 x 计入窗口
            mx = max(mx, cnt[x])  # 用 x 的新频次更新窗口内最大频次
            if r - l + 1 - mx > k:  # 窗口长度减去众数频次就是必须删掉的元素个数，超过 k 则不合法
                cnt[nums[l]] -= 1  # 把左端点元素移出窗口
                l += 1  # 左指针右移，缩小窗口
        return mx  # 最大的众数频次就是最长等值子数组的长度
