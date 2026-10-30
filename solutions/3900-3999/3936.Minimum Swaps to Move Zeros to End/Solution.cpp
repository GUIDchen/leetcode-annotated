// 3936. 将 0 移到末尾的最少交换次数 / Minimum Swaps to Move Zeros to End
// 核心思路：双指针从两端向中间收缩，左侧第一个 0 与右侧第一个非 0 配对交换，交换次数即答案。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类定义
public:  // 公开接口
    int minimumSwaps(vector<int>& nums) {  // 主函数：计算把 0 全部移到末尾的最少交换次数
        int ans = 0;  // 交换次数计数
        int n = nums.size();  // 数组长度
        for (int i = 0, j = n - 1; i < j; ++i, --j) {  // 左右指针同时向中间收缩
            while (i < n && nums[i] != 0) {  // 从左找到第一个 0
                ++i;  // 左指针右移
            }  // 找 0 的循环结束

            while (j > 0 && nums[j] == 0) {  // 从右找到第一个非 0
                --j;  // 右指针左移
            }  // 找非 0 的循环结束

            if (i >= j) {  // 两指针相遇，没有可配对交换的元素
                break;  // 提前结束
            }  // if 分支结束

            ++ans;  // 完成一次交换，计数加 1
        }  // 外层循环结束

        return ans;  // 返回最少交换次数
    }  // minimumSwaps 函数结束
};  // 类定义结束