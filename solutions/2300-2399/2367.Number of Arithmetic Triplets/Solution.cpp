// 题目：2367. 等差三元组的数目（Number of Arithmetic Triplets）
// 核心思路：因为数组严格递增，直接三重循环枚举下标 i<j<k，检查相邻两段差是否都等于 diff，计数即可。
// 时间复杂度：O(n^3)，三重循环枚举全部三元组；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int arithmeticTriplets(vector<int>& nums, int diff) {  // nums：严格递增的数组；diff：要求的公差
        int ans = 0;  // 答案计数器：满足条件的三元组个数
        int n = nums.size();  // 数组长度，供下面三层循环共同使用
        for (int i = 0; i < n; ++i) {  // 枚举三元组的第一个下标 i
            for (int j = i + 1; j < n; ++j) {  // 枚举第二个下标 j，从 i+1 开始保证 i < j
                for (int k = j + 1; k < n; ++k) {  // 枚举第三个下标 k，从 j+1 开始保证 j < k
                    if (nums[j] - nums[i] == diff && nums[k] - nums[j] == diff) {  // 检查两段相邻差是否都等于 diff，都满足才是等差三元组
                        ++ans;  // 三元组 (i, j, k) 合法，计数加一
                    }  // if 分支结束
                }  // k 循环结束
            }  // j 循环结束
        }  // i 循环结束
        return ans;  // 返回合法的等差三元组总数
    }  // 方法结束
};  // 类定义结束（别忘了分号）