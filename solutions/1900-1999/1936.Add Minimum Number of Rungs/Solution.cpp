// 题目：1936. 新增的最少台阶数（Add Minimum Number of Rungs）
// 思路：相邻高度差 gap 超过 dist 时，需要插入 (gap-1)/dist 级新台阶，逐段累加即可。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int addRungs(vector<int>& rungs, int dist) {  // 返回到达顶端所需新增的最少台阶数
        int ans = 0, prev = 0;  // ans 计数，prev 表示当前所在高度，地面记为 0
        for (int& x : rungs) {  // 依次跨越已有的每级台阶
            ans += (x - prev - 1) / dist;  // 高度差每超过 dist 一次就要多插一级台阶，整除正好把「最后一步不算」的边界处理掉
            prev = x;  // 更新当前高度，作为下一段的起点
        }  // for 结束
        return ans;  // 返回总共新增的台阶数
    }  // 方法结束
};  // 类结束