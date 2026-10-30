// 题目：1953. 你可以工作的最大周数（Maximum Number of Weeks for Which You Can Work）
// 思路：设最大里程碑为 mx、其余之和为 rest；若 mx > rest + 1 则最多做 2·rest+1 周，否则所有里程碑都能做完。
// 时间复杂度：O(n)，求最大值与求和各一遍；空间复杂度：O(1)，只用了几个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfWeeks(vector<int>& milestones) {  // milestones：每项工作剩余的里程碑数
        int mx = *max_element(milestones.begin(), milestones.end());  // 最大的那一项里程碑数
        long long s = accumulate(milestones.begin(), milestones.end(), 0LL);  // 所有里程碑之和，用 0LL 防止溢出
        long long rest = s - mx;  // 除最大项之外其余里程碑之和
        return mx > rest + 1 ? rest * 2 + 1 : s;  // 最大项过多只能交替做，否则可以全部做完
    }
};  // LeetCode 题解类结束