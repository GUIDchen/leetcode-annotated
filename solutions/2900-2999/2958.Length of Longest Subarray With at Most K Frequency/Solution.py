# 题目：2958. 最多 K 个重复元素的最长子数组（Length of Longest Subarray With at Most K Frequency）
# 思路：滑动窗口 + 计数器，右端扩张后若当前元素超过 k 次，就移动左端收缩，窗口内始终满足限制。
# 时间复杂度：O(n)，左右指针各自最多移动 n 次；空间复杂度：O(n)，计数器最多保存不同元素的出现次数。
class Solution:  # LeetCode 约定的题解类
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:  # nums 为输入数组，k 为元素允许的最大重复次数
        ans = l = 0  # ans 记录最长长度，l 是窗口左端点
        cnt = defaultdict(int)  # 用默认字典统计窗口内各元素的出现次数
        for r, x in enumerate(nums):  # 枚举右端点 r 和当前元素 x
            cnt[x] += 1  # 新元素进入窗口，计数加一
            while cnt[x] > k:  # 当前元素超过 k 次就收缩窗口
                cnt[nums[l]] -= 1  # 左端元素移出窗口，计数减一
                l += 1  # 左端点右移
            ans = max(ans, r - l + 1)  # 用当前合法窗口长度更新答案
        return ans  # 返回最长长度
