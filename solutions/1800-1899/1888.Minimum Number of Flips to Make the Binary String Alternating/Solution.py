# 题目：1888. 使二进制字符串字符交替的最少反转次数（Minimum Number of Flips to Make the Binary String Alternating）
# 思路：交替目标只有 "01" 与 "10" 两种；先用生成器求和统计原串与 "01" 的不匹配数 cnt（"10" 即 n-cnt），再滑动枚举 n 种旋转，逐位撤销旧贡献、加上新贡献。
# 时间复杂度：O(n)，一次统计加一次滑动；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, s: str) -> int:  # s 是二进制字符串，可任意次把首字符移到末尾，返回最少翻转次数
        n = len(s)  # 字符串长度
        target = "01"  # 模式串 "01"，用它的循环下标表示交替串的两种模式
        cnt = sum(c != target[i & 1] for i, c in enumerate(s))  # 布尔值可当 0/1 直接相加，一次性统计与 "01" 不匹配的位数
        ans = min(cnt, n - cnt)  # 另一种模式 "10" 的不匹配数是 n - cnt，取较小者作为初值
        for i in range(n):  # 枚举 n 种旋转：每轮把 s[i] 从队首搬到队尾
            cnt -= s[i] != target[i & 1]  # s[i] 离开位置 i，先减去它此刻的不匹配贡献（True 即 1）
            cnt += s[i] != target[(i + n) & 1]  # 它落到位置 i + n，与新模式位比较，不匹配就加回 1
            ans = min(ans, cnt, n - cnt)  # 两种模式取小，刷新答案
        return ans  # 返回所有旋转、所有模式下的最少翻转次数
