// 题目：41. 缺失的第一个正数（First Missing Positive）
// 思路：原地哈希——把每个落在 [1, n] 内的数交换到下标 v-1 上；再从头扫一遍，第一个 nums[i] != i+1 的位置对应答案 i+1，全部对得上则答案是 n+1。
// 时间复杂度：O(n)，每个数最多被交换常数次；空间复杂度：O(1)，只用了几个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int firstMissingPositive(vector<int>& nums) {  // nums 是整数数组；返回其中缺失的最小正整数
        int n = nums.size();  // n 既是数组长度，也是答案上界：长度 n 的数组最多容纳 1..n，所以答案必在 1..n+1
        for (int i = 0; i < n; ++i) {  // 第一趟：逐格处理，把每个在 [1, n] 内的数换到它「应该在」的下标上
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {  // 当前数合法、且不在自己的位置上就继续换；用 while 是因为换进来的新值可能仍需挪动
                swap(nums[i], nums[nums[i] - 1]);  // 交换 nums[i] 与它该去的位置 nums[nums[i]-1]；每换一次就有一个数归位，因此总体仍是线性
            }  // while 结束
        }  // 第一趟结束，1..n 范围内的数都尽量回到了自己的位置
        for (int i = 0; i < n; ++i) {  // 第二趟：寻找第一个位不配值的位置
            if (nums[i] != i + 1) {  // 位置 i 上本应是 i+1，不相等就说明 i+1 缺失
                return i + 1;  // 返回缺失的最小正整数
            }  // if 分支结束
        }  // 第二趟结束
        return n + 1;  // 1..n 全都到位，那么缺失的最小正整数只能是 n+1
    }  // 方法结束
};  // 类定义结束
