// 题目：1072. 按列翻转得到最大值等行数（Flip Columns For Maximum Number of Equal Rows）
// 思路：某两行能同时变成相同行，当且仅当它们完全相同或逐位互补；把首元素统一归一化为 0 后用哈希表统计出现最多的行模式。
// 时间复杂度：O(n · m)，逐行逐列扫一遍；空间复杂度：O(n · m)，哈希表存归一化后的行串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {  // matrix：0/1 矩阵；返回若干次整列翻转后最多能有多少行完全相同
        unordered_map<string, int> cnt;  // 归一化行模式 → 该模式出现的次数
        int ans = 0;  // 记录出现次数最多的模式对应的行数，即答案
        for (auto& row : matrix) {  // 逐行处理，取引用避免拷贝
            string s;  // 当前行归一化后的模式串
            for (int x : row) {  // 逐列取值
                s.push_back('0' + (row[0] == 0 ? x : x ^ 1));  // 首元素为 0 时保持原样；为 1 时整行异或 1 取反，让互补的行落到同一模式
            }  // end for：本行模式串构造完成
            ans = max(ans, ++cnt[s]);  // 先把该模式计数加一，再用它更新最大值
        }  // end for：所有行统计完毕
        return ans;  // 最大同模式行数就是答案（这些行可借同一组列翻转变成完全相同）
    }  // end method
};  // end class