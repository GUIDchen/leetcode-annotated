// 题目：835. 图像重叠（Image Overlap）
// 思路：枚举 img1 与 img2 中所有为 1 的格子，用它们的坐标差作为平移向量，同一向量出现多少次就代表该平移下有多少个 1 重合，取最大值即可。
// 时间复杂度：O(n^4)，四重循环枚举 img1 的 1 与 img2 的 1 的所有配对；空间复杂度：O(n^2)，哈希表最多记录 O(n^2) 个不同平移向量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {  // img1、img2 都是 n×n 的 0/1 矩阵，允许任意平移后求最多重合的 1 的个数
        int n = img1.size();  // 图像边长
        map<pair<int, int>, int> cnt;  // 键是平移向量 (dx,dy)，值是该平移下重合的 1 的个数
        int ans = 0;  // 记录历史最大重合数
        for (int i = 0; i < n; ++i) {  // 枚举 img1 中值为 1 的格子的行下标
            for (int j = 0; j < n; ++j) {  // 枚举 img1 中值为 1 的格子的列下标
                if (img1[i][j]) {  // 只有值为 1 的格子才可能贡献重叠
                    for (int h = 0; h < n; ++h) {  // 枚举 img2 中值为 1 的格子的行下标
                        for (int k = 0; k < n; ++k) {  // 枚举 img2 中值为 1 的格子的列下标
                            if (img2[h][k]) {  // img2 的 1 才有配对价值
                                ans = max(ans, ++cnt[{i - h, j - k}]);  // 同一个平移向量计数加一，并顺手更新最大值
                            }  // img2 的列循环结束
                        }  // img2 的行循环结束
                    }  // img1 的列循环结束
                }  // if 结束
            }  // img1 的行循环结束
        }  // 外层 img1 行循环结束
        return ans;  // 返回最大重叠的 1 的个数
    }  // 方法结束
};