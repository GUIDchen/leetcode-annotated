// 题目：3111. 覆盖所有点的最少矩形数目（Minimum Rectangles to Cover Points）
// 思路：贪心：按 x 升序排序，每个矩形都让左端与被覆盖的最左点对齐，从而向右尽量多覆盖宽度 w 内的点，越界就新开矩形。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(1)，除排序外只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {  // points 是点集，w 是每个矩形宽度的上限
        sort(points.begin(), points.end());  // 按 x 坐标升序排序，矩形只关心 x 方向的覆盖范围
        int ans = 0, x1 = -1;  // ans 记矩形个数，x1 记当前矩形的右端点（-1 表示还没开矩形）
        for (const auto& p : points) {  // 从左到右依次扫描每个点
            int x = p[0];  // 取出该点的 x 坐标，y 坐标对覆盖没有影响
            if (x > x1) {  // 当前点已经超出已有矩形的覆盖范围
                ++ans;  // 必须新开一个矩形
                x1 = x + w;  // 新矩形左端与该点对齐时覆盖最远，右端点设为 x + w
            }
        }
        return ans;  // 返回覆盖所有点所需的最少矩形数
    }
};
