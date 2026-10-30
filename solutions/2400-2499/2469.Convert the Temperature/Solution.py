# 题目：2469. 温度转换（Convert the Temperature）
# 核心思路：直接套换算公式，开尔文 = 摄氏度 + 273.15，华氏度 = 摄氏度 × 1.8 + 32，返回 [开尔文, 华氏度]。
# 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)，返回固定两个元素。
class Solution:  # LeetCode 约定的题解类
    def convertTemperature(self, celsius: float) -> List[float]:  # celsius 是输入的摄氏温度，返回 [开尔文, 华氏度]
        return [celsius + 273.15, celsius * 1.8 + 32]  # 列表第一项转开尔文，第二项转华氏度
