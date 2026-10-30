// 题目：1182. 与目标颜色间的最短距离（Shortest Distance to Target Color）
// 思路：预处理两个方向表：right[i][c] 为从 i 往右第一个颜色 c 的位置，left[i][c] 为 i 左边最近颜色 c 的位置；
//       查询时两侧取更近的一侧即可，均不存在则返回 -1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {  // colors 为颜色数组，queries 每项是 [下标, 目标颜色]
        int n = colors.size();  // 数组长度
        int right[n + 1][3];  // right[i][c]：从位置 i（包含）向右第一个颜色 c 的下标
        const int inf = 1 << 30;  // 无穷大哨兵，表示该方向压根不存在目标颜色
        fill(right[n], right[n] + 3, inf);  // 边界：位置 n 之后没有元素，三种颜色都记为 inf
        for (int i = n - 1; i >= 0; --i) {  // 从右往左倒推，保证 right[i+1] 已经算好
            for (int j = 0; j < 3; ++j) {  // 枚举 3 种颜色
                right[i][j] = right[i + 1][j];  // 先整体继承右邻位置的最近目标信息
            }  // 三种颜色继承完毕
            right[i][colors[i] - 1] = i;  // 当前位置的颜色最近就是它自己，覆盖刚继承来的值
        }  // 右侧预处理完成
        int left[n + 1][3];  // left[i][c]：位置 i 左边（不含 i）最近颜色 c 的下标
        fill(left[0], left[0] + 3, -inf);  // 边界：0 号位置左边没有元素，三种颜色都记为 -inf 哨兵
        for (int i = 1; i <= n; ++i) {  // 从左往右构造，i 表示“前 i 个元素”
            for (int j = 0; j < 3; ++j) {  // 枚举 3 种颜色
                left[i][j] = left[i - 1][j];  // 先整体继承前一个位置的最近目标信息
            }  // 三种颜色继承完毕
            left[i][colors[i - 1] - 1] = i - 1;  // 前 i 个元素里最新出现的颜色就是下标 i-1 处那个
        }  // 左侧预处理完成
        vector<int> ans;  // 按查询顺序保存答案
        for (auto& q : queries) {  // 逐个查询处理
            int i = q[0], c = q[1] - 1;  // 取查询位置，并把颜色换成 0 基下标
            int d = min(i - left[i + 1][c], right[i][c] - i);  // 左边距离与右边距离取较小者，哨兵会让一侧变成巨大值
            ans.push_back(d > n ? -1 : d);  // 若距离超过 n 说明该颜色从未出现（仍带哨兵），返回 -1
        }  // 当前查询处理完毕
        return ans;  // 返回全部查询答案
    }  // 方法体结束
};  // 题解类结束