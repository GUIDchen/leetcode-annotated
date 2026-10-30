// 题目：2768. 黑格子的数目（Number of Black Blocks）
// 思路：一个黑格子只可能影响它作为四个角的 4 个 2×2 块，用哈希表统计每个块的黑格数，再让块总数减去被占用的块数得到全白块数。
// 时间复杂度：O(k)，k 为黑格子个数；空间复杂度：O(k)，哈希表最多记录 4k 个块。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {  // m 行 n 列的网格；coordinates 是黑格子的坐标列表
        unordered_map<long long, int> cnt;  // 键是「2×2 块左上角」的压缩编码，值是该块内的黑格子数
        int dirs[5] = {0, 0, -1, -1, 0};  // 环形偏移数组：相邻两项拼出 (0,0)、(0,-1)、(-1,-1)、(-1,0) 四个块的左上角偏移
        for (auto& e : coordinates) {  // 遍历每一个黑格子
            int x = e[0], y = e[1];  // 当前黑格子的行号与列号
            for (int k = 0; k < 4; ++k) {  // 枚举这个黑格子可能作为其右下/右上/左下/左上角的 4 个块
                int i = x + dirs[k], j = y + dirs[k + 1];  // 对应的块左上角坐标
                if (i >= 0 && i < m - 1 && j >= 0 && j < n - 1) {  // 左上角合法，说明这个 2×2 块完全落在网格内
                    ++cnt[1LL * i * n + j];  // 把二维坐标压成一个 long long 键，并给该块的黑格计数加一
                }  // 边界判断结束
            }  // 4 个候选块枚举结束
        }  // 黑格子遍历结束
        vector<long long> ans(5);  // ans[c] 表示黑格子数恰好为 c 的块数，c 最大是 4
        ans[0] = (m - 1LL) * (n - 1);  // 块总数先全部算作「黑格数为 0」
        for (auto& [_, x] : cnt) {  // 遍历所有至少含一个黑格子的块
            ++ans[x];  // 黑格数为 x 的块数加一
            --ans[0];  // 这个块不再是全白块，从 ans[0] 中扣除
        }  // 统计结束
        return ans;  // 返回长度为 5 的结果数组
    }  // 方法结束
};  // 类定义结束