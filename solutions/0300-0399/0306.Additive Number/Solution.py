# 题目：306. 累加数（Additive Number）
# 思路：枚举前两个数的切分位置，再用 DFS 逐位校验后续能否由前两项之和拼出。
# 时间复杂度：最坏 O(n^3)，n 为串长；空间复杂度：O(n)，递归栈与切片开销。
class Solution:  # LeetCode 约定的题解类
    def isAdditiveNumber(self, num: str) -> bool:  # num 是数字字符串，判断能否拆成累加序列
        def dfs(a, b, num):  # 深度优先：已知前两项 a、b，判断剩余串 num 能否续成累加序列
            if not num:  # 剩余串为空，说明整个串已成功拆分
                return True  # 返回成功
            if a + b > 0 and num[0] == '0':  # 下一项 a+b 若为正数，剩余串就不能以 '0' 开头，否则拼不出合法数字
                return False  # 直接判定失败
            for i in range(1, len(num) + 1):  # 枚举下一项的长度 i（最长取到整个剩余串）
                if a + b == int(num[:i]):  # 若剩余串前 i 位恰好等于 a+b
                    if dfs(b, a + b, num[i:]):  # 把 b 与 a+b 当作新的前两项继续递归
                        return True  # 某条分支成功即整体成功
            return False  # 所有长度都不行，本层失败

        n = len(num)  # 串长
        for i in range(1, n - 1):  # 枚举第一个数的结束位置 i
            for j in range(i + 1, n):  # 枚举第二个数的结束位置 j
                if i > 1 and num[0] == '0':  # 第一个数多位且以 '0' 开头不合法，后面的 i 只会更长，直接跳出
                    break  # 跳出内层循环
                if j - i > 1 and num[i] == '0':  # 第二个数多位且以 '0' 开头不合法，换下一个 j
                    continue  # 跳过本次 j
                if dfs(int(num[:i]), int(num[i:j]), num[j:]):  # 用前两个数启动深度优先搜索
                    return True  # 找到一种合法拆分即返回
        return False  # 全部枚举完仍未找到
