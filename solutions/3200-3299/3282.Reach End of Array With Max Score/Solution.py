# 3282. 到达数组末尾的最大得分（Reach End of Array With Max Score）
# 核心思路：得分为每次跳跃长度乘以起跳位置的值，等价于把每个位置（末尾除外）乘上它之前的前缀最大值后求和；因此维护前缀最大值并累加即可。
# 复杂度：时间 O(n)，空间 O(1)

class Solution:  # 定义题解类
    def findMaximumScore(self, nums: List[int]) -> int:  # 返回从下标 0 跳到最后一个下标能获得的最大得分
        ans = mx = 0  # ans 为累计得分，mx 为目前见过的最大值
        for x in nums[:-1]:  # 遍历除最后一个元素外的所有元素，把它们当作跳跃起点
            mx = max(mx, x)  # 维护前缀最大值
            ans += mx  # 每步都能直接跳到历史最大值处，故累加该最大值
        return ans  # 返回最大得分
