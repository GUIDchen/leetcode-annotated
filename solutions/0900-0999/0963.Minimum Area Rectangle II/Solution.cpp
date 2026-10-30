// 题目：963. 最小面积矩形 II（Minimum Area Rectangle II）
// 思路：枚举直角顶点与两条邻边，用平行四边形公式算出第四个顶点，若它在点集中且两邻边垂直，就用两边长乘积更新最小面积。
// 时间复杂度：O(n^3)，三重枚举顶点；空间复杂度：O(n)，哈希集合保存全部点的编码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double minAreaFreeRect(vector<vector<int>>& points) {  // points 是平面上所有点，返回最小矩形面积（不存在则返回 0）
        auto f = [](int x, int y) {  // 哈希函数：坐标上限 40000，乘 40001 再相加可把 (x, y) 无冲突地压成一个整数
            return x * 40001 + y;  // 返回点 (x, y) 的编码
        };  // lambda 定义结束
        int n = points.size();  // 点的个数
        unordered_set<int> s;  // 集合：保存所有出现过的点，便于 O(1) 判断第四点是否存在
        for (auto& p : points) {  // 把每个点编码后插入集合
            s.insert(f(p[0], p[1]));  // 插入点 p 的编码
        }  // 建表循环结束
        double ans = 1e20;  // ans 记录最小面积，先用一个足够大的值表示「还没找到」
        for (int i = 0; i < n; ++i) {  // 枚举矩形的第一个顶点 i（作为直角顶点）
            int x1 = points[i][0], y1 = points[i][1];  // 直角顶点的坐标
            for (int j = 0; j < n; ++j) {  // 枚举与 i 相邻的第二个顶点 j
                if (j != i) {  // 跳过与 i 相同的点
                    int x2 = points[j][0], y2 = points[j][1];  // 第二个顶点的坐标
                    for (int k = j + 1; k < n; ++k) {  // 枚举与 i 相邻的第三个顶点 k，从 j+1 开始减少重复枚举
                        if (k != i) {  // 跳过与 i 相同的点
                            int x3 = points[k][0], y3 = points[k][1];  // 第三个顶点的坐标
                            int x4 = x2 - x1 + x3, y4 = y2 - y1 + y3;  // 平行四边形法则：以 i 为直角顶点时，第四点 = 点 j + 点 k - 点 i
                            if (x4 >= 0 && x4 <= 40000 && y4 >= 0 && y4 <= 40000 && s.count(f(x4, y4))) {  // 第四点必须在坐标范围内，并且确实存在于点集中，才可能构成矩形
                                if ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) == 0) {  // 两条邻边方向向量的点积为 0，说明互相垂直，此时三点加第四点构成矩形
                                    long long ww = (long long) (x2 - x1) * (x2 - x1) + (long long) (y2 - y1) * (y2 - y1);  // 邻边一的长度平方（转 long long 防止相乘溢出 int）
                                    long long hh = (long long) (x3 - x1) * (x3 - x1) + (long long) (y3 - y1) * (y3 - y1);  // 邻边二的长度平方
                                    ans = min(ans, sqrt(ww * hh));  // 矩形面积 = 两邻边长度之积 = sqrt(ww * hh)，更新最小值
                                }  // 垂直判断结束
                            }  // 第四点存在性判断结束
                        }  // k != i 判断结束
                    }  // 第三重循环结束
                }  // j != i 判断结束
            }  // 第二重循环结束
        }  // 第一重循环结束
        return ans == 1e20 ? 0 : ans;  // ans 仍是初值说明不存在矩形，按题意返回 0，否则返回最小面积
    }  // 方法结束
};  // 题解类结束