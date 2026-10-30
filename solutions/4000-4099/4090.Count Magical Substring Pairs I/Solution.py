# 题目：4090. 统计神奇子字符串对 I（Count Magical Substring Pairs I）
# 思路：枚举分界点 j，先倒序枚举左半子串 s[i..j]，把「恰好含 d 个不同字符」的左半子串个数记入 cnt[d]；再正序枚举右半子串 s[j+1..k]，用 cnt2 得到右半的不同字符数 d，直接累加 cnt[d]。左右两半不同字符数相等即为一个神奇子字符串对。
# 时间复杂度：O(n^3)，分界点、左端点、右端点各一层循环；空间复杂度：O(1)，cnt 固定 27 个格子，两个 defaultdict 最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def countMagicalPairs(self, s: str) -> int:  # s：待统计的字符串；返回满足左右两半不同字符数相等的位置对个数
        n = len(s)  # n 是字符串长度
        ans = 0  # ans 累计答案
        for j in range(n - 1):  # 枚举分界点 j：左半是 s[0..j]，右半从 j+1 开始
            cnt1 = defaultdict(int)  # cnt1：当前左半子串内各字符的出现次数
            cnt = [0] * 27  # cnt[d]：恰好含 d 个不同字符的左半子串个数，d 最大为 26
            for i in range(j, -1, -1):  # 左端点 i 从 j 递减到 0，逐步扩充左半子串
                cnt1[s[i]] += 1  # 把 s[i] 计入左半子串
                cnt[len(cnt1)] += 1  # 当前左半子串的不同字符数为 len(cnt1)，对应桶加一

            cnt2 = defaultdict(int)  # cnt2：当前右半子串内各字符的出现次数
            for k in range(j + 1, n):  # 右端点 k 从 j+1 递增到 n-1，逐步扩充右半子串
                cnt2[s[k]] += 1  # 把 s[k] 计入右半子串
                ans += cnt[len(cnt2)]  # 右半不同字符数为 len(cnt2)，与之相等的左半子串有 cnt[…] 个，全部计入答案

        return ans  # 返回神奇子字符串对的总数
