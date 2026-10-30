# 题目：2281. 巫师的总力量和（Sum of Total Strength of Wizards）
# 核心思路：单调栈求出每个元素作为最小值的最左/最右边界，再用累加和及其累加和 O(1) 算出该元素对答案的加权贡献。
# 时间复杂度：O(n)，两趟单调栈与两次 accumulate 都是线性；空间复杂度：O(n)，边界数组与两份前缀和都随 n 增长。
class Solution:  # LeetCode 约定的题解类
    def totalStrength(self, strength: List[int]) -> int:  # strength：每位巫师的力量值
        n = len(strength)  # 数组长度，后续循环的上界
        left = [-1] * n  # left[i]：i 左边第一个严格更小元素的下标，-1 表示不存在
        right = [n] * n  # right[i]：i 右边第一个不大于当前元素的下标，n 表示不存在
        stk = []  # 单调递增栈，存放还没确定左边界的下标
        for i, v in enumerate(strength):  # 从左往右扫，求每个位置的左边界
            while stk and strength[stk[-1]] >= v:  # 栈顶元素不小于 v，就不再是 v 的左边界
                stk.pop()  # 弹出无效的栈顶
            if stk:  # 弹完后栈非空，说明左边存在更小的元素
                left[i] = stk[-1]  # 栈顶下标就是左边第一个更小的元素
            stk.append(i)  # 当前下标入栈，供后面的元素复用
        stk = []  # 清空栈，复用于从右往左的扫描
        for i in range(n - 1, -1, -1):  # 从右往左扫，求每个位置的右边界
            while stk and strength[stk[-1]] > strength[i]:  # 用严格大于弹栈，与左边界配合避免同一区间被重复统计
                stk.pop()  # 弹出无效的栈顶
            if stk:  # 栈非空说明右边存在不大于当前值的元素
                right[i] = stk[-1]  # 记录右边界
            stk.append(i)  # 入栈，等待成为左边元素的右边界

        ss = list(accumulate(list(accumulate(strength, initial=0)), initial=0))  # 前缀和再前缀和：ss[k] 是 strength 前 k 项按位置加权的总和，供 O(1) 查询区间加权和
        mod = int(1e9) + 7  # 结果对 1e9+7 取模
        ans = 0  # 累计所有子数组的「最小值 × 元素和」之和
        for i, v in enumerate(strength):  # 让每个元素充当所在子数组的最小值来统计贡献
            l, r = left[i] + 1, right[i] - 1  # 合法子数组必须同时包含 i，端点落在 [l, r] 内
            a = (ss[r + 2] - ss[i + 1]) * (i - l + 1)  # 左端点取 [l, i] 时，右半部分区间和的加权结果
            b = (ss[i + 1] - ss[l]) * (r - i + 1)  # 右端点取 [i, r] 时，左半部分区间和的加权结果
            ans = (ans + (a - b) * v) % mod  # 乘上最小值 v 累加；Python 取模天然返回非负值
        return ans  # 返回最终答案
