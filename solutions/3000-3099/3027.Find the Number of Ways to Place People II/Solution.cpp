// 题目：3027. 人员站位的方案数 II（Find the Number of Ways to Place People II）
// 核心思路：与 I 同一套做法——按 x 升序、x 相同时按 y 降序排序，枚举左上角 i 后向右扫描 j 并维护已遇到的最大纵坐标 maxY；只有 maxY < y2 ≤ y1 时才说明矩形内没有第三人，方案数 +1，避免 O(n^3) 地检查矩形内部。
// 时间复杂度：O(n^2)，n ≤ 1000 时可接受；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfPairs(vector<vector<int>>& points) {  // points：所有点坐标 [x, y]；返回合法的站位方案数
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {  // 自定义排序：x 升序，x 相同时 y 降序
            return a[0] < b[0] || (a[0] == b[0] && b[1] < a[1]);  // 满足该条件时 a 排在 b 前面
        });
        int n = points.size();  // n：点的个数
        int ans = 0;  // ans：累计的合法方案数
        for (int i = 0; i < n; ++i) {  // 枚举矩形的左上角 i（x 较小的那个点）
            int y1 = points[i][1];  // y1：左上角的纵坐标，是纵向下界的上限
            int maxY = INT_MIN;  // maxY：i 之后已扫描点的最大纵坐标，用来排除矩形内部的点
            for (int j = i + 1; j < n; ++j) {  // 枚举矩形右下角 j，排序保证 j 的 x 不小于 i
                int y2 = points[j][1];  // y2：候选右下角的纵坐标
                if (maxY < y2 && y2 <= y1) {  // y2 落在 (maxY, y1] 内，说明这个矩形内部没有其它点
                    maxY = y2;  // 更新已遇到的最大纵坐标，以后更低的点都会被它挡住
                    ++ans;  // 找到一种合法站位方案
                }
            }
        }
        return ans;  // 返回方案总数
    }
};