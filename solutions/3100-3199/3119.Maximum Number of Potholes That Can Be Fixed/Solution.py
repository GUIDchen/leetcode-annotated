# 题目：3119. 最大数量的可修复坑洼（Maximum Number of Potholes That Can Be Fixed，会员题）
# 思路：统计每种长度的连续坑洼段；按段长从大到小贪心，修完一段长 k 的坑洼要 k+1 预算、得 k 个坑，预算不够就拆成更短的段。
# 时间复杂度：O(n)，扫描道路一次 + 按段长倒序枚举；空间复杂度：O(n)，cnt 数组按段长计数。
class Solution:  # LeetCode 约定的题解类
    def maxPotholes(self, road: str, budget: int) -> int:  # road：道路字符串（'x' 为坑洼、'.' 为完好）；budget：可用预算
        road += "."  # 末尾补一个非坑洼字符，保证最后一段连续坑洼也能被结算
        n = len(road)  # 补齐后的长度，同时也是段长的上限
        cnt = [0] * n  # cnt[k]：长度为 k 的连续坑洼段共有多少段
        k = 0  # 当前连续坑洼的长度
        for c in road:  # 顺序扫描道路上的每个字符
            if c == "x":  # 遇到坑洼，当前段长加一
                k += 1  # 段长累加
            elif k:  # 遇到完好路面，且之前累计过坑洼
                cnt[k] += 1  # 这个长度的坑洼段又出现一次
                k = 0  # 段长清零，开始统计下一段
        ans = 0  # 记录能修好的坑洼总数
        for k in range(n - 1, 0, -1):  # 从长段到短段贪心，k 从大到小枚举
            if cnt[k] == 0:  # 该长度没有坑洼段，跳过
                continue  # 继续看更短的段
            t = min(budget // (k + 1), cnt[k])  # 修一整段长 k 的坑洼要 k+1 预算（末尾还要补一格），可获得 k 个坑洼
            ans += t * k  # 累加修好的坑洼数
            budget -= t * (k + 1)  # 扣除对应预算
            if budget == 0:  # 预算花完就结束
                break  # 跳出循环
            cnt[k - 1] += cnt[k] - t  # 没修的段拆成长度 k-1 的段，留给后面继续处理
        return ans  # 返回能修好的最大坑洼数
