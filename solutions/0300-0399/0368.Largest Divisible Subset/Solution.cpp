// 题目：368. 最大整除子集（Largest Divisible Subset）
// 思路：先排序，令 f[i] 表示以 nums[i] 结尾的最大整除子集长度，枚举 j < i 且 nums[i] % nums[j] == 0 转移；再按长度从 k 倒序回溯还原具体元素。
// 时间复杂度：O(n^2)，双重枚举 + O(n) 回溯；空间复杂度：O(n)，f 数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> largestDivisibleSubset(vector<int>& nums) {  // nums：输入集合（可含重复度无关，排序后判断整除更方便）
        ranges::sort(nums);  // 升序排序：整除关系对有序对才方便自小向大递推
        int n = nums.size();  // 元素个数
        int f[n];  // f[i]：以 nums[i] 结尾的最大整除子集长度（C 风格变长数组）
        int k = 0;  // k：目前 f 值最大的下标，最终答案位于 k
        for (int i = 0; i < n; ++i) {  // 按升序逐个作为「子集最后一个元素」处理
            f[i] = 1;  // 单独成集至少长度为 1
            for (int j = 0; j < i; ++j) {  // 枚举所有更小的前驱 nums[j]
                if (nums[i] % nums[j] == 0) {  // 整除关系：nums[i] 能被 nums[j] 整除即满足子集约束
                    f[i] = max(f[i], f[j] + 1);  // 尝试把 nums[i] 接到以 j 结尾的最优子集后面
                }  // 内层条件闭合
            }  // 前驱枚举结束
            if (f[k] < f[i]) {  // 记录当前最长的子集末尾下标
                k = i;  // 更新最大值位置 k
            }  // 判断闭合
        }  // 外层枚举结束
        int m = f[k];  // 目标答案的长度
        vector<int> ans;  // 存放还原出的子集（倒序插入）
        for (int i = k; m > 0; --i) {  // 从最长末尾 k 出发向前回溯，每找到一个元素 m 减一
            if (nums[k] % nums[i] == 0 && f[i] == m) {  // 只选能整除 nums[k] 且长度正好等于当前 m 的前驱
                ans.push_back(nums[i]);  // 加入该元素
                k = i;  // 以 i 作为下一轮回溯的基准
                --m;  // 剩余待补长度减一
            }  // 条件闭合
        }  // 回溯循环结束
        return ans;  // 返回最大整除子集
    }  // 方法结束
};  // 类定义结束