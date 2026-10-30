// 题目：169. 多数元素（Majority Element）
// 核心思路：Boyer-Moore 摩尔投票，相同则票数加一、不同则抵消一票；多数元素超过一半，最终留下的候选必然是它。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只维护候选值和票数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int majorityElement(vector<int>& nums) {  // 求出现次数严格大于 n/2 的元素
        int cnt = 0, m = 0;  // cnt：候选的票数；m：当前候选元素
        for (int& x : nums) {  // 引用遍历，避免逐个元素拷贝
            if (cnt == 0) {  // 票数归零说明之前的候选已被完全抵消
                m = x;  // 换当前元素作为新的候选
                cnt = 1;  // 新候选票数记为 1
            } else {  // 候选仍然有效
                cnt += m == x ? 1 : -1;  // 与候选相同加一票，不同则抵消一票
            }
        }  // 多数元素超过一半，抵消到最后剩下的必定是它
        return m;
    }
};