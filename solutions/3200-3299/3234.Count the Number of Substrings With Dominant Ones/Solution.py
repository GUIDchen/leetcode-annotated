# 题目：3234. 统计 1 显著的字符串的数量（Count the Number of Substrings With Dominant Ones）
# 思路：先用 nxt 数组预处理出每个位置右侧第一个 0 的位置。枚举左端点，按窗口内 0 的个数 c 逐个 0 向右扩展；c 个 0 至少需要 c² 个 1，据此直接算出可行的右端点个数，c² > n 时提前停止。
# 时间复杂度：O(n√n)，每个左端点最多扩展 O(√n) 个 0；空间复杂度：O(n)，nxt 数组。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubstrings(self, s: str) -> int:  # s：只含 "0"/"1" 的字符串；返回“1 显著”的子串数量
        n = len(s)  # 字符串长度
        nxt = [n] * (n + 1)  # nxt[i]：从下标 i 起向右遇到的第一个 '0' 的位置，初值 n 作哨兵
        for i in range(n - 1, -1, -1):  # 从右往左递推
            nxt[i] = nxt[i + 1]  # 默认继承右边位置的结果
            if s[i] == "0":  # 当前位置本身就是 0
                nxt[i] = i  # 那么第一个 0 就是自己
        ans = 0  # 合法子串的计数
        for i in range(n):  # 枚举子串左端点
            cnt0 = int(s[i] == "0")  # 当前窗口中 0 的个数
            j = i  # j 是当前窗口中最右边 0 的位置
            while j < n and cnt0 * cnt0 <= n:  # 0 太多时 1 的数量不可能达标（需要 c² 个 1），提前退出
                cnt1 = (nxt[j + 1] - i) - cnt0  # 窗口内 1 的总数：全部长度减去 0 的个数
                if cnt1 >= cnt0 * cnt0:  # 1 的总量足够时，才可能存在满足条件的右端点
                    ans += min(nxt[j + 1] - j, cnt1 - cnt0 * cnt0 + 1)  # 右端点只能落在 [j, nxt[j+1]-1] 内，其中靠右的 cnt1-cnt0²+1 个位置能保证 1 显著
                j = nxt[j + 1]  # 把窗口向右延续到下一个 0 的位置
                cnt0 += 1  # 窗口内 0 的个数加一
        return ans  # 返回所有满足条件的子串数量
