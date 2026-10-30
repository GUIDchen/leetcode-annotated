# 3660. Jump Game IX（3660. 跳跃游戏 IX）
# 核心思路：用前缀最大值 pre_max 与后缀最小值 suf_min 判断能否越过当前位置继续向右借力，从右往左一维递推得到每个起点的答案。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义题解类
    def maxValue(self, nums: List[int]) -> List[int]:  # 计算从每个位置出发所能到达的数值上界
        n = len(nums)  # 数组长度
        ans = [0] * n  # 答案数组
        pre_max = [nums[0]] * n  # pre_max[i] 表示 nums[0..i] 的前缀最大值
        for i in range(1, n):  # 从左到右递推前缀最大值
            pre_max[i] = max(pre_max[i - 1], nums[i])  # 取前一个前缀最大值与当前元素的较大者
        suf_min = inf  # 后缀最小值，初值取正无穷
        for i in range(n - 1, -1, -1):  # 从右往左处理每个起点
            ans[i] = ans[i + 1] if pre_max[i] > suf_min else pre_max[i]  # 前缀最大值大于后缀最小值时可继续向右，继承 i+1 的答案
            suf_min = min(suf_min, nums[i])  # 把 nums[i] 并入后缀最小值
        return ans  # 返回答案数组
