// 题目：2418. 按身高排序（Sort the People）
// 思路：不直接改原数组，而是对下标数组按身高从大到小排序，再按排好的下标顺序取出姓名，就得到按身高降序的名单。
// 时间复杂度：O(n log n)，瓶颈是下标排序；空间复杂度：O(n)，下标数组与答案数组各占 n 个位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {  // names 与 heights 按下标一一对应
        int n = names.size();  // 人数，两个数组长度相同
        vector<int> idx(n);  // idx 存 0..n-1 的下标，排序下标就能保留「姓名—身高」的对应关系
        iota(idx.begin(), idx.end(), 0);  // 用 iota 把 idx 填成 0, 1, 2, ..., n-1 递增序列
        sort(idx.begin(), idx.end(), [&](int i, int j) { return heights[j] < heights[i]; });  // 按身高降序比较下标：身高大的排前面
        vector<string> ans;  // 按身高降序排列的姓名结果
        for (int i : idx) {  // 依次取出排好序的下标
            ans.push_back(names[i]);  // 用下标找回对应姓名并追加
        }
        return ans;  // 返回排序后的姓名列表
    }
};