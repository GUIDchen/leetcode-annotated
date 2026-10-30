// 题目：3542. 将所有元素变为 0 的最少操作次数（Minimum Operations to Convert All Elements to Zero）
// 思路：用单调递增栈维护当前尚未结算的层级，遇到更小的值就把被截断的层依次结算，最后把栈中剩余的层一次性计入答案。
// 时间复杂度：O(n)，每个元素最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：非负整数数组
        vector<int> stk;  // 单调递增栈，保存尚未结算的正数层级
        int ans = 0;  // 已经统计出的操作次数
        for (int x : nums) {  // 从左到右扫描数组
            while (!stk.empty() && stk.back() > x) {  // 栈顶比当前值大，说明这一层到这里被截断
                ++ans;  // 被截断的这一层单独贡献一次操作
                stk.pop_back();  // 弹出已经结算的层级
            }
            if (x != 0 && (stk.empty() || stk.back() != x)) {  // 当前值非 0 且与栈顶不同，才需要新开一层
                stk.push_back(x);  // 记录这一层，后面相同的值可以复用同一段操作
            }
        }
        ans += stk.size();  // 栈中剩余的每个层级都还需要一次独立操作
        return ans;  // 返回最少操作次数
    }
};
