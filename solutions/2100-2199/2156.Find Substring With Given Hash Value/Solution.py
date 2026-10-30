# 题目：2156. 查找给定哈希值的子串（Find Substring With Given Hash Value）
# 思路：先算出最后一个长度为 k 的窗口的哈希，再借助 power^(k-1) 从右向左滚动更新，哈希命中就更新起点，最终得到最靠左的子串。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个整数变量。
class Solution:  # LeetCode 约定的题解类
    def subStrHash(  # 方法签名：参数较多，按 black 风格折行
        self, s: str, power: int, modulo: int, k: int, hashValue: int  # s：原串；power：幂底数；modulo：取模数；k：子串长度；hashValue：目标哈希值
    ) -> str:  # 返回找到的子串
        h, n = 0, len(s)  # h：当前窗口的哈希值；n：原串长度
        p = 1  # p：power^(k-1) % modulo，滚动时用于减去最高位
        for i in range(n - 1, n - 1 - k, -1):  # 从右往左累加，先算出最后一个长度为 k 的窗口的哈希
            val = ord(s[i]) - ord("a") + 1  # 把字符映射到 1..26
            h = ((h * power) + val) % modulo  # 反向累加：越靠窗口左边的字符权重越高
            if i != n - k:  # 最右字符权重为 power^0，不计入 p
                p = p * power % modulo  # 累乘得到 power^(k-1) % modulo
        j = n - k  # 答案子串的起始下标，先默认是最后一个窗口
        for i in range(n - 1 - k, -1, -1):  # 窗口整体左移一位，滚动更新哈希
            pre = ord(s[i + k]) - ord("a") + 1  # 即将滑出窗口的最右字符
            cur = ord(s[i]) - ord("a") + 1  # 新进入窗口的最左字符
            h = ((h - pre * p) * power + cur) % modulo  # 减去最高位、整体左移、加上新字符；Python 取模结果自动非负
            if h == hashValue:  # 哈希命中目标值，记录候选起点
                j = i  # 越往左移动下标越小，最终保留最靠左的起点
        return s[j : j + k]  # 切片取出长度为 k 的答案子串
