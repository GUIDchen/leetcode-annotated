// 题目：457. 环形数组是否存在循环（Circular Array Loop）
// 思路：枚举起点，用快慢指针在同向路径上判环；一条路径走完后把其中元素置 0 标记已访问，整体均摊 O(n)。
// 时间复杂度：O(n)，每个下标最多被访问并标记常数次；空间复杂度：O(1)，原地置 0 标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool circularArrayLoop(vector<int>& nums) {  // nums[i] 表示从 i 前进（正数）或后退（负数）的步数，判断是否存在同向且长度大于 1 的循环
        int n = nums.size();  // n 是数组长度，取模环绕时反复使用
        for (int i = 0; i < n; ++i) {  // 枚举每个下标作为环的起点
            if (!nums[i]) continue;  // 值为 0 说明已被标记为访问过，跳过
            int slow = i, fast = next(nums, i);  // 快慢指针初始化：slow 在起点，fast 先走一步
            while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(nums, fast)] > 0) {  // 继续追及的条件：当前点与下一点同号，且 fast 的下一点也同号（从而排除长度为 1 的自环）
                if (slow == fast) {  // 快慢指针相遇，说明路径上存在环
                    if (slow != next(nums, slow)) return true;  // 环长必须大于 1（slow 的下一个不是它自己）才算合法循环
                    break;  // 是自环，退出本次探查
                }  // 结束相遇分支
                slow = next(nums, slow);  // 慢指针走一步
                fast = next(nums, next(nums, fast));  // 快指针走两步
            }  // 结束追及循环
            int j = i;  // 从起点重新走一遍，把这条路径上的元素标记为 0
            while (nums[j] * nums[next(nums, j)] > 0) {  // 只要下一步仍同号，就仍属于这条路径
                nums[j] = 0;  // 置 0 标记已访问，后续不再从该下标出发
                j = next(nums, j);  // 移动到下一个下标
            }  // 结束标记循环
        }  // 结束起点枚举
        return false;  // 所有起点都尝试过，不存在合法循环
    }  // 结束方法

    int next(vector<int>& nums, int i) {  // 辅助函数：计算从 i 走 nums[i] 步后的下标（支持负步数，结果保证非负）
        int n = nums.size();  // 用数组长度 n 做取模环绕
        return (i + nums[i] % n + n) % n;  // 先对步数取模防溢出，+n 把负数纠正为正，再取模得到 [0,n)
    }
};