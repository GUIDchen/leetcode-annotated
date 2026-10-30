# 题目：412. Fizz Buzz（Fizz Buzz）
# 思路：逐个判断优先级：15 的倍数先判，再判 3、5，都不满足就转成字符串。
# 时间复杂度：O(n)，每个数处理一次；空间复杂度：O(n)，答案列表存 n 个字符串。
class Solution:  # LeetCode 约定的题解类
    def fizzBuzz(self, n: int) -> List[str]:  # n 是上界，返回 1..n 的 Fizz Buzz 结果列表
        ans = []  # 结果列表
        for i in range(1, n + 1):  # range(1, n + 1) 覆盖 1 到 n
            if i % 15 == 0:  # 同时被 3 和 5 整除，必须放在最前面判断
                ans.append('FizzBuzz')  # 追加 FizzBuzz
            elif i % 3 == 0:  # 只被 3 整除
                ans.append('Fizz')  # 追加 Fizz
            elif i % 5 == 0:  # 只被 5 整除
                ans.append('Buzz')  # 追加 Buzz
            else:  # 都不满足
                ans.append(str(i))  # 输出数字本身的字符串形式
        return ans  # 返回完整结果
