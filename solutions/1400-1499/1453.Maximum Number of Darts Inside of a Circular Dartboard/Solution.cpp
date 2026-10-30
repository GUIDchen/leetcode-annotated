// 题目：1453. 圆形靶内的最大飞镖数量（Maximum Number of Darts Inside of a Circular Dartboard）
// 核心思路：最优圆一定可以平移/旋转到边界经过两枚飞镖，于是枚举所有点对，求出半径为 r 且过这两点的两个圆心，分别统计覆盖的飞镖数取最大。
// 时间复杂度：O(n^3)，点对 O(n^2) 乘以每次统计 O(n)；空间复杂度：O(1) 额外空间（不含输入）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numPoints(vector<vector<int>>& darts, int r) {  // 返回半径为 r 的圆最多能覆盖的飞镖数量
        int n = darts.size();  // 飞镖总数
        int maxDarts = 1;  // 至少能覆盖 1 枚飞镖（题目保证 n ≥ 1）
        for (int i = 0; i < n; ++i) {  // 枚举圆边界上的一枚飞镖
            for (int j = i + 1; j < n; ++j) {  // 枚举圆边界上的另一枚飞镖（只取 j > i 避免重复）
                auto centers = possibleCenters(darts[i][0], darts[i][1], darts[j][0], darts[j][1], r);  // 求同时经过这两个点、半径为 r 的两个候选圆心
                for (auto& c : centers) {  // 分别以每个候选圆心统计覆盖的飞镖数
                    maxDarts = max(maxDarts, countDarts(c[0], c[1], darts, r));  // 用当前圆心的覆盖数刷新最大值
                }  // 候选圆心循环结束
            }  // 点对循环结束
        }  // 点对循环结束
        return maxDarts;  // 返回最大覆盖数量
    }  // numPoints 方法结束

private:  // 以下为内部辅助函数
    vector<array<double, 2>> possibleCenters(int x1, int y1, int x2, int y2, int r) {  // 求同时经过 (x1,y1)、(x2,y2) 且半径为 r 的圆心，最多两个
        vector<array<double, 2>> centers;  // 候选圆心列表，两点距离超过直径时为空
        double dx = x2 - x1, dy = y2 - y1;  // 两点之间的位移向量
        double d = sqrt(dx * dx + dy * dy);  // 两点间的距离，也就是圆上弦的长度
        if (d > 2.0 * r) {  // 弦长超过直径，半径为 r 的圆无法同时经过这两点
            return centers;  // 直接返回空列表
        }  // if 分支结束
        double midX = (x1 + x2) / 2.0, midY = (y1 + y2) / 2.0;  // 弦的中点，两个圆心都在过中点且垂直于弦的中垂线上
        double distToCenter = sqrt(1.0 * r * r - (d / 2.0) * (d / 2.0));  // 由勾股定理求中点沿中垂线到圆心的距离
        double offsetX = distToCenter * dy / d;  // 弦的单位法向量是 (dy/d, -dx/d)，乘以偏移距离得到 x 方向偏移
        double offsetY = distToCenter * -dx / d;  // 同一法向量乘以偏移距离得到 y 方向偏移
        centers.push_back({midX + offsetX, midY + offsetY});  // 中垂线一侧的圆心
        centers.push_back({midX - offsetX, midY - offsetY});  // 中垂线另一侧的圆心
        return centers;  // 返回两个候选圆心
    }  // possibleCenters 方法结束

    int countDarts(double x, double y, vector<vector<int>>& darts, int r) {  // 统计以 (x,y) 为圆心、半径为 r 的圆内的飞镖数量
        int count = 0;  // 计数器初始化
        for (auto& dart : darts) {  // 遍历每一枚飞镖
            if (hypot(dart[0] - x, dart[1] - y) <= r + 1e-7) {  // 欧氏距离不超过半径（加 1e-7 容差抵消浮点误差）
                ++count;  // 该飞镖落在圆内，计数加一
            }  // if 分支结束
        }  // for 循环结束
        return count;  // 返回圆内飞镖数量
    }  // countDarts 方法结束
};  // 类定义结束
