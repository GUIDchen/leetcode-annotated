# 题目：2489. 固定比率的子字符串数（Number of Substrings With Fixed Ratio）
# 思路：把 n0/n1 == num1/num2 变形为 n1*num1 - n0*num2 == 0，用前缀特征值之差为 0 来统计，字典记录每个前缀值的出现次数。
# 时间复杂度：O(n)，一次遍历加 O(1) 均摊查表；空间复杂度：O(n)，字典最多保存 n+1 个前缀值。
class Solution:  # LeetCode 约定的题解类
    def fixedRatio(self, s: str, num1: int, num2: int) -> int:  # s 只含 '0' 与 '1'，num1:num2 是目标比率
        n0 = n1 = 0  # 前缀中 '0' 与 '1' 的个数，初始为空前缀
        ans = 0  # 满足比率的子串计数
        cnt = Counter({0: 1})  # 前缀特征值 → 出现次数；空前缀的特征值 0 先记 1 次
        for c in s:  # 从左到右扩展前缀
            n0 += c == '0'  # 遇到 '0' 时 n0 加 1（True 即 1）
            n1 += c == '1'  # 遇到 '1' 时 n1 加 1
            x = n1 * num1 - n0 * num2  # 前缀特征值；两处相等说明中间子串满足 n1*num1 == n0*num2
            ans += cnt[x]  # 之前出现过几次相同特征值，就能配出几个合法子串
            cnt[x] += 1  # 当前特征值出现次数加一
        return ans  # 返回合法子串总数
