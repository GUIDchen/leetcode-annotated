// 题目：2610. 转换二维数组（Convert an Array Into a 2D Array With Conditions）
// 思路：统计每个值的出现次数 v，让它的第 j 次出现落在第 j 行，即可保证每行元素互不相同且总行数最少。
// 时间复杂度：O(n)，只遍历数组与值域各一次；空间复杂度：O(n)，计数数组与结果数组的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findMatrix(vector<int>& nums) {  // nums：输入数组；返回行内元素互不相同、行数最少的二维数组
        vector<vector<int>> ans;  // ans：结果二维数组，每一行内的元素互不相同
        int n = nums.size();  // n：数组长度，同时也是元素值的上界
        vector<int> cnt(n + 1);  // cnt[x]：数字 x 在数组中出现的次数
        for (int& x : nums) {  // 遍历每个元素
            ++cnt[x];  // 统计出现次数
        }  // 计数结束
        for (int x = 1; x <= n; ++x) {  // 按元素值从小到大处理，保证输出顺序稳定
            int v = cnt[x];  // v：数字 x 一共要放 v 次
            for (int j = 0; j < v; ++j) {  // 第 j 次出现就放进第 j 行
                if (ans.size() <= j) {  // 第 j 行还不存在
                    ans.push_back({});  // 先补一个空行
                }  // 分支结束
                ans[j].push_back(x);  // 把 x 追加到第 j 行，同一行不会重复
            }  // x 放置完毕
        }  // 所有元素处理完毕
        return ans;  // 返回构造好的二维数组
    }  // 方法结束
};  // 类定义结束