// 题目：3738. 替换至多一个元素后最长非递减子数组（Longest Non-Decreasing Subarray After Replacing at Most One Element）
// 核心思路：先用 left[i] 表示以 i 结尾的最长非递减段长度、right[i] 表示以 i 开头的最长非递减段长度；再枚举被替换的位置 i，若左右邻居能直接衔接（nums[i-1] <= nums[i+1]）就把左右两段合并，否则只能任选较长的一侧，全程取最大值。
// 复杂度：时间 O(n)，只需两次线性扫描加一次枚举；空间 O(n)，需要 left 与 right 两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubarray(vector<int>& nums) {  // nums：整数数组；返回替换至多一个元素后最长非递减子数组的长度
        int n = nums.size();  // 数组长度
        vector<int> left(n, 1), right(n, 1);  // left[i]：以 i 结尾的最长非递减段长度；right[i]：以 i 开头的最长非递减段长度，初值都是 1

        for (int i = 1; i < n; ++i) {  // 从左往右预处理 left
            if (nums[i] >= nums[i - 1]) {  // 相邻元素满足非递减
                left[i] = left[i - 1] + 1;  // 可以接在上一段后面，长度加一
            }  // 非递减判断结束
        }  // left 预处理结束

        for (int i = n - 2; i >= 0; --i) {  // 从右往左预处理 right
            if (nums[i] <= nums[i + 1]) {  // 相邻元素满足非递减
                right[i] = right[i + 1] + 1;  // 可以接在后面那一段的前面，长度加一
            }  // 非递减判断结束
        }  // right 预处理结束

        int ans = ranges::max(left);  // 答案至少是原本最长的一段（也可以选择不替换）

        for (int i = 0; i < n; ++i) {  // 枚举被替换（即被新值覆盖）的位置 i
            int a = (i - 1 < 0) ? 0 : left[i - 1];  // 左侧能接上的长度，越界则为 0
            int b = (i + 1 >= n) ? 0 : right[i + 1];  // 右侧能接上的长度，越界则为 0
            if (i - 1 >= 0 && i + 1 < n && nums[i - 1] > nums[i + 1]) {  // 左右邻居都存在但接不上：新值无法同时衔接两侧
                ans = max({ans, a + 1, b + 1});  // 只能保留其中一侧，用新值替换掉较短的一侧
            } else {  // 两侧可以接上（或只有一侧存在）
                ans = max(ans, a + b + 1);  // 用一个新值把位置 i 替换掉，左右两段合并成一段
            }  // 分支结束
        }  // 枚举结束

        return ans;  // 返回最长非递减子数组的长度
    }  // 方法结束
};  // 类定义结束
