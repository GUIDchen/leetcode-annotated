// 题目：1282. 用户分组（Group the People Given the Group Size They Belong To）
// 思路：按「组大小」把下标分桶，再依次从每个桶里按桶大小切出若干组，正好满足每组人数等于组大小。
// 时间复杂度：O(n)，每个下标只入桶、出桶各一次；空间复杂度：O(n)，桶与答案合计保存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {  // groupSizes[i] 是第 i 个人希望所在组的人数
        int n = groupSizes.size();  // 人数
        vector<vector<int>> g(n + 1);  // g[s] 收集所有希望组大小为 s 的人的下标，下标最大为 n
        for (int i = 0; i < n; ++i) {  // 遍历每个人
            g[groupSizes[i]].push_back(i);  // 按下标 i 的期望组大小投进对应桶
        }
        vector<vector<int>> ans;  // 存放最终分好的所有组
        for (int i = 0; i < g.size(); ++i) {  // 遍历每种可能出现的组大小 i
            for (int j = 0; j < g[i].size(); j += i) {  // 每 i 个人切一组；i 为 0 时桶为空，循环不会执行
                vector<int> t(g[i].begin() + j, g[i].begin() + j + i);  // 取桶中连续 i 个下标组成一组
                ans.push_back(t);  // 把这一组加入答案
            }
        }
        return ans;  // 返回所有分组结果
    }
};  // 题解类定义结束（本文件末尾无换行，已保留）