// 题目：665. 非递减数列（Non-decreasing Array）
// 思路：从左往右找第一处下降 nums[i] > nums[i+1]，只尝试两种修补（压低 nums[i] 成 b、抬高 nums[i+1] 成 a），再用 is_sorted 判整体有序。
// 时间复杂度：O(n)，最多两次线性扫描；空间复杂度：O(1)，原地修改数组，不额外开空间。
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    bool checkPossibility(vector<int>& nums) {  // nums 是输入数组，判断最多改一个元素后能否非递减
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n - 1; ++i) {  // 找到第一处下降即可，其余情况交给 is_sorted 统一判断
            int a = nums[i], b = nums[i + 1];  // 下降处相邻的两个元素
            if (a > b) {  // 出现 nums[i] > nums[i+1]，必须改掉其中一个
                nums[i] = b;  // 方案一：把 nums[i] 压低成较小的 b
                if (is_sorted(nums.begin(), nums.end())) {  // 试改后整体有序就成功
                    return true;  // 方案一可行，立刻返回 true
                }
                nums[i] = a;  // 撤销方案一，恢复 nums[i]
                nums[i + 1] = a;  // 方案二：把 nums[i+1] 抬高成较大的 a
                return is_sorted(nums.begin(), nums.end());  // 只允许改一次，方案二成不成立就是最终答案
            }
        }  // 结束 for 循环
        return true;  // 全程没有下降，本来就是非递减数列
    }  // 结束 checkPossibility
};