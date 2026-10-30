// 题目：2772. 使数组中的所有元素都等于零（Apply Operations to Make All Array Elements Equal to Zero）
// 思路：从左到右贪心 + 差分数组。要让 nums[i] 归零，必须以 i 为左端点对长度 k 的区间整体减去 nums[i]；用差分数组 d 和累计量 s 记录这些区间操作产生的效果。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(n)，差分数组长度为 n + 1。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    bool checkArray(vector<int>& nums, int k) {  // nums 是目标数组，k 是每次操作选定的子数组长度
        int n = nums.size();  // 数组长度
        vector<int> d(n + 1);  // 差分数组：d[i] 是“作用于下标 i 的变化量”相对前一位的增量
        int s = 0;  // 当前位置实际生效的数值变化总量，即 d 的前缀和
        for (int i = 0; i < n; ++i) {  // 从左到右依次把每个位置清零
            s += d[i];  // 把从下标 i 开始生效的差分增量并入累计变化量
            nums[i] += s;  // 加上此前所有区间操作对当前位置的实际影响，得到剩余值
            if (nums[i] == 0) {  // 剩余值已为 0，不需要以它为左端点再做操作
                continue;  // 直接处理下一个位置
            }
            if (nums[i] < 0 || i + k > n) {  // 剩余值为负说明被减过头；剩余长度不足 k 也无法再消去它
                return false;  // 该数组无法全部归零
            }
            s -= nums[i];  // 对区间 [i, i + k - 1] 整体减去 nums[i]：当前位置立即生效，累计量随之减少
            d[i + k] += nums[i];  // 差分标记：这次减法的效果在窗口右端 i + k 处撤回
        }
        return true;  // 所有位置都成功清零
    }
};