# 题目：967. 连续差相同的数字（Numbers With Same Consecutive Differences）
# 思路：DFS 从 1~9 作为最高位逐位向下构造，每次追加与末位相差 k 的数字，位数达到 n 位就收集。
# 时间复杂度：O(答案个数 * n)，每个答案构造 n 位；空间复杂度：O(n)，递归深度等于位数。
class Solution:  # LeetCode 约定的题解类
    def numsSameConsecDiff(self, n: int, k: int) -> List[int]:  # n 是位数，k 是相邻两位数字差的绝对值
        def dfs(x: int):  # 内部 DFS：把已构造出的数 x 继续向低位扩展
            if x >= boundary:  # x 已不小于 10^(n-1)，说明位数已够，构造完成
                ans.append(x)  # 收集这个数
                return  # 结束当前分支
            last = x % 10  # 位数判断结束，取出末位数字
            if last + k <= 9:  # 末位加 k 仍是个位数字，可以继续追加
                dfs(x * 10 + last + k)  # 追加 (last + k) 这一位后继续递归
            if last - k >= 0 and k != 0:  # 末位减 k 仍是个位数字；k 为 0 时与上一分支重复，故需排除
                dfs(x * 10 + last - k)  # 追加 (last - k) 这一位后继续递归

        ans = []  # 收集答案的列表（dfs 通过闭包往里追加）
        boundary = 10 ** (n - 1)  # 10^(n-1) 是 n 位数的最小值，用来判断位数是否足够
        for i in range(1, 10):  # 首位不能为 0，从 1 到 9 依次作为起点
            dfs(i)  # 以 i 为最高位开始构造
        return ans  # 返回全部结果
