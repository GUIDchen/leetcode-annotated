// 题目：1499. 满足不等式的最大值（Max Value of Equation）
// 思路：把 y_i + y_j + |x_i - x_j| 改写成 (x+y) + (y'-x')，用大根堆维护窗口内 y'-x' 最大的点，距离超过 k 就弹出。
// 时间复杂度：O(n log n)，每个点进出堆各一次；空间复杂度：O(n)，堆最多存 n 个点。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {  // 在满足 |x_i - x_j| <= k 的点对中，最大化 y_i + y_j + |x_i - x_j|
        int ans = -(1 << 30);  // 答案初始化为极小值（题目保证至少存在一对）
        priority_queue<pair<int, int>> pq;  // 大根堆，存 (y - x, x)，堆顶是 y-x 最大的点
        for (auto& p : points) {  // 按 x 升序处理每个点
            int x = p[0], y = p[1];  // 取出当前点的坐标
            while (pq.size() && x - pq.top().second > k) {  // 堆顶点的 x 与当前 x 距离超过 k，已经失效
                pq.pop();  // 弹出失效点
            }  // while 结束
            if (pq.size()) {  // 堆里还有合法点，就可以和当前点组成点对
                ans = max(ans, x + y + pq.top().first);  // 化简后为 (x+y) + (y'-x')，堆顶给出最大的 y'-x'
            }  // if 结束
            pq.emplace(y - x, x);  // 把当前点作为后续点的候选项压入堆
        }  // for 结束
        return ans;  // 返回最大值
    }  // 方法结束
};  // 类定义结束