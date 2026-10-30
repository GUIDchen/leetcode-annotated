# 题目：66. 加一（Plus One）
# 思路：从个位向高位逐位加一，逢十置零继续进位；一旦某位加完不为 0 就提前返回，全部位归零时在最前面补 1。
# 时间复杂度：O(n)，最坏遍历全部 n 位；空间复杂度：O(1)，除返回值外只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def plusOne(self, digits: List[int]) -> List[int]:  # digits：按高位到低位存放的数字数组
        n = len(digits)  # 先取长度，供下面的倒序遍历使用
        for i in range(n - 1, -1, -1):  # 从末位（个位）向高位倒序扫描
            digits[i] += 1  # 当前这一位加 1
            digits[i] %= 10  # 取模 10：若原来是 9，加一后变 0，表示要向更高位进位
            if digits[i] != 0:  # 加完不为 0，说明本次没有产生进位
                return digits  # 高位都不受影响，立即返回结果
        return [1] + digits  # 所有位都变成了 0（如 999 -> 000），前面补一个 1 作为新的最高位
