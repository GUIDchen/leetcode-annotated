# 题目：1566. 重复至少 K 次且长度为 M 的模式（Detect Pattern of Length M Repeated K or More Times）
# 思路：逐个比较 arr[i] 与 arr[i-m]，累计连续相等的次数；达到 (k-1)*m 就说明某个长度 m 的模式连续重复了 k 次。
# 时间复杂度：O(n)，n 为数组长度，只扫一遍；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def containsPattern(self, arr: List[int], m: int, k: int) -> bool:  # arr：输入数组；m：模式长度；k：最少重复次数
        if len(arr) < m * k:  # 总长度不足 m*k 时放不下 k 个长度为 m 的模式
            return False  # 直接判定不存在
        cnt, target = 0, (k - 1) * m  # cnt：已连续匹配的字符数；target：除首段外需要匹配的字符总数
        for i in range(m, len(arr)):  # 从下标 m 开始，才能与 i-m 处的字符对应比较
            if arr[i] == arr[i - m]:  # 与前 m 位的字符相等，说明模式正在延续
                cnt += 1  # 连续匹配长度加一
                if cnt == target:  # 已达 k 次重复所需的长度
                    return True  # 找到合法模式
            else:  # 模式被打断
                cnt = 0  # 计数清零，重新开始寻找
        return False  # 扫描结束仍未找到
