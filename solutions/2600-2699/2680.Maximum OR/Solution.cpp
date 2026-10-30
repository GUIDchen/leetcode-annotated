// 题目：2680. 最大或值（Maximum OR）
// 思路：预处理后缀或，再从左到右滚动维护前缀或；枚举把 k 次左移全部用在同一元素上，用「前缀或 | 左移后的值 | 后缀或」更新答案。
// 时间复杂度：O(n)，前后各扫一遍；空间复杂度：O(n)，suf 数组保存后缀或。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumOr(vector<int>& nums, int k) {  // nums：整数数组；k：可以全部作用在同一个数上的左移次数
        int n = nums.size();  // 记下数组长度，建表与遍历都要用到
        long long suf[n + 1];  // suf[i] 表示 nums[i..n-1] 的按位或（后缀或）
        memset(suf, 0, sizeof(suf));  // 全部清零，保证空后缀 suf[n] = 0 的边界成立
        for (int i = n - 1; i >= 0; --i) {  // 从后往前递推，先算出所有后缀或
            suf[i] = suf[i + 1] | nums[i];  // 当前后缀或 = 后一个后缀或 再或上 nums[i]
        }  // 后缀或数组填充完毕
        long long ans = 0, pre = 0;  // ans：最优答案；pre：nums[0..i-1] 的前缀或
        for (int i = 0; i < n; ++i) {  // 枚举把 k 次左移全用第 i 个元素上
            ans = max(ans, pre | (1LL * nums[i] << k) | suf[i + 1]);  // 左移只会让位更高，把它与前后缀的或合并后取最大
            pre |= nums[i];  // 把当前元素并入前缀或，供下一个元素使用
        }  // 枚举结束
        return ans;  // 返回能得到的最大按位或值
    }  // 方法结束
};  // 类定义结束