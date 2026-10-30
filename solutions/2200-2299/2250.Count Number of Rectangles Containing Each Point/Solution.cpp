// 题目：2250. 统计包含每个点的矩形数目（Count Number of Rectangles Containing Each Point）
// 思路：矩形左下角在原点，按高度 y 分桶存放宽度 x 并排序；查询点 (x, y) 时，对所有高度 ≥ y 的桶二分出宽度 ≥ x 的个数并累加。
// 时间复杂度：O(R log R + 101·P·log R)，R 为矩形数、P 为点数；空间复杂度：O(R)，桶里存所有矩形的宽度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {  // rectangles 每项是 [宽, 高]；points 每项是 [x, y]，返回每个点被多少个矩形包含
        int n = 101;  // 高度 y 的最大值是 100，所以用 101 个桶覆盖 0..100
        vector<vector<int>> d(n);  // d[h]：所有高度恰为 h 的矩形的宽度列表
        for (auto& r : rectangles) d[r[1]].push_back(r[0]);  // 按高度 r[1] 把宽度 r[0] 放进对应的桶
        for (auto& v : d) sort(v.begin(), v.end());  // 每个桶内按宽度升序排序，便于之后二分
        vector<int> ans;  // ans：每个查询点的答案，顺序与 points 一致
        for (auto& p : points) {  // 依次处理每个询问点
            int x = p[0], y = p[1];  // 取出当前查询点的横、纵坐标
            int cnt = 0;  // cnt：包含当前点的矩形个数
            for (int h = y; h < n; ++h) {  // 矩形高度必须 ≥ 点的高度，才能把点包住，故从 y 枚举到 100
                auto& xs = d[h];  // 取出所有高度为 h 的矩形的宽度集合
                cnt += xs.size() - (lower_bound(xs.begin(), xs.end(), x) - xs.begin());  // 宽度 ≥ x 的个数 = 总数 − 第一个 ≥ x 元素的下标
            }  // 结束高度枚举
            ans.push_back(cnt);  // 记录当前点的答案
        }  // 结束点遍历
        return ans;  // 按查询顺序返回每个点被包含的矩形数
    }  // 结束题解方法
};  // 结束题解类