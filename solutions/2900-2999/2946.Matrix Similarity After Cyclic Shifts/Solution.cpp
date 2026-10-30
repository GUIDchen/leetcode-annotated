// 题目：2946. 循环移位后的矩阵相似检查（Matrix Similarity After Cyclic Shifts）
// 思路：奇数行左移 k 位、偶数行右移 k 位后仍要与原矩阵相同，等价于每行的元素沿移位方向每隔 k 个位置循环相等；于是逐格比对即可。
// 时间复杂度：O(m·n)，每个格子只检查一次；空间复杂度：O(1)，只用了几个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool areSimilar(vector<vector<int>>& mat, int k) {  // mat 是待检查的矩阵，k 是右移/左移的步数
        int m = mat.size(), n = mat[0].size();  // m 为行数，n 为列数
        k %= n;  // 移位 k 位与移位 k % n 位效果相同，先取模避免无效计算
        for (int i = 0; i < m; ++i) {  // 逐行处理
            for (int j = 0; j < n; ++j) {  // 逐列检查当前行移位后是否与原来一致
                if (i % 2 == 1 && mat[i][j] != mat[i][(j + k) % n]) {  // 奇数行左移 k 位：移位后位置 j 上的值来自原位置 j + k
                    return false;  // 一旦发现不等，矩阵不相似
                }
                if (i % 2 == 0 && mat[i][j] != mat[i][(j - k + n) % n]) {  // 偶数行右移 k 位：移位后位置 j 上的值来自原位置 j - k
                    return false;  // 出现不一致即可提前返回
                }
            }
        }
        return true;  // 所有位置都匹配，矩阵相似
    }
};