# 题目：1144. 递减元素使数组呈锯齿状（Decrease Elements To Make Array Zigzag）
# 思路：枚举两种锯齿形态：偶数下标为谷或奇数下标为谷，每个谷位置计算需减到比两侧都小的步数，取两方案最小值。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def movesToMakeZigzag(self, nums: List[int]) -> int:  # nums 是待调整的数组，只能减小元素，返回变成锯齿数组的最少操作次数
        ans = [0, 0]  # 分别累计两种形态的操作数：下标 0 存「偶数位为谷」，下标 1 存「奇数位为谷」
        n = len(nums)  # 数组长度
        for i in range(2):  # 两种形态都枚举一遍
            for j in range(i, n, 2):  # 只处理属于谷的那一半下标，步长 2
                d = 0  # 本位置需要减少的量
                if j:  # 不是首元素，就要比左邻小
                    d = max(d, nums[j] - nums[j - 1] + 1)  # 减到 nums[j-1]-1，共需 nums[j]-nums[j-1]+1 次
                if j < n - 1:  # 不是末元素，就要比右邻小
                    d = max(d, nums[j] - nums[j + 1] + 1)  # 两侧要求取较大者，才能同时满足两边
                ans[i] += d  # 累加到当前形态的总操作数
        return min(ans)  # 两种形态取较小值
