// 题目：896. 单调数列（Monotonic Array）
// 核心思路：一次遍历，分别记录是否出现过严格上升、严格下降；两者同时出现即不单调。
// 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，只用两个标记变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isMonotonic(vector<int>& nums) {  // nums：待判定的数组
        bool asc = false, desc = false;  // asc 标记是否出现过严格上升，desc 标记是否出现过严格下降
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，与前一个元素比较
            if (nums[i - 1] < nums[i]) {  // 出现严格上升
                asc = true;  // 记录上升
            } else if (nums[i - 1] > nums[i]) {  // 出现严格下降
                desc = true;  // 记录下降
            }
            if (asc && desc) {  // 同时出现过上升和下降，既非单调增也非单调减
                return false;  // 直接判定不是单调数列
            }
        }
        return true;  // 整个数组只朝一个方向变化（或全部相等），是单调数列
    }
};