// 题目：2345. 寻找可见山的数量（Finding the Number of Visible Mountains）
// 思路：山 (x, y) 遮住山底区间 [x-y, x+y]，把区间转成 (左端点, 右端点) 后排序，右端点严格大于历史最远右端点的山才可见；顶点重复的山互相遮挡都不可见。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，存储变换后的区间数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int visibleMountains(vector<vector<int>>& peaks) {  // peaks 中每组为山峰顶点坐标 [x, y]
        vector<pair<int, int>> arr;  // 存放变换后的 (左端点 x-y, -右端点)，取负号是为了让右端点降序
        for (auto& e : peaks) {  // 逐座处理山峰
            int x = e[0], y = e[1];  // 顶点的横坐标与高度
            arr.emplace_back(x - y, -(x + y));  // 山底区间为 [x-y, x+y]；pair 默认升序排序，故把右端点取负
        }
        sort(arr.begin(), arr.end());  // 先按左端点升序，左端点相同则按右端点降序（题解的关键次序）
        int n = arr.size();  // 山的总数
        int ans = 0, cur = INT_MIN;  // ans 为可见山计数，cur 为已扫描到的最大右端点
        for (int i = 0; i < n; ++i) {  // 从左到右扫描区间
            int l = arr[i].first, r = -arr[i].second;  // 还原左端点 l 与右端点 r
            if (r <= cur) {  // 右端点没有超过历史最远右端点，说明整座山被之前的山覆盖，不可见
                continue;  // 直接跳过，也不更新 cur
            }
            cur = r;  // 更新能看到的最远右端点，作为后面山的判定基准
            ans += i == n - 1 || (i < n - 1 && arr[i] != arr[i + 1]);  // 最后一个或与下一座不完全相同：说明没有同顶点的山与它互相遮挡，才计入答案
        }
        return ans;  // 返回可见山的数量
    }
};