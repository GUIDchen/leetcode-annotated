// 题目：3030. 找出网格的区域平均强度（Find the Grid of Region Average）
// 思路：枚举每个 3×3 子网格，先检查所有相邻格子的差是否都不超过阈值；合法就用整数除法求平均，累加到这 9 个格子上并记录覆盖次数，最后按覆盖次数求平均。
// 时间复杂度：O(n * m)，每个 3×3 区域是常数次检查与累加；空间复杂度：O(n * m)，需要 ans 与 ct 两个矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {  // image：原始网格；threshold：相邻格子允许的最大差值
        int n = image.size(), m = image[0].size();  // n：行数；m：列数
        vector<vector<int>> ans(n, vector<int>(m));  // ans：每个格子被覆盖的区域平均强度之和
        vector<vector<int>> ct(n, vector<int>(m));  // ct：每个格子被多少个合法区域覆盖
        for (int i = 0; i + 2 < n; ++i) {  // 枚举 3×3 区域左上角行号，i + 2 < n 保证不越界
            for (int j = 0; j + 2 < m; ++j) {  // 枚举 3×3 区域左上角列号，j + 2 < m 保证不越界
                bool region = true;  // 先假设这个 3×3 区域是合法的
                for (int k = 0; k < 3; ++k) {  // 逐行检查水平方向的相邻格子
                    for (int l = 0; l < 2; ++l) {  // 每行有 2 对水平相邻格子
                        region &= abs(image[i + k][j + l] - image[i + k][j + l + 1]) <= threshold;  // 有一对差值超阈值就把区域标记为非法
                    }
                }
                for (int k = 0; k < 2; ++k) {  // 逐行检查竖直方向的相邻格子，只需前 2 行
                    for (int l = 0; l < 3; ++l) {  // 每对竖直相邻格子按列遍历
                        region &= abs(image[i + k][j + l] - image[i + k + 1][j + l]) <= threshold;  // 竖直差值超阈值同样令区域非法
                    }
                }
                if (region) {  // 只有完全合法的区域才参与平均强度统计
                    int tot = 0;  // tot：该 3×3 区域的元素总和
                    for (int k = 0; k < 3; ++k) {  // 遍历区域内的行
                        for (int l = 0; l < 3; ++l) {  // 遍历区域内的列
                            tot += image[i + k][j + l];  // 累加区域内的元素
                        }
                    }
                    for (int k = 0; k < 3; ++k) {  // 再遍历一次区域内各行，把平均值分发到每个格子
                        for (int l = 0; l < 3; ++l) {  // 遍历区域内各列
                            ct[i + k][j + l]++;  // 该格子被一个合法区域覆盖，计数加一
                            ans[i + k][j + l] += tot / 9;  // 按题目要求先用整数除法求区域平均，再累加
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {  // 整理最终结果：逐行
            for (int j = 0; j < m; ++j) {  // 逐列
                if (ct[i][j] == 0) {  // 没有被任何合法区域覆盖
                    ans[i][j] = image[i][j];  // 保留原始强度
                } else {  // 至少被一个合法区域覆盖
                    ans[i][j] /= ct[i][j];  // 平均强度之和除以覆盖次数，得到最终平均强度
                }
            }
        }
        return ans;  // 返回处理后的网格
    }
};
