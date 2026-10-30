// 题目：469. 凸多边形（Convex Polygon）
// 思路：依次计算相邻两条边向量的叉积，用其符号表示该顶点的拐向；所有非零叉积必须同号（允许 0 表示共线），出现异号即为凹多边形。
// 时间复杂度：O(n)，遍历一次顶点；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isConvex(vector<vector<int>>& points) {  // points：按顺序给出的多边形顶点坐标
        int n = points.size();  // 顶点个数
        long long pre = 0, cur = 0;  // pre 记录上一个非零叉积，cur 是当前叉积
        for (int i = 0; i < n; ++i) {  // 依次检查每个顶点处的拐向
            int x1 = points[(i + 1) % n][0] - points[i][0];  // 第一条边向量（指向下一个顶点）的 x 分量
            int y1 = points[(i + 1) % n][1] - points[i][1];  // 第一条边向量的 y 分量
            int x2 = points[(i + 2) % n][0] - points[i][0];  // 第二条边向量（指向下下个顶点）的 x 分量
            int y2 = points[(i + 2) % n][1] - points[i][1];  // 第二条边向量的 y 分量
            cur = 1L * x1 * y2 - x2 * y1;  // 叉积决定拐向：正为逆时针，负为顺时针
            if (cur != 0) {  // 0 表示三点共线，不提供方向信息
                if (cur * pre < 0) {  // 与之前的拐向相反，说明出现凹角
                    return false;  // 立即判定不是凸多边形
                }  // 结束异号判断
                pre = cur;  // 记录本次拐向供后续比较
            }  // 结束非零判断
        }  // 结束顶点遍历
        return true;  // 所有拐向一致，是凸多边形
    }  // 结束 isConvex
};  // 结束 Solution 类