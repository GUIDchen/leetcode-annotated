# 3663. Find The Least Frequent Digit（3663. 出现频率最低的数字）
# 核心思路：逐位拆解整数，用长度为 10 的列表统计每个数字的出现次数，再从小到大枚举取出现次数最少的数字（并列取较小者）。
# 复杂度：时间 O(log n)（数的位数），空间 O(1)。
class Solution:  # 定义题解类
    def getLeastFrequentDigit(self, n: int) -> int:  # 返回 n 中出现频率最低的数字，并列时取较小者
        cnt = [0] * 10  # 统计 0~9 每个数字出现的次数
        while n:  # 逐位拆解 n，直到 n 为 0
            n, x = divmod(n, 10)  # 一次除法同时得到商与最低位数字
            cnt[x] += 1  # 最低位数字计数加一
        ans, f = 0, inf  # ans 记录答案，f 记录当前最小出现次数（初值为正无穷）
        for x, v in enumerate(cnt):  # 从小到大枚举数字 0~9 及其出现次数
            if 0 < v < f:  # 该数字出现过且次数比当前最小次数更少
                f = v  # 更新最小出现次数
                ans = x  # 更新答案（严格小于保证并列时取较小数字）
        return ans  # 返回出现次数最少的数字
