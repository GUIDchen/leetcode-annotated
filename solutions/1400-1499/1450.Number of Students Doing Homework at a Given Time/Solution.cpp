// 题目：1450. 在既定时间做作业的学生人数（Number of Students Doing Homework at a Given Time）
// 核心思路：遍历每个学生，判断 queryTime 是否落在闭区间 [startTime[i], endTime[i]] 内，成立就累加计数。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用一个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {  // 返回在 queryTime 时刻正在做作业的学生人数
        int ans = 0;  // 计数器初始化为 0
        for (int i = 0; i < startTime.size(); ++i) {  // 逐个学生检查其做作业的时间区间
            ans += startTime[i] <= queryTime && queryTime <= endTime[i];  // 布尔表达式参与加法：条件成立贡献 1，不成立贡献 0
        }  // for 循环结束
        return ans;  // 返回满足条件的学生人数
    }  // busyStudent 方法结束
};  // 类定义结束（源文件此处无结尾换行，保持原样）