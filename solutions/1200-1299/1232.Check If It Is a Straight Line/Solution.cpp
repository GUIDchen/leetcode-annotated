// 题目：1232. 缀点成线（Check If It Is a Straight Line）
// 思路：以第 1、2 个点为基准，其余点逐个用叉积判断是否与基准点共线（两边斜率相等即叉积为 0）。
// 时间复杂度：O(n)，遍历所有点一次；空间复杂度：O(1)，只用常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkStraightLine(vector<vector<int>>& coordinates) {  // coordinates 是所有点的坐标，返回这些点是否全部共线
        int x1 = coordinates[0][0], y1 = coordinates[0][1];  // 取第 1 个点作为共线判断的基准点
        int x2 = coordinates[1][0], y2 = coordinates[1][1];  // 取第 2 个点确定直线的方向 (x2 - x1, y2 - y1)
        for (int i = 2; i < coordinates.size(); ++i) {  // 从第 3 个点开始逐个验证
            int x = coordinates[i][0], y = coordinates[i][1];  // 当前待验证的点 (x, y)
            if ((x - x1) * (y2 - y1) != (y - y1) * (x2 - x1)) {  // 叉积不为 0 表示斜率不同，该点不在基准直线上（用乘法避免除法与浮点误差）
                return false;  // 发现不共线的点，立即返回 false
            }  // if 结束
        }  // for 结束
        return true;  // 所有点都共线
    }  // 方法结束
};  // 类定义结束