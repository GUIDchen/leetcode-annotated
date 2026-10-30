// 题目：1491. 去掉最低工资和最高工资后的工资平均值（Average Salary Excluding the Minimum and Maximum Salary）
// 思路：一趟遍历同时维护工资总和、最小值、最大值，最后从总和中扣掉最值再除以 n-2。
// 时间复杂度：O(n)，只遍历数组一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double average(vector<int>& salary) {  // 返回去掉一个最小值和一个最大值后的平均值
        int s = 0;  // 工资总和
        int mi = 1e7, mx = 0;  // 最小值初始化得比任何工资都大，最大值初始化为 0，方便后续更新
        for (int v : salary) {  // 遍历每个工资
            s += v;  // 累加总和
            mi = min(mi, v);  // 更新最小值
            mx = max(mx, v);  // 更新最大值
        }  // 从总和中扣掉一个最小值和一个最大值
        s -= (mi + mx);  // 除以 n-2 得到平均值；(double) 强转避免整数除法丢精度
        return (double) s / (salary.size() - 2);  // 方法结束
    }
};  // 类定义结束