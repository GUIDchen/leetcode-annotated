# 题目：2681. 英雄的力量（Power of Heroes）
# 思路：升序排序后从大到小遍历，每个 x 充当「最大值」，用滚动变量 p 累积前面更小元素作为最小值的 2 次幂权值，累加 x^3 与 x*p。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，反转切片额外拷贝了一份数组。
class Solution:  # LeetCode 约定的题解类
    def sumOfPower(self, nums: List[int]) -> int:  # nums 是英雄的力量值数组
        mod = 10**9 + 7  # 取模常量，答案需要对 1e9+7 取模
        nums.sort()  # 升序排序，稍后反向遍历就等价于降序
        ans = 0  # ans 用来累加答案
        p = 0  # p 保存前面（更小）元素贡献的 2 次幂加权和
        for x in nums[::-1]:  # 反向遍历，让当前 x 成为子集里的最大值
            ans = (ans + (x * x % mod) * x) % mod  # 只含 x 一个元素的子集贡献 x^3，先加上并取模
            ans = (ans + x * p) % mod  # 以 x 为最大值的更大子集贡献 x*p，再加上并取模
            p = (p * 2 + x * x) % mod  # 更新 p：多出 x 一个候选最小值后权值整体翻倍，并加上 x^2
        return ans  # 返回取模后的总力量
