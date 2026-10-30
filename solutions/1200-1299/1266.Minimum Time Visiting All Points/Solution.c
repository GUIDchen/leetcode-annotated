// 题目：1266. 访问所有点的最小时间（Minimum Time Visiting All Points）
// 思路：两点间最短耗时等于切比雪夫距离 max(|dx|, |dy|)——对角线可以同时消掉两个方向的差，剩下的再直线移动；把相邻点的该距离累加即可。
// 时间复杂度：O(n)，一次遍历所有点；空间复杂度：O(1)，只用了常数个变量。
#define max(a, b) ((a) > (b) ? (a) : (b))  // C 标准库没有 max，这里用宏自己实现取较大值（三目运算符，注意参数需加括号防优先级问题）

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize) {  // points 是点坐标数组，pointsSize 为点数，pointsColSize 为每行列数（本题恒为 2，无需使用）
    int ans = 0;  // ans 累加相邻点之间的最短时间
    for (int i = 1; i < pointsSize; ++i) {  // 从第二个点开始，每次与它的前一个点配对计算
        int dx = abs(points[i][0] - points[i - 1][0]);  // 两点在 x 方向上的距离
        int dy = abs(points[i][1] - points[i - 1][1]);  // 两点在 y 方向上的距离
        ans += max(dx, dy);  // 切比雪夫距离 max(|dx|,|dy|) 就是这一段的最短耗时，累加到答案
    }  // 结束相邻点循环
    return ans;  // 返回访问全部点的总耗时
}  // 结束函数
