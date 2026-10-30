// 题目：2766. 重新放置石块（Relocate Marbles）
// 思路：用哈希集合记录所有石块当前所在的位置；每次移动先从集合删掉源位置、再加入目标位置，最后把集合排成升序返回。
// 时间复杂度：O(n + k + p log p)，p 为最终不同位置数；空间复杂度：O(p)，集合与结果数组都只存这些位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {  // nums：初始位置；moveFrom/moveTo：逐次移动的源位置与目标位置
        unordered_set<int> pos(nums.begin(), nums.end());  // 哈希集合去重地记录所有石块当前所在的位置（同一位置上可能有多块石头）
        for (int i = 0; i < moveFrom.size(); ++i) {  // 按顺序处理每一次移动
            pos.erase(moveFrom[i]);  // 石块离开源位置；该位置上没有其他石块时，这个位置就从集合中消失
            pos.insert(moveTo[i]);  // 石块到达目标位置，集合自动去重
        }  // 一次移动处理结束
        vector<int> ans(pos.begin(), pos.end());  // 把集合中的位置拷贝到数组，便于排序
        sort(ans.begin(), ans.end());  // 题目要求按升序返回
        return ans;  // 返回排序后的所有石块位置
    }  // 方法结束
};  // 类定义结束