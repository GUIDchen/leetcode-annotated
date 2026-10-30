// 题目：956. 最高的广告牌（Tallest Billboard）
// 思路：记忆化搜索，状态为「处理到第几根钢筋」与「两柱高度差」；每根钢筋有不用、放到较高一侧、放到较矮一侧三种选择。
// 时间复杂度：O(n·s)，n 为钢筋根数、s 为钢筋总长（状态数 n×(s+1)）；空间复杂度：O(n·s)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int tallestBillboard(vector<int>& rods) {  // rods：每根钢筋的长度，返回两根柱子的最大公共高度
        int s = accumulate(rods.begin(), rods.end(), 0);  // s：所有钢筋长度之和，也是两柱高度差的上界
        int n = rods.size();  // n：钢筋的根数
        int f[n][s + 1];  // f[i][j]：处理完前 i 根、两柱高度差为 j 时，还能取得的公共高度（-1 表示未计算）
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，作为「这个状态还没算过」的标记
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 记忆化搜索函数：i 是当前钢筋下标，j 是左柱比右柱高出的量（可为负，用 abs 处理）
            if (i >= n) {  // 递归出口：所有钢筋都处理完了
                return j == 0 ? 0 : -(1 << 30);  // 差为 0 说明两柱等高，合法并贡献 0；否则该状态无效，返回极小值
            }
            if (f[i][j] != -1) {  // 这个状态算过了，直接取缓存
                return f[i][j];  // 返回缓存值，避免重复搜索
            }
            int ans = max(dfs(i + 1, j), dfs(i + 1, j + rods[i]));  // 方案一：这根钢筋不用；方案二：放到较高的一侧（差值变大、公共高度不变）
            ans = max(ans, dfs(i + 1, abs(j - rods[i])) + min(j, rods[i]));  // 方案三：放到较矮的一侧，新差值为 |j - rods[i]|，公共高度增加 min(j, rods[i])（矮的一侧被补齐）
            return f[i][j] = ans;  // 先写入缓存再返回，这是记忆化的关键
        };  // lambda 定义结束
        return dfs(0, 0);  // 从第 0 根钢筋、高度差 0 开始搜索，返回值就是两柱最终的最大公共高度
    }
};