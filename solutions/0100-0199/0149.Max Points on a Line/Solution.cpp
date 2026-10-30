// 题目：149. 直线上最多的点数（Max Points on a Line）
// 思路：枚举两个点确定一条直线，再用叉积判断其余点是否共线；叉积两式相等说明三点共线。
// 时间复杂度：O(n^3)，三重循环枚举点对与第三点；空间复杂度：O(1)，只用常数个变量。
class Solution {  // 题目要求的题解类
public:  // 对外提供 maxPoints 方法
    int maxPoints(vector<vector<int>>& points) {  // points 是二维坐标点集，返回落在同一直线上的最多点数
        int n = points.size();  // 点的总个数
        int ans = 1;  // 至少有一个点时，答案至少为 1
        for (int i = 0; i < n; ++i) {  // 枚举直线上的第一个点
            int x1 = points[i][0], y1 = points[i][1];  // 取出第 i 个点的坐标
            for (int j = i + 1; j < n; ++j) {  // 枚举第二个点：两个不同点唯一确定一条直线
                int x2 = points[j][0], y2 = points[j][1];  // 取出第 j 个点的坐标
                int cnt = 2;  // 这条直线目前至少包含 i、j 这两个点
                for (int k = j + 1; k < n; ++k) {  // 再枚举其后的点，检查它们是否也在这条直线上
                    int x3 = points[k][0], y3 = points[k][1];  // 取出第 k 个点的坐标
                    int a = (y2 - y1) * (x3 - x1);  // 叉积的第一项 (y2-y1)*(x3-x1)
                    int b = (y3 - y1) * (x2 - x1);  // 叉积的第二项 (y3-y1)*(x2-x1)，两项相等即三点共线
                    cnt += a == b;  // 共线则把这条直线的计数加一（bool 值为 1/0）
                }  // 第三个点枚举结束
                ans = max(ans, cnt);  // 用这条直线上的点数更新答案
            }  // 第二个点枚举结束
        }  // 第一个点枚举结束
        return ans;  // 返回最多的共线点数
    }  // maxPoints 方法结束
};  // Solution 类定义结束