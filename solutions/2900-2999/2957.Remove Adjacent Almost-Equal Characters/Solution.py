# 题目：2957. 消除相邻近似相等字符（Remove Adjacent Almost-Equal Characters）
# 思路：贪心扫描相邻字符对，编码差小于 2 就记一次修改，并把指针一次跳过两位。
# 时间复杂度：O(n)，每个字符最多被访问一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def removeAlmostEqualCharacters(self, word: str) -> int:  # word 为输入字符串，返回最少操作次数
        ans = 0  # 记录已做的修改次数
        i, n = 1, len(word)  # i 从下标 1 开始与前一字符比较，n 为字符串长度
        while i < n:  # 依次检查每一对相邻字符
            if abs(ord(word[i]) - ord(word[i - 1])) < 2:  # ord 取字符编码，差小于 2 说明近似相等，必须修改
                ans += 1  # 需要一次修改
                i += 2  # 改完后该位置与后一位也不再冲突，跳过下一位置，避免重复计数
            else:  # 不冲突的情况
                i += 1  # 继续检查下一对相邻字符
        return ans  # 返回最少修改次数
