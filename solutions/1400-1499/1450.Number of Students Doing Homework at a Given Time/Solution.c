// 题目：1450. 在既定时间做作业的学生人数（Number of Students Doing Homework at a Given Time）
// 核心思路：遍历每个学生，判断 queryTime 是否落在闭区间 [startTime[i], endTime[i]] 内，落入则计数加一。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用一个计数变量。
int busyStudent(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int queryTime) {  // 返回在 queryTime 时刻正在做作业的学生人数（判题片段，无 main 函数）
    int ans = 0;  // 计数器初始化为 0
    for (int i = 0; i < startTimeSize; i++) {  // 逐个学生检查其做作业的时间区间
        if (startTime[i] <= queryTime && endTime[i] >= queryTime) {  // 开始时间不晚于查询时刻，且结束时间不早于查询时刻，即区间包含 queryTime
            ans++;  // 该学生此刻正在做作业，计数加一
        }  // if 分支结束
    }  // for 循环结束
    return ans;  // 返回满足条件的学生人数
}  // busyStudent 函数结束
