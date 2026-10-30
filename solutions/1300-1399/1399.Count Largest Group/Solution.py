# 题目：1399. 统计最大组的数目（Count Largest Group）
# 思路：用 Counter 按「十进制数位和」分组计数；遍历过程中维护当前最大组大小 mx，以及有多少个组达到了这个大小。
# 时间复杂度：O(n * log10 n)，每个数都要拆一遍数位；空间复杂度：O(log10 n)，计数器里最多只有几十个键。
class Solution:  # LeetCode 约定的题解类
    def countLargestGroup(self, n: int) -> int:  # n 是统计范围 1 ~ n
        cnt = Counter()  # 记录每个「数位和」对应的数字个数
        ans = mx = 0  # ans：达到最大组大小的组数；mx：当前最大的组大小
        for i in range(1, n + 1):  # 依次处理 1 ~ n 中的每个数
            s = 0  # 当前数字的数位和
            while i:  # 循环变量 i 在这里被就地拆解（for 每轮会重新赋值，所以不影响外层遍历）
                s += i % 10  # 取出最低位并累加到数位和
                i //= 10  # 去掉最低位
            cnt[s] += 1  # 数位和为 s 的这一组计数加一
            if mx < cnt[s]:  # 出现了比当前最大组更大的组
                mx = cnt[s]  # 更新最大组大小
                ans = 1  # 目前只有这一个组达到最大，重置计数为 1
            elif mx == cnt[s]:  # 该组追平了当前的最大组
                ans += 1  # 达到最大组大小的组数加一
        return ans  # 返回达到最大大小的组数
