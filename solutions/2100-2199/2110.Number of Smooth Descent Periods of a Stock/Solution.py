# 题目：2110. 股票平滑下跌阶段的数目（Number of Smooth Descent Periods of a Stock）
# 思路：找出所有「相邻差值恰为 1」的极大连续段，段长为 cnt 时贡献 cnt*(cnt+1)/2 个子段；逐段累加即为答案。
# 时间复杂度：O(n)，每个位置只被访问一次；空间复杂度：O(1)，只用了几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def getDescentPeriods(self, prices: List[int]) -> int:  # prices 是每日价格数组，返回平滑下跌阶段的总数
        ans = 0  # ans 累计答案
        i, n = 0, len(prices)  # i 记录当前连续段的起点，n 是数组长度
        while i < n:  # 逐段扫描，直到数组末尾
            j = i + 1  # j 从 i 的下一格开始找段尾
            while j < n and prices[j - 1] - prices[j] == 1:  # 相邻两天价格差恰为 1 就继续延长这一段
                j += 1  # 段尾后移
            cnt = j - i  # cnt = j - i，即极大平滑下跌段 [i, j) 的长度
            ans += (1 + cnt) * cnt // 2  # 该段内共有 cnt*(cnt+1)/2 个合法子段，累加（// 为整数除法）
            i = j  # 下一段从 j 开始
        return ans  # 返回最终答案
