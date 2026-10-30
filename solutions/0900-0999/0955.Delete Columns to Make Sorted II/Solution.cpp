// 题目：955. 删列造序 II（Delete Columns to Make Sorted II）
// 思路：按列从左到右贪心扫描，用布尔数组标记哪些相邻行已在前面的列中分出严格大小；若某列使尚未分出的行出现逆序，就整列删除。
// 时间复杂度：O(n·m)，n 为字符串个数、m 为字符串长度，最坏每列扫描一遍所有相邻行；空间复杂度：O(n)，标记数组长度为 n-1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDeletionSize(vector<string>& strs) {  // strs：等长字符串数组，返回最少需要删除的列数
        int n = strs.size();  // n：字符串个数，也就是行数
        int m = strs[0].size();  // m：每个字符串的长度，也就是列数
        vector<bool> st(n - 1, false);  // st[i] 为真表示第 i 行与第 i+1 行已经严格递增，后续列无需再比较它们
        int ans = 0;  // ans：已经删除的列数
        for (int j = 0; j < m; ++j) {  // 逐列扫描，列下标 j 从左到右
            bool must_del = false;  // 标记当前这一列是否必须删除
            for (int i = 0; i < n - 1; ++i) {  // 检查所有还没分出大小的相邻行
                if (!st[i] && strs[i][j] > strs[i + 1][j]) {  // 本列出现逆序（上面大于下面），这一列就非删不可
                    must_del = true;  // 记录必须删除
                    break;  // 已经确定要删，无需继续检查后面的行
                }
            }  // 这一列必须删除，答案加一
            if (must_del) {  // 本列不删，那么它可以帮一些相邻行确定严格的大小关系
                ++ans;
            } else {  // 再扫一遍，找出本列能分出大小的相邻行
                for (int i = 0; i < n - 1; ++i) {  // 上面小于下面，说明这两行的顺序已经由这一列确定
                    if (!st[i] && strs[i][j] < strs[i + 1][j]) {  // 标记为已确定，之后再有逆序的列也不会影响它们
                        st[i] = true;
                    }
                }
            }
        }
        return ans;  // 返回最少需要删除的列数
    }
};
