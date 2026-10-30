// 题目：939. 最小面积矩形（Minimum Area Rectangle）
// 思路：按 x 分组收集同列的 y，枚举同一列内的纵向边对 (y1, y2)，用哈希表记录该边对上次出现的 x，不同 x 上的同一对 y 就能围成矩形。
// 时间复杂度：O(n²)，最坏每列枚举所有 y 对；空间复杂度：O(n)，存分组与边对哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minAreaRect(vector<vector<int>>& points) {  // points 是点集，返回最小矩形面积，找不到合法矩形时返回 0
        map<int, vector<int>> d;  // 按 x 升序分组：键是横坐标，值是该列上所有 y 坐标
        for (auto& p : points) {  // 遍历每一个点
            int x = p[0], y = p[1];  // 拆出该点的横坐标与纵坐标
            d[x].emplace_back(y);  // 把 y 归到它所属的那一列里
        }
        unordered_map<int, int> pos;  // 哈希表：编码后的纵向边对 → 最近一次出现该边对的 x
        int ans = 1 << 30;  // 答案初值取足够大的数（这里相当于无穷大）
        for (auto& [x, ys] : d) {  // 按 x 从小到大处理每一列，后处理的列一定更靠右
            sort(ys.begin(), ys.end());  // 同列的 y 排序，保证枚举时恒有 y1 < y2
            int n = ys.size();  // 该列上共有多少个点
            for (int i = 0; i < n; ++i) {  // 枚举纵向边对的下端点 y1
                int y1 = ys[i];  // 边对的下端点纵坐标
                for (int j = i + 1; j < n; ++j) {  // 枚举边对的上端点 y2，从 i+1 开始保证 y1 < y2 且不重复
                    int y2 = ys[j];  // 边对的上端点纵坐标
                    int p = y1 * 40001 + y2;  // 把 (y1, y2) 编码成一个整数当哈希键，乘 40001 是因为 y 坐标不超过 40000
                    if (pos.count(p)) {  // 之前某一列也出现过同一对 y，说明四个点能围成矩形
                        ans = min(ans, (x - pos[p]) * (y2 - y1));  // 面积 = 宽(x 差) × 高(y 差)，更新最小值
                    }
                    pos[p] = x;  // 记录该边对最新出现的 x，列按升序处理所以宽最小
                }
            }
        }
        return ans == 1 << 30 ? 0 : ans;  // 一次都没围成过矩形就返回 0
    }
};  // 类定义结束