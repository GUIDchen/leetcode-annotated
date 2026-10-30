# 题目：1826. 有缺陷的传感器（Faulty Sensor）
# 核心思路：先跳过两数组相同的前缀；从第一处差异开始，分别假设 sensor1 或 sensor2 缺了一个读数而整体错位一位，再验证哪种假设能让后续元素全部对齐。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，仅用两个下标变量。
class Solution:  # LeetCode 约定的题解类
    def badSensor(self, sensor1: List[int], sensor2: List[int]) -> int:  # 返回有缺陷的传感器编号（1 或 2），无法判定时返回 -1
        i, n = 0, len(sensor1)  # i 为当前下标，n 为序列长度
        while i < n - 1:  # 跳过两路读数完全相同的部分
            if sensor1[i] != sensor2[i]:  # 遇到第一处不同就停下
                break  # 结束前缀匹配
            i += 1  # 从差异位置继续向后验证
        while i < n - 1:  # 这里开始验证两种「缺一个读数」的假设
            if sensor1[i + 1] != sensor2[i]:  # 假设 sensor1 缺读数，则 sensor1 应整体前移一位
                return 1  # 命中说明传感器 1 有缺陷
            if sensor1[i] != sensor2[i + 1]:  # 假设 sensor2 缺读数，则 sensor2 应整体前移一位
                return 2  # 命中说明传感器 2 有缺陷
            i += 1  # 两种假设都不成立时继续向后检查
        return -1  # 两种假设都无法排除，返回 -1
