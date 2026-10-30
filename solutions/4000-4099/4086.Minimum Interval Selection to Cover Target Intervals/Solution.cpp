// 题目：4086. 覆盖目标区间的最少区间（Minimum Interval Selection to Cover Target Intervals）
// 核心思路：把可用区间与目标区间都按左端点升序排序，然后做「跳跃式覆盖」贪心：对每个目标区间，从当前覆盖位置 cur 与目标左端点 l 的较大值开始，在所有左端点能接上缺口的可用区间里取右端点最远的一个，使覆盖尽量右伸；若接不上就说明出现断层，返回 -1。
// 复杂度：时间 O((n+m) log(n+m))，主要是两次排序，指针 i 单调前进故内层扫描总计线性；空间 O(1) 额外空间（不计排序开销）。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {  // 返回覆盖全部目标区间所需的最少可用区间数，无法覆盖则返回 -1
        sort(availableIntervals.begin(), availableIntervals.end(), [](auto& a, auto& b) { return a[0] < b[0]; });  // 可用区间按左端点升序排序
        sort(targetIntervals.begin(), targetIntervals.end(), [](auto& a, auto& b) { return a[0] < b[0]; });  // 目标区间也按左端点升序排序，保证从左到右依次覆盖
        int ans = 0, cur = 0, i = 0;  // ans 为已选区间数，cur 为当前已覆盖到的位置，i 为可用区间指针（只前进不回退）
        for (auto& t : targetIntervals) {  // 依次处理每个目标区间 [l, r]
            int l = t[0], r = t[1];  // 取出目标区间的左右端点
            while (cur < r) {  // 还没覆盖到目标右端点时，继续补充区间
                int uncover = max(l, cur);  // 当前真正需要被覆盖的起点：目标左端点与已覆盖位置的较大值
                int nxt = cur;  // nxt 记录这一轮能延伸到的最远位置
                while (i < (int) availableIntervals.size() && availableIntervals[i][0] <= uncover) {  // 扫描所有左端点不超过缺口起点的可用区间
                    nxt = max(nxt, availableIntervals[i][1]);  // 在其中取右端点最远的那个，延伸得最多
                    i++;  // 指针后移；这些区间之后也不会更优，可以永久跳过
                }  // 候选区间扫描结束
                if (nxt < uncover || nxt == cur) {  // 没有任何区间能覆盖缺口起点，或者无法再向右推进
                    return -1;  // 出现断层，不可能覆盖全部目标区间
                }  // 断层判断结束
                cur = nxt;  // 已覆盖位置推进到最远处
                ans++;  // 又使用了一个可用区间
            }  // 当前目标区间覆盖完成
        }  // 全部目标区间处理完毕
        return ans;  // 返回最少的区间选择数量
    }  // minSelection 结束
};  // Solution 类结束