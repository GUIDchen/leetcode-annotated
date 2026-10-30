// 题目：2015. 每段建筑物的平均高度（Average Height of Buildings in Each Segment）
// 思路：差分思想，cnt 记录各坐标处建筑数量的变化量、d 记录高度和的变化量；按坐标升序扫描，只要当前覆盖数大于 0 就产出一段「起点、终点、平均高度」，并与前一段合并。
// 时间复杂度：O(n log n)，n 为建筑数（有序 map 的扫描代价）；空间复杂度：O(n)，两张端点表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& buildings) {  // buildings：每栋建筑的 [起点, 终点, 高度]；返回合并后的 [起点, 终点, 平均高度] 列表
        unordered_map<int, int> cnt;  // cnt[x] 记录坐标 x 处建筑物数量的变化量（差分）
        map<int, int> d;  // d[x] 记录坐标 x 处高度总和的变化量，用有序 map 以便按坐标从小到大扫描

        for (const auto& e : buildings) {  // 遍历每栋建筑，在两端打差分标记
            int start = e[0], end = e[1], height = e[2];  // 拆出起点、终点、高度
            cnt[start]++;  // 起点处建筑数量 +1
            cnt[end]--;  // 终点处建筑数量 -1
            d[start] += height;  // 起点处高度和加上该建筑高度
            d[end] -= height;  // 终点处高度和减去该建筑高度
        }  // 差分标记结束

        int s = 0, m = 0;  // s 是当前区间的总高度，m 是当前区间的建筑数量
        int last = -1;  // last 记录上一段的起点坐标
        vector<vector<int>> ans;  // ans 保存合并后的结果段

        for (const auto& [k, v] : d) {  // 按坐标升序扫描所有端点（结构化绑定取出坐标 k 与高度变化 v）
            if (m > 0) {  // 上一段有建筑覆盖时才可能产出结果段 [last, k]
                int avg = s / m;  // 该段的平均高度，题目保证能整除
                if (!ans.empty() && ans.back()[2] == avg && ans.back()[1] == last) {  // 与上一段平均高度相同且首尾相接，可以合并
                    ans.back()[1] = k;  // 延长上一段的右端点
                } else {  // 否则需要新开一段
                    ans.push_back({last, k, avg});  // 把 [last, k] 这一段及其平均高度加入答案
                }  // 合并/新开分支结束
            }  // 产出判断结束
            s += v;  // 把当前坐标的高度变化计入总高度
            m += cnt[k];  // 把当前坐标的建筑数量变化计入覆盖数
            last = k;  // 当前坐标成为下一段的起点
        }  // 端点扫描结束

        return ans;  // 返回所有结果段
    }  // 方法结束
};  // 类定义结束
