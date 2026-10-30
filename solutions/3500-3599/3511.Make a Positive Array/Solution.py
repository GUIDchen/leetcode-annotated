# 题目：3511. 构造正数组（Make a Positive Array）
# 思路：一次扫描做贪心。s 是当前窗口的和，pre_mx 是窗口内更短子数组和的最大值；窗口长度达到 3 后若 s <= pre_mx，说明窗口里已出现和不为正的子数组，必须修改一次，于是答案加一，并以当前位置为新窗口起点重新累计。窗口长度不足 3 时只更新 pre_mx。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用了几个常数变量。
class Solution:  # LeetCode 约定的题解类
    def makeArrayPositive(self, nums: List[int]) -> int:  # nums：可修改的数组；返回需要的最少修改次数
        l = -1  # 窗口左边界的前一个下标，-1 表示从数组开头算起
        ans = pre_mx = s = 0  # ans：修改次数；pre_mx：窗口内更短子数组和的最大值；s：当前窗口和
        for r, x in enumerate(nums):  # r 从左向右扫描，x 是当前元素
            s += x  # 把当前元素累加进窗口和
            if r - l > 2 and s <= pre_mx:  # 窗口长度至少 3，且存在和更小或相等的子数组，说明已出现非正和的子数组
                ans += 1  # 必须做一次修改
                l = r  # 以当前位置为新窗口起点，之前的元素不再参与
                pre_mx = s = 0  # 重置窗口和与子数组和的最大值
            elif r - l >= 2:  # 否则窗口长度至少 2 时，更新更短子数组和的最大值
                pre_mx = max(pre_mx, s - x - nums[r - 1])  # s - x - nums[r-1] 就是窗口内以 r-2 结尾的那个子数组的和
        return ans  # 返回最少修改次数
