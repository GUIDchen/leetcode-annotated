# 题目：3340. 检查平衡字符串（Check Balanced String）
# 思路：按下标奇偶分成两组分别累加数字，最后比较两组和是否相等。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(1)，只用一个长度 2 的列表。
class Solution:  # LeetCode 约定的题解类
    def isBalanced(self, num: str) -> bool:  # num 是只含数字字符的字符串，返回是否为平衡字符串
        f = [0, 0]  # f[0]/f[1] 分别累加偶数下标与奇数下标的数字和
        for i, x in enumerate(map(int, num)):  # 同时取得下标 i 与 map(int, num) 转换后的数字 x
            f[i & 1] += x  # i & 1 区分奇偶下标，把数字累加到对应位置
        return f[0] == f[1]  # 两组数字和相等即为平衡字符串
