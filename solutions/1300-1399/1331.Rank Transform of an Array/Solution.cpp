// 题目：1331. 数组序号转换（Rank Transform of an Array）
// 思路：把数组排序去重得到「名次表」，每个元素的名次就是它在名次表中的位置（1 起）；用 upper_bound 的下标直接得到名次。
// 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，名次表与答案数组。
class Solution {  // 题解类
public:  // 对外暴露题解接口
    vector<int> arrayRankTransform(vector<int>& arr) {  // arr：输入数组，返回每个元素对应的序号（从 1 开始，重复元素序号相同）
        vector<int> t = arr;  // 拷贝一份，排序时不影响原数组顺序
        sort(t.begin(), t.end());  // 升序排序，得到候选名次表
        t.erase(unique(t.begin(), t.end()), t.end());  // unique 把重复元素挤到末尾，erase 真正删掉，得到有序去重数组
        vector<int> ans;  // 按原数组顺序保存每个元素的序号
        for (int x : arr) {  // 逐个元素计算序号
            ans.push_back(upper_bound(t.begin(), t.end(), x) - t.begin());  // upper_bound 返回第一个大于 x 的位置，其下标正好等于 x 的序号（1 起计）
        }  // 元素遍历结束
        return ans;  // 返回序号数组
    }  // 方法结束
};  // 类定义结束