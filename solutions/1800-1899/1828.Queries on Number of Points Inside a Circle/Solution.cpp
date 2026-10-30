// 题目：1828. 统计一个圆中点的数目（Queries on Number of Points Inside a Circle）
// 思路：每个查询枚举所有点，用平方距离与半径平方比较，避免开方带来的精度问题。
// 时间复杂度：O(q * p)；空间复杂度：O(q)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {  // points：点集；queries：每个查询形如 [圆心x, 圆心y, 半径r]；返回每个查询的点数
        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 逐个查询处理
            int x = q[0], y = q[1], r = q[2];  // 取出圆心坐标与半径
            int cnt = 0;  // 当前查询命中点数
            for (auto& p : points) {  // 枚举所有点
                int i = p[0], j = p[1];  // 取出该点的横纵坐标
                int dx = i - x, dy = j - y;  // 点与圆心的坐标差
                cnt += dx * dx + dy * dy <= r * r;  // 平方距离不超过半径平方即计入（布尔值直接累加）
            }  // 点集遍历结束
            ans.emplace_back(cnt);  // 记录该查询的答案
        }  // 查询遍历结束
        return ans;  // 返回所有查询的答案
    }  // 方法结束
};  // 类定义结束