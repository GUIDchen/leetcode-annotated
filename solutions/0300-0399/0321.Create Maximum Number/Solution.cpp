// 题目：321. 拼接最大数（Create Maximum Number）
// 思路：枚举从 nums1 取 x 个、从 nums2 取 k-x 个，各自用单调栈求最大子序列，再按字典序贪心合并，取全局最大。
// 时间复杂度：O(k * (m + n)^2)，需枚举 k+1 种分配且每次合并要递归比较；空间复杂度：O(m + n)，存放两个栈与合并结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {  // 从 nums1、nums2 中共取 k 个数字且保持原相对顺序，返回能拼出的最大序列
        auto f = [](vector<int>& nums, int k) {  // f：从 nums 中取 k 个数字能组成的最大子序列（单调栈实现）
            int n = nums.size();  // 数组长度，用来算出可以丢弃多少个元素
            vector<int> stk(k);  // 结果栈，最终恰好装 k 个数字
            int top = -1;  // 栈顶下标，-1 表示栈为空
            int remain = n - k;  // 可以丢弃的元素个数，也就是弹栈次数的上限
            for (int x : nums) {  // 按原顺序遍历每个数字
                while (top >= 0 && stk[top] < x && remain > 0) {  // 栈顶更小且还有丢弃名额时弹栈，让更大的数字前移
                    --top;  // 弹出栈顶
                    --remain;  // 消耗一个丢弃名额
                }  // 弹栈循环结束
                if (top + 1 < k) {  // 栈还没满 k 个，可以继续压入
                    stk[++top] = x;  // 把当前数字压栈
                } else {  // 栈已满时只能丢弃当前数字
                    --remain;  // 直接丢弃，同样消耗一个名额
                }  // 分支结束
            }  // 遍历结束
            return stk;  // 返回长度为 k 的最大子序列
        };  // f 定义结束
        function<bool(vector<int>&, vector<int>&, int, int)> compare = [&](vector<int>& nums1, vector<int>& nums2, int i, int j) -> bool {  // compare：从 i、j 开始比较两个后缀，判断从 nums1[i] 开始的那个后缀是否字典序更大
            if (i >= nums1.size()) {  // 第一个后缀已经耗尽
                return false;  // 一方先耗尽说明它更小，返回 false
            }  // 分支结束
            if (j >= nums2.size()) {  // 第二个后缀耗尽而第一个仍有剩余
                return true;  // 剩余更长的一方更大，返回 true
            }  // 分支结束
            if (nums1[i] > nums2[j]) {  // 当前位第一个更大
                return true;  // 第一个后缀整体更大
            }  // 分支结束
            if (nums1[i] < nums2[j]) {  // 当前位第一个更小
                return false;  // 第一个后缀整体更小
            }  // 分支结束
            return compare(nums1, nums2, i + 1, j + 1);  // 当前位相等，继续比较下一位
        };  // compare 定义结束

        auto merge = [&](vector<int>& nums1, vector<int>& nums2) {  // merge：把两个子序列合并成字典序最大的结果
            int m = nums1.size(), n = nums2.size();  // 两个子序列的长度
            int i = 0, j = 0;  // 两个子序列各自的读取指针
            vector<int> ans(m + n);  // 合并结果，长度是两者之和
            for (int k = 0; k < m + n; ++k) {  // 依次确定结果的每一位
                if (compare(nums1, nums2, i, j)) {  // 第一个后缀更大，就先取它的当前位
                    ans[k] = nums1[i++];  // 取 nums1[i] 后让 i 后移
                } else {  // 否则取第二个子序列的当前位
                    ans[k] = nums2[j++];  // 取 nums2[j] 后让 j 后移
                }  // 分支结束
            }  // 逐位循环结束
            return ans;  // 返回合并后的最大序列
        };  // merge 定义结束

        int m = nums1.size(), n = nums2.size();  // 两个数组的长度
        int l = max(0, k - n), r = min(k, m);  // nums1 至少要取 l 个、至多取 r 个才能凑够 k 个
        vector<int> ans(k);  // 保存目前找到的最大序列
        for (int x = l; x <= r; ++x) {  // 枚举从 nums1 取 x 个的所有可行分配
            vector<int> arr1 = f(nums1, x);  // 从 nums1 取 x 个的最大子序列
            vector<int> arr2 = f(nums2, k - x);  // 从 nums2 取 k-x 个的最大子序列
            vector<int> arr = merge(arr1, arr2);  // 合并成一个候选答案
            if (ans < arr) {  // vector 已重载字典序比较，候选更大就替换
                ans = move(arr);  // 移动赋值，避免整份拷贝
            }  // 分支结束
        }  // 分配方案枚举结束
        return ans;  // 返回所有分配方案中的最大值
    }  // 方法结束
};  // 类定义结束