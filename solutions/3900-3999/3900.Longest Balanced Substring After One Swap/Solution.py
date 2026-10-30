# 3900. 一次交换后的最长平衡子串 / Longest Balanced Substring After One Swap
# 核心思路：把 1 记 +1、0 记 -1 求前缀和，同前缀和的距离给出不交换时的答案；交换只能让区间差值改变 0 或 ±2，故再查相差 2 的前缀和位置，判断区间内是否还有可交换的字符。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 题解类
    def longestBalanced(self, s: str) -> int:  # s 为 0/1 串，返回至多交换一次后能得到的最长平衡子串长度
        cnt0 = s.count("0")  # 统计全串 0 的个数
        cnt1 = len(s) - cnt0  # 全串 1 的个数
        pos = {0: [-1]}  # 记录每个前缀和出现过的下标，空前缀和记为 -1
        ans = pre = 0  # ans 为答案，pre 为当前前缀和（1 记 +1，0 记 -1）
        for i, c in enumerate(s):  # 从左到右枚举右端点
            pre += 1 if c == "1" else -1  # 更新前缀和
            pos.setdefault(pre, []).append(i)  # 记录该前缀和出现的位置

            ans = max(ans, i - pos[pre][0])  # 不交换时，同一前缀和的最远左端点即可构成平衡子串
            if pre - 2 in pos:  # 相差 2 说明区间内 1 比 0 多 2，需要把一个 0 换进来
                p = pos[pre - 2]  # 取出该前缀和的所有出现位置
                if (i - p[0] - 2) // 2 < cnt0:  # 区间内还有多余的 0 可交换，整段可以保留
                    ans = max(ans, i - p[0])  # 以最远左端点更新答案
                elif len(p) > 1:  # 否则退到次远左端点，把缺的 1 挤出去
                    ans = max(ans, i - p[1])  # 用次远位置更新答案

            if pre + 2 in pos:  # 相差 2 说明区间内 0 比 1 多 2，需要把一个 1 换进来
                p = pos[pre + 2]  # 取出该前缀和的所有出现位置
                if (i - p[0] - 2) // 2 < cnt1:  # 区间内还有多余的 1 可交换，整段可以保留
                    ans = max(ans, i - p[0])  # 以最远左端点更新答案
                elif len(p) > 1:  # 否则退到次远左端点，把缺的 0 挤出去
                    ans = max(ans, i - p[1])  # 用次远位置更新答案
        return ans  # 返回最长平衡子串长度
