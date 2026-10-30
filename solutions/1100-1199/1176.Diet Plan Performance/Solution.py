# 题目：1176. 健身计划评估（Diet Plan Performance）
# 思路：用 accumulate 构造前缀和，再用长度固定为 k 的滑动窗口 O(1) 求每段总和，按阈值累加得分。
# 时间复杂度：O(n)，一次前缀和 + 一次滑窗；空间复杂度：O(n)，前缀和数组占 n+1 个位置。
class Solution:  # LeetCode 约定的题解类
    def dietPlanPerformance(  # calories：每日摄入热量；k：连续 k 天；lower/upper：评分阈值
        self, calories: List[int], k: int, lower: int, upper: int  # 签名换行只是排版，形参含义同上
    ) -> int:  # 返回值为总得分，可能被扣成负数
        s = list(accumulate(calories, initial=0))  # 前缀和：initial=0 使 s[i] 恰好表示前 i 天热量之和
        ans, n = 0, len(calories)  # ans 累计得分，n 为总天数
        for i in range(n - k + 1):  # 枚举所有长度恰好为 k 的窗口起点，共 n-k+1 个
            t = s[i + k] - s[i]  # 窗口和 = 前缀和相减，O(1) 取得，避免内层累加
            if t < lower:  # 该窗口热量低于下界：每出现一次扣 1 分
                ans -= 1  # 扣分
            elif t > upper:  # 该窗口热量高于上界：每出现一次加 1 分
                ans += 1  # 加分
        return ans  # 返回最终得分（区间内不加不减的情况不进入任何分支）
