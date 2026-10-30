# 题目：3800. 使二进制字符串相等的最小成本（Minimum Cost to Make Two Binary Strings Equal）
# 思路：先统计 s 与 t 不同位置上「s 为 0」与「s 为 1」的数量，再枚举三种操作组合（全翻转 / 交换+翻转 / 交叉+交换+翻转）取最小值。
# 时间复杂度：O(n)，一趟扫描统计差异；空间复杂度：O(1)，只用了常数个计数器。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # 返回把 s 变成 t 所需的最小成本
        self, s: str, t: str, flipCost: int, swapCost: int, crossCost: int  # 参数：s、t 两个等长二进制串；flipCost 翻一位、swapCost 换一对、crossCost 交叉操作一对
    ) -> int:  # 返回最小总成本
        diff = [0] * 2  # diff[0]、diff[1]：s 为 '0' / '1' 而 t 不同的位置数量
        for c1, c2 in zip(s, t):  # 逐位配对比较两串
            if c1 != c2:  # 该位不同
                diff[int(c1)] += 1  # 按 s 上的字符分类计数
        ans = (diff[0] + diff[1]) * flipCost  # 方案一：所有不同的位都逐个翻转
        mx = max(diff)  # 两类不匹配数量的较大者
        mn = min(diff)  # 两类不匹配数量的较小者
        ans = min(ans, mn * swapCost + (mx - mn) * flipCost)  # 方案二：先两两交换 min 对，剩下 (mx-mn) 位单独翻转
        avg = (mx + mn) // 2  # 方案三的折中点：用交叉操作把两类数量拧成一样
        ans = min(  # 开始取方案三与当前答案的最小值
            ans,  # 当前最优答案
            (avg - mn) * crossCost + avg * swapCost + (mx + mn - avg * 2) * flipCost,  # 方案三：交叉操作 + 剩余两两交换 + 可能的单点翻转
        )  # 取最小值的表达式结束
        return ans  # 三种方案的最小值即为答案
