// 题目：506. 相对名次（Relative Ranks）
// 思路：对下标按得分降序排序，名次 i 对应的运动员下标是 idx[i]；前三名填奖牌名，其余填 i+1。
// 时间复杂度：O(n log n)，排序开销；空间复杂度：O(n)，下标数组、答案数组与奖牌名数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findRelativeRanks(vector<int>& score) {  // score：各运动员得分；返回与输入同序的名次字符串数组
        int n = score.size();  // 运动员人数（即下标个数）
        vector<int> idx(n);  // idx 存放下标 0..n-1，稍后按得分从高到低排序
        iota(idx.begin(), idx.end(), 0);  // iota 把 0,1,2,... 依次填入 idx
        sort(idx.begin(), idx.end(), [&score](int a, int b) {  // 按得分降序排列下标，得分高的排在前面
            return score[a] > score[b];  // 比较器：a 的得分高于 b 时，a 应排在 b 前面
        });  // 排序结束，idx[0] 就是第一名的原始下标
        vector<string> ans(n);  // 结果数组，下标与输入一一对应
        vector<string> top3 = {"Gold Medal", "Silver Medal", "Bronze Medal"};  // 前三名的固定奖牌名
        for (int i = 0; i < n; ++i) {  // i 是名次下标（0 表示第一名）
            ans[idx[i]] = i < 3 ? top3[i] : to_string(i + 1);  // 前三名填奖牌名，其余填从 1 开始的名次数字
        }  // 所有运动员的名次都填完了
        return ans;  // 返回结果数组
    }  // 方法结束
};  // 类定义结束
