# 题目：1578. 使绳子变成彩色的最短时间（Minimum Time to Make Rope Colorful）
# 思路：把颜色相同的气球按连续段分组；每一段若长度大于 1，就必须删到只剩一个，最优是保留耗时最长的那个，代价为段内总耗时减去最大耗时。
# 时间复杂度：O(n)，每个气球只被扫描一次；空间复杂度：O(1)，只用常数个累加变量。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, colors: str, neededTime: List[int]) -> int:  # colors 为颜色串，neededTime 为移除每个气球的耗时，返回最小总耗时
        ans = i = 0  # ans 累计答案，i 是当前同色组的起点，二者初始都为 0
        n = len(colors)  # 气球数量
        while i < n:  # 逐组扫描，直到越过末尾
            j = i  # j 从组首开始向后延伸
            s = mx = 0  # s 为组内耗时总和，mx 为组内最大耗时
            while j < n and colors[j] == colors[i]:  # 颜色与组首相同就继续扩大本组
                s += neededTime[j]  # 累加本组总耗时
                if mx < neededTime[j]:  # 手写比较以更新本组最大耗时
                    mx = neededTime[j]  # 记录更大的耗时
                j += 1  # 后移一位
            if j - i > 1:  # 组内多于一个气球就必须移除
                ans += s - mx  # 保留最贵的那个，删掉其余，代价为总和减最大值
            i = j  # 跳到下一组的起点
        return ans  # 返回最小总耗时
