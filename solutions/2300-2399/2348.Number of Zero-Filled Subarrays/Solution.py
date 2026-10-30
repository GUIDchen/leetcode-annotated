# 题目：2348. 全 0 子数组的数目（Number of Zero-Filled Subarrays）
# 思路：cnt 表示以当前元素结尾的连续 0 的个数，每个 0 会新产生 cnt 个全 0 子数组，累加即可。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个计数变量。
class Solution:  # LeetCode 约定的题解类
    def zeroFilledSubarray(self, nums: List[int]) -> int:  # nums 为输入数组
        ans = cnt = 0  # ans 累计答案，cnt 记录以当前元素结尾的连续 0 的个数
        for x in nums:  # 顺序遍历数组
            if x == 0:  # 当前元素为 0，连续 0 段延长
                cnt += 1  # 连续 0 的个数加一
                ans += cnt  # 以这个 0 结尾的全 0 子数组恰有 cnt 个，全部计入
            else:  # 遇到非 0，连续段被打断
                cnt = 0  # 计数清零，等待下一段连续 0
        return ans  # 返回全 0 子数组的总数
