// 题目：2202. K 次操作后最大化顶端元素（Maximize the Topmost Element After K Moves）
// 思路：每次操作只能删除栈顶或把删掉的元素放回栈顶，所以最终顶端只可能是前 k-1 个元素的最大值（删了再放回），或下标 k 的元素（连删 k 个）。
// 时间复杂度：O(min(k, n))，只需扫一遍前 k-1 个元素；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumTop(vector<int>& nums, int k) {  // nums：从栈底到栈顶的数组；k：允许的操作次数
        if (k == 0) return nums[0];  // 一次也不操作，顶端就是 nums[0]
        int n = nums.size();  // 元素个数
        if (n == 1) {  // 只有一个元素时，操作只能在「弹出」和「放回」之间交替
            if (k % 2) return -1;  // 奇数次操作会把唯一元素弹掉，栈变空，按题意返回 -1
            return nums[0];  // 偶数次操作后元素回到栈顶
        }  // 结束 n == 1 分支
        int ans = -1;  // 候选答案，先设为 -1；若最终取不到值正好与栈空对应
        for (int i = 0; i < min(k - 1, n); ++i) ans = max(ans, nums[i]);  // 前 k-1 个元素都能被删掉再放回栈顶，取其中最大值；min(k-1, n) 防止越界
        if (k < n) ans = max(ans, nums[k]);  // 若 k < n，也可以把前 k 个元素全部删掉，让 nums[k] 成为新的栈顶
        return ans;  // 返回两者中较大的可能顶端值
    }  // 结束方法
};  // 结束 Solution 类