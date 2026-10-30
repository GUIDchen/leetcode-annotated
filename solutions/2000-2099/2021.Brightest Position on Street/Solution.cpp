// 题目：2021. 街上最亮的位置（Brightest Position on Street）
// 思路：把每盏灯照亮的闭区间 [x - r, x + r] 转成差分数组，按坐标升序扫描前缀和；用严格大于更新，即可在同一亮度下保留最小的坐标。
// 时间复杂度：O(n log n)，map 的插入与遍历都是对数级；空间复杂度：O(n)，差分表最多 2n 个端点。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int brightestPosition(vector<vector<int>>& lights) {  // lights 的每项是 [位置, 光照半径]，返回最亮位置的编号
        map<int, int> d;  // 差分表：键是坐标，值是亮度变化量；map 保证按键升序遍历
        for (auto& x : lights) {  // 逐盏灯处理
            int l = x[0] - x[1], r = x[0] + x[1];  // 该灯照亮的闭区间 [l, r]
            ++d[l];  // 区间左端点亮度加一
            --d[r + 1];  // 右端点之后亮度减一，这样前缀和正好还原出区间覆盖
        }  // 灯遍历结束
        int ans = 0, s = 0, mx = 0;  // ans 记录答案坐标，s 是当前亮度，mx 是历史最大亮度
        for (auto& [i, v] : d) {  // 按坐标升序扫描所有差分端点
            s += v;  // 累加差分值得到当前位置的亮度
            if (mx < s) {  // 只有严格更亮才更新，保证同亮度时答案坐标更小
                mx = s;  // 记录新的最大亮度
                ans = i;  // 记录取得最大亮度的坐标
            }  // 更新结束
        }  // 扫描结束
        return ans;  // 返回最亮位置（同亮度时取编号最小者）
    }  // brightestPosition 方法结束
};  // Solution 类定义结束