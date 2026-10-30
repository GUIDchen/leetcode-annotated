// 题目：2643. 一最多的行（Row With Maximum Ones）
// 思路：逐行用 accumulate 统计 1 的个数，只有严格更大时才更新答案，因此并列时天然保留更小的行下标。
// 时间复杂度：O(m * n)，每个格子看一次；空间复杂度：O(1)，只保存行下标与 1 的个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {  // mat：只含 0/1 的 m 行 n 列矩阵
        vector<int> ans(2);  // 答案格式为 [行下标, 该行 1 的个数]，初值 [0, 0]
        for (int i = 0; i < mat.size(); ++i) {  // 逐行扫描
            int cnt = accumulate(mat[i].begin(), mat[i].end(), 0);  // 把本行元素求和，得到 1 的个数
            if (ans[1] < cnt) {  // 只有严格更大才更新，保证并列时保留最小行号
                ans = {i, cnt};  // 记录当前最优的行下标与个数
            }
        }
        return ans;  // 返回 [行下标, 1 的个数]
    }
};
