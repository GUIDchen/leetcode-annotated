// 题目：986. 区间列表的交集（Interval List Intersections）
// 思路：双指针扫描两个有序区间列表，每次求交集 [max(左端), min(右端)]，谁的右端更小就推进谁的指针。
// 时间复杂度：O(m+n)，每个区间最多被访问一次；空间复杂度：O(1)，不计答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {  // firstList、secondList 都是按左端点升序且内部互不相交的区间列表
        vector<vector<int>> ans;  // ans 保存所有交集区间
        int m = firstList.size(), n = secondList.size();  // m、n 分别是两个列表的区间个数
        for (int i = 0, j = 0; i < m && j < n;) {  // 双指针同时扫描，任一列表走完即结束
            int l = max(firstList[i][0], secondList[j][0]);  // 交集左端取两个区间左端的较大者
            int r = min(firstList[i][1], secondList[j][1]);  // 交集右端取两个区间右端的较小者
            if (l <= r) ans.push_back({l, r});  // 左端不大于右端说明确实有交集，加入答案
            if (firstList[i][1] < secondList[j][1])  // 第一个区间右端更小，它会先结束
                ++i;  // 推进第一个列表的指针
            else  // 否则
                ++j;  // 推进第二个列表的指针
        }  // 循环结束
        return ans;  // 返回所有交集
    }  // 方法结束
};  // 类定义结束