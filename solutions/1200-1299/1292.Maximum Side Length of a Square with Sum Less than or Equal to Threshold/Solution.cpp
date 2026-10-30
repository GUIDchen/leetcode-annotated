// 题目：1292. 元素和小于等于阈值的正方形的最大边长（Maximum Side Length of a Square with Sum Less than or Equal to Threshold）
// 核心思路：先用二维前缀和 O(1) 求任意子方阵的和，再对边长二分答案，用前缀和判定是否存在满足条件的方阵。
// 时间复杂度：O(m·n·log min(m,n))，二分 log 层、每层判定 O(m·n)；空间复杂度：O(m·n)，用于二维前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSideLength(vector<vector<int>>& mat, int threshold) {  // mat 是非负矩阵，求元素和 ≤ threshold 的正方形最大边长
        int m = mat.size(), n = mat[0].size();  // m、n 分别是矩阵的行数与列数
        int s[m + 1][n + 1];  // s 是二维前缀和数组，多开一行一列以省去边界判断
        memset(s, 0, sizeof(s));  // 把前缀和数组全部清零
        for (int i = 1; i <= m; ++i) {  // 枚举行下标 i（前缀和下标从 1 开始）
            for (int j = 1; j <= n; ++j) {  // 枚举列下标 j（前缀和下标从 1 开始）
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + mat[i - 1][j - 1];  // 容斥原理求 (1,1) 到 (i,j) 的矩形和：上 + 左 - 重叠的左上 + 当前格子
            }  // 结束列循环
        }  // 结束行循环
        auto check = [&](int k) {  // 局部 lambda check(k)：判断是否存在边长恰为 k、元素和 ≤ threshold 的正方形
            for (int i = 0; i < m - k + 1; ++i) {  // 枚举正方形左上角的行下标
                for (int j = 0; j < n - k + 1; ++j) {  // 枚举正方形左上角的列下标
                    if (s[i + k][j + k] - s[i][j + k] - s[i + k][j] + s[i][j] <= threshold) {  // 二维前缀和 O(1) 求正方形和：右下 - 上方 - 左侧 + 左上角
                        return true;  // 找到一个满足条件的正方形即可返回 true
                    }  // 结束 if 分支
                }  // 结束列循环
            }  // 结束行循环
            return false;  // 所有位置都不满足，返回 false
        };  // lambda 定义结束
        int l = 0, r = min(m, n);  // 二分答案的左右边界：边长最小取 0，最大不超过矩阵短边
        while (l < r) {  // 二分查找满足条件的最大边长
            int mid = (l + r + 1) >> 1;  // mid 取上中位数（+1 配合下面的 l = mid 才能避免死循环）
            if (check(mid)) {  // 边长 mid 可行，说明答案至少为 mid
                l = mid;  // 把左边界抬到 mid
            } else {  // 否则边长 mid 不可行
                r = mid - 1;  // 把右边界收缩到 mid - 1
            }  // 结束 if-else
        }  // 结束二分循环
        return l;  // l 即满足条件的最大边长
    }  // 结束函数
};  // 结束题解类