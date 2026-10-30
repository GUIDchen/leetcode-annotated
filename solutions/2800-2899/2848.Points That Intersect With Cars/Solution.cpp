// 题目：2848. 与车相交的点（Points That Intersect With Cars）
// 思路：对每个区间做差分标记 +1 与 -1，再求前缀和；前缀和大于 0 的位置就是被至少一辆车覆盖的点。
// 时间复杂度：O(n + 100)，一次差分遍历加一次扫描；空间复杂度：O(100)，固定大小的差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfPoints(vector<vector<int>>& nums) {  // nums：若干区间 [start, end]，统计被至少一个区间覆盖的整数点个数
        int d[102]{};  // 差分数组，多开 2 位以容纳 end + 1 与下标 0..101
        for (const auto& e : nums) {  // 遍历每个区间做差分标记
            int start = e[0], end = e[1];  // 取出区间的左右端点
            ++d[start];  // 区间起点处覆盖数 +1
            --d[end + 1];  // 区间终点的下一位覆盖数 -1，前缀和时覆盖自动结束
        }
        int ans = 0, s = 0;  // ans 统计被覆盖的点数，s 维护当前覆盖数
        for (int x : d) {  // 从左到右扫描整个差分数组
            s += x;  // 累加差分得到当前位置的覆盖数
            ans += s > 0;  // 覆盖数大于 0 说明该点被至少一辆车覆盖，计入答案
        }
        return ans;  // 返回被覆盖的整数点总数
    }
};
