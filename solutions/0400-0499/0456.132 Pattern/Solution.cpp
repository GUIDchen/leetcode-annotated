// 题目：456. 132 模式（132 Pattern）
// 思路：从右往左扫描，单调栈维护可充当「3」的元素，vk 记录已确认的最大「2」；当前元素比 vk 小即构成 132。
// 时间复杂度：O(n)，每个元素最多入栈出栈一次；空间复杂度：O(n)，单调栈最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool find132pattern(vector<int>& nums) {  // 判断是否存在 i<j<k 且 nums[i]<nums[k]<nums[j] 的 132 模式
        int vk = INT_MIN;  // vk 是已确认的「2」（即 nums[k]）的最大值，INT_MIN 表示还没找到任何「2」
        stack<int> stk;  // 单调栈：自栈底到栈顶递减，栈内元素都可能充当「3」（即 nums[j]）
        for (int i = nums.size() - 1; ~i; --i) {  // 从右往左遍历，i 充当 132 模式最左侧的「1」
            if (nums[i] < vk) {  // 当前元素比已找到的「2」还小，说明存在 1<2<3
                return true;  // 确认存在 132 模式，返回真
            }  // 结束本次判断
            while (!stk.empty() && stk.top() < nums[i]) {  // 把栈中所有小于当前元素的元素弹出，它们可以升级为候选「2」
                vk = stk.top();  // 栈顶元素即候选「2」，保留其中最大的（越大越容易匹配到更小的「1」）
                stk.pop();  // 弹出后它不再参与充当「3」
            }  // 结束弹栈
            stk.push(nums[i]);  // 当前元素入栈，作为可能的「3」，等待更左边的元素充当「1」
        }  // 结束本轮扫描
        return false;  // 全部扫描完仍未找到，返回假
    }  // 结束方法
};