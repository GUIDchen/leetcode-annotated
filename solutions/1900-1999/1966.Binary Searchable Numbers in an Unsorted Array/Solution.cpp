// 题目：1966. 未排序数组中的可被二分查找的数（Binary Searchable Numbers in an Unsorted Array）
// 思路：元素能被二分查到，当且仅当它不小于左侧所有元素且不大于右侧所有元素；从左扫一遍查前缀最大、从右扫一遍查后缀最小即可。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，ok 数组记录每个位置是否可能被二分查到。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int binarySearchableNumbers(vector<int>& nums) {  // nums 是待判断的数组，返回其中可被二分查找命中的元素个数
        int n = nums.size();  // 数组长度
        vector<int> ok(n, 1);  // ok[i] = 1 表示下标 i 仍是候选，0 表示已被排除
        int mx = -1000000, mi = 1000000;  // mx 是左侧最大值，mi 是右侧最小值；用题目值域（1..10^6）之外的哨兵初始化
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，检查「不小于左侧所有元素」
            if (nums[i] < mx) {  // 左边存在比它大的数，二分时可能被排除到左半边
                ok[i] = 0;  // 标记为不合格
            }  // if 结束
            mx = max(mx, nums[i]);  // 更新左侧最大值，供后面的元素比较
        }  // for 结束
        int ans = 0;  // 统计满足条件的元素个数
        for (int i = n - 1; i >= 0; --i) {  // 从右到左扫描，检查「不大于右侧所有元素」
            if (nums[i] > mi) {  // 右边存在比它小的数，二分时可能被排除到右半边
                ok[i] = 0;  // 同样标记为不合格
            }  // if 结束
            mi = min(mi, nums[i]);  // 更新右侧最小值
            ans += ok[i];  // 顺手累加，省去第三次遍历
        }  // for 结束
        return ans;  // 返回可被二分查找命中的元素个数
    }  // 方法结束
};  // 类定义结束