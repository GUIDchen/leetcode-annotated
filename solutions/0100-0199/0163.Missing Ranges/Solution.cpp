// 题目：163. 缺失的区间（Missing Ranges）
// 核心思路：先处理首元素之前的空档，再扫描相邻元素之间差大于 1 的空档，最后处理末元素之后到 upper 的空档。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，除输出数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {  // nums：严格递增数组，所有取值都落在闭区间 [lower, upper] 内
        int n = nums.size();  // 缓存长度，后面判断首尾时都要用到
        if (n == 0) {  // 数组为空：整个 [lower, upper] 都缺失
            return {{lower, upper}};  // 直接返回这唯一一段缺失区间
        }
        vector<vector<int>> ans;  // 用二维数组收集所有缺失的闭区间 [l, r]
        if (nums[0] > lower) {  // 首元素大于下界，说明 lower 到 nums[0]-1 这一截缺失
            ans.push_back({lower, nums[0] - 1});  // 记录下界到首元素前一个数的区间
        }
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，检查每一对相邻元素之间是否有空档
            if (nums[i] - nums[i - 1] > 1) {  // 相邻差大于 1，说明中间存在缺失的整数
                ans.push_back({nums[i - 1] + 1, nums[i] - 1});  // 缺失区间两端分别是前一个数加一、后一个数减一
            }
        }
        if (nums[n - 1] < upper) {  // 末元素小于上界，说明 nums[n-1]+1 到 upper 这一截缺失
            ans.push_back({nums[n - 1] + 1, upper});  // 记录末元素后一个数到右边界
        }
        return ans;  // 按从左到右的顺序返回全部缺失区间
    }
};