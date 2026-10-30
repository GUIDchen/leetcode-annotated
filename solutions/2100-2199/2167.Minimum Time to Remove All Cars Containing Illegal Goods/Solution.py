# 题目：2167. 移除所有载有违禁货物车厢所需的最少时间（Minimum Time to Remove All Cars Containing Illegal Goods）
# 思路：pre[i] 表示清空前 i 节车厢中违禁车厢的最少时间，suf[i] 表示清空第 i 节及其之后违禁车厢的最少时间；枚举分界点取两侧之和的最小值。
# 时间复杂度：O(n)，两趟预处理加一趟求最小；空间复杂度：O(n)，两个长度 n+1 的数组。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, s: str) -> int:  # s：字符串，'1' 表示违禁车厢；返回清空所需的最少时间
        n = len(s)  # n：车厢总数
        pre = [0] * (n + 1)  # pre[i]：清空前 i 节车厢中的违禁车厢所需的最少时间
        suf = [0] * (n + 1)  # suf[i]：清空第 i 节及之后车厢中的违禁车厢所需的最少时间
        for i, c in enumerate(s):  # 从左到右预处理前缀数组
            pre[i + 1] = pre[i] if c == '0' else min(pre[i] + 2, i + 1)  # 正常车厢不产生开销；违禁车厢取「左侧方案再加 2 秒单独移出」与「直接花 i+1 秒从左侧移除」的较小值
        for i in range(n - 1, -1, -1):  # 从右到左预处理后缀数组
            suf[i] = suf[i + 1] if s[i] == '0' else min(suf[i + 1] + 2, n - i)  # 与左侧对称：违禁车厢取「右侧方案再加 2 秒」与「花 n-i 秒从右侧移除」的较小值
        return min(a + b for a, b in zip(pre[1:], suf[1:]))  # 枚举分界点，把 pre[1:] 与 suf[1:] 逐项配对求和并取最小值
