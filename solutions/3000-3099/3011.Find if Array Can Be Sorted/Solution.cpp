// 题目：3011. 判断一个数组是否可以变为有序（Find if Array Can Be Sorted）
// 思路：只有相邻且二进制中 1 的个数相同的元素才能互换，因此数组被切分成若干可自由排序的连续块；逐块求最小/最大值，只要每块的最小值都不小于前一块的最大值，就能整体排成非降序。
// 时间复杂度：O(n)，每个元素只被归入一个块访问一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canSortArray(vector<int>& nums) {  // nums：输入数组；返回它能否排成非降序
        int preMx = 0;  // preMx 记录前一个可交换块的最大值；第一块之前没有约束，初值 0（题面元素为正）
        int i = 0, n = nums.size();  // i 是当前块的左端点，n 是元素个数
        while (i < n) {  // 外层循环：按顺序处理每一个可交换块
            int cnt = __builtin_popcount(nums[i]);  // 当前块的标志：二进制中 1 的个数（__builtin_popcount 是编译器内建函数）
            int j = i + 1;  // j 指向块内下一个位置，用来向后扩展同一块
            int mi = nums[i], mx = nums[i];  // 块内最小值与最大值，初始都是块的第一个元素
            while (j < n && __builtin_popcount(nums[j]) == cnt) {  // 相邻元素 1 的个数相同就可以互换，因此同属一个块
                mi = min(mi, nums[j]);  // 维护块内最小值
                mx = max(mx, nums[j]);  // 维护块内最大值
                j++;  // 右端点继续前进
            }  // 块扩展结束
            if (preMx > mi) {  // 块内可以任意排序，但块与块之间不能跨越；前一块最大值大于本块最小值就是跨块逆序
                return false;  // 存在无法消除的逆序，直接判定不可行
            }  // if 语句结束
            preMx = mx;  // 更新前一块的最大值，供下一块比较
            i = j;  // 从下一块的开头继续
        }  // 所有块都处理完毕
        return true;  // 每块最小值都不小于前一块最大值，整体可以排成非降序
    }  // 方法结束
};  // 类定义结束