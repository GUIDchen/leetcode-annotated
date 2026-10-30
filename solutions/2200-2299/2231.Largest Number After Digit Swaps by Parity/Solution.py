# 题目：2231. 按奇偶性交换后的最大数字（Largest Number After Digit Swaps by Parity）
# 核心思路：交换只能发生在奇偶性相同的数字之间，因此每一位的候选集合由该位原数字的奇偶性固定；
#           先统计各数字出现次数，再从高位到低位尽量放同奇偶性中最大的可用数字。
# 时间复杂度：O(n + 10)，n 为位数；空间复杂度：O(1)，只有计数表与常数个变量。
class Solution:  # LeetCode 约定的题解类
    def largestInteger(self, num: int) -> int:  # num：输入的非负整数
        nums = [int(c) for c in str(num)]  # 拆出每一位数字，保留原来的顺序
        cnt = Counter(nums)  # cnt[d]：数字 d 的剩余可用次数
        idx = [8, 9]  # idx[0]=当前最大偶数字，idx[1]=当前最大奇数字
        ans = 0  # 逐位拼接出的答案
        for x in nums:  # 从左到右处理每一位
            while cnt[idx[x & 1]] == 0:  # 该奇偶性下最大的数字已经用完
                idx[x & 1] -= 2  # 往下找同奇偶性的次大数字（减 2 不改变奇偶性）
            ans = ans * 10 + idx[x & 1]  # 高位填尽量大的数字，保证结果最大
            cnt[idx[x & 1]] -= 1  # 用掉一个，剩余计数减一
        return ans  # 返回最大结果
