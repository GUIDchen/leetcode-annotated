// 题目：1266. 访问所有点的最小时间（Minimum Time Visiting All Points）
// 思路：相邻两点的最短耗时就是切比雪夫距离 max(|dx|, |dy|)——先沿对角线同时缩小两个方向的差，剩余部分再走直线；全部累加即为答案。
// 时间复杂度：O(n)，遍历所有相邻点对；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {  // points 是点坐标数组，按顺序访问
        int ans = 0;  // ans 累加相邻两点之间的最短耗时
        for (int i = 1; i < points.size(); ++i) {  // 从第二个点开始，与它前一个点配对（points.size() 为点数）
            int dx = abs(points[i][0] - points[i - 1][0]);  // 两点在 x 方向上的距离
            int dy = abs(points[i][1] - points[i - 1][1]);  // 两点在 y 方向上的距离
            ans += max(dx, dy);  // 切比雪夫距离就是这一段的最短耗时；std::max 由头文件提供
        }  // 结束循环
        return ans;  // 返回访问全部点的总耗时
    }  // 结束 minTimeToVisitAllPoints
};  // 结束题解类