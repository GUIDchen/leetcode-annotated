// 题目：2446. 判断两个事件是否存在冲突（Determine if Two Events Have Conflict）
// 思路：每个事件是 [开始, 结束] 两个 "HH:MM" 字符串，时间格式定长同构，可直接按字典序比较；两段闭区间相交等价于「不满足 event1 整体在 event2 之后，也不满足 event1 整体在 event2 之前」。
// 时间复杂度：O(1)，只做常数次字符串比较；空间复杂度：O(1)，只用若干临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool haveConflict(vector<string>& event1, vector<string>& event2) {  // event1、event2 分别是两个事件的 [开始时间, 结束时间]
        return !(event1[0] > event2[1] || event1[1] < event2[0]);  // 前者表示 event1 开始晚于 event2 结束（event1 在后），后者表示 event1 结束早于 event2 开始（event1 在前）；两者都不成立说明区间有交集，取反即为冲突
    }
};
