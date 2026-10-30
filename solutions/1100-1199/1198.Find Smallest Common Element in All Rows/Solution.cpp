// 题目：1198. 找出所有行中最小公共元素（Find Smallest Common Element in All Rows）
// 思路：用计数数组统计每个元素出现在多少行里，扫描最后一行时第一个计数达到行数的元素就是答案。
// 时间复杂度：O(mn)，每个元素扫一次；空间复杂度：O(C)，C 为元素值域（数组长度 10001）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestCommonElement(vector<vector<int>>& mat) {  // mat 是每行严格升序的矩阵，返回所有行共有的最小元素
        int cnt[10001]{};  // cnt[x] 记录元素 x 出现在多少行中；{} 把值域 1..10000 全部清零
        for (auto& row : mat) {  // 逐行遍历矩阵
            for (int x : row) {  // 遍历当前行里的每个元素
                if (++cnt[x] == mat.size()) {  // 先把 x 的计数加一，再看是否已经覆盖所有行
                    return x;  // 计数等于行数，说明前面每一行都出现过 x；按行升序扫描保证它最小
                }
            }
        }
        return -1;  // 没有任何元素出现在所有行里，按题目约定返回 -1
    }
};