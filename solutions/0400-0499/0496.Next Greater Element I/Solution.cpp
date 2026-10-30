// 题目：496. 下一个更大元素 I（Next Greater Element I）
// 思路：从右往左扫描 nums2，用单调栈维护右侧候选值，栈顶就是最近的那个更大元素，结果记入哈希表后再按 nums1 的顺序查表回答。
// 时间复杂度：O(m + n)，每个元素最多进栈、出栈各一次；空间复杂度：O(n)，栈与哈希表各最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {  // nums1 是查询数组，nums2 是母数组（nums1 是 nums2 的子集）
        stack<int> stk;  // 单调栈：从栈底到栈顶递减，栈顶就是当前元素右边最近的更大候选
        unordered_map<int, int> d;  // 哈希表：键是 nums2 中的元素，值是它的下一个更大元素
        ranges::reverse(nums2);  // 反转 nums2 让扫描方向变成从右往左，这样栈里保存的才是右侧元素
        for (int x : nums2) {  // 逐个处理 nums2 的元素（此时遍历顺序是从右到左）
            while (!stk.empty() && stk.top() < x) {  // 把栈顶所有比当前元素小的弹出，它们不可能再成为别人右侧的更大元素
                stk.pop();  // 弹出较小元素，维持栈的单调性
            }  // 弹栈结束；此时栈顶若存在就是右侧第一个比 x 大的值
            if (!stk.empty()) {  // 栈非空说明右侧确实存在更大元素
                d[x] = stk.top();  // 记录 x 的下一个更大元素
            }  // 否则 x 右侧没有更大元素，不写入哈希表
            stk.push(x);  // 当前元素入栈，供它左侧的元素查询
        }  // nums2 处理完毕，映射表建成
        vector<int> ans;  // 存放答案的数组
        for (int x : nums1) {  // 按 nums1 的顺序逐个查表
            ans.push_back(d.contains(x) ? d[x] : -1);  // C++20 的 contains 判断有无记录，有则取值，没有则按题意返回 -1
        }  // 答案组装完毕
        return ans;  // 返回结果数组
    }  // 方法体结束
};  // 类定义结束
