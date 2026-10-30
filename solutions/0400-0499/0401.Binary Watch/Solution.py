# 题目：401. 二进制手表（Binary Watch）
# 思路：暴力枚举。遍历小时 0-11 与分钟 0-59 的全部 720 种组合，筛出「小时与分钟二进制中 1 的个数之和」等于 turnedOn 的时刻。
# 时间复杂度：O(1)，固定 12*60 次枚举；空间复杂度：O(1)，除答案列表外只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def readBinaryWatch(self, turnedOn: int) -> List[str]:  # 返回所有恰好点亮 turnedOn 个 LED 的时刻
        return [  # 用列表推导式枚举全部时刻并一次性构造结果
            '{:d}:{:02d}'.format(i, j)  # 格式化成 H:MM，{:02d} 表示分钟不足两位时补 0
            for i in range(12)  # 枚举小时 0 到 11
            for j in range(60)  # 枚举分钟 0 到 59
            if (bin(i) + bin(j)).count('1') == turnedOn  # bin() 结果里的 1 的个数就是亮灯数，两段相加与 turnedOn 比较
        ]  # 推导式结束，得到答案列表
