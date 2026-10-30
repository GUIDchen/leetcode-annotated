// 题目：2798. 满足目标工作时长的员工数目（Number of Employees Who Met the Target）
// 思路：用 count_if 遍历工时数组，统计满足 h >= target 的员工人数。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {  // hours：每位员工的工时；target：目标工时
        return count_if(hours.begin(), hours.end(), [target](int h) { return h >= target; });  // count_if 统计区间内使谓词为真的元素个数，lambda 捕获 target 并判断 h >= target
    }  // 方法结束
};  // 类定义结束