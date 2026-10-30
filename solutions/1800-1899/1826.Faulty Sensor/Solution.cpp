// 题目：1826. 有缺陷的传感器（Faulty Sensor）
// 核心思路：先跳过两数组完全相同的前缀；从第一处差异开始，分别假设 sensor1 或 sensor2 少了一个读数（即整体错位一位），再验证哪种假设能让后续元素全部对齐。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，仅用两个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int badSensor(vector<int>& sensor1, vector<int>& sensor2) {  // sensor1、sensor2 是两路传感器的读数序列，长度相同
        int i = 0;  // i 指向第一处可能出现差异的下标
        int n = sensor1.size();  // n 是序列长度
        for (; i < n - 1 && sensor1[i] == sensor2[i]; ++i) {}  // 先跳过读数完全相同的前缀，把 i 停在第一处差异上
        for (; i < n - 1; ++i) {  // 从差异位置开始，验证「谁少读了一个数」的两种假设
            if (sensor1[i + 1] != sensor2[i]) return 1;  // 假设 sensor1 缺读数：sensor1 应整体比 sensor2 前移一位
            if (sensor1[i] != sensor2[i + 1]) return 2;  // 假设 sensor2 缺读数：sensor2 应整体比 sensor1 前移一位
        }
        return -1;  // 两种假设都与后续数据吻合，无法判定谁有缺陷
    }
};  // 类定义结束