// 题目：215. 数组中的第K个最大元素（Kth Largest Element in an Array）
// 核心思路：把「第 k 大」换算成升序下标 n-k，用快速选择（双指针划分）每次只递归目标所在的一侧。
// 时间复杂度：O(n) 平均，每轮划分期望排除一半元素；空间复杂度：O(log n)，递归栈深度期望为对数级。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int findKthLargest(vector<int>& nums, int k) {  // 返回数组升序排序后第 k 大的元素
        int n = nums.size();  // 数组长度
        k = n - k;  // 第 k 大等价于升序下标 n-k（0 基），后面按目标下标查找
        auto quickSort = [&](auto&& quickSort, int l, int r) -> int {  // 泛型 lambda：把自己作为参数传进去实现递归，[&] 捕获 nums 与 k
            if (l == r) {  // 区间只剩一个元素，它必然是目标
                return nums[l];  // 直接返回该元素
            }  // if 结束
            int i = l - 1, j = r + 1;  // 双指针都从区间外侧一格开始，便于先自增/自减再比较
            int x = nums[(l + r) >> 1];  // 取中点元素作为划分基准（比取端点更抗有序数据）
            while (i < j) {  // 左右指针尚未交错时继续划分
                while (nums[++i] < x) {  // 左指针右移，跳过所有小于基准的元素
                }  // 循环体为空：找到第一个不小于基准的位置就停下
                while (nums[--j] > x) {  // 右指针左移，跳过所有大于基准的元素
                }  // 循环体为空：找到第一个不大于基准的位置就停下
                if (i < j) {  // 两指针没有交错，说明这两个元素站错了边
                    swap(nums[i], nums[j]);  // 交换它们，使左边不大于基准、右边不小于基准
                }  // if 结束
            }  // 划分结束：此时 [l, j] 都不大于基准，[j+1, r] 都不小于基准
            if (j < k) {  // 目标下标落在右半区
                return quickSort(quickSort, j + 1, r);  // 只在右半区继续递归查找
            }  // if 结束
            return quickSort(quickSort, l, j);  // 否则目标在左半区（含 j 本身），继续在 [l, j] 里找
        };  // lambda 定义结束
        return quickSort(quickSort, 0, n - 1);  // 在整个数组 [0, n-1] 上启动快速选择
    }  // 方法结束
};  // 类定义结束
