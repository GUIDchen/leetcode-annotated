// 题目：2670. 找出不同元素数目差数组（Find the Distinct Difference Array）
// 核心思路：先从右往左预处理后缀不同元素个数 suf[i]，再从左往右用哈希集合维护前缀不同元素个数，两者相减即为答案。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，后缀数组与哈希集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> distinctDifferenceArray(vector<int>& nums) {  // nums：输入数组，返回每个下标对应的「前缀不同数 - 后缀不同数」
        int n = nums.size();  // 数组长度
        vector<int> suf(n + 1);  // suf[i]：nums[i..n-1] 这个后缀里不同元素的个数，多开一位便于取空后缀 0
        unordered_set<int> s;  // 哈希集合：统计当前后缀中出现过的不同元素
        for (int i = n - 1; i >= 0; --i) {  // 从右往左扫描，逐步构造后缀
            s.insert(nums[i]);  // 把当前元素加入集合（重复元素不会增加集合大小）
            suf[i] = s.size();  // 记录从 i 开始的后缀的不同元素个数
        }  // 后缀预处理完成
        s.clear();  // 清空集合，复用为前缀统计
        vector<int> ans(n);  // 答案数组，长度与原数组相同
        for (int i = 0; i < n; ++i) {  // 从左往右扫描，逐步构造前缀
            s.insert(nums[i]);  // 把当前元素加入前缀集合
            ans[i] = s.size() - suf[i + 1];  // 前缀不同数（集合大小）减去后缀 nums[i+1..] 的不同数
        }  // 前缀扫描结束
        return ans;  // 返回每个位置算好的差值
    }  // 方法结束
};  // 类定义结束（文件末尾无换行，按原样保留）