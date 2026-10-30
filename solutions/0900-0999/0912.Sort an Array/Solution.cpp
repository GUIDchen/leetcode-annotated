// 题目：912. 排序数组（Sort an Array）
// 核心思路：手写快速排序（Hoare 式双指针划分），取中间元素为基准，左右指针相向扫描并交换逆序元素，再递归排序两段；用 lambda 捕获数组以便递归调用。
// 时间复杂度：平均 O(n log n)、最坏 O(n^2)；空间复杂度：O(log n)，为递归栈深度（不计返回数组）。
class Solution {  // 题解类
public:  // 对外接口
    vector<int> sortArray(vector<int>& nums) {  // 返回 nums 升序排序后的数组（题目要求返回值）
        function<void(int, int)> quick_sort = [&](int l, int r) {  // 定义递归 lambda 排序闭区间 [l, r]，[&] 按引用捕获 nums 等外部变量
            if (l >= r) {  // 区间元素不足 2 个时天然有序，直接返回
                return;  // 递归出口
            }  // 出口判断结束
            int i = l - 1, j = r + 1;  // Hoare 划分：i 从左侧外开一步、j 从右侧外开一步，先移动再比较
            int x = nums[(l + r) >> 1];  // 取中间元素作基准值（右移一位等价于除以 2），避免有序数据退化
            while (i < j) {  // 双指针相向扫描，直到交错为止
                while (nums[++i] < x) {  // 从左往右找第一个 >= 基准的元素
                }  // 空循环体：只靠 ++i 推进
                while (nums[--j] > x) {  // 从右往左找第一个 <= 基准的元素
                }  // 空循环体：只靠 --j 推进
                if (i < j) {  // 两指针未交错，说明找到了一对位置不对的元素
                    swap(nums[i], nums[j]);  // 交换它们，让小的去左边、大的去右边
                }  // 交换分支结束
            }  // 划分结束：此时 [l, j] 都不大于基准，[j+1, r] 都不小于基准
            quick_sort(l, j);  // 递归排序左半段
            quick_sort(j + 1, r);  // 递归排序右半段
        };  // lambda 定义结束
        quick_sort(0, nums.size() - 1);  // 对整个数组 [0, n-1] 排序
        return nums;  // 返回排序结果
    }  // 方法结束
};  // 类定义结束