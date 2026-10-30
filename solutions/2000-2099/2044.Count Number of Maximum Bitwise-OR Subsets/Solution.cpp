// 题目：2044. 统计按位或能得到最大值的子集数目（Count Number of Maximum Bitwise-OR Subsets）
// 思路：任意子集的按位或都不会超过整个数组的按位或 mx，所以先求出 mx，再用「选/不选」的 DFS 枚举全部子集，统计或值恰为 mx 的个数。
// 时间复杂度：O(2^n)，每个元素只有选与不选两条分支；空间复杂度：O(n)，递归栈最深为元素个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countMaxOrSubsets(vector<int>& nums) {  // nums：输入数组；返回按位或等于最大值的非空子集个数
        int ans = 0;  // ans：计数器，记录或值恰好等于 mx 的子集数量
        int mx = accumulate(nums.begin(), nums.end(), 0, bit_or<int>());  // mx：整个数组的按位或；或运算只会让 1 变多，所以任意子集的或值都不可能超过它
        auto dfs = [&](this auto&& dfs, int i, int t) {  // 利用 C++23 显式对象参数 this auto&& dfs，让 lambda 能递归调用自己；i 是当前元素下标，t 是已选元素的按位或
            if (i == nums.size()) {  // 所有元素都已决定完，到达搜索树叶子，开始判断当前子集
                if (t == mx) {  // 当前子集的按位或恰好等于最大值
                    ans++;  // 这个子集计入答案
                }  // 结束内层 if
                return;  // 叶子处理完就回溯，不再继续递归
            }  // 结束叶子判断
            dfs(i + 1, t);  // 分支一：不选 nums[i]，或值保持 t 不变
            dfs(i + 1, t | nums[i]);  // 分支二：选 nums[i]，把它的二进制位并入或值
        };  // lambda 表达式定义结束
        dfs(0, 0);  // 从下标 0、或值 0 开始枚举所有子集
        return ans;  // 返回统计到的子集数目
    }  // 方法结束
};  // 题解类结束
