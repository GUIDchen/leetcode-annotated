# 题目：1704. 判断字符串的两半是否相似（Determine if String Halves Are Alike）
# 思路：前后两半同步遍历，前半遇元音计 +1、后半遇元音计 -1，最终计数为 0 即两半元音数量相等。
# 时间复杂度：O(n)，只需扫描半串长度；空间复杂度：O(1)，元音集合大小固定。
class Solution:  # LeetCode 约定的题解类
    def halvesAreAlike(self, s: str) -> bool:  # s 是长度为偶数的字符串
        cnt, n = 0, len(s) >> 1  # cnt 记录两半元音数之差；n 是半串长度，右移一位等价于除以 2
        vowels = set('aeiouAEIOU')  # 十个元音字符（大小写）放进集合，查询是 O(1)
        for i in range(n):  # 同步遍历前半下标 i 与后半下标 i + n
            cnt += s[i] in vowels  # 前半出现元音就 +1（True 当作 1，False 当作 0）
            cnt -= s[i + n] in vowels  # 后半出现元音就 -1，与前半贡献抵消
        return cnt == 0  # 差值为 0 说明两半元音个数相同，字符串相似
