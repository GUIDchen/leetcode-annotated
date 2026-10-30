// 题目：944. 删列造序（Delete Columns to Make Sorted）
// 思路：逐列检查该列是否自上而下非递减，一旦某行的字符比上一行小，这一列就必须整列删除并计数。
// 时间复杂度：O(m·n)，m 为列数、n 为行数（最坏）；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDeletionSize(vector<string>& strs) {  // strs 是等长的字符串数组，返回必须删除的列数（最少删除数）
        int m = strs[0].size(), n = strs.size();  // m 是列数（字符串长度），n 是行数（字符串个数）
        int ans = 0;  // 记录需要删除的列数
        for (int j = 0; j < m; ++j) {  // 逐列检查
            for (int i = 1; i < n; ++i) {  // 从第 2 行开始，与上一行同列字符比较
                if (strs[i][j] < strs[i - 1][j]) {  // 当前行字符比上一行小，说明这一列不是非递减，必须删除
                    ++ans;  // 该列需要删除，计数加一
                    break;  // 这一列已判定，无需再检查后面的行
                }
            }
        }
        return ans;  // 返回最少删除的列数
    }
};  // 类定义结束