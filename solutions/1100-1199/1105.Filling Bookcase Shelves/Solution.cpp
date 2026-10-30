// 题目：1105. 填充书架（Filling Bookcase Shelves）
// 思路：动态规划，f[i] 表示摆好前 i 本书的最小总高度；倒序枚举最后一层的起始书 j，在宽度允许的范围内用层内最高书更新答案。
// 时间复杂度：O(n^2)，两层循环最坏各 n 次；空间复杂度：O(n)，f 数组保存 n+1 个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题接口
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {  // books 每项是 {厚度, 高度}，shelfWidth 是书架宽度上限
        int n = books.size();  // 书本总数
        int f[n + 1];  // f[i]：前 i 本书摆放后的最小总高度（变长数组，长度由入参 n 决定）
        f[0] = 0;  // 边界：一本书都没有时总高度为 0
        for (int i = 1; i <= n; ++i) {  // 逐渐扩大规模，依次求出前 i 本书的最优值
            int w = books[i - 1][0], h = books[i - 1][1];  // 先让第 i 本书独占最后一层：w 是层宽，h 是层高
            f[i] = f[i - 1] + h;  // 初始方案：前 i-1 本的最优解再加上这一层的高度
            for (int j = i - 1; j > 0; --j) {  // 倒序把第 j 本书也并入最后一层，枚举最后一层的起点
                w += books[j - 1][0];  // 把第 j 本书的厚度累加进当前层宽
                if (w > shelfWidth) {  // 层宽超过书架宽度，再往前放只会更宽
                    break;  // 宽度是单调递增的，可以立刻停止内层枚举
                }
                h = max(h, books[j - 1][1]);  // 同一层的高度由层内最高的那本书决定
                f[i] = min(f[i], f[j - 1] + h);  // 用「前 j-1 本的最优高度 + 当前层高度」尝试更新 f[i]
            }
        }
        return f[n];  // 前 n 本书的最小总高度就是答案
    }
};