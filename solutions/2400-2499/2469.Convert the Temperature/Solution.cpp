// 题目：2469. 温度转换（Convert the Temperature）
// 核心思路：直接套换算公式，开尔文 = 摄氏度 + 273.15，华氏度 = 摄氏度 × 1.8 + 32，用初始化列表返回两项结果。
// 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)，返回固定两个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<double> convertTemperature(double celsius) {  // celsius 是输入的摄氏温度
        return {celsius + 273.15, celsius * 1.8 + 32};  // 依次返回开尔文温度与华氏温度
    }
};