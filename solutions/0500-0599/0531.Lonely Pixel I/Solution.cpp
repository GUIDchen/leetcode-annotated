// 题目：531. 孤独像素 I（Lonely Pixel I）
// 思路：两遍扫描。第一遍统计每行、每列的黑色像素数；第二遍只统计行列计数都恰好为 1 的黑色像素。
// 时间复杂度：O(m*n)，两次遍历整个矩阵；空间复杂度：O(m+n)，存放行、列的黑色计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int findLonelyPixel(vector<vector<char>>& picture) {  // picture 是 'B'/'W' 组成的矩阵
        int m = picture.size(), n = picture[0].size();  // m 行 n 列
        vector<int> rows(m);  // rows[i] 记录第 i 行的黑色像素个数，默认初始化为 0
        vector<int> cols(n);  // cols[j] 记录第 j 列的黑色像素个数，默认初始化为 0
        for (int i = 0; i < m; ++i) {  // 第一遍：逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (picture[i][j] == 'B') {  // 遇到黑色像素
                    ++rows[i];  // 所在行的黑像素计数加一
                    ++cols[j];  // 所在列的黑像素计数加一
                }
            }
        }
        int ans = 0;  // 孤独像素的个数
        for (int i = 0; i < m; ++i) {  // 第二遍：重新逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (picture[i][j] == 'B' && rows[i] == 1 && cols[j] == 1) {  // 自身是黑，且所在行、列都只有它这一个黑
                    ++ans;  // 这就是一个孤独像素
                }
            }
        }
        return ans;  // 返回孤独像素总数
    }
};