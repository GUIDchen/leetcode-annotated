// 题目：442. 数组中重复的数据（Find All Duplicates in an Array）
// 思路：利用值域 1..n，原地把每个值 x 交换到下标 x-1 的位置；再扫一遍，位置上不是 i+1 的值就是重复出现的那个。
// 复杂度：时间复杂度 O(n)，每个元素最多被交换常数次；空间复杂度 O(1)，除返回值外只用原数组。
class Solution {  // 题解类：找出数组中所有出现两次的元素
public:  // 公开部分
    vector<int> findDuplicates(vector<int>& nums) {  // nums 中每个元素出现一次或两次，返回所有出现两次的元素
        int n = nums.size();  // 缓存数组长度，避免循环里反复调用 size()
        for (int i = 0; i < n; ++i) {  // 逐个位置处理，把下标 i 上的值送到它应该在的位置
            while (nums[i] != nums[nums[i] - 1]) {  // 值 x 应该在位置 x-1；只要还没归位就继续交换
                swap(nums[i], nums[nums[i] - 1]);  // 原地交换：一次 swap 把 nums[i] 送到它的目标位置
            }  // 该位置的值已经正确，内层循环结束
        }  // 归位阶段结束
        vector<int> ans;  // 用来收集答案
        for (int i = 0; i < n; ++i) {  // 再扫一遍，看看哪些位置没有被正确的值占住
            if (nums[i] != i + 1) {  // 位置 i 上不是 i+1，说明这个值出现了两次，占掉了别人的位置
                ans.push_back(nums[i]);  // 记录这个重复出现的值
            }  // 闭合 if
        }  // 扫描结束
        return ans;  // 返回所有重复元素
    }  // findDuplicates 方法结束
};  // Solution 类定义结束