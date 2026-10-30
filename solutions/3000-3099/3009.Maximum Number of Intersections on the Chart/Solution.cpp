// 题目：3009. 折线图上的最大交点数量（Maximum Number of Intersections on the Chart）
// 核心思路：把每条线段覆盖的 y 坐标区间映射到 2 倍坐标上（消去半单位），用差分表记录区间增减，再按坐标扫描取最大重叠层数。
// 时间复杂度：O(n log n)，差分表按坐标有序；空间复杂度：O(n)，差分表最多 2n 个键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIntersectionCount(vector<int>& y) {  // y：折线在 x = 0..n-1 处的 y 坐标
        int n = y.size();  // 折线的点数
        map<int, int> line;  // 差分表：key 是坐标，value 是该坐标处覆盖层数的增量
        for (int i = 1; i < n; ++i) {  // 逐段考察折线的每条边（共 n-1 段）
            int start = 2 * y[i - 1];  // 起点坐标乘 2，避免后半段的中点出现小数
            int end = 2 * y[i] + (i == n - 1 ? 0 : (y[i] > y[i - 1] ? -1 : 1));  // 终点坐标：最后一段不再外延，其余段按上升/下降偏半个单位（乘 2 后即 ±1）
            ++line[min(start, end)];  // 差分：区间左端点覆盖层数加一
            --line[max(start, end) + 1];  // 差分：区间右端点之后覆盖层数减一
        }  // 差分表构建结束
        int ans = 0, intersection = 0;  // ans 记录最大交点个数，intersection 是当前坐标处的重叠线段数
        for (auto& [_, count] : line) {  // 按坐标从小到大扫描差分表
            intersection += count;  // 累加差分增量，得到当前坐标处覆盖的线段数
            ans = max(ans, intersection);  // 用当前覆盖数更新最大值
        }  // 扫描结束
        return ans;  // 返回折线图上的最大交点数量
    }  // 方法结束
};  // 类定义结束
