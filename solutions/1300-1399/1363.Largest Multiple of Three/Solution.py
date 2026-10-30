# 题目：1363. 形成三的最大倍数（Largest Multiple of Three）
# 思路：排序后做「数字和模 3」的长度 DP：f[i][j] 表示前 i 个数字能选出的、和模 3 余 j 的最大长度，再从后往前回溯出具体数字，最后去掉前导零。
# 时间复杂度：O(n)，一次 DP 加一次回溯；空间复杂度：O(n)，DP 数组 f。
class Solution:  # LeetCode 约定的题解类
    def largestMultipleOfThree(self, digits: List[int]) -> str:  # digits 是可用数字列表，返回能被 3 整除的最大数字串
        digits.sort()  # 升序排序，便于 DP 以及回溯时先取到较大的数字
        n = len(digits)  # n 是数字个数
        f = [[-inf] * 3 for _ in range(n + 1)]  # f[i][j]：前 i 个数字中能选出的、和模 3 余 j 的最大长度，先全部置为 -inf
        f[0][0] = 0  # 一个都不选时和为 0、余 0、长度 0
        for i, x in enumerate(digits, 1):  # 逐个考虑每个数字（enumerate 从 1 开始编号）
            for j in range(3):  # 枚举目标余数 j
                f[i][j] = max(f[i - 1][j], f[i - 1][(j - x % 3 + 3) % 3] + 1)  # 不选第 i 个数字，或选它（余数由 k 变为 j），取长度更大的方案
        if f[n][0] <= 0:  # 没有任何非空子集能被 3 整除
            return ""  # 按题意返回空字符串
        arr = []  # 保存回溯出的数字（先记大数，结果天然最大）
        j = 0  # 当前状态需要满足的余数是 0
        for i in range(n, 0, -1):  # 从最后一位往前回溯
            k = (j - digits[i - 1] % 3 + 3) % 3  # 若选第 i 个数字，则上一状态需要的余数 k
            if f[i - 1][k] + 1 == f[i][j]:  # 长度恰好差 1，说明第 i 个数字确实被选中
                arr.append(digits[i - 1])  # 记录该数字
                j = k  # 更新需要的余数，继续往前回溯
        i = 0  # 从头开始找第一个非零数字
        while i < len(arr) - 1 and arr[i] == 0:  # 跳过前导零，但至少保留一位
            i += 1  # 继续后移
        return "".join(map(str, arr[i:]))  # 保留非前导零部分并拼接成字符串返回
