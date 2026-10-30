// 题目：3531. 统计被覆盖的建筑（Count Covered Buildings）
// 思路：按列、按行分别收集坐标并排序。若某建筑在同一列中存在 x 更小和更大的建筑、同一行中存在 y 更小和更大的建筑，则它上下左右都有建筑，被覆盖。
// 时间复杂度：O(m log m)，m 为建筑数量（排序开销）；空间复杂度：O(m)，两个哈希表存坐标。
class Solution {  // LeetCode 约定的题解类
public:  // 判题器只调用 public 区的方法
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {  // n 为城市边长，buildings[i] = [x, y] 是互不相同的建筑坐标
        unordered_map<int, vector<int>> g1;  // g1[x] 存同一列（x 相同）所有建筑的 y 坐标
        unordered_map<int, vector<int>> g2;  // g2[y] 存同一行（y 相同）所有建筑的 x 坐标

        for (const auto& building : buildings) {  // 一次遍历收集行列信息
            int x = building[0], y = building[1];  // 当前建筑的坐标
            g1[x].push_back(y);  // 按列归入
            g2[y].push_back(x);  // 按行归入
        }  // 收集结束

        for (auto& e : g1) {  // 逐列处理
            sort(e.second.begin(), e.second.end());  // 该列的 y 坐标升序排序，便于取最小/最大值
        }  // 列排序结束
        for (auto& e : g2) {  // 逐行处理
            sort(e.second.begin(), e.second.end());  // 该行的 x 坐标升序排序
        }  // 行排序结束

        int ans = 0;  // 被覆盖的建筑数量

        for (const auto& building : buildings) {  // 逐个建筑判断是否被覆盖
            int x = building[0], y = building[1];  // 当前建筑的坐标
            const vector<int>& l1 = g1[x];  // 同一列中所有建筑的 y 列表
            const vector<int>& l2 = g2[y];  // 同一行中所有建筑的 x 列表

            if (l2[0] < x && x < l2[l2.size() - 1] && l1[0] < y && y < l1[l1.size() - 1]) {  // 同一列里有更小和更大的 y，同一行里有更小和更大的 x，即上下左右都有建筑
                ans++;  // 满足被覆盖条件，计数加一
            }  // if 结束
        }  // 遍历结束

        return ans;  // 返回被覆盖的建筑数量
    }  // 方法结束
};  // 类定义结束
