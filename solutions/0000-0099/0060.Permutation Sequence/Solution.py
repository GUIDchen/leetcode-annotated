# 题目：60. 排列序列（Permutation Sequence）
# 思路：逐位构造。固定前 i 位后，剩余数字的排列数是 (n-i-1)!，用它当块大小去和 k 比较，跳过整块即可定位当前位。
# 时间复杂度：O(n^2)，n 位各扫描最多 n 个候选数；空间复杂度：O(n)，vis 标记数组与答案列表。
class Solution:  # LeetCode 约定的题解类
    def getPermutation(self, n: int, k: int) -> str:  # n：数字个数（1..n），k：第 k 个排列（1 起计）
        ans = []  # 逐位收集答案字符，最后再拼接成字符串
        vis = [False] * (n + 1)  # vis[x] 表示数字 x 是否已被使用；多开一位方便用 1..n 直接下标
        for i in range(n):  # 依次确定答案的第 0..n-1 位
            fact = 1  # 剩余位数的全排列数，也就是每个首位数字能覆盖的块大小
            for j in range(1, n - i):  # 连乘 1 到 n-i-1，得到 (n-i-1)!
                fact *= j  # 累乘
            for j in range(1, n + 1):  # 从小到大枚举这一位可选的数字
                if not vis[j]:  # 只考虑还没用过的数字
                    if k > fact:  # 以 j 开头的排列有 fact 个，k 比它大说明目标在后面
                        k -= fact  # 整块跳过，k 变为块内偏移
                    else:  # 目标就在以 j 打头的这一块里
                        ans.append(str(j))  # 确定这一位
                        vis[j] = True  # 标记 j 已使用
                        break  # 这一位确定完毕，退出候选枚举
        return ''.join(ans)  # 把字符列表拼成最终的排列字符串
