# 题目：1177. 构建回文串检测（Can Make Palindrome from Substring）
# 思路：二维前缀计数，ss[i][c] 表示前 i 个字符中字母 c 的个数；区间内出现奇数次的字母有 cnt 种时，
#       只需改 cnt//2 个字符即可成回文，因此判断 cnt//2 <= k。时间复杂度 O((n+q)*26)，空间 O(26n)。
class Solution:  # LeetCode 约定的题解类
    def canMakePaliQueries(self, s: str, queries: List[List[int]]) -> List[bool]:  # s 为原字符串，queries 每项是 [l, r, k] 的查询
        n = len(s)  # 字符串长度
        ss = [[0] * 26 for _ in range(n + 1)]  # 前缀计数表，(n+1) x 26 的一维步进方式，ss[i] 表示前 i 个字符的字母频次
        for i, c in enumerate(s, 1):  # 从 1 开始编号，i 表示“前 i 个字符”
            ss[i] = ss[i - 1][:]  # 用切片复制上一行，保证各行独立，不会互相污染
            ss[i][ord(c) - ord("a")] += 1  # 把当前字符计入对应字母，得到前 i 个字符的频次
        ans = []  # 按查询顺序保存布尔结果
        for l, r, k in queries:  # 逐个查询取出区间端点与最多可替换字符数
            cnt = sum((ss[r + 1][j] - ss[l][j]) & 1 for j in range(26))  # 统计区间内出现奇数次的字母种数，&1 取最低位判断奇偶
            ans.append(cnt // 2 <= k)  # 奇数种数 cnt 最多保留 1 个，需改 cnt//2 个字符，判断是否不超过 k
        return ans  # 返回全部查询的答案
