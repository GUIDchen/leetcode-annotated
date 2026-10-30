# 题目：1894. 找到需要补充粉笔的学生编号（Find the Student that Will Replace the Chalk）
# 思路：一轮总消耗为 sum(chalk)，先对 k 取模去掉所有完整轮次，再依次扣减，第一个扣不动的人即答案。
# 时间复杂度：O(n)，取模加一次扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def chalkReplacer(self, chalk: List[int], k: int) -> int:  # chalk：每位学生消耗的粉笔数；k：初始粉笔总数，返回需要补充粉笔的学生下标
        s = sum(chalk)  # 一轮消耗的粉笔总数
        k %= s  # 跳过所有完整轮次，剩余 k 一定小于一轮总和
        for i, x in enumerate(chalk):  # 按顺序逐个扣减，enumerate 同时给出下标 i 与消耗 x
            if k < x:  # 剩余粉笔不够第 i 位学生使用，他就是答案
                return i  # 返回该学生的下标
            k -= x  # 够用就扣掉，继续下一位（题目保证有解，循环内必然返回）
