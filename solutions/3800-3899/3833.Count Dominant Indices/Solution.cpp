// 3833. 统计主导元素下标数 / Count Dominant Indices（简单）
// 核心思路：从右往左维护后缀和 suf，对每个位置 i 判断 nums[i] 是否严格大于其右侧元素的平均值（用乘法代替除法避免浮点误差），满足则计数加一。
// 复杂度：一次线性扫描，时间 O(n)，空间 O(1)。
class Solution {  // 统计满足“严格大于右侧所有元素平均值”的下标个数
public:  // 对外接口区
    int dominantIndices(vector<int>& nums) {  // 返回主导下标数量
        int n = nums.size();  // 数组长度
        int ans = 0;  // 答案计数
        int suf = nums[n - 1];  // 后缀和：先包含最右侧元素（其右侧为空，不会被统计）
        for (int i = n - 2; i >= 0; --i) {  // 从倒数第二个位置向前枚举
            if (nums[i] * (n - i - 1) > suf) {  // nums[i] 乘以右侧元素个数与后缀和比较，等价于大于右侧平均值
                ans++;  // 满足主导条件，答案加一
            }
            suf += nums[i];  // 把当前元素并入后缀和，供更左侧的位置使用
        }
        return ans;  // 返回主导下标总数
    }
};
