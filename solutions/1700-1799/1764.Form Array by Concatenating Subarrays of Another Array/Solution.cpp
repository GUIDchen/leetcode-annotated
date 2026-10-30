// 题目：1764. 通过连接另一个数组的子数组得到一个数组（Form Array by Concatenating Subarrays of Another Array）
// 思路：双指针。从 nums 的当前位置 j 起尝试匹配 groups[i]；匹配成功则 j 后移该组长度、i 前进一组，否则 j 后移一位继续找。
// 时间复杂度：O(n*m)，最坏情况每个位置都要比较；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {  // groups：需按顺序拼接的若干子数组；nums：源数组
        auto check = [&](vector<int>& a, vector<int>& b, int j) {  // 判断 a 是否等于 b 从下标 j 开始的一段
            int m = a.size(), n = b.size();  // m 是模式长度，n 是源数组长度
            int i = 0;  // 模式内部的下标
            for (; i < m && j < n; ++i, ++j) {  // 两个数组同步前进，任一越界即停止
                if (a[i] != b[j]) {  // 出现不同元素，说明匹配失败
                    return false;  // 立即返回失败
                }
            }
            return i == m;  // 模式被完整匹配完才算成功（源数组不够长时 i < m，返回 false）
        };
        int n = groups.size(), m = nums.size();  // n 是分组个数，m 是源数组长度
        int i = 0;  // 当前要匹配的分组下标
        for (int j = 0; i < n && j < m;) {  // j 是源数组中尝试匹配的位置；所有组匹配完或源数组用尽则结束
            if (check(groups[i], nums, j)) {  // 当前分组在 j 处匹配成功
                j += groups[i].size();  // 跳过这一整段，子数组之间不允许重叠
                ++i;  // 继续匹配下一个分组
            } else {  // 当前位置匹配失败
                ++j;  // 源数组位置右移一位，重新尝试当前分组
            }
        }
        return i == n;  // 所有分组都按顺序匹配成功才返回 true
    }
};