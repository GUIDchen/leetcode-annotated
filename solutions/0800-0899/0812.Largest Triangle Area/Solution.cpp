// 题目：812. 最大三角形面积（Largest Triangle Area）
// 思路：枚举所有三点组合，用两条边向量的叉积绝对值除以 2 得到面积，取最大值。
// 时间复杂度：O(n^3)，三重循环枚举点；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double largestTriangleArea(vector<vector<int>>& points) {  // points 是点坐标数组，返回最大三角形面积
        double ans = 0;  // 记录当前最大面积，初值为 0
        for (auto& p1 : points) {  // 枚举第一个点
            int x1 = p1[0], y1 = p1[1];  // 取出第一个点的坐标
            for (auto& p2 : points) {  // 枚举第二个点
                int x2 = p2[0], y2 = p2[1];  // 取出第二个点的坐标
                for (auto& p3 : points) {  // 枚举第三个点
                    int x3 = p3[0], y3 = p3[1];  // 取出第三个点的坐标
                    int u1 = x2 - x1, v1 = y2 - y1;  // 以 p1 为起点的向量 p2 - p1 的两个分量
                    int u2 = x3 - x1, v2 = y3 - y1;  // 以 p1 为起点的向量 p3 - p1 的两个分量
                    double t = abs(u1 * v2 - u2 * v1) / 2.0;  // 叉积绝对值的一半就是三角形面积
                    ans = max(ans, t);  // 更新当前最大值
                }  // 第三重循环结束
            }  // 第二重循环结束
        }  // 第一重循环结束
        return ans;  // 返回最大面积
    }  // 方法结束
};  // 类定义结束