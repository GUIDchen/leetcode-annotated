// 题目：2537. 统计好子数组的数目（Count the Number of Good Subarrays）
// 思路：滑动窗口 + 计数。维护窗口内「至少存在一对相同元素」的配对数 cur，窗口右端每扩一步，
// 就把左端尽量右移；时间 O(n)，空间 O(n)（哈希表最多存不同元素个数）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countGood(vector<int>& nums, int k) {  // nums 为数组，k 为好子数组所需的配对数，返回好子数组个数
        unordered_map<int, int> cnt;  // 哈希表记录窗口内每个值出现的次数
        long long ans = 0;  // 答案最大可达 O(n^2)，必须用 long long
        long long cur = 0;  // cur 是当前窗口内的配对对数，即同值元素两两配成的对数
        int i = 0;  // i 是窗口左端点
        for (int& x : nums) {  // 右端点持续右移，逐个把元素纳入窗口
            cur += cnt[x]++;  // x 与窗口内原有的 cnt[x] 个相同元素各配成一对，再把计数加一
            while (cur - cnt[nums[i]] + 1 >= k) {  // 若把最左元素移出后配对数仍不少于 k（移除会使 cur 减少 cnt[nums[i]]-1 对），窗口还能缩
                cur -= --cnt[nums[i++]];  // 先把 cnt[nums[i]] 减一，再从 cur 中减去该值剩余个数（即因移除它而消失的配对），最后 i 右移
            }  // while 结束，此时 [i, 右端点] 是满足条件的最短窗口
            if (cur >= k) {  // 窗口内配对数已达 k，说明该窗口合法
                ans += i + 1;  // 起点可以是 0..i 中任意位置，终点固定为右端点，共 i+1 个好子数组
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回好子数组总数
    }  // 方法结束
};  // 类定义结束