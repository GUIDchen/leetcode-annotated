// 题目：3073. 最大递增三元组（Maximum Increasing Triplet Value）🔒
// 思路：先用后缀最大值数组 right 预处理右侧最大元素，再用有序集合维护左侧前缀，枚举中间下标 j 取最优。
// 时间复杂度：O(n log n)，每个位置各做一次 set 的查找与插入；空间复杂度：O(n)，后缀最大值数组与有序集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumTripletValue(vector<int>& nums) {  // nums：输入数组；返回最大的 nums[i] - nums[j] + nums[k]（要求 i<j<k 且 nums[i]<nums[j]<nums[k]）
        int n = nums.size();  // 数组长度，后面会反复用到
        vector<int> right(n, nums.back());  // right[i] 表示从 i 到末尾的最大值，先统一初始化为末尾元素
        for (int i = n - 2; ~i; --i) {  // 从倒数第二个位置向前扫描；~i 为真等价于 i >= 0
            right[i] = max(nums[i], right[i + 1]);  // 后缀最大值递推：取自身与右侧最大值中的较大者
        }
        set<int> ts;  // 有序集合：保存已经扫描过的前缀元素，方便找「小于 nums[j] 的最大值」
        ts.insert(nums[0]);  // 先把第一个元素放进前缀集合
        int ans = 0;  // 记录最大三元组值，初始为 0
        for (int j = 1; j < n - 1; ++j) {  // 枚举中间下标 j；左右两侧都要有元素，所以范围是 [1, n-2]
            if (right[j + 1] > nums[j]) {  // 右侧必须存在严格大于 nums[j] 的元素，才可能构成递增三元组
                auto it = ts.lower_bound(nums[j]);  // 二分找第一个大于等于 nums[j] 的前缀位置
                if (it != ts.begin()) {  // 不是 begin 说明左边存在严格小于 nums[j] 的元素
                    --it;  // 左移一位，得到严格小于 nums[j] 的最大前缀值，即最优的 nums[i]
                    ans = max(ans, *it - nums[j] + right[j + 1]);  // 用当前的 i、j、k 更新答案
                }
            }
            ts.insert(nums[j]);  // 把当前元素并入前缀集合，供后面的中间下标使用
        }
        return ans;  // 返回最大三元组值
    }
};