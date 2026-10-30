# 题目：2950. 可整除子串的数量（Number of Divisible Substrings）
# 思路：先按题意把 26 个字母映射成 1..9 的权值，再双重循环枚举所有子串，边扩展边累加权值和并做整除判断。
# 时间复杂度：O(n^2)，枚举所有子串；空间复杂度：O(1)，只有固定大小的字符权值字典。
class Solution:  # LeetCode 约定的题解类
    def countDivisibleSubstrings(self, word: str) -> int:  # word 是小写字母串；返回数字和能被长度整除的子串个数
        d = ["ab", "cde", "fgh", "ijk", "lmn", "opq", "rst", "uvw", "xyz"]  # 字母到权值的分组表：第 1 组权值为 1，依次递增
        mp = {}  # 字典：字母 -> 权值
        for i, s in enumerate(d, 1):  # enumerate 的起始值设为 1，因此 i 直接就是该组的权值
            for c in s:  # 遍历当前组里的每个字符
                mp[c] = i  # 登记字母 c 的权值
        ans = 0  # 计数器：合法子串数量
        n = len(word)  # 字符串长度，循环中复用
        for i in range(n):  # 枚举子串左端点 i
            s = 0  # 当前子串的权值和，换起点时清零
            for j in range(i, n):  # 枚举右端点 j，逐个扩展子串
                s += mp[word[j]]  # 把新字符的权值累加进去
                ans += s % (j - i + 1) == 0  # 布尔值参与加法：条件成立记 1，否则记 0
        return ans  # 返回可整除子串的总数
