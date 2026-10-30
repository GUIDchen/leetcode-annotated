// 题目：2732. 找到矩阵中的好子集（Find a Good Subset of the Matrix）
// 思路：把每行压成二进制掩码，好子集只需 1 或 2 行；用哈希表按掩码去重后两两做按位与检查。
// 时间复杂度：O(m × n + k²)，k 为不同掩码的数量（≤ 2^n）；空间复杂度：O(k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {  // 返回任意一个好子集的行下标列表
        unordered_map<int, int> g;  // 哈希表：二进制掩码 → 该掩码对应的行号，相同掩码只保留最后一行
        for (int i = 0; i < grid.size(); ++i) {  // 逐行处理矩阵
            int mask = 0;  // 把当前行压缩成一个二进制掩码
            for (int j = 0; j < grid[0].size(); ++j) {  // 枚举这一行的每一列
                mask |= grid[i][j] << j;  // 第 j 列的值放到掩码的第 j 位上
            }
            if (mask == 0) {  // 全 0 行单独就构成好子集（任意两列之和都不超过 1）
                return {i};  // 直接返回只含这一行下标的好子集
            }
            g[mask] = i;  // 记录该掩码对应的行号；掩码相同的行位置等价，留一行即可
        }
        for (auto& [a, i] : g) {  // 枚举所有出现过的掩码 a 及其行号 i
            for (auto& [b, j] : g) {  // 再枚举另一个掩码 b 及其行号 j
                if ((a & b) == 0) {  // 按位与为 0 说明不存在某一列上两行同时为 1
                    return {min(i, j), max(i, j)};  // 按行号升序返回这两个下标
                }
            }
        }
        return {};  // 没有找到好子集，返回空数组
    }
};