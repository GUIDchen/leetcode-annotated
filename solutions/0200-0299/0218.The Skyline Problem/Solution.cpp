// 题目：218. 天际线问题（The Skyline Problem）
// 核心思路：把所有楼的左右端点作为扫描线位置从左到右扫描，用大顶堆维护当前覆盖的最高楼；堆顶高度变化处即为关键点。
// 时间复杂度：O(n log n)，排序与每个楼入堆出堆各一次；空间复杂度：O(n)，端点数组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {  // 输入 [左端, 右端, 高度] 的楼群，返回天际线的关键点集合
        vector<int> lines;  // 收集所有楼的左右端点横坐标，作为扫描线的候选位置
        for (auto& v : buildings) {  // 遍历每栋楼
            lines.push_back(v[0]);  // 记录左端点
            lines.push_back(v[1]);  // 记录右端点
        }  // 循环结束
        sort(lines.begin(), lines.end());  // 端点升序排序，得到扫描线从左到右的推进顺序
        priority_queue<pair<int, int>> pq;  // 大顶堆：pair 先按高度比较，堆顶是当前覆盖的最高楼
        vector<vector<int>> skys;  // 天际线关键点结果
        int city = 0, n = buildings.size();  // city：下一栋待入堆的楼下标；n：楼的总数
        for (int line : lines) {  // 按横坐标从小到大依次扫描每个端点
            while (city < n && buildings[city][0] <= line && buildings[city][1] > line) {  // 把左端点已到、且右端点仍严格大于当前横坐标的楼依次入堆
                pq.emplace(buildings[city][2], buildings[city][1]);  // 压入 (高度, 右端点)，堆按高度取最大
                ++city;  // 处理下一栋楼
            }  // while 结束
            while (!pq.empty() && pq.top().second <= line) {  // 堆顶那栋楼已在当前横坐标处或之前结束，弹出失效的最高楼
                pq.pop();  // 弹出过期元素
            }  // while 结束
            int high = pq.empty() ? 0 : pq.top().first;  // 当前扫描线上的最大高度；没有楼覆盖时为 0
            if (!skys.empty() && skys.back()[1] == high) {  // 高度与上一个关键点相同，说明这里不产生新轮廓
                continue;  // 跳过，不记录这个点
            }  // if 结束
            skys.push_back({line, high});  // 记录关键点 (横坐标, 当前最大高度)
        }  // for 结束
        return skys;  // 返回天际线关键点
    }  // 方法结束
};  // 类定义结束
