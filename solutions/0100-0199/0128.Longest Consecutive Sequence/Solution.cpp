// 题目：128. 最长连续序列（Longest Consecutive Sequence）
// 思路：把数组放进哈希集合，对每个 x 顺着 x+1、x+2… 一路删除到断点 y，再用哈希表 d 记下「从 x 起的连续长度 = 断点后已知长度 + y - x」，每个数字只会被删除一次。
// 时间复杂度：O(n)，每个数字至多被 erase 一次；空间复杂度：O(n)，集合与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestConsecutive(vector<int>& nums) {  // nums：无序整数数组，返回最长连续序列的长度
        unordered_set<int> s(nums.begin(), nums.end());  // 全部数字放进哈希集合，支持 O(1) 的存在性判断与删除
        int ans = 0;  // 当前找到的最长连续序列长度
        unordered_map<int, int> d;  // 记录以某个数为起点时向后能延伸多长
        for (int x : nums) {  // 依次以每个数作为候选起点
            int y = x;  // y 用来沿 x+1、x+2… 一直向后探查
            while (s.contains(y)) {  // y 还在集合里，说明 x 到 y 这一段是连续的
                s.erase(y++);  // 删除 y 并让 y 后移一位，保证每个数字只被遍历一次
            }  // while 结束，此时 y 是第一个不在集合中的断点
            d[x] = (d.contains(y) ? d[y] : 0) + y - x;  // 断点 y 若已属于更长的序列，就直接接上它记录的长度
            ans = max(ans, d[x]);  // 更新全局最长长度
        }  // for 结束
        return ans;  // 返回最长连续序列长度
    }  // longestConsecutive 结束
};
