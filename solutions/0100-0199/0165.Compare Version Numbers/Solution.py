# 题目：165. 比较版本号（Compare Version Numbers）
# 核心思路：两个指针同步遍历，按 '.' 切段解析成整数比较；短的版本号缺段时用 0 补齐，第一个不相等的段决定结果。
# 时间复杂度：O(m + n)，每个字符只访问一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def compareVersion(self, version1: str, version2: str) -> int:  # 逐段比较两个版本号，返回 -1 / 0 / 1
        m, n = len(version1), len(version2)  # 两个字符串的长度
        i = j = 0  # 两个指针分别指向各自当前处理位置
        while i < m or j < n:  # 任一串未读完就继续；某一串提前结束时其缺的段按 0 处理
            a = b = 0  # 当前段解析出的整数值，从 0 开始累加
            while i < m and version1[i] != '.':  # 解析 version1 的一段，遇到 '.' 或结尾停止
                a = a * 10 + int(version1[i])  # 逐位累加：左移一位再加当前数字
                i += 1  # 指针后移一位
            while j < n and version2[j] != '.':  # 解析 version2 的一段
                b = b * 10 + int(version2[j])  # 同样的逐位累加
                j += 1  # 指针后移一位
            if a != b:  # 本段数值不同即可返回结果
                return -1 if a < b else 1  # 小者返回 -1，大者返回 1
            i, j = i + 1, j + 1  # 跳过本段结尾（'.' 或已越界的位置）
        return 0  # 所有段都相等，版本相同
