// 题目：3380. 用点构造面积最大的矩形 I（Maximum Area Rectangle With Point Constraints I）
// 思路：n 很小，枚举任意两点作为矩形的两个对角顶点并规整成 (x3,y3)-(x4,y4)；check 扫描全部点，要求矩形内无点、四条边上恰好只有 4 个给定点（四个角），满足则更新最大面积。
// 时间复杂度：O(n^3)，枚举点对 O(n^2) 乘以 check 的 O(n)；空间复杂度：O(1)，只用常数个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int maxRectangleArea(vector<vector<int>>& points) {  // points：所有给定点；矩形只能由这些点作为四个角，且内部与边上不能有多余的点
        auto check = [&](int x1, int y1, int x2, int y2) -> bool {  // check 是局部 lambda：判断以 (x1,y1)、(x2,y2) 为左下/右上角的矩形是否合法
            int cnt = 0;  // 计数器：统计落在矩形四角上的点数
            for (const auto& point : points) {  // 遍历所有给定点
                int x = point[0];  // 取出点的横坐标
                int y = point[1];  // 取出点的纵坐标
                if (x < x1 || x > x2 || y < y1 || y > y2) {  // 点落在矩形外（含边界外），与本题无关
                    continue;  // 直接跳过这个点
                }  // 越界判断结束
                if ((x == x1 || x == x2) && (y == y1 || y == y2)) {  // 点正好落在矩形的某个角上
                    cnt++;  // 合法角点，计数加一
                    continue;  // 跳过，继续看下一个点
                }  // 角点判断结束
                return false;  // 既在矩形内又不在角上：内部有点或边上有点，矩形不合法
            }  // 全部点扫描结束
            return cnt == 4;  // 恰好 4 个角点且没有其他点，说明构成合法矩形
        };  // check lambda 定义结束

        int ans = -1;  // 答案初始为 -1，表示暂时找不到合法矩形
        for (int i = 0; i < points.size(); i++) {  // 枚举第一个对角顶点 i
            int x1 = points[i][0], y1 = points[i][1];  // 取出第 i 个点的坐标
            for (int j = 0; j < i; j++) {  // 枚举另一个对角顶点 j（只看 j < i，避免重复枚举点对）
                int x2 = points[j][0], y2 = points[j][1];  // 取出第 j 个点的坐标
                int x3 = min(x1, x2), y3 = min(y1, y2);  // 两个点可能顺序颠倒，统一取较小的 x、y 作为左下角
                int x4 = max(x1, x2), y4 = max(y1, y2);  // 统一取较大的 x、y 作为右上角
                if (check(x3, y3, x4, y4)) {  // 用规整后的边界检查矩形是否合法
                    ans = max(ans, (x4 - x3) * (y4 - y3));  // 合法就用「宽 × 高」更新最大面积
                }  // 更新分支结束
            }  // 内层点对枚举结束
        }  // 外层点枚举结束
        return ans;  // 返回最大面积（找不到合法矩形时为 -1）
    }  // maxRectangleArea 方法结束
};  // Solution 类定义结束
