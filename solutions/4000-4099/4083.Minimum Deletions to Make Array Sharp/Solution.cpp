// 题目：4083. 使相邻元素按位异或非零的最少删除次数（Minimum Deletions to Make Array Sharp）
// 核心思路：数组已有序，相邻两元素按位异或为 0 当且仅当二者相等；要让所有相邻异或都不为零，每出现一对相等相邻元素删掉其中一个即可，且每次删除恰好消掉一处冲突，故答案为相等相邻对的个数。
// 复杂度：时间 O(n)，一次线性扫描；空间 O(1)，只用计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    int minDeletions(vector<int>& nums) {  // nums：已排序数组；返回使相邻异或全非零的最少删除次数
        int ans = 0;  // ans 统计需要删除的元素个数
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，扫描每一对相邻元素
            if (nums[i] == nums[i - 1]) {  // 相邻两元素相等，其异或结果为 0，必须删掉其中一个
                ++ans;  // 冲突计数加一，同时也是需要删除的元素数
            }  // 相等分支结束
        }  // 相邻对遍历结束
        return ans;  // 返回最少删除次数
    }  // minDeletions 结束
};  // Solution 类结束